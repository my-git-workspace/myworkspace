#include <iostream>
#include <merge-sort.h>

using namespace std;

int main(int argc, char **argv){
	int arr[]={5,1,6,4,3};

	int size=sizeof(arr)/sizeof(int);
	
	cout<<"original"<<endl;
	printArr(arr, size);	
	mergeSort(arr, 0, size);
	cout<<"sorted"<<endl;
	printArr(arr, size);	

	//return main
	return (0);
}
