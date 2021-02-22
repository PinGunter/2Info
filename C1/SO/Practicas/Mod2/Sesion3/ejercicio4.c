/**
 * @brief Ejercicio 4 Sesión 3 Mod2 SO
 * @author Salvador Romero Cortés
 * @author Alberto Palomo Campos
 * @author Alejandro Rueda López
 * @author Fernando Pastrana Gomez
 * @author Rodrigo Ibáñez Blanco
 **/

#include<sys/types.h>	
#include<unistd.h>		
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <signal.h>
int main(int argc, char *argv[]){
    //pid_t pid[5];   
    pid_t pid = getpid();
    int estado;
    int segundos[5];
    struct timeval tm;
    gettimeofday(&tm,NULL);
    srandom(tm.tv_sec + tm.tv_sec*1000000ul);
    int duracion;

    for (int i=0; i < 5; i++){
        segundos[i] = random() % 5;
    }


    for (int i=0; i < 5 && pid > 0; i++){
        if((pid = fork()) < 0){
             perror("Error al crear niños\n");
             exit(EXIT_FAILURE);
        }
              
        if (pid == 0){    //Esto lo ejecuta el niño
            printf ("Soy el hijo %d y me voy a dormir\n", getpid());
            duracion = segundos[i];
            sleep(duracion);
            printf("Hijo %d ha dormido por %d segundos\n",getpid(), duracion);
            //exit(0);
        }
    }

    if (pid != 0){ // esto lo ejecuta el padre
        for(int contador_ninios_por_morir = 4; contador_ninios_por_morir>=0; contador_ninios_por_morir--){
        pid = wait(&estado);
        printf("Acaba de finalizar mi hijo con PID: %d\n", pid);
        printf("Sólo me queda %d hijos vivos\n",contador_ninios_por_morir);
    }
}
    
    //parece que funciona pero con while 
    // do{
    //     pid = fork();
    //     if (pid > 0 ){
    //         ninio_muerto = wait(&estado);
    //         printf("Acaba de finalizar mi hijo con PID: %d\n", ninio_muerto);
    //         printf("Sólo me queda %d hijos vivos\n",contador_ninios_por_morir);
    //     }
    //     else if (pid == 0){
    //         printf ("Soy el hijo %d\n", getpid());
    //         printf("Me voy a dormir\n");
    //         sleep(segundos[contador_ninios_por_morir]);
    //         //contador_ninios_por_morir--;
    //     }
    //     else{
    //         printf ("Error al crear hijos\n");
    //     }
    // } while ((contador_ninios_por_morir--) > 0 && pid > 0);


    // este funciona mas o menos

    // pid = getpid();
    // for (int i=0; i < 5 && pid != 0; i++){
    //     pid = fork();
    //     if (pid == 0)
    //         printf ("Soy el hijo %d\n", getpid());
    //     else{
    //         ninio_muerto = wait(&estado);
    //         printf("Acaba de finalizar mi hijo con PID: %d\n", ninio_muerto);
    //         printf("Sólo me queda %d hijos vivos\n",contador_ninios_por_morir-i-1);
    //     }
    // }

    
    
    // }

    return EXIT_SUCCESS;
}