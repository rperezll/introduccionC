#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

//todo esto pasa por que los thread van al ritmo que ellos quieren y se 
//imprimen en el orden que quieren, por ello ponemos los semaforos.

//Creamos el semáforo
sem_t sem;

void *th_func1(void *arg)
{
	printf ("Soy el thread 1\n");	//esto no esta sincronizado
	//le digo que cuando llegue aqui, si el semaforo esta a 0 lo bloquea, 
	//como cuando llega por 1a vez es 0 lo bloquea
	sem_wait(&sem);	
	printf("Y esto se tiene que imprimir después\n");
	pthread_exit(0);	//se puede evitar por que lo hace el sistema , pero es bueno ponerlo
}
void *th_func2(void *arg)
{
	printf("Hola, soy el thread 2\n");	//esto no esta sincronizado
	printf("Esto se tiene que imprimir primero\n");
	//sem_post -1 para que vuelva arriba
	sem_post(&sem);
	pthread_exit(0);
}
int main(int argc, char **argv)
{
	//Creamos 2 hilos
	pthread_t th1, th2; 
	
	//Inicializamos el semáforo
	sem_init(&sem, 0, 0); //el primer 0 es por que es un semáforo para THREAD
	//el segundo 0 es para que el semaforo empiece a 0
	//El wait es el bloqueante cuando ve el 0.
	//si fuera para entrar en la zona critica pondria un 1.
	
	//si quisiera pasar argumentos lo pondria donde pone NULL, lo unico que si quiero.. 
	//..pasar algo no puedo pasar un numero si no un puntero. Como yo no quiero pasar nada le pongo NULL.
	pthread_create(&th1, NULL, th_func1, NULL);
	pthread_create(&th2, NULL, th_func2, NULL);	
	
	//Para que el prgrama principal espere a la finalización de ambos hilos
	pthread_join(th1, NULL);	
	pthread_join(th2, NULL);
	
	return 0;
}

