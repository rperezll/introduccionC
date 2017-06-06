#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/***
- Cree 4 procesos hijos, que se quedarán a la espera de recibir alguna 
señal para comenzar a correr. Una vez creados los hijos, indicará que 
comience la carrera, con lo que uno de los hijos deberá empezar a correr.
- Cuando un hijo termina de correr (poner algún mensaje en pantalla y 
esperar un par de segundos con sleep) deberá pasar el testigo a uno de 
sus hermanos para que comience a correr, y terminará su ejecución (la 
suya propia).
- Cuando el último hijo termine de correr, el padre mostrará un mensaje 
indicando que todos los hijos han terminado.
***/

pid_t hijos[4] = {0, 0, 0, 0};  //Para almacenar los pids de los hijos
int i; // Numero de hijo, gracias a esto, se puede saber desde todos sitios el numero de hijos

void manejador_hijo(int sig);


int main()
{
	pid_t pid;

	signal(SIGUSR2, manejador_hijo); //Asocio el manejador_hijo a la señal SIGUSR2	
	
	for(i = 0; i < 4; i++)
	{
		pid = fork();
		if(pid == 0) //Al hacer fork() empieza la ejecu´ción del hijo, por lo cual... 
		//...hay que pausarlo
		{
			pause();
		}
		else
		{
			hijos[i] = pid;  //guardo el pid del hijo			
		}
	}
	
	//Una vez creados todos los hijos ordeno al último que empiece a correr
	kill(hijos[3], SIGUSR2);
	
	//Bucle para esperar que terminen los 4 hijos (Para que hay que usarlo??)
	for(i = 0; i < 4; i++)
	{
		wait(NULL);
	}
	printf("Todos los hijos terminaron\n");
	
	return 0;
}

//Manejador del hijo: cuando le llega la señal se pone a correr
//Cuando un hijo termina indica al siguiente que corra mediante una señal
//Para ello el hijo necesita saber el pid del hermano al que debe enviar la señal
//Podemos identificar el orden en que se creo cada hijo mediante el valor que tenga la variable i
//Los hijos no conocen los pids de todos sus hermanos
//El hijo 3 conoce los pids del 2, 1 y 0
//El hijo 2 conoce los pids del 1 y el 0
//El hijo 1 conoce el pid del 0
//El hijo 0 no conoce ningún pid
//Por tanto el orden en que deben correr para que cada uno pueda señalar al siguiente es
//Primero el 3, luego el 2, luego el 1 y por último el 0
void manejador_hijo(int sig)
{
	printf("Soy el hijo %d con pid %d, corriendo . . . \n", i, getpid());
	sleep(1);
	if(i != 0)
	{
		printf("Terminé. Paso el testigo al hijo %d con pid %d\n",i-1, hijos[i-1]);
		kill(hijos[i-1], SIGUSR2); //Mando una señal al que le toca correr
	}
	else
		printf("Terminé!\n");

	exit(0);	
}