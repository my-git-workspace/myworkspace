
#include <String.h>

int smallestLargestWordFromString( const char *str ){
	
	char buf[512];
	int small = strLen(str);
	int large = 0;
	int ind = 0;

	char largest[512]={'\0'};
	char smallest[512]={'\0'};
	
	while ( *(str+ind ) ) {
		int len = word( str + ind ,buf );	

		if( len < small ) {
			small=len;
			strCpy(buf, smallest);
		}

		if( len > large ){
			large = len;		
			strCpy(buf, largest);
		}
		ind += len;
		if ( *(str + ind) ){
			ind++;	
		}
	}	

	printf("smallest: %s largest: %s\n", smallest, largest);
	return (0);
}
