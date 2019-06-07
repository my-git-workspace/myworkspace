#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include "queue.h"

#define TOTAL_ELEMENT 2000
#define BUF_SIZE MAX
int produce_count=0;
int consumer_count=TOTAL_ELEMENT;
int buffer[BUF_SIZE];
int i = 0;
sem_t sem_full;
sem_t sem_empty;

void *produce(void *param){
	static int data;
	while ( produce_count < TOTAL_ELEMENT ) {
		sem_wait(&sem_empty);
		put(data++);
		produce_count++;
		sem_post(&sem_full);
	}
}
void *consume(void *param){
	while ( consumer_count  ) {
		sem_wait(&sem_full);
		get();
		consumer_count--;
		sem_post(&sem_empty);
	}
}

int main(int argc, char **argv){
	pthread_t producer, consumer;
	int ret=0;
	sem_init(&sem_full, 0, 0);
	sem_init(&sem_empty, 0, BUF_SIZE);
	ret=pthread_create(&producer, NULL, produce, NULL);
	if( ret ){
		printf("pthread 1 create failed");	
	}
	ret=pthread_create(&consumer, NULL, consume, NULL);
	if( ret ){
		printf("pthread 2 create failed");	
	}
	pthread_join(producer, NULL);
	pthread_join(consumer, NULL);
	//return 
	return (0);
}
