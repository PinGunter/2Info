#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
    pid_t pid = getpid();
    int fd[2], n = 0, fdr;
    char buffer [64], name[1024], result[1024];
    int leidos;
    umask(0);
    
    if (pipe(fd) != 0){
        perror("Error en pipe");
        exit(EXIT_FAILURE);
    }


    for (int i=0; i < argc && pid != 0; i++){
        if ((pid = fork()) == 0){ //codigo del hijo
            close(fd[0]);
            dup2(fd[1],STDOUT_FILENO);
            execlp("du","-k",argv[i],NULL);

        } else if (pid < 0){
            perror("Error en fork()");
            exit(EXIT_FAILURE);
        }

    }
    close(fd[1]);
    while ((leidos = read(fd[0],buffer,sizeof(buffer))) > 0){
        sprintf(name,"dato_%d.txt",n);
        sprintf(result,"%s - %s",buffer, argv[n]);

        int fdr = open(name,O_CREAT | O_WRONLY | O_TRUNC, 0666);
        write(fdr,result,sizeof(fdr));

        write(STDOUT_FILENO,buffer,leidos);
        n++;

    }
    wait(NULL);
}