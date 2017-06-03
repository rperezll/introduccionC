#!/bin/bash

#Comprobación de argumentos (Simpre al principio)
if test $# -gt 1									#Si tiene más de 1 argumento, error...
then
	echo "Uso: \"$0 directorio\", o \"$0\" para buscar en el directorio actual"
	exit 1										#Error 1: Finalizacion con error (Exit 0: finalización correcta)

elif test $# -eq 1									#else if, si el número de argumentos es igual a 1
then
	if test -d $1									#$1 existe y es un directorio
	then
		WDIR=$1

	else										#Si no existe o no es un directorio

		echo "$1 no existe o no es un directorio"
		exit 2
	fi
else											#Si no hay argumentos, se pone directorio actual (./ = este directorio
	WDIR="./"
fi

for FILE in `find $WDIR -name "*.sh"` 							#Recorre todos los archivos que tengan .sh del directorio $WDIR
do
	chmod u+x $FILE									#Dar permisos: al usuario le doy (+) ejecucion
done
