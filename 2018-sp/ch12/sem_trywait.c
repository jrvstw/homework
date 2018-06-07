#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int global=0;
int trywait_fail=0;
sem_t semaphores;
void thread(void) {
	int i;
	for (i=0; i<10000; i++) {
		if (sem_trywait(&semaphores) == -1)	{	//lock應該會失敗
			sem_wait(&semaphores);	//向OS要求進入critical section修改global
			trywait_fail++;
		}
        for (int j=0; j<random()%10000; j++) //busy
            ;
        global++;
		sem_post(&semaphores);	//告訴OS修改完成，離開critical section
	}
}
int main(void) {
	pthread_t id1, id2;
	sem_init(&semaphores, 0, 1);	/*0: thread使用，1: semaphore只允許一個人修改global*/
	pthread_create(&id1,NULL,(void *) thread,NULL);
	pthread_create(&id2,NULL,(void *) thread,NULL);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	printf("1000000000+1000000000 = %d\n", global);
	printf("trywait_fail = %d\n", trywait_fail);
	return (0);
}