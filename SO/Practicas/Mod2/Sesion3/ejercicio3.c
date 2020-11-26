/*Ejercicio 3. Indica qué tipo de jerarquías de procesos se generan mediante la ejecución de cada
uno de los siguientes fragmentos de código. Comprueba tu solución implementando un código
para generar 20 procesos en cada caso, en donde cada proceso imprima su PID y el del padre,
PPID.*/

/*la orden FORK() crea un nuevo proceso (hijo) idéntico en código y datos al proceso que ha rea-
 * lizado la llamada (padre). Sin embargo, si alguno de los dos procesos alterase alguna varia-
 * ble, el cambio sólo repercutiría en su copia local, ya que NO COMPARTEN MEMORIA. El proceso
 * padre hereda el pid del hijo, mientras que el hijo recibe un 0.
 */

#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){

    const int nprocs = 20;
    pid_t childpid;

//TIPO 1: En la jerarquia de tipo 1 un padre crea a un hijo, pero los hijos son de padres distintos.
    for(int i=0 ; i < nprocs ; i++){
        if((childpid=fork()) < 0){
            fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
            exit(-1);
        }
        if(childpid){
            printf("Child: %d   \nFather: %d\n", getpid(), getppid());    //Salida para comprobar los PID del proceso y de su padre
            break;
        }
    }

/*
    //TIPO 2: En la jerarquia de tipo 2 un padre crea varios hijos, pero los hijos son del mismo padre
    for(int j = 0; j < nprocs; j++){
        if((childpid=fork()) < 0){
            fprintf(stderr, "Could not create child %d: %s\n", j, strerror(errno));
            exit(-1);
        }
        if(!childpid){
            printf("Child: %d   \nFather: %d\n", getpid(), getppid());    //Salida para comprobar los PID del proceso y de su padre
            break;
        }
    }
    */

   exit(-1);
}
