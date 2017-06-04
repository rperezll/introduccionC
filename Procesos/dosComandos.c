#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>    
#include <sys/stat.h>
#include <fcntl.h>

char *p_1 ="ls";
char *p_2 ="-la";

char *s_1 ="tr";
char *s_2="'d'";
char *s_3="'D'";

int main(int argc, char *argv[])
{
	//inicializamos el pid para hacer el fork()
	pid_t pid;
	//Creamos matriz de flujo de lectura y escritura del pipe
	int fd[2];
	//Creamos el pipe
	pipe(fd);
	//Creamos el primer hijo
	pid = fork();

	if(pid==0)
	{	//Hijo 1

	    dup2(fd[1], STDOUT_FILENO);
	    close(fd[0]);
	    close(fd[1]);
	    execlp(p_1,p_1,p_2,(char*) NULL);
	}
	else
	{
		//Creamos el segundo hijo
	    pid=fork();

	    if(pid==0)
	    {	//hijo 2

	        dup2(fd[0], STDIN_FILENO);
	        close(fd[1]);
	        close(fd[0]);
	        execlp(s_1, s_1, s_2, s_3,(char*) NULL);
	    }
	    else
	    {	//Padre

	        int status;
	        close(fd[0]);
	        close(fd[1]);
	        waitpid(pid, &status, 0);

	    }
	}	

}