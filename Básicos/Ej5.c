#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int lineas;
	char buf[1024];
  	int cuenta = 0;
	
	if(argc == 1) //Si no le paso ninguna argumento, por defecto que me muestre las 3 primeras lines, lineas=10
	{
		lineas = 10; 
	}
	else if (argc == 2) //Si existe un argumento
	{
		char *num = argv[1] + 1; //argv[1] es un puntero a apunta al comienzo de la cadena (-), ese mismo puntero +1 apunta al numero (N)	
		lineas = atoi(num);		
	}
	else
	{
		printf("Uso: \"%s -N\" para ver las N primeras líneas, o \"%s\" para las 10 primeras líneas\n", argv[0], argv[0]);
		return 1;
	}
	
  	
	while((cuenta < lineas) && (fgets(buf, 1, stdin) != NULL))	//fgets devuelve un char* (Si vale null significa que no tiene mas lineas que leer) | CRL+D para la ejecucion de stdin 
	//fgets(buf, 1024, stdin) Espera a que el usuario introduzca una linea para comenzar la iteración, stdin es como el scanner de java (entrada por teclado)
	{
		printf("%s", buf); 
		cuenta++;  
	}
	
	return 0;	
}
