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

#define IS_CHAR_SPACE(c) (c==' ')
#define IS_CHAR_NULLTERM(c) (c=='\0')

int maxLengthEvenWord(const char *string, char *maxEvenLengthWord) {
	char c='\0';
	char wordBegin=0;
	int maxEvenLen=0;
	int charCount=0;
	int i=0;
	while((c=*(string + i))){
		if( !wordBegin && !IS_CHAR_SPACE(c) ){
			wordBegin=1;
			charCount++;
		}else if ( wordBegin && !IS_CHAR_SPACE(c) && !IS_CHAR_NULLTERM(*(string+i+1)) ){
			charCount++;
		}else if ( IS_CHAR_SPACE(c) || IS_CHAR_NULLTERM(*(string+i+1))){
			if(IS_CHAR_NULLTERM(*(string+i+1))){
				charCount++;
				i++;
			}
			if ( charCount % 2 == 0 && charCount > maxEvenLen ){
				maxEvenLen = charCount;	
				strncpy(maxEvenLengthWord, string + i - charCount,charCount);
				maxEvenLengthWord[charCount]='\0';
			}
			charCount=0;
			wordBegin = 0;
		}	
		i++;
	}
	printf("maxLengthEvenWord(\"%s\") = \"%s\"\n", string,maxEvenLengthWord);
	return charCount;
}

int main(int argc, char **argv){
	char buf[32];
	maxLengthEvenWord("Hello Hi 12345678 hell", buf);
	return 0;
}
