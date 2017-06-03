#include <stdio.h>  //entrada y salida estandar
#include <stdlib.h>	
#include <string.h>


void concatena(int lineas);

int main(int argc, char *argv[])
{
	int lineas;
	
	
	if(argc == 1) //Si no le paso ningun argumento, por defecto que me muestre LAS 10 ÚLTIMAS FILAS.
	{
		lineas = 10;
		concatena(lineas);
		return 1;
	}
	else if (argc == 2) //Si existe un argumento
	{
		char *num = argv[1] + 1; //argv[1] es un puntero que al añadir +1 apunta a la siguiente posición 	
		lineas = atoi(num);
		concatena(lineas);
		return 1;
	}
}

	void concatena(int lineas) {
		int total=0;
		int  elemento1;
		char buf[1024];
		char *tokens;
		void *p1; //Puntero genérico apuntado a null
		p1 = malloc(512*sizeof(char)); //Reservo memoria para un char
		char *p1_char = (char *)p1;

		while((fgets(buf, 1024, stdin) != NULL))	//fgets devuelve un char* (Si vale null significa que no tiene 
													//mas lineas que leer) | CRL+D parar la ejecucion de stdin 
													//fgets(buf, 1024, stdin) Espera a que el usuario introduzca una 
													//linea para comenzar la iteración, stdin es como el scanner de java (entrada por teclado)
		{
			strcat(p1_char,buf); // Preguntar si usar strcat en lugar de strcopy!!!
			total++;
		}

		elemento1 = total - lineas;
		tokens = strtok(p1_char,"\n");
		int contadorTokens=0;
		
		while (tokens) { //Mientras tokens siga siendo distinto de null
			if (tokens != NULL) {
				if (elemento1 <= contadorTokens) {	 //Si str no se ha acabado == tokens!=NULL
					printf("%s\n", tokens);
				}
			}
			tokens=strtok(NULL,"\n"); //Para seguir en el siguiente elemento de la cadena separada por : usamos NULL como primer argumento
			contadorTokens++;
		}

	}