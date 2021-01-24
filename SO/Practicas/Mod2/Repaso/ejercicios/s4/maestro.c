#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#define NUM_HIJOS 5

void manejador(){
    wait(NULL);
}

int main(int argc, char * argv[]){
    int min, max, por_hijo;
	int minI, maxI;
	int fd[NUM_HIJOS][2];
	pid_t PID[NUM_HIJOS];
	int primo;
	int fd_padre[2];

    if (argc != 3){
        perror("Sintaxis incorrecta");
        exit(EXIT_FAILURE);
    }
    signal(SIGCHLD,manejador);
    min = strtol(argv[1], NULL, 10);
	max = strtol(argv[2], NULL, 10);
	por_hijo = (max-min)/NUM_HIJOS ;
	printf("Por hijo: %d\n", por_hijo);

    for (int i=0; i < NUM_HIJOS; i++){
        if (pipe(fd[i]) < 0){
            perror("Error de pipe");
            exit(EXIT_FAILURE);
        }
    }
    pipe(fd_padre);

    int sigue = 1;
    for (int i=0; i < NUM_HIJOS; i++){
        if ((PID[i] = fork()) < 0){
            perror("Error fork");
            exit(EXIT_FAILURE);
        } else if (PID[i] == 0){
            for (int j=0; j < NUM_HIJOS; j++){
                if (i != j){
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
            }
            close(fd[i][1]);
            close(fd_padre[0]);
            dup2(fd[i][0],STDIN_FILENO);
            dup2(fd_padre[1],STDOUT_FILENO);
            execlp("./esclavo", "esclavo", NULL);
        }
    }

    close(fd_padre[1]);
    for (int i=0; i < NUM_HIJOS; i++){
		minI = i * por_hijo + min;
		maxI = minI + 1 + por_hijo;

		close(fd[i][0]);

		write(fd[i][1], &minI, sizeof(int));
		write(fd[i][1], &maxI, sizeof(int));
	}

	while ((read(fd_padre[0],&primo, sizeof(int))) > 0) {
		printf("%d\n", primo);
	}


    return 0;

}