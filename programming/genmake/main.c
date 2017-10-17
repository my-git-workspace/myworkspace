#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define __CTASSERT(x, y) \
        //typedef char __compile_time_assertion__ ## y [(x) ? 1 : -1]

int main(int argc, char **argv){
 //int sysctlbyname(const char *name, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
 //	sysctlbyname("ABC", NULL, NULL, NULL, 0);
 //   	strlcpy(NULL, NULL);
 //   	strlcat(NULL, NULL);
	//printf(	__CTASSERT(0,100));
	printf("Hello BsdLinux\n");
	//return from main
	return (0);
}
