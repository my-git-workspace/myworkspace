#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <blkid/blkid.h>
#include <dirent.h>
#include <sys/stat.h>
#include <assert.h>
#include "sysfs.c"

struct lsblk {
	struct libscols_table *table;	/* output table */
	struct libscols_column *sort_col;/* sort output by this column */
	int sort_id;

	int flags;			/* LSBLK_* */

	unsigned int all_devices:1;	/* print all devices, including empty */
	unsigned int bytes:1;		/* print SIZE in bytes */
	unsigned int inverse:1;		/* print inverse dependencies */
	unsigned int nodeps:1;		/* don't print slaves/holders */
	unsigned int scsi:1;		/* print only device with HCTL (SCSI) */
	unsigned int paths:1;		/* print devnames with "/dev" prefix */
	unsigned int sort_hidden:1;	/* sort column not between output columns */
	unsigned int force_tree_order:1;/* sort lines by parent->tree relation */
};

struct blkdev_cxt {
	struct blkdev_cxt *parent;

	struct libscols_line *scols_line;
	struct stat	st;

	char *name;		/* kernel name in /sys/block */
	char *dm_name;		/* DM name (dm/block) */

	char *filename;		/* path to device node */

	struct sysfs_cxt  sysfs;

	int partition;		/* is partition? TRUE/FALSE */

	int probed;		/* already probed */
	char *fstype;		/* detected fs, NULL or "?" if cannot detect */
	char *uuid;		/* filesystem UUID (or stack uuid) */
	char *label;		/* filesystem label */
	char *parttype;		/* partition type UUID */
	char *partuuid;		/* partition UUID */
	char *partlabel;	/* partition label */
	char *partflags;	/* partition flags */
	char *wwn;		/* storage WWN */
	char *serial;		/* disk serial number */

	int npartitions;	/* # of partitions this device has */
	int nholders;		/* # of devices mapped directly to this device
				 * /sys/block/.../holders */
	int nslaves;		/* # of devices this device maps to */
	int maj, min;		/* devno */
	int discard;		/* supports discard */

	uint64_t size;		/* device size */
};

static struct lsblk *lsblk;	/* global handler */

#ifndef XALLOC_EXIT_CODE
# define XALLOC_EXIT_CODE EXIT_FAILURE
#endif

/* columns[] array specifies all currently wanted output column. The columns
 * are defined by infos[] array and you can specify (on command line) each
 * column twice. That's enough, dynamically allocated array of the columns is
 * unnecessary overkill and over-engineering in this case */
static int columns[ARRAY_SIZE(infos) * 2];
static size_t ncolumns;

static int is_dm(const char *name)
{
        return strncmp(name, "dm-", 3) ? 0 : 1;
}

char *canonicalize_dm_name(const char *ptname)
{
        FILE    *f;
        size_t  sz;
        char    path[256], name[256], *res = NULL;

        if (!ptname || !*ptname)
                return NULL;

        snprintf(path, sizeof(path), "/sys/block/%s/dm/name", ptname);
        if (!(f = fopen(path, "r" UL_CLOEXECSTR)))
                return NULL;

        /* read "<name>\n" from sysfs */ 
        if (fgets(name, sizeof(name), f) && (sz = strlen(name)) > 1) {
                name[sz - 1] = '\0';
                snprintf(path, sizeof(path), "/dev/mapper/%s", name);

                if (access(path, F_OK) == 0)
                        res = strdup(path);
        }
        fclose(f);
        return res;
}
static void fill_table_line(struct blkdev_cxt *cxt, struct libscols_line *scols_parent)
{
        size_t i;

        cxt->scols_line = scols_table_new_line(lsblk->table, scols_parent);
        if (!cxt->scols_line)
                err(EXIT_FAILURE, _("failed to allocate output line"));

        for (i = 0; i < ncolumns; i++) 
                set_scols_data(cxt, i, get_column_id(i), cxt->scols_line);
}

static inline char __attribute__((warn_unused_result)) *xstrdup(const char *str)
{
        char *ret;
        
        if (!str)
                return NULL;

        ret = strdup(str);

        if (!ret)
                err(XALLOC_EXIT_CODE, "cannot duplicate string");
        return ret;
}

