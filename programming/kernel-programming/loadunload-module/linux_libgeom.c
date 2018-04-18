
/*
static int zpool_find_import_blkid(libzfs_handle_t *hdl, kmutex_t *lock, avl_tree_t **slice_cache)
{
	rdsk_node_t *slice;
	blkid_cache cache;
	blkid_dev_iterate iter;
	blkid_dev dev;
	avl_index_t where;
	int error;

	*slice_cache = NULL;

	error = blkid_get_cache(&cache, NULL);
	if (error != 0)
		return (error);

	error = blkid_probe_all_new(cache);
	if (error != 0) {
		blkid_put_cache(cache);
		return (error);
	}

	iter = blkid_dev_iterate_begin(cache);
	if (iter == NULL) {
		blkid_put_cache(cache);
		return (EINVAL);
	}

	error = blkid_dev_set_search(iter, "TYPE", "zfs_member");
	if (error != 0) {
		blkid_dev_iterate_end(iter);
		blkid_put_cache(cache);
		return (error);
	}

	*slice_cache = zfs_alloc(hdl, sizeof (avl_tree_t));
	avl_create(*slice_cache, slice_cache_compare, sizeof (rdsk_node_t),
	    offsetof(rdsk_node_t, rn_node));

	while (blkid_dev_next(iter, &dev) == 0) {
		slice = zfs_alloc(hdl, sizeof (rdsk_node_t));
		slice->rn_name = zfs_strdup(hdl, blkid_dev_devname(dev));
		slice->rn_vdev_guid = 0;
		slice->rn_lock = lock;
		slice->rn_avl = *slice_cache;
		slice->rn_hdl = hdl;
		slice->rn_labelpaths = B_TRUE;

		error = zfs_path_order(slice->rn_name, &slice->rn_order);
		if (error == 0)
			slice->rn_order += IMPORT_ORDER_SCAN_OFFSET;
		else
			slice->rn_order = IMPORT_ORDER_DEFAULT;

		mutex_enter(lock);
		if (avl_find(*slice_cache, slice, &where)) {
			free(slice->rn_name);
			free(slice);
		} else {
			avl_insert(*slice_cache, slice, where);
		}
		mutex_exit(lock);
	}

	blkid_dev_iterate_end(iter);
	blkid_put_cache(cache);

	return (0);
}
*/

#include <blkid/blkid.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <libgen.h>
static int zpool_find_import_blkid(/*libzfs_handle_t *hdl, kmutex_t *lock, avl_tree_t **slice_cache*/)
{
	//rdsk_node_t *slice;
	blkid_cache cache;
	blkid_dev_iterate iter;
	blkid_dev dev;
	//avl_index_t where;
	int error;

	//*slice_cache = NULL;

	error = blkid_get_cache(&cache, NULL);
	error= blkid_probe_all(cache);
	if (error != 0)
		return (error);

	/*
	error = blkid_probe_all_new(cache);
	if (error != 0) {
		blkid_put_cache(cache);
		return (error);
	}
*/
	iter = blkid_dev_iterate_begin(cache);
	if (iter == NULL) {
		blkid_put_cache(cache);
		return (EINVAL);
	}
/*
        error = blkid_dev_set_search(iter, "TYPE", "zfs_member");
        if (error != 0) { 
                blkid_dev_iterate_end(iter);
                blkid_put_cache(cache);
                return (error);
        }
*/
	//error = blkid_dev_set_search(iter, "TYPE", "*");
	//if (error != 0) {
	//	blkid_dev_iterate_end(iter);
	//	blkid_put_cache(cache);
	//	return (error);
	//}

	//*slice_cache = zfs_alloc(hdl, sizeof (avl_tree_t));
	//avl_create(*slice_cache, slice_cache_compare, sizeof (rdsk_node_t), offsetof(rdsk_node_t, rn_node));

	while (blkid_dev_next(iter, &dev) == 0) {
		//slice = zfs_alloc(hdl, sizeof (rdsk_node_t));
		//slice->rn_name = zfs_strdup(hdl, blkid_dev_devname(dev));
		//slice->rn_vdev_guid = 0;
		//slice->rn_lock = lock;
		//slice->rn_avl = *slice_cache;
		//slice->rn_hdl = hdl;
		//slice->rn_labelpaths = B_TRUE;
		printf("device: %s\n", blkid_dev_devname(dev));
		//printf("device: %s\n", blkid_dev_devname(dev));
	}

	blkid_dev_iterate_end(iter);
	blkid_put_cache(cache);

	return (0);
}


int main(int argc, char **argv){


#ifdef QNAP_ZFS_LINUX

	blkid_cache cache;
	blkid_dev_iterate iter;
	blkid_dev dev;
	int error;

	error = blkid_get_cache(&cache, NULL);
	error= blkid_probe_all(cache);
	if (error != 0)
		return (error);

	error = blkid_probe_all_new(cache);
	if (error != 0) {
		blkid_put_cache(cache);
		return (error);
	}

	iter = blkid_dev_iterate_begin(cache);
	if (iter == NULL) {
		blkid_put_cache(cache);
		return (EINVAL);
	}

	while (blkid_dev_next(iter, &dev) == 0) {
                slice = zfs_alloc(hdl, sizeof (rdsk_node_t));
                slice->rn_name = zfs_strdup(hdl, basename((char *)blkid_dev_devname(dev)));
                slice->rn_avl = &slice_cache;
                slice->rn_dfd = dfd;
                slice->rn_hdl = hdl;
                slice->rn_nozpool = B_FALSE;
                avl_add(&slice_cache, slice);

	}

	blkid_dev_iterate_end(iter);
	blkid_put_cache(cache);

#else
	zpool_find_import_blkid();
#endif


	//return from main
	return 0;
}
