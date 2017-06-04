#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

/***
- Cree un proceso hijo que será el encargado de generar números 
aleatorios. Este proceso hijo escribirá en un pipe un número 
aleatorio del 0 al 10 cada vez que reciba una señal por 
parte del padre.
- El proceso padre lee líneas de la entrada estándar y por cada 
línea que lea solicitará al hijo que le envíe un número aleatorio, 
lo leerá y lo imprimirá en pantalla.
- Cuando el proceso padre termine de leer líneas de la entrada 
estándar, enviará una señal al hijo para que este terminé, y 
después terminará el padre.
***/

int p[2];  //Para almacenar los descriptores de la tubería

//Manejador de señales del hijo
//SIGUSR1 => generar un numero aleatorio y ponerlo en la tubería
//SIGUSR2 => terminar el proceso hijo
void manejador_hijo(int sig)
{
	int num;
	
	if(sig == SIGUSR2)
		exit(0);
	else if(sig == SIGUSR1)
	{		
	  //num = rand() % 10;
		num = 1+(int) (10.0*rand()/(RAND_MAX+1.0));
		write(p[1], &num, sizeof(int));
	}
}

int main()
{
	pid_t pid;
	
	char buf[1024];
	int num;
	
	//Activo el manejador del hijo para SIGUSR1 y SIGUSR2
	//prepara al proceso para que cuendo llegue esa señal ejecute manejador_hijo
	signal(SIGUSR1, manejador_hijo);
	signal(SIGUSR2, manejador_hijo);
	//Creacion de pipe antes del fork, pero despues de signal.
	//Creamos un solo pipe
	pipe(p);

	srand(time(NULL));  //***Inciar el generador de numeros aleatorios con una nueva semilla
	//Creción del duplicado
	pid = fork();
	
	if(pid == 0)
	{
		//Proceso hijo
		printf("Hola, soy el hijo\n");
		close(p[0]); //Cierro el extremo de lectura de la tubería.
		while(1);  //Bucle infinito. El hijo solo hará algo cuando le llegue una señal.
	}
	else
	{
		//Proceso padre
		printf("Hola, soy el padre\n");
	    close(p[1]); // cierro el extremo de escritura en el pipe
		while(fgets(buf,1024,stdin) != NULL)
		{			
			//Cada vez que se lee una linea por el teclado se envia una señal al hijo
			//Y se lee de la tubería
			kill(pid, SIGUSR1);	//Envia señal al hijo		
			read(p[0], &num, sizeof(int));
			printf("%d\n", num);
		}
		
		//Cuando se recibe un EOF (Ctrl+D por el teclado), se sale del bucle y se indica al hijo que termine
		kill(pid, SIGUSR2);
		wait(NULL);

		exit(0);
	}
}