static char *get_device_path(struct blkdev_cxt *cxt)
{
        char path[PATH_MAX];

        assert(cxt);
        assert(cxt->name);

        if (is_dm(cxt->name))
                return canonicalize_dm_name(cxt->name);

        snprintf(path, sizeof(path), "/dev/%s", cxt->name);
        sysfs_devname_sys_to_dev(path);
        return xstrdup(path);
}

static int set_cxt(struct blkdev_cxt *cxt,
		    struct blkdev_cxt *parent,
		    struct blkdev_cxt *wholedisk,
		    const char *name)
{
	dev_t devno;

	DBG(CXT, ul_debugobj(cxt, "setting context for %s [parent=%p, wholedisk=%p]",
				name, parent, wholedisk));

	cxt->parent = parent;
	cxt->name = xstrdup(name);
	cxt->partition = wholedisk != NULL;

	cxt->filename = get_device_path(cxt);
	if (!cxt->filename) {
		DBG(CXT, ul_debugobj(cxt, "%s: failed to get device path", cxt->name));
		return -1;
	}
	DBG(CXT, ul_debugobj(cxt, "%s: filename=%s", cxt->name, cxt->filename));

	devno = sysfs_devname_to_devno(cxt->name, wholedisk ? wholedisk->name : NULL);

	if (!devno) {
		DBG(CXT, ul_debugobj(cxt, "%s: unknown device name", cxt->name));
		return -1;
	}

	if (lsblk->inverse) {
		if (sysfs_init(&cxt->sysfs, devno, wholedisk ? &wholedisk->sysfs : NULL)) {
			DBG(CXT, ul_debugobj(cxt, "%s: failed to initialize sysfs handler", cxt->name));
			return -1;
		}
		if (parent)
			parent->sysfs.parent = &cxt->sysfs;
	} else {
		if (sysfs_init(&cxt->sysfs, devno, parent ? &parent->sysfs : NULL)) {
			DBG(CXT, ul_debugobj(cxt, "%s: failed to initialize sysfs handler", cxt->name));
			return -1;
		}
	}

	cxt->maj = major(devno);
	cxt->min = minor(devno);
	cxt->size = 0;

	if (sysfs_read_u64(&cxt->sysfs, "size", &cxt->size) == 0)	/* in sectors */
		cxt->size <<= 9;					/* in bytes */

	if (sysfs_read_int(&cxt->sysfs,
			   "queue/discard_granularity", &cxt->discard) != 0)
		cxt->discard = 0;

	/* Ignore devices of zero size */
	if (!lsblk->all_devices && cxt->size == 0) {
		DBG(CXT, ul_debugobj(cxt, "zero size device -- ignore"));
		return -1;
	}
	if (is_dm(cxt->name)) {
		cxt->dm_name = sysfs_strdup(&cxt->sysfs, "dm/name");
		if (!cxt->dm_name) {
			DBG(CXT, ul_debugobj(cxt, "%s: failed to get dm name", cxt->name));
			return -1;
		}
	}

	cxt->npartitions = sysfs_count_partitions(&cxt->sysfs, cxt->name);
	cxt->nholders = sysfs_count_dirents(&cxt->sysfs, "holders");
	cxt->nslaves = sysfs_count_dirents(&cxt->sysfs, "slaves");

	DBG(CXT, ul_debugobj(cxt, "%s: npartitions=%d, nholders=%d, nslaves=%d",
			cxt->name, cxt->npartitions, cxt->nholders, cxt->nslaves));

	/* ignore non-SCSI devices */
	if (lsblk->scsi && sysfs_scsi_get_hctl(&cxt->sysfs, NULL, NULL, NULL, NULL)) {
		DBG(CXT, ul_debugobj(cxt, "non-scsi device -- ignore"));
		return -1;
	}

	DBG(CXT, ul_debugobj(cxt, "%s: context successfully initialized", cxt->name));
	return 0;
}

static int process_blkdev(struct blkdev_cxt *cxt, struct blkdev_cxt *parent,
			  int do_partitions, const char *part_name);
