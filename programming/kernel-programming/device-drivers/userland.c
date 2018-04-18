#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define DEV_PATH "/dev/chr_device"
int main(int argc, char *argv[]){
    	printf("userland called\n");
	char buff[2];
    	int fd=open(DEV_PATH,O_RDWR);
	if(fd==-1){
		printf("device open failed %s\n",DEV_PATH);
	}
	printf("ioctl: %d\n",ioctl(fd,1,0));
	printf("read: %d\n",(int)read(fd,buff,1));
	printf("write: %d\n",(int)write(fd,buff,1));
	close(fd);
	return (0);
}
