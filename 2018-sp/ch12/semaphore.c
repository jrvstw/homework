#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int global=0;
sem_t semaphores;

void thread(void) {
	int i;
	for (i=0; i<1000000000; i++) {
		sem_wait(&semaphores);
		global+=1;
		sem_post(&semaphores);
	}
}

int main(void) {
	pthread_t id1, id2;
	
	sem_init(&semaphores, 0, 1);
	pthread_create(&id1,NULL,(void *) thread,NULL);
	pthread_create(&id2,NULL,(void *) thread,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("1000000000+1000000000 = %d\n", global);
	return (0);
}
