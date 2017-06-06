#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

volatile int j=0;
sem_t sem;

void *th_func1 (void * arg){
	int i;
	for (i = 0; i < 10000 ; i++){
		//El primero que llega aquí, si entra a la región crítica. Tras su paso, bloquea el semáforo
		//y lo desbloquea con el post
		sem_wait(&sem);
		j=j+1;
		sem_post(&sem);
	}
}

int main (){

	pthead_t th1,th2;
	sem_init(&sem,0,1);
	
	pthread_create(&th1,NULL,th_func1,NULL);
	pthread_create(&th2,NULL,th_func1,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);

	printf("j=%d\n",j);	//j Vale 20000
}