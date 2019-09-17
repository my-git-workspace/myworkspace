#include <merge-sort.h>

/*
 *
 *	devide array into two and call mergeSort for left and right side;
 *
 */

int mergeSort(int *arr, int l, int r){

	if ( l < r ){
		int m=(l+r)/2;
		mergeSort(arr, l, m);	
		mergeSort(arr, m+1, r);	
		merge(arr,l,m,r);
	}
	return (0);
}
/*
 *
 * merge the sorted arrays;
 *
 */
int merge(int *arr, int l, int m, int r){
	int nl = m-l+1; 
	int nr = r-m;
	
	int L [nl];
	int R [nr];

	int il=0;
	int ir=0;
	int k=0;

	//devide into two arrays

	for( il=0;il<nl;il++ ) {
		L[il] = arr[l+il];			
	}
	for( ir=0;ir<nr;ir++ ) {
		R[ir] = arr[m+1+ir];			
								
	}
	
	//merge array
	il=0;
	ir=0;
	k=l;
	while ( il < nl && ir < nr ){
		if ( L[il] <= R[ir] ){
			arr[k] = L[il];
			il++;
		}else {	
			arr[k] = R[ir];
			ir++;
		}
		k++;
	
	}
	while (il < nl){
		arr[k]=L[il];
		il++;
		k++;
	}
	while (ir < nr){
		arr[k]=R[ir];
		ir++;
		k++;
	}
	return 0;
}

int printArr(int *arr, int n){
	for(int i=0;i<n;i++){
		cout<<"["<<i<<"]: "<<arr[i]<<endl;
	}
	return (0);
}
