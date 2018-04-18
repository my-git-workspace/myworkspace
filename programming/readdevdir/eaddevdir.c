#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

static void lookup(const char *arg)
{
    DIR *dirp;
    struct dirent *dp;


    if ((dirp = opendir(arg)) == NULL) {
        perror("couldn't open '.'");
        return;
    }


    do {
        errno = 0;
        if ((dp = readdir(dirp)) != NULL) {
	    struct stat fileStat;
	    char f_name[512]="/home/msys/devdir/";
	    strcat(f_name,dp->d_name);
	    if(stat(f_name,&fileStat) < 0){    
			perror("stat failed.");	
			return;
	    }
	    if(S_ISBLK(fileStat.st_mode)){
	    	printf("blkdev dp->d_name: %s\n",dp->d_name);	
	    }else
	    	printf("dp->d_name: %s\n",dp->d_name);	

        }
    } while (dp != NULL);


    if (errno != 0){
        perror("error reading directory");
    }
    (void) closedir(dirp);
    return;
}


int main(int argc, char *argv[])
{
    int i;
    for (i = 1; i < argc; i++)
        lookup(argv[i]);
    return (0);
}
