#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

//para compilar: gcc nombre.c -lpthread

#define FILOSOFOS 5
int estado_filosofo[FILOSOFOS];
pthread_mutex_t palillo[FILOSOFOS];

void *filosofo(void *num) {
	
	int fil_id = *(int *)num; //Primer *: Entrar en contenido de num; int *: Transformar de puntero generico (void) a puntero int
	
	while (1) {
		estado_filosofo[fil_id] = 0;	//Folósofo pensando
		printf("Filósofo %d pensando\n", fil_id);
		sleep( (rand() % 2) + 1 );	//Espera un tiempo aleatorio
		
		estado_filosofo[fil_id] = 1; //Filósofo queriendo comer 
		printf("Filósofo %d quiere comer\n", fil_id);
		// Entrando en sección crítica
		// Los filósofos pares cogen el palillo con menor número primero, los impares al revés.
		if ( ( *(int *)num % 2)==0 ) {

			pthread_mutex_lock(&palillo[fil_id%FILOSOFOS]);
			pthread_mutex_lock(&palillo[(fil_id+1)%FILOSOFOS]);

		} else {

			pthread_mutex_lock(&palillo[(fil_id+1)%FILOSOFOS]);
			pthread_mutex_lock(&palillo[fil_id%FILOSOFOS]);

		}
		estado_filosofo[fil_id] = 2; //Filósofo Comiendo
		printf("Filósofo %d comiendo\n", fil_id);
		sleep( (rand() % 2) + 1); //Come un tiempo aleatorio
		// Todos los filósofos devuelven los palillos al revés de como los cogieron.
		if ( (*(int *)num%2)!=0 ) {
			pthread_mutex_unlock(&palillo[fil_id%FILOSOFOS]);
			pthread_mutex_unlock(&palillo[(fil_id+1)%FILOSOFOS]);

		} else {

			pthread_mutex_unlock(&palillo[(fil_id+1)%FILOSOFOS]);
			pthread_mutex_unlock(&palillo[fil_id%FILOSOFOS]);
			
		}
		// Saliendo de sección crítica
	}
}

int main(void) {
	pthread_t th;
	int i;
	int fil_id[FILOSOFOS];

	for(i = 0; i < FILOSOFOS; i++) {
		fil_id[i] = i;
		pthread_mutex_init(&palillo[i],NULL);
		pthread_create(&th,NULL,filosofo,(void*)&fil_id[i]);
	}

	while(1);
}
