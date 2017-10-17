#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv){
	
	int devfd=open("mydev", O_RDONLY);
	printf("devfd: %d\n", devfd);
	close(devfd);

	//return from main
	return 0;
}
