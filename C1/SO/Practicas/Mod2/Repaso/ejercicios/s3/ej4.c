#include<sys/types.h>	
#include<unistd.h>		
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
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
        if ((pid = fork()) < 0){
            perror("Error de fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0){ //codigo hijo
            printf("Soy el hijo %d y me voy a dormir\n", getpid());
            duracion = segundos[i];
            sleep(duracion);
            printf("Me he despertado de un sueño de %d segundos. -%d\n", duracion, getpid());   
        }
    }

    if (pid != 0){
        for (int restantes = 4; restantes >= 0; restantes--){
            pid = wait(&estado);
            printf("Mi hijo %d ha finalizado con codigo %d\n", pid, estado);
            printf("Quedan %d hijos vivos\n", restantes);
            
        }
    }
}