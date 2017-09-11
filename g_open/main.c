
#include <stdio.h>
#include <stdlib.h>
#ifdef QNAP_ZFS_LINUX
/*
 * By "whole disk" we mean an entire physical disk (something we can
 * label, toggle the write cache on, etc.) as opposed to the full
 * capacity of a pseudo-device such as lofi or did.  We act as if we
 * are labeling the disk, which should be a pretty good test of whether
 * it's a viable device or not.  Returns B_TRUE if it is and B_FALSE if
 * it isn't.
 */
int
zfs_dev_is_whole_disk(char *dev_name)
{
        struct dk_gpt *label;
        int fd;

        if ((fd = open(dev_name, O_RDONLY | O_DIRECT)) < 0)
                return (0);

        if (efi_alloc_and_init(fd, EFI_NUMPAR, &label) != 0) {
                (void) close(fd);
                return (0);
        }

        efi_free(label);
        (void) close(fd);

        return (1);
}

#endif

int main(int argc, char **argv){
#ifdef QNAP_ZFS_LINUX
	zfs_dev_is_whole_disk("/dev/sda5");
#endif	
	//return from main
	return (0);
}
