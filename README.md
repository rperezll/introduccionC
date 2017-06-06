# introduccionC
Ejemplos introductorios al lenguaje + Scripts Linux

## ./Scripting

| Ejercicio | Descripción |
| --------- | ----------- |
| script1.sh | Que busque cuales de los ficheros del directorio /bin no tienen página de manual en la sección 1 |
| script2.sh | A partir de un directorio que recibe como argumento, añada permisos de ejecución de forma recursiva a todos los archivos con extensión .sh |
| script3.sh | Que muestre recursivamente todos los ficheros y directorios cuyo nombre empiece por *a* o por *b* y que no contenga el caracter "~", a partir de un directorio que se pasa por argumentos |
| script4.sh | Que busque en todos los directorios en la variable de entorno *PATH* el nombre de un archivo que se le pasa como parámetros |
| script5.sh | A partir de un directorio que recibe como argumento, busque los dos archivos de más tamaño y muestre su nombre y su tamaño |

## ./Básicos

| Ejercicio | Descripción |
| --------- | ----------- |
| Ej1.c | Funcionamiento de mandato sep() |
| Ej2.c | Muestre la cadena pasada como argumentos al revés (invert) |
| Ej3.c | Que cambie el directorio actual (si no se le pasa un directorio por argumentos, el cambio se realiza al directorio HOME) |
| Ej4.c | Buscar en todos los directorios contenidos en la variable PATH el nombre de un mandato pasado por argumentos |
| Ej5.c | Funcionamiento de myhead()  |
| Ej6.c | Funcionamiento de myTail() |

## ./Procesos

| Ejercicio | Descripción |
| --------- | ----------- |
| aleatorios.c | Cree un proceso hijo que será el encargado de generar números aleatorios. Este proceso hijo escribirá en un pipe un número aleatorio del 0 al 10 cada vez que reciba una señal por parte del padre -> El proceso padre lee líneas de la entrada estándar y por cada línea que lea solicitará al hijo que le envíe un número aleatorio, lo leerá y lo imprimirá en pantalla -> Cuando el proceso  padre termine de leer líneas de la entrada estándar, enviará una señal al hijo para que este terminé, y después terminará el padre. |
| dosComandos.c | Que ejecute dos comandos con sus respectivos argumentos, y redireccione la salida estándar del primero a la entrada estándar del segundo. Los comandos y sus argumentos no es necesario que se pasen como argumentos al programa, si no que pueden ir directamente escritos en el código del programa para no complicar demasiado el problema. Para ello el programa debe crear dos procesos hijo (cada hijo ejecutará uno de los comandos), y utilizando pipes se harán las redirecciones necesarias. |
| ejecuta.c | Que reciba como argumentos el comando y las opciones del comando que se quiere ejecutar. El programa debe crear un proceso hijo que ejecute el comando con las opciones correspondientes mostrando un mensaje de error en el caso de que no se realizase correctamente la ejecución. El padre debe esperar a que el hijo termine e informar si se produjo alguna anomalía en la ejecución del hijo.|
| mayusculas.c | Cree un proceso hijo -> El proceso padre y el proceso hijo se comunicarán de forma bidireccional utilizando tuberías -> El proceso padre leerá líneas de la entrada estándar y las enviará por una tubería al proceso hijo -> El proceso hijo leerá por una tubería el texto que le envía el padre, lo transformará todo a letras mayúsculas y se lo enviará al padre por otra tubería -> El padre imprimirá en pantalla lo que recibe del hijo. |
| relevos.c | Cree 4 procesos hijos, que se quedarán a la espera de recibir alguna señal para comenzar a correr. Una vez creados los hijos, indicará que comience la carrera, con lo que uno de los hijos deberá empezar a correr -> Cuando un hijo termina de correr (poner algún mensaje en pantalla y esperar un par de segundos con sleep) deberá pasar el testigo a uno de sus hermanos para que comience a correr, y terminará su ejecución (la suya propia) -> Cuando el último hijo termine de correr, el padre mostrará un mensaje indicando que todos los hijos han terminado. |

## ./Threads

| Ejercicio | Descripción |
| --------- | ----------- |
| cenafilosofos.c |  |
| cenafilosofos_condiciones.c |  |
| ejemplo.c |  |
| mutex.c |  |
| orden.c |   |
