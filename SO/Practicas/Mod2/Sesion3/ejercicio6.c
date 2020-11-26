//Ejercicio 6. ¿Qué hace el siguiente programa?

/*
tarea5.c
Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    pid_t pid;
    int estado;
    if ((pid = fork()) < 0)
    {
        perror("\nError en el fork");
        exit(-1);
    }
    else if (pid == 0){ //proceso hijo ejecutando el programa
        if ((execl("/usr/bin/ls", "ls", "-l","/home/salva", NULL) < 0)){
            perror("\nError en el execl");
            exit(-1);
        }
    }
    wait(&estado);
    
/*
<estado> mantiene información codificada a nivel de bit sobre el motivo de
finalización del proceso hijo que puede ser el número de señal o 0 si alcanzó su finalización normalmente.
Mediante la variable estado de wait(), el proceso padre recupera el valor
especificado por el proceso hijo como argumento de la llamada exit(), pero
desplazado 1 byte porque el sistema incluye en el byte menos significativo el
código de la señal que puede estar asociada a la terminación del hijo. Por eso se
utiliza estado>>8 de forma que obtenemos el valor del argumento del exit() del
hijo.
*/
        printf("\nMi hijo %d ha finalizado con el estado %d\n", pid, estado >> 8);
        exit(0);
}

/*Lo que hace la orden execl es ejecutar el archivo que reciben como primer argumento, 
seguido de los argumentos que necesite dicho archivo para ser ejecutado. El ultimo argumento 
que reciba la funcion debe ser siempre NULL. En caso de que ocurra un error, execl devolverá -1 y 
establecerá errno al error indicado. Las tres primeras lineas que se muestra por pantalla son las 
bibliotecas compartidas necesarias para ejecutar ./ejercicio6 (este es el resultado de ejecutar la orden ldd)
La última linea que se muestra es el mensaje de la linea 21 que muestra el PID del hijo que ha ejecutado 
el proceso y el estado con el que ha acabado.
	(estado == 0) BIEN
	(ESTADO != 0) ERROR
*/