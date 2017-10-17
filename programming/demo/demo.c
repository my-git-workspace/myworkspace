#include <stdio.h>
#include <stdlib.h>


#if HI
	#define STR "hi"
#else
	#define STR "hello"

#endif


int main(int argc, char **argv){

	printf("%s\n", STR);
	//return from main
	return (0);
}
