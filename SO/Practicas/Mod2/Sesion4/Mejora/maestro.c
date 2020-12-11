#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define NUM_HIJOS 2

int main(int argc, char *argv[])
{
	int min, max, por_hijo;
	int minI, maxI;
	int fd[NUM_HIJOS][2];
	pid_t PID[NUM_HIJOS];
	int primo;
	int fd_padre[2];


	if (argc != 3) {
		printf("Sintaxis de ejecucion incorrecta\n");
		exit(-1);
	}

	min = strtol(argv[1], NULL, 10);
	max = strtol(argv[2], NULL, 10);
	por_hijo = (max-min)/NUM_HIJOS ;
	printf("Por hijo: %d\n", por_hijo);

	// creamos los cauces
	for (int i=0; i < NUM_HIJOS; i++){
		if (pipe(fd[i]) < 0){
			printf("Error pipe");
			exit(EXIT_FAILURE);
		}
	}
	pipe(fd_padre);
	int sigue = 1;
	// hacemos los forks y el trabajo de cada hijo
	for (int i=0; i < NUM_HIJOS && sigue; i++){
		if ((PID[i] = fork()) < 0 ){
			printf("Error de fork");
			exit(EXIT_FAILURE);
		} else if (PID[i] == 0){		//codigo del hijo
			printf("Soy el hijo %d\n", i);
			sigue = 0;
			close(fd[i][1]);
			close(fd_padre[0]);
			dup2(fd[i][0],STDIN_FILENO);
			dup2(fd_padre[1],STDOUT_FILENO);
			execl("./esclavo", "esclavo", NULL);
			exit(EXIT_SUCCESS);
		} else{
			dup2(fd_padre[0],STDIN_FILENO);
			minI = i*por_hijo + min;
			maxI = minI+1 + por_hijo;
			close(fd_padre[1]);
			write(fd[i][1], &minI, sizeof(int));
			write(fd[i][1], &maxI, sizeof(int));
			while ((read(fd_padre[0],&primo, sizeof(int))) > 0)
				printf("%d\n", primo);
		}
	}




	// if ((PID1 = fork()) == 0) {
	// 	close(fdE2[0]);
	// 	close(fdE2[1]);
	// 	close(fdE1[1]);
	// 	close(fdM[0]);

	// 	dup2(fdE1[0], STDIN_FILENO);
	// 	dup2(fdM[1], STDOUT_FILENO);
		
	// 	execl("./esclavo", "esclavo", NULL);
	// } else if ((PID2 = fork()) == 0) {
	// 	close(fdE1[0]);
	// 	close(fdE1[1]);
	// 	close(fdE2[1]);
	// 	close(fdM[0]);

	// 	dup2(fdE2[0], STDIN_FILENO);
	// 	dup2(fdM[1], STDOUT_FILENO);

	// 	execl("./esclavo", "esclavo", NULL);
	// } else {
	// 	close(fdE1[0]);
	// 	close(fdE2[0]);
	// 	close(fdM[1]);

	// 	write(fdE1[1], &minA, sizeof(int));
	// 	write(fdE1[1], &maxA, sizeof(int));

	// 	write(fdE2[1], &minB, sizeof(int));
	// 	write(fdE2[1], &maxB, sizeof(int));

	// 	while((read(fdM[0], &primo, sizeof(int))) != 0) {
	// 		printf("%d\n", primo);
	// 	}
	// }

	return 0;
}