
#include "sorting-algo.h"

void printarray(int *arr, int size, char *message){
	printf("%s\n", message);
	for (int i=0;i<size;i++){
		printf("arr[%d]:%d\n",i, arr[i]);
	}	
	printf("\n");
}


void insersion_sort(int *arr, int size){
	int i,j,val=0;
	printarray(arr, size, "array");
	printf("\n");
	for(int i=1;i<size;i++){
		val=arr[i];
		j=i-1;		
		while(val<arr[j] && j>=0 ){
			arr[j+1]=arr[j];		
			j=j-1;
		}
		arr[j+1]=val;
	}	
	printarray(arr, size, "insersion_sort");
	printf("\n");

}
void sort(int *arr, int size){
	int i=0;
	printarray(arr, size, "array: ");
	printf("\n");
	for(i=0;i<size-1;i++){
		if(arr[i]>arr[i+1]){
			swapval(&arr[i], &arr[i+1]);
			i=-1;
		}
	}
	printarray(arr, size, "after sort: ");
	
	
}
