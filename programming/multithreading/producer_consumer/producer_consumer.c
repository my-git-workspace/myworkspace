#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"
#include "atomic.h"

#define TOTAL_ELEMENT 10
#define BUF_SIZE MAX
int produce_count=0;
atomic_t consumer_count=ATOMIC_INIT(TOTAL_ELEMENT + 1);
int buffer[BUF_SIZE];
int i = 0;
sem_t sem_full;
sem_t sem_empty;

void *produce(void *param){
	static int data;
	while ( produce_count < TOTAL_ELEMENT ) {
		sem_wait(&sem_empty);
		printf("tid %lu: ", pthread_self());
		put(data++);
		produce_count++;
		sem_post(&sem_full);
	}
	return NULL;
}
void *consume(void *param){
	while ( atomic_read(&consumer_count) ) {
		sem_wait(&sem_full);
		printf("tid %lu: ", pthread_self());
		get();
		atomic_dec(&consumer_count);
		sem_post(&sem_empty);
	}
	return NULL;
}

int main(int argc, char **argv){
	pthread_t producer, consumer[2];
	int ret=0;
	sem_init(&sem_full, 0, 0);
	sem_init(&sem_empty, 0, BUF_SIZE);
	ret=pthread_create(&producer, NULL, produce, NULL);
	if( ret ){
		printf("producer create failed");	
	}
	ret=pthread_create(&consumer[0], NULL, consume, NULL);
	if( ret ){
		printf("consumer [0] create failed");	
	}
	ret=pthread_create(&consumer[1], NULL, consume, NULL);
	if( ret ){
		printf("consumer [1] create failed");	
	}
	pthread_join(producer, NULL);
	pthread_join(consumer[0], NULL);
	pthread_join(consumer[1], NULL);
	//return 
	return (0);
}
