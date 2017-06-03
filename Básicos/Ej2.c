#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) //int argc: Da el tamaño del argumento
{	
	int i;

	if (argc <= 1) { //Si el único argumento es el nombre del programa
	  fprintf(stderr,"Uso: %s frase\n", argv[0]); //Mensaje de error (stderr) del programa argv[0]
	  return 1;	//Error simple
	}


	for(i = argc-1; i>0; i--) //recorremos el argumento de manera descendente (Situandonos inicialmente en la última palabra)
	{
		int j;
		int longitud;
		longitud = strlen(argv[i]);	 //Calculamos la longuitud de la palabra
		for(j = longitud-1; j >= 0; j--)	//recorremos la palabra de manera descendente
		{
			printf("%c", argv[i][j]); //escribimos letra
		}
		printf(" "); //Cuando terminamos con una palabra añadimos un espacio
	}
	printf("\n"); 	

	return 0; //Ejecución satisfactoria
}
