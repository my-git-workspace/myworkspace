#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	char *parent="/root";
	char *cp=strrchr(parent, 'r');
	if(cp)
		printf("cp: %s\n",cp);
	else
	     printf("not found\n");		
	//return from main
	return (0);
}
