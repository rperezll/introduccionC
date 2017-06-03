#! /bin/bash

#Comprobación de argumentos (Simpre al principio)
if test $# -ne 1	#No tiene argumentos
then
	echo "Uso: \"$0 nombre_archivo\""
	exit 1
fi

FILE=$1
FOUND=0

for DIR in `echo $PATH | tr ':' '\n'` 
do
	STRING=`find  $DIR -name $FILE` #Busca el archivo que se llame $FILE
	if ! test -z $STRING  #Cuando el tamaño de STRING no (!) es 0
	then
		echo "$FILE está en $STRING"
		FOUND=1
	fi
done

if test $FOUND -eq 0 #Si FOUND sigue valiendo 0, Entonces no se encontró nada.
then
	echo "$FILE no se encuentra en ningún directorio del PATH"
	exit 2
fi
