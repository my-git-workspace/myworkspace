#include <stdio.h>
#include <stdlib.h>
#include <langinfo.h>
int main(int argc, char **argv){
	printf("fmt: %s\n",nl_langinfo(_DATE_FMT));
	return (0);	
}
