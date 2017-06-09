#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

FILE * fichero_numeros;
FILE * fichero_salida;
FILE * p;
char buf [4096];
char buf2 [4096];
char cadena [4096];
int i;

int main (int argc, char *argv[]){
	
	fichero_salida = fopen(argv[2],"w");
	fichero_numeros = fopen(argv[1],"r");
	pid_t pid;
	i=0;
	int fd[2];
	pipe(fd);
	pid = fork();
	if (pid == 0){ //Hijo: consumidor
		p=fdopen(fd[0],"r");
		close(fd[1]);
		while (fgets(buf,4096,p) != NULL){
			char * b = buf;
			i++;
			if (*(int *)b % 2 == 0){ //si es par...	
				//strcpy(cadena,i); //i entero, habría que pasarlo a cadena.
				//strcat(cadena,": ");	
				//strcat(cadena,buf);	
				//strcat(i,buf);
				
				fputs(buf,fichero_salida);
			}
		}
	}else{	//Padre: productor
		close(fd[0]);
		p = fdopen(fd[1],"w");
		while ( fgets(buf,4096, fichero_numeros) != NULL){
			fputs(buf,p);
			fflush(p);		
		}		
	}
}	
