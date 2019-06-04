/*
 *thread A
 *statement a1
statement a2
 *
 *
 * thread B
 *
 * statement b1
statement b2

a1 > b1
b1 > a2
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_a;
sem_t sem_b;

void *routine_A(void *arg){
	//a1
	printf("a1 %s called\n",__func__);
	
	sem_post(&sem_a);

	sem_wait(&sem_b);
	//a2
	printf("a2 %s called\n",__func__);
	sem_post(&sem_a);
	pthread_exit(NULL);
	return NULL;
}   
void *routine_B(void *arg){

	sem_wait(&sem_a);
	//b1
	printf("b1 %s called\n",__func__);

	sem_post(&sem_b);
	sem_wait(&sem_a);
	//b2
	printf("b2 %s called\n",__func__);
	pthread_exit(NULL);
	return NULL;
}   
int main(int argc, char **argv){

	sem_init(&sem_a, 0, 0);
	sem_init(&sem_b, 0, 0);

	pthread_t th[2];
	pthread_create(&th[0], NULL, routine_A, NULL);
	pthread_create(&th[1], NULL, routine_B, NULL);

	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	//return from main
	return 0;
}
