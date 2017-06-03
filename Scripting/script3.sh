#!/bin/bash

											#Comprobación de argumentos (Simpre al principio)
if test $# -gt 1									#tiene mas de 1 argumento 
then
	echo "Uso: \"$0 directorio\", o \"$0\" para buscar en el directorio actual"
	exit 1										#Error 1: Finalizacion con error (Exit 0: finalización correcta)

#--------------------------------------

elif test $# -eq 1									#else if, si el número de argumentos es igual a 1
then
	if test -d $1
	then
		WDIR=$1
	else
		echo "$1 no existe o no es un directorio"
		exit 2
	fi
else
	WDIR="./"
fi

find $WDIR -name "[ab]*"  | grep -v "~"	 						#Busca en el directorio WDIR todos los archivos cuyo nombre empiece por a o b y no contenga ~.

