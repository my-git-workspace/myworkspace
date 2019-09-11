#include <stdio.h>
#include <stdlib.h>
#include <array.h>


int main(int argc, char **argv) {
	int arr[]={1,2,3,4,5,6,7};

	array_rotate(arr, sizeof(arr)/sizeof(int), 2);
	//return (0);
	return (0);
}
