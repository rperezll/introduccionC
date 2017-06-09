#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

FILE * fichero_numeros;
FILE * fichero_salida;
FILE * compartido;
char buf [1024];
char buf2 [1024];
int i;
sem_t sem;

void *th_productor (){
	printf("Soy el productor\n");
	int j = 0;
	compartido = fopen("compartido","w");
	while (fgets(buf,1024,fichero_numeros)!=NULL){
		fputs(buf,compartido);
	}
	fclose(compartido);
	sem_post(&sem);
	pthread_exit(0);
}
void *th_consumidor (){
	printf("Soy el consumidor\n");
	sem_wait(&sem);
	compartido = fopen("compartido","r");
	while(fgets(buf2,1024,compartido)!=NULL){	
		char * b = buf2;
		i++;
		char iaux = (char)i;
		if (*(int *)b % 2 == 0){
			fputs(buf2,fichero_salida);			
		}	
	}
	pthread_exit(0);
}

int main (int argc, char *argv[]){
	
	fichero_salida = fopen(argv[2],"w");
	fichero_numeros = fopen(argv[1],"r");
	pthread_t th, th2;
	sem_init(&sem, 0, 0);
	pthread_create(&th2,NULL,th_productor,NULL);
	pthread_create(&th,NULL,th_consumidor,NULL);
	pthread_join(th2,NULL);
	pthread_join(th,NULL);

}


