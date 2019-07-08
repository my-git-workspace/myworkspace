#include <stdio.h>

#include <stdlib.h>

//287
//           0   256 128   64  32  16   8   4   2  1 
//		  1  0     0   0   1    1   1   1  1	
//           

int main(int argc, char **argv){
	int a = 287;
	char *ptr=(char *)&a;
	printf("*ptr: %d\n", *ptr); //out would be 31

	int num=(10,20,30);
	printf("num: %d\n", num);

	float f=0.7;

	if(f<0.7){
		printf("f < 0.7\n");
	}

	char str[11]="The African Queen";

	printf("str: %s\n", str);

	//exit
	exit(0);
}
