#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Ejercicio4
char * cmd2path(char * cmd);

int main(int argc, char *argv[])  //[puntero a direccion donde esta 1,puntero a direccion donde estaria 2,puntero a direccion donde estaria 3]
{

	char *ruta;

	if(argc != 2)	//Si el número de argumentos es incorrecto
	{
	  fprintf(stderr,"Uso: %s COMANDO\n", argv[0]);
	  return 1;
	}
	else
	{
	  ruta = cmd2path(argv[1]);	//le paso el comando (ej ls)
	  if (ruta == NULL) {	//Si me devuelve null, el comando no estaria en el PATH
		fprintf(stdout,"%s no se encuentra en ningún directorio del PATH\n",argv[1]);
	  } else { //Si el comando está en el PATH
		fprintf(stdout,"%s esta en %s\n",argv[1],ruta);
	  }
	  return 0;
	} 
}

char * cmd2path(char * cmd) {
	char buf[1024];		//Creo un buffer de 1024 bits
	char * str;			//Creo un puntero que apunte a una direccion de memoria (Una ruta, un char)
	char * tokens;		//Creo otro puntero que 

	if (strchr(cmd, '/')) {		//Si encuentro una / significa que el argumento es una ruta completa
		if (!access(cmd, X_OK))	//Chequea si tiene permisos para ejecutar: 0 si tiene permisos, si no -1 [X_OK]	
	//Si uso access con !: Los valores que devuelve son: 0 si NO tengo permisos y 1 SI tengo permisos (0FALSE,1TRUE)
			return strdup(cmd);	//Devuelve el puntero que apunta a la ruta cmd
		else
			return NULL;
	}
	str = getenv("PATH");	   //busca el directorio de PATH
	if (!str) {		           //En el caso de la variable PATH no exista
		str = "/bin:/usr/bin";	//Le paso una ruta fija por defecto para que no me de error
	}

	tokens = strtok(str,":");	//Seprar la cadena str en diferentes fragmentos separados por :
	while (tokens) { //Mientras tokens siga siendo distinto de null
		printf("%s %s\n",tokens,str); 
		tokens=strtok(NULL,":"); //Para seguir en el siguiente elemento de la cadena separada por : usamos NULL como primer argumento
		if (tokens != NULL) {	 //Si str no se ha acabado == tokens!=NULL
			strcpy(buf,tokens);	 //Sobreescribe lo que hay en el buf y añade el tokens
			strcat(buf, "/");	 //Concatena en el buf "/"
			strcat(buf, cmd);	 //Concatena en el buf el cmd (comando, ej ls) tendriamos en el buf por ejemplo ruta/ls 
 
			if (!access(buf, X_OK)) {	//Chequea si tiene permisos para ejecutar, si tiene permisos para ejecutar significa que esa ruta existe!!
				return strdup(buf);	    //strdup(ruta): duplica buf y crea un puntero que apunta a ese duplicado
			}
		}	
	}
	return NULL;
}
