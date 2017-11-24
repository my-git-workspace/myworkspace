#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>
#define BUFSIZE 4098
char buf [BUFSIZE];

#if 0
struct mnttab {
        char    *mnt_special;
        char    *mnt_mountp;
        char    *mnt_fstype;
        char    *mnt_mntopts;
};

void print_mnttap(struct mnttab mgetp){
	printf("=====%s=====\n",__func__);
	printf("mnt_special:%s\n",mgetp.mnt_special);
	printf("mnt_mountp:%s\n",mgetp.mnt_mountp);
	printf("mnt_fstype:%s\n",mgetp.mnt_fstype);
	printf("mnt_mntopts:%s\n",mgetp.mnt_mntopts);
}

int statfs2mnttab(FILE *fp, struct mnttab *mgetp)
{
        struct mntent mntbuf;
        struct mntent *ret;

        if(fp == NULL || mgetp == NULL)
                return -1; 

        ret = getmntent_r(fp, &mntbuf, buf, BUFSIZE);
	
        if (ret != NULL) {
                mgetp->mnt_special = mntbuf.mnt_fsname;
                mgetp->mnt_mountp = mntbuf.mnt_dir;
                mgetp->mnt_fstype = mntbuf.mnt_type;
                mgetp->mnt_mntopts = mntbuf.mnt_opts;
                return 0;
        }
	perror("getmntent_r failed");
        if(feof(fp)) {
            return -1; 
        }
        return -1; 

}


int main(int argc, char *argv[]){
	struct mnttab mnt_var;
	FILE *fp=setmntent("/zolpool/qfs", "r");
	//FILE *fp=setmntent("/home/msys/devdir/mydev", "r");
	//FILE *fp=fopen("/home/msys/devdir/mydev", "r+");
	if(!fp){
		perror("fopen failed");
		return 0;
	}	
	int ret=statfs2mnttab(fp,&mnt_var);
	printf("ret: %d\n",ret);
	print_mnttap(mnt_var);
	fclose(fp);	
	return 0;
}
#endif

#if 0
int main(int argc, char **argv) {
  FILE* mtab = setmntent("/etc/mtab", "r");
  struct mntent* m;
  struct mntent mnt;
  char strings[4096];
  if (argc!=2){
		return 0;
	}
  printf("fsname\t\tmnt_dir\t\tmnt_type\t\tmnt_opts\n");	
  while ((m = getmntent_r(mtab, &mnt, strings, sizeof(strings)))) {
    struct statfs fs;
    if ((mnt.mnt_dir != NULL) && (statfs(argv[1], &fs) == 0)) {
      	//printf("%s\t%s\t%s\t%s\n", mnt.mnt_fsname, mnt.mnt_dir, mnt.mnt_type, mnt.mnt_opts);
	if(!strcmp(mnt.mnt_dir, argv[1]))
		break;
    }
  }
  printf("%s\t%s\t%s\t%s\n", mnt.mnt_fsname, mnt.mnt_dir, mnt.mnt_type, mnt.mnt_opts);
  endmntent(mtab);
}
#endif

#include <mntent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>           /* Definition of AT_* constants */
#include <errno.h>


typedef unsigned int uint_t;

struct mnttab {
        char    *mnt_special;
        char    *mnt_mountp;
        char    *mnt_fstype;
        char    *mnt_mntopts;
};

struct extmnttab {
        char *mnt_special;
        char *mnt_mountp;
        char *mnt_fstype;
        char *mnt_mntopts;
        uint_t mnt_major;
        uint_t mnt_minor;
};

int
statfs2mnttab(FILE *fp, struct mnttab *mgetp)
{
        struct mntent mntbuf;
        struct mntent *ret;

        if(fp == NULL || mgetp == NULL)
                return -1;

        ret = getmntent_r(fp, &mntbuf, buf, BUFSIZE);

        if (ret != NULL) {
                mgetp->mnt_special = mntbuf.mnt_fsname;
                mgetp->mnt_mountp = mntbuf.mnt_dir;
                mgetp->mnt_fstype = mntbuf.mnt_type;
                mgetp->mnt_mntopts = mntbuf.mnt_opts;
                return 0;
        }
        if(feof(fp)) {
            return -1;
        }
        return -1;

}


int 
getextmntent(FILE *fp, struct extmnttab *mp, int len)
{
        int ret;
        struct stat st_var; 

        ret = statfs2mnttab(fp, (struct mnttab *)mp); 
        if (ret == 0) {
                if (stat64(mp->mnt_mountp, &st_var) != 0) {
                        mp->mnt_major = 0;
                        mp->mnt_minor = 0;
                        return (ret);
                }   
                mp->mnt_major = major(st_var.st_dev);
                mp->mnt_minor = minor(st_var.st_dev);
        }

        return (ret);
}

int main(int argc, char **argv){
	int ret=0;
	struct stat statbuf;
	struct extmnttab entry;
	if(argc!=2){
		return 0;	
	}
	if (stat64(argv[1], &statbuf) != 0) {
                (void) fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
                return (0);
        }
	FILE* mtab = setmntent("/etc/mtab", "r");
	while ((ret = getextmntent(mtab, &entry, 0)) == 0) { 
		if (makedev(entry.mnt_major, entry.mnt_minor) == statbuf.st_dev) {
            	 break;
       		}
        } 
        printf("==========%s:%d========ret: %d==\n",__func__,__LINE__,ret);     
	endmntent(mtab);   
	return 0;
}
