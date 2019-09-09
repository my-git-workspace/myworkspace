#include <stdio.h>
#include <stdlib.h>


#if HI
	#define STR "hi"
#else
	#define STR "hello"

#endif


int main(int argc, char **argv){
	

	printf("%s\n", STR);


	int vSize = 64;
	const int fSize = 129;
	if ( ( fSize > vSize ) && ( fSize%vSize == 1 ) ){
		printf("update adress\n");
	}

	//return from main
	return (0);
}
