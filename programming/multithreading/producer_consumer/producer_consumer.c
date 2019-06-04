#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define TOTAL_ELEMENT 20
#define BUF_SIZE 10
int produce_count=0;
int consumer_count=TOTAL_ELEMENT;
int buffer[BUF_SIZE];
int i = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_p;
sem_t sem_c;

void *producer(void *param){
	int static data;
	while ( produce_count <= TOTAL_ELEMENT - BUF_SIZE ) {
		//sleep(1);
		sem_wait(&sem_c);
		printf("producer\n");

		for (i=0;i<BUF_SIZE;i++){
			buffer[i]=data++;
			printf(" %d ", buffer[i]);
			produce_count++;
		}	

		sem_post(&sem_p);
		printf("\n");
	}
	return NULL;
}
void *consumer(void *param){
	while ( consumer_count  ) {
		//sleep(1);
		sem_wait(&sem_p);
		printf("consumer\n");
		for (i=0;i<BUF_SIZE;i++){
			printf(" %d ", buffer[i]);
			buffer[i]=0;
			consumer_count--;

		}	
		sem_post(&sem_c);
		printf("\n");
	}
	return NULL;
}

int main(int argc, char **argv){
	pthread_t th[2];
	int ret=0;
	sem_init(&sem_p, 0, 0);
	sem_init(&sem_c, 0, 1);
	ret=pthread_create(&th[0], NULL, producer, NULL);
	if( ret ){
		printf("pthread 1 create failed");	
	}
	ret=pthread_create(&th[1], NULL, consumer, NULL);
	if( ret ){
		printf("pthread 2 create failed");	
	}
	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	//return 
	return (0);
}
