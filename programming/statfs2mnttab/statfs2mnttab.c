#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>
#define BUFSIZE 4098
char buf [BUFSIZE];
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
        if(feof(fp)) {
            return -1; 
        }
        return -1; 

}


int main(int argc, char *argv[]){
	struct mnttab mnt_var;
	FILE *fp=setmntent("/home/msys/devdir/mydev", "r");
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
