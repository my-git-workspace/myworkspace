#include <stdio.h>

#include <stdlib.h>
#include <string.h>

int strLen(const char *str) {
	int len=0;
	while(*str++)
		len++;
	printf("strLen(%s):%d\n", str-len-1, len);
	return len;
}

int maxLengthEvenWord(const char *string, char *maxLengthWord) {
	return 0;
}

int main(int argc, char **argv){
	strLen("Somnath");
	return 0;
}
