#include  "array.h"

void secondlargestfromarray(int *arr, int size){
	int i=0;
	int largest=0;
	int secondlargest=0;
	if(size<2){
		return;
	}
	if(arr[i]>arr[i+1]){
		largest=arr[i];
		secondlargest=arr[i+1];
	}else{
		largest=arr[i+1];
		secondlargest=arr[i];
	}
	for(i=2;i<size;i++){
		if(arr[i]>largest ){
			secondlargest=largest;
			largest=arr[i];
		}else if (arr[i]<largest && arr[i] > secondlargest && arr[i] != largest ){
			secondlargest=arr[i];
		}		
	}
	if (largest==secondlargest){
		printf("can't find.. all numbers are equal..\n");
		return;
	}	
	printarray(arr, size, "\narray: ");
	printf("largest: %d\n", largest);	
	printf("second largest: %d\n", secondlargest);	
}
void reversearray(int *arr, int size){
	printf("\nreverse array:\n");
	int i=0;
	printarray(arr, size, "\narray: ");
	for(i=0;i<size/2;i++){
		swapval(&arr[i], &arr[size-i-1]);	
	}
	printarray(arr, size, "\nafter reverse array: ");

}
void smallestandsecondsmallestitem(int *arr, int size){
	int i=0;
	int smallest=0;
	int secondsmallest=0;
	if (size<2){
		return;
	}

start:	
	if(arr[i]<arr[i+1]){
		smallest=arr[i];
		secondsmallest=arr[i+1];
	}else if (arr[i+1] < arr[i])	{
		smallest=arr[i+1];
		secondsmallest=arr[i];
	}else if (arr[i]==arr[i+1]){
		i++;
		goto start;		
	}
	for(i=i+2;i<size;i++){
		if(smallest>arr[i]){
			secondsmallest=smallest;
			smallest=arr[i];
		}else if (arr[i]<secondsmallest && arr[i] != smallest){
			secondsmallest=arr[i];
		}
		
	}
	if (smallest==secondsmallest){
		printf("can't find.. all numbers are equal..\n");
		return;	
	}	
	printarray(arr, size, "\nsmallestandsecondsmallestitem array: ");
	printf("smallest: %d\n", smallest);	
	printf("second smallest: %d\n", secondsmallest);	
}
void largestandsmallest(int *arr, int size){
	int i=0;	
	int largest=arr[i];
	int smallest=arr[i];
	for (i=1; i<size;i++){
		if(largest< arr[i]){
			largest=arr[i];
		}
		if(smallest>arr[i]){
			smallest=arr[i];
		}
	}
	if(largest==smallest){
		printf("can't find.. all numbers are equal..\n");
		return;	
	}
	printarray(arr, size, "\n largestandsmallest array: ");
	printf("smallest: %d\n", smallest);	
	printf("largest: %d\n", largest);	
}
void testarray(){
	printf("execution started\n");		
	//int  arr[]={100, -1, -6, -1000};
	//secondlargestfromarray(arr, 4);
	int  arr[]={1,1,1,1,1};
	//reversearray(arr, 5);
	//smallestandsecondsmallestitem(arr,6);
	//secondlargestfromarray(arr, 5);
	largestandsmallest(arr,5);
}
