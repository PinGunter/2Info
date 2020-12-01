#include <math.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <sys/wait.h>


int main(int argc, char * args[]){
    if (argc != 3){
        printf ("Error en la llamada.\nSe necesita un intervalo de números\n");
        exit(EXIT_FAILURE);
    } else if (atoi(args[1]) >= atoi(args[2])){
        printf ("El intervalo debe ser correcto, el primer número menor al siguiente\n");
        exit(EXIT_FAILURE);
    }

    int minimo = atoi(args[1]);
    int maximo = atoi(args[2]);
    int a,b;
    int primo = 1;
    int fd[2];
    int leido;
    pid_t PID = getpid();

    for (int i=0; i < 2 && PID > 0; i++){
        if((PID = fork()) < 0){
             perror("Error al crear niños\n");
             exit(EXIT_FAILURE);
        }
              
        if (PID == 0){    //Esto lo ejecuta el hijo
            //close(fd[0]);
            //dup2(fd[1],STDOUT_FILENO);
            //printf("hola");
            if (i==0){
                a = minimo;
                b = maximo/2;
            } else{
                a = maximo/2 +1;
                b = maximo; 
            }
            for (int j=a; j < b; j++){
                primo = 1;
                for (int k=2; k <= sqrt(j) && primo; k++){
                    if (j % k == 0){
                        primo = 0;
                    }
                }
                if (primo){
                    if (write(fd[1],&j,4) < 0)
                        printf("error write");
                    write(fd[1],"\n",1);
                }
            }
            close(fd[1]);
            _exit(EXIT_SUCCESS);
        }
    }
    char buf[80];
    if (PID != 0){ // esto lo ejecuta el padre
     //   wait(NULL); wait(NULL);
        dup2(fd[0],STDIN_FILENO);
        close(fd[1]);
        while ((leido=read(fd[0], &buf, 4)) > 0){
            write(STDOUT_FILENO, &buf, 4);
        }
        if (leido < 0)
            printf("error read\n");
        write(STDOUT_FILENO,"\n",1);
        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    
}