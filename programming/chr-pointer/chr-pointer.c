#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

	int i = 320;
	char *ptr = (char *)&i;

	printf("%d\n", *ptr);
	//return (0);
	return (0);
}
