#ifndef STRING_H
#define STRING_H

#define IS_CHAR_SPACE(c) (c==' ')
#define IS_CHAR_NULLTERM(c) (c=='\0')

int strLen(const char *str);
int strCpy(const char *src, char *dest);

//Find the first maximum length even word from a string
int maxLengthEvenWord(const char *string, char *maxLengthWord);
int smallestLargestWordFromString( const char *str );
int word( const char *src, char *buf );

#endif
