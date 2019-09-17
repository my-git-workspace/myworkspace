#include <iostream>

#define BUF_SIZE 10
using namespace std;

void swap(int *src, int *dest){
	//cout<<"swap( "<<*src <<","<<*dest<<")"<<endl;
	int temp=*src;
	*src=*dest;
	*dest=temp;
}

void assending_order(int *arr){
	cout<<"assending_order"<<endl;
	for ( int first=0; first<BUF_SIZE; first++ ){
		for ( int second=first+1; second<BUF_SIZE; second++ ){
			if(arr[first]>arr[second]){
				swap(arr+first, arr+second);
			}
		}	
	}
}


bool binary_search(int *arr,int k, int l, int r){

	int m = 0;
	if ( l <= r ) {
		m=(l+r)/2;
		if( k < arr[m] )
			return binary_search(arr, k, l, m-1);
		else if ( k > arr[m] )
			return binary_search(arr, k, m+1, r);
		else{
			cout<<"key at index: "<<m<<endl;
			return true;
		}
	}
	return false;
}


bool binary_search( int *arr, int k ){ //normal
	cout<<"binary_search"<<endl;
	int r=BUF_SIZE-1;
	int l=0;
	int m=0;
	while(l<=r){
		m = (l+r)/2;		
		if ( k < arr[m] ){
			r=m-1;
		}else if ( k > arr[m] ){
			l = m+1;	
		}else{
			cout<<"key at index: "<<m<<endl;
			return true;
		}
	}			
	cout<<"key not found"<<endl;
	return false;
}

void print_array(int *arr){
	for(int i=0;i<BUF_SIZE;i++){
		cout<<"arr["<<i<<"]: "<<arr[i]<<endl;
	}
}
/*
int main(int argc, char **argv){
	int arr[BUF_SIZE];

	for (int i=0; i<BUF_SIZE;i++){
		arr[i]=random();
	}
	//print_array(arr);
	assending_order(arr);
	print_array(arr);
	//binary_search(arr, 1);
	binary_search(arr, arr[0], 0, BUF_SIZE-1);

	//return 0
	exit (0);
}*/
