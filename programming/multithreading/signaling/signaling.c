#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

/*
 *routine_two should be executed before routine_one
    routine_two > routine_one
 *
 */

void *routine_one(void *arg){
	sem_t *sema = (sem_t *)arg;
	sem_wait(sema);	
	printf("%s called\n",__func__);
	pthread_exit(NULL);
	return NULL;
}   
void *routine_two(void *arg){
	sem_t *sema = (sem_t *)arg;
	printf("%s called\n",__func__);
	sem_post(sema);	
	pthread_exit(NULL);
	return NULL;
}   
int main(int argc, char **argv){

	sem_t sema;
	sem_init(&sema, 0, 0);
	pthread_t th[2];
	pthread_create(&th[0], NULL, routine_one, &sema);
	pthread_create(&th[1], NULL, routine_two, &sema);

	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);
	//return from main
	return 0;
}
