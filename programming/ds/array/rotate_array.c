
#include <array.h>


void showArray(int *arr, int n){

	printf("\n");
	for (int i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int array_rotate(int *arr, int n, int d){
	int i = 0;
	showArray(arr,n);
	while ( d > 0 ){
		d--;
		int first=arr[0];
		for ( i=0; i<n; i++ ){
			arr[i] = arr[i+1];
		}
		arr[i-1]=first;
	}
	showArray(arr,n);
	return (0);
}

