#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>


/****
-El proceso padre y el proceso hijo se comunicarán de forma 
bidireccional utilizando tuberías.
-El proceso padre leerá líneas de la entrada estándar y las
enviará por una tubería al proceso hijo.
-El proceso hijo leerá por una tubería el texto que le envía 
el padre, lo transformará todo a letras mayúsculas y se lo 
enviará al padre por otra tubería.
****/
/*
p_padre[0] -> lectura
p_padre[1] -> Escritura
*/


int main(int argc, char **argv)
{
    pid_t pid;

    int p_padre[2]; //Tubería en la que escribe el padre
    int p_hijo[2];  //Tubería en la que escribe el hijo

    char buf[1024];
    
    FILE *p_p, *p_h;  //variables para manejar las tuberías con fputs y fgets

    //Siempre que queramos usar un pipe con nuestro hijo SIMPRE antes del fork()
    pipe(p_padre);
    pipe(p_hijo);
    
    pid = fork();

    if (pid < 0) { /* Error */
		fprintf(stderr, "Falló el fork().\n%s\n", strerror(errno));
		exit(1);

    } else if (pid == 0) { //Hijo 1
    	//Cierro los extremos de las tuberías que no usa el hijo
    	close(p_padre[1]); //Escritura del padre
    	close(p_hijo[0]);  //Lectura del hijo
    	p_p = fdopen(p_padre[0], "r");  //Lectura en el pipe del padre 
    	p_h = fdopen(p_hijo[1], "w");  //Escritura en pipe del hijo
        printf("Hola soy el hijo\n");
    	//Con lo anterior, he leido la frase en el pipe del padre y he escrito en mayusculas la misma frase en el pipe del hijo
    	while( fgets(buf, 1024, p_p) != NULL ) { //El hijo lee del padre mediante el flujo p_p
    		int longitud = strlen(buf); //Calculo la longuitud de la cadena
    		int i;    
    		for(i = 0; i < longitud; i++) {   //Sobrescribo el buffer con la nueva cadena 
    			buf[i] = toupper(buf[i]); //toupper pasa la cadena a mayúsculas
		}
		fputs(buf, p_h);  //El hijo envia el por el flujo p_h para que el padre reciba la cadena
		fflush(p_h); //Envia
		}

    }else{ //Proceso padre
	//Cierro los extremos de las tuberías que no usa el padre
        printf("Hola soy el padre\n");
    	close(p_padre[0]); //El padre cierra la lectura del su pipe
    	close(p_hijo[1]);  //El padre, cierra la escritura del hijo
    	p_p = fdopen(p_padre[1], "w"); //quiere escribir la entrada estandar en su pipe
    	p_h = fdopen(p_hijo[0], "r"); //Quiere leer lo que escribe su hijo
    	
    	while( fgets(buf, 1024, stdin) != NULL )
    	{ //Mismo procedimiento que en el hijo, esta vez capturando la salida estandar
    		fputs(buf, p_p);
    		fflush(p_p);
    		fgets(buf, 1024, p_h);
    		fputs(buf, stdout);    	
    	}
    
    }
    
    return 0;
    
}