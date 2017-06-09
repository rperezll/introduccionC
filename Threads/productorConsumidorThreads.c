#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

FILE * fichero_numeros;
FILE * fichero_salida;
FILE * compartido;
char buf [1024];
char buf2 [1024];
//char cadena [4096];
int i;
sem_t sem;

void *th_consumidor (){
	printf("Soy el consumidor");
	while (fgets(buf,1024,fichero_numeros)!=NULL){
		fputs(buf,compartido);
		sem_post(&sem);
	}
	sem_post(&sem);
	pthread_exit(0);
}
void *th_productor (){
	printf("Soy el productor");
	sem_wait(&sem);
	while(fgets(buf2,1024,compartido)!=NULL){
		char * b = buf;
		i++;
		if (*(int *)b % 2 == 0){
			fput(buf,fichero_salida);			
		}	
	}
	pthread_exit(0);
}

int main (int argc, char *argv[]){
	
	fichero_salida = fopen(argv[2],"w");
	fichero_numeros = fopen(argv[1],"r");
	pthread_t th, th2;
	sem_init(&sem, 0, 0);
	pthread_create(&th,NULL,th_consumidor,NULL);
	pthread_create(&th2,NULL,th_productor,NULL);
	pthread_join(th_consumidor,NULL);
	pthread_join(th_productor,NULL);

}