/*
 * List device partitions if any.
 */
static int list_partitions(struct blkdev_cxt *wholedisk_cxt, struct blkdev_cxt *parent_cxt,
			   const char *part_name)
{
	DIR *dir;
	struct dirent *d;
	struct blkdev_cxt part_cxt = { NULL };
	int r = -1;

	assert(wholedisk_cxt);

	/*
	 * Do not process further if there are no partitions for
	 * this device or the device itself is a partition.
	 */
	if (!wholedisk_cxt->npartitions || wholedisk_cxt->partition)
		return -1;

	DBG(CXT, ul_debugobj(wholedisk_cxt, "probe whole-disk for partitions"));

	dir = sysfs_opendir(&wholedisk_cxt->sysfs, NULL);
	if (!dir)
		err(EXIT_FAILURE, ("failed to open device directory in sysfs"));

	while ((d = xreaddir(dir))) {
		/* Process particular partition only? */
		if (part_name && strcmp(part_name, d->d_name))
			continue;

		if (!(sysfs_is_partition_dirent(dir, d, wholedisk_cxt->name)))
			continue;

		DBG(CXT, ul_debugobj(wholedisk_cxt, "  checking %s", d->d_name));

		if (lsblk->inverse) {
			/*
			 * <parent_cxt>
			 * `-<part_cxt>
			 *   `-<wholedisk_cxt>
			 *    `-...
			 */
			if (set_cxt(&part_cxt, parent_cxt, wholedisk_cxt, d->d_name))
				goto next;

			if (!parent_cxt && part_cxt.nholders)
				goto next;

			wholedisk_cxt->parent = &part_cxt;
			fill_table_line(&part_cxt, parent_cxt ? parent_cxt->scols_line : NULL);
			if (!lsblk->nodeps)
				process_blkdev(wholedisk_cxt, &part_cxt, 0, NULL);
		} else {
			/*
			 * <parent_cxt>
			 * `-<wholedisk_cxt>
			 *   `-<part_cxt>
			 *    `-...
			 */
			int ps = set_cxt(&part_cxt, wholedisk_cxt, wholedisk_cxt, d->d_name);

			/* Print whole disk only once */
			if (r)
				fill_table_line(wholedisk_cxt, parent_cxt ? parent_cxt->scols_line : NULL);
			if (ps == 0 && !lsblk->nodeps)
				process_blkdev(&part_cxt, wholedisk_cxt, 0, NULL);
		}
	next:
		reset_blkdev_cxt(&part_cxt);
		r = 0;
	}

	DBG(CXT, ul_debugobj(wholedisk_cxt, "probe whole-disk for partitions -- done"));
	closedir(dir);
	return r;
}

static int process_blkdev(struct blkdev_cxt *cxt, struct blkdev_cxt *parent,
			  int do_partitions, const char *part_name)
{
	if (do_partitions && cxt->npartitions)
		list_partitions(cxt, parent, part_name);		/* partitions + whole-disk */
	else
		fill_table_line(cxt, parent ? parent->scols_line : NULL); /* whole-disk only */

	return list_deps(cxt);
}
static int iterate_block_devices(void)
{
	DIR *dir;
	struct dirent *d;
	struct blkdev_cxt cxt = { NULL };

	if (!(dir = opendir(_PATH_SYS_BLOCK)))
		return -errno;

	DBG(DEV, ul_debug("iterate on " _PATH_SYS_BLOCK));

	while ((d = xreaddir(dir))) {

		DBG(DEV, ul_debug(" %s dentry", d->d_name));


		/* Skip devices in the middle of dependency tree. */
		if ((lsblk->inverse ? cxt.nholders : cxt.nslaves) > 0)
			goto next;

		process_blkdev(&cxt, NULL, 1, NULL);
	next:
		reset_blkdev_cxt(&cxt);
	}

	closedir(dir);

	DBG(DEV, ul_debug("iterate on " _PATH_SYS_BLOCK " -- done"));
	return 0;
}
int main(int argc, char *argv[]){
	return 0;
}
