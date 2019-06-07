
#include "queue.h"

int ind=-1;
int front=0;
int buffer[MAX];
int counter=0;


int isFull(){
	return (counter==MAX);
}

int isEmpty(){
	return counter==0;
}

void put(int val){
	if(isFull()){
		printf("queue full\n");
		return;	
	}	
	if ( ind == MAX-1 ){
		ind = -1;
	}
	buffer[++ind]=val;
	printf(" put [%d]: %d\n", ind,val);
	counter++;
}
int get(){
	int val=-1;
	if( front == MAX ){
		front=0;
	}
	if(isEmpty()){
		printf("queue empty\n");
		front=0;
	}else{
		val = buffer[front] ;
		printf(" get [%d]: %d\n", front,val);
		front++;
		counter--;
	}
	return val;
}
/*
int main(int argc, char **argv){
	put(10);	
	put(20);	
	put(30);	
	put(30);	
	put(30);	
	put(30);	
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	printf("%d\n", get());
	return 0;
}
*/
