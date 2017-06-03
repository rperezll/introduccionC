#!/bin/bash

#Comprobación de argumentos (Simpre al principio)
if test $# -ne 0					# args < 0
then
	echo "Error. Uso: $0"				#No tiene argumentos
	exit 1						#Error 1: Finalizacion con error (Exit 0: finalización correcta)
fi

#----------Comienza ejercicio------------

for FILE in `ls -la /bin | grep "^-" `			#ls muestra la lista de directorios /bin, el for la recorre
do
	if ! test -e "/usr/share/man/man1/$FILE.1.gz"	#El mandato test permite hacer comparaciones. En este caso (test -e) dictamina si existe el directoria citado
	then
		echo "$FILE no tiene entrada de manual"
	fi
done
