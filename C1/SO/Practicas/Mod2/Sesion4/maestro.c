#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int minA, maxA;
	int minB, maxB;
	int fdE1[2], fdE2[2], fdM[2];
	pid_t PID1, PID2;
	int primo;

	if (argc != 3) {
		printf("Sintaxis de ejecucion incorrecta\n");
		exit(-1);
	}

	minA = strtol(argv[1], NULL, 10);
	maxB = strtol(argv[2], NULL, 10);
	maxA = (minA + maxB) / 2;
	minB = maxA + 1;

	pipe(fdE1);
	pipe(fdE2);
	pipe(fdM);

	if ((PID1 = fork()) == 0) {
		close(fdE2[0]);
		close(fdE2[1]);
		close(fdE1[1]);
		close(fdM[0]);

		dup2(fdE1[0], STDIN_FILENO);
		dup2(fdM[1], STDOUT_FILENO);
		
		execl("./esclavo", "esclavo", NULL);
	} else if ((PID2 = fork()) == 0) {
		close(fdE1[0]);
		close(fdE1[1]);
		close(fdE2[1]);
		close(fdM[0]);

		dup2(fdE2[0], STDIN_FILENO);
		dup2(fdM[1], STDOUT_FILENO);

		execl("./esclavo", "esclavo", NULL);
	} else {
		close(fdE1[0]);
		close(fdE2[0]);
		close(fdM[1]);

		write(fdE1[1], &minA, sizeof(int));
		write(fdE1[1], &maxA, sizeof(int));

		write(fdE2[1], &minB, sizeof(int));
		write(fdE2[1], &maxB, sizeof(int));

		while((read(fdM[0], &primo, sizeof(int))) != 0) {
			printf("%d\n", primo);
		}
	}

	return 0;
}