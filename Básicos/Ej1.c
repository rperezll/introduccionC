#include <stdio.h>
#include <stdlib.h>

//Para ejecutar .c: gcc nombre.c -o nombre

int main(int argc, char** argv) //argc: longitud del array de argumentos ; char** argv ó char* argv[] valen igual
{
	int i;
	int inicio=1;
	int fin;
	int incremento=1;
	char micadena="hola amigo";
	int mientero=4;

	switch (argc){
		case 2: 
			fin=atoi(argv[1]);	//Primer argumento argv[0] es el nombre del programa (NO VALE), argv[1] es el primer argumento
			break;
		case 3: 
			inicio=atoi(argv[1]);
			fin=atoi(argv[2]);
			break;
		case 4: 
			inicio=atoi(argv[1]);
			fin=atoi(argv[3]);
			incremento=atoi(argv[2]);
			break;
		default:
			
			printf("Cadena: %s\n, Entero : %i\n", micadena, mientero);
			//printf("Uso: \n%s Fin\n%s INICIO INCREMENTO FIN\n", argv[0],argv[0],argv[0]);
			return 1;
	}
    for (i=inicio;i<=fin;i=i+incremento){
    	printf("%d \n",i);
    }
    return 0; 	
}
