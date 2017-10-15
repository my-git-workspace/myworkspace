#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>
#define BUFSIZE 4098
struct mnttab {
        char    *mnt_special;
        char    *mnt_mountp;
        char    *mnt_fstype;
        char    *mnt_mntopts;
};
int statfs2mnttab(FILE *fp, struct mnttab *mgetp)
{
        struct mntent mntbuf;
        struct mntent *ret;
	char buf[BUFSIZE];
        if(fp == NULL || mgetp == NULL)
                return -1; 

        ret = getmntent_r(fp, &mntbuf, buf, BUFSIZE);
        printf("======%s:%d====ret:%p=mntbuf:%p=\n",__func__,__LINE__,ret,&mntbuf);
        if (ret != NULL) {
                mgetp->mnt_special = mntbuf.mnt_fsname;
                mgetp->mnt_mountp = mntbuf.mnt_dir;
                mgetp->mnt_fstype = mntbuf.mnt_type;
                mgetp->mnt_mntopts = mntbuf.mnt_opts;
                printf("mgetp->mnt_special: %s\n",mgetp->mnt_special);  
                printf("mgetp->mnt_fstype: %s\n",mgetp->mnt_fstype);    
                printf("mgetp->mnt_mountp: %s\n",mgetp->mnt_mountp);    
                printf("mgetp->mnt_mntopts: %s\n",mgetp->mnt_mntopts);  
                return 0;
        }
        if(feof(fp)) {
                printf("====error==%s:%d=========\n",__func__,__LINE__);
                return -1; 
        }
}
int main(int argc, char *argv[]){
	struct mnttab mgetp;
	FILE *fp=fopen("/proc/self/mounts","r");
	if(!fp){
		printf("fopen error\n");
		return (0);
	}
	while(!statfs2mnttab(fp, &mgetp));
	fclose(fp);
	//return from main
	return (0);
}
