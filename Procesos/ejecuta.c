#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>


//Ejercicio1 TEMA4
void creacion(char ** argv);

//wifexited Y WEXISTATUS buscar man wait
int main(int argc, char *argv[])  //[puntero a direccion donde esta 1,puntero a direccion donde estaria 2,puntero a direccion donde estaria 3]
{

	//char *ruta;
	//char* mandato[];

	if(argc != 3){	//Si el número de argumentos es incorrecto

	  	printf("Error: Argumentos incorrectos");
		return 1;

	}else if (argc==3){

		creacion(argv); 
		return 0;

	}else{

		printf("Otro tipo de error");

	}
}

void creacion(char ** argv){
	int status;

	pid_t pid;

	pid = fork();

	if (pid < 0){	//Error
		//printf("Error");
		fprintf(stderr, "Error: %s\n", strerror(errno));
		exit(-1);	//SAlida por error

	}else if (pid==0){ //Ejecución del hijo

		printf("Se está ejecutando el Hijo"); //No se imprime.
		execvp(argv[1],argv+1); //Si la ejecución es correcta, va a la linea del wait del padre. Si no, sigue &argv[1] ó argv +1
		printf("Se ha producido un error\n");
		exit(1); //Salida por error

	}else { //Ejecución del padre

		printf("Hola, soy el padre\n");
		wait(NULL); //Espera a que el hijo termine
		printf("Terminó el wait en el padre");
		if(WIFEXITED(status) != 0){ //Si el hijo ha salido de manera natural es 0, por lo cual no entra
			if (WEXITSTATUS(status) != 0){ //Compruba algo...
				printf("El comando no se ha ejecutado correctamente en el hijo\n");
			}
		}
		printf("El hijo terminó\n");
		exit(0);	//Salida satisfactoria
	}
	
}