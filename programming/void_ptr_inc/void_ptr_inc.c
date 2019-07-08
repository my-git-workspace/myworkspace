#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
	int number=10;
	//void *ptr=(void *)&number;
	void *ptr;
	printf("ptr: %p\n", ptr);
	ptr++;
	printf("ptr: %p\n", ptr);
	return (0);
}
