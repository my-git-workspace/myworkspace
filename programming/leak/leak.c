#include <stdio.h>
#include <stdlib.h>
#define SIZE 4
void leak(){
	int *ptr=(int *)malloc(sizeof(int)*SIZE);
	ptr[SIZE-1]=0;
}
int main(int argc, char **argv){

	leak();
	//return from main
	return (0);
}
