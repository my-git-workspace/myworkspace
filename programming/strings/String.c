#include <stdio.h>
#include <string.h>
#include <String.h>

int strLen(const char *str) {
	int len=0;
	while(*(str+len))
		len++;
	return len;
}

int strCpy( const char *src, char *dest ) {
	int ind=0;	
	while( *(dest +ind)=*(src+ind) ) ind++;
	
	*(dest+ind)='\0';
	return 0;
}

int word( const char *src, char *buf ) {
	int ind = 0;
	while ( *(src + ind) ){
		if( IS_CHAR_SPACE(*(src+ind)) ){
			break;
		}		
		buf[ind]=*(src+ind);
		ind++;
	}	
	buf[ind]='\0';
	return ind;
}


int maxLengthEvenWord( const char *string, char *maxEvenLengthWord ) {
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
	printf("maxLengthEvenWord(\"%s\") = \"%s\"\n", string, maxEvenLengthWord );
	return charCount;
}

int main (int argc, char **argv) {
	//char buf[32];
	const char *str="12345678";
	//maxLengthEvenWord("Hello Hi 12345678 hell", buf);
	//int len=word(str, buf);
	//len=word(str+len+1, buf);
	smallestLargestWordFromString(str);
	return 0;
}
