#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define THREADS 10


void *multiplex(void *param){
	int *val=(int *)param;
	printf("val: %d\n", *val);
	pthread_exit(NULL);
	return NULL;
}

int main(int argc, char **argv){
	int i=0;
	int ret=0;
	pthread_t th[THREADS];
	for (i=0;i<THREADS;i++){
		ret=pthread_create(&th[i], NULL, multiplex, &i);
		if(ret){
			printf("pthread  %d create failed\n", i);
		}		
	}
	
	for (i=0;i<THREADS;i++){
		ret=pthread_join(th[0], NULL);
	}
	//return 0
	return 0;	
}


