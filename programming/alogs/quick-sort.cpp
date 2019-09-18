#include <quick-sort.h>

/*
int swap(int *one, int *two ){
	int temp=*one;
	*one=*two;
	*two=temp;
}
*/

int qqsort(int *arr, int low, int high){
	if(low < high ){
		int pi=partition(arr, low, high);
		qqsort( arr, low, pi-1 );
		qqsort( arr, pi+1, high );
	}
	return 0;
}
int partition( int *arr, int low, int high ){
	int pivot = arr[high];	
	int i=low-1, j; 

	for ( j=low; j<=high-1; j++ ){
		if( arr[j] < pivot ) { 
			i++;		
			swap(&arr[i], &arr[j]);
		}
	}
	swap( &arr[i+1], &arr[high] );
	return i+1;
}
