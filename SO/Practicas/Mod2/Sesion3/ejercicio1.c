/*

 Ejercicio 3.1 : Trabajo con la llamada al sistema fork

 Implementa un programa en C que tenga como argumento un número entero.
 Esteprograma debe crear un proceso hijo que se encargará de comprobar si
 dicho número es unnúmero par o impar e informará al usuario con un mensaje
 que se enviará por la salida estándar.A su vez, el proceso padre comprobará si
 dicho número es divisible por 4, e informará si lo es ono usando igualmente la salida estándar.

*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {    // Comprobacion de los argumentos de la funcion main
        printf("Formato %s <num>", argv[0]);
		exit(-2);
	}

	int num = atoi(argv[1]);    // Numero pasado por parametro convertido a entero

    pid_t pid;

    printf("\nMensaje previo a la ejecución de fork\n\n");

    pid = fork();   // pid que devuelve la funcion fork:  0 al proceso hijo; pid del hijo al padre
    if (pid < 0) {
        perror("\nError en el fork");
        exit(-1);
    } else if (pid == 0) {
        //proceso hijo ejecutando el programa
        printf("Al hijo le ha llegado %d, y el número", num);
        if (num%2!=0) printf(" no");
        printf(" es par\n");
    } else {
        //proceso padre ejecutando el programa
        printf("El padre tiene %d, y el número", num);
        if (num%4!=0) printf(" no");
        printf(" es divisible entre 4\n");
        sleep(1);  // sleep para evitar que el proceso hijo termine antes que el padre (retoque estético)
    }
    exit(0);
}

