#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

void mimanejador(int senal)
{
	int estado;
	pid_t pid;

	pid = wait(&estado);
}

int main(int argc, char **argv)
{
	int fdfifoe, fdfifos, fdbloqueo, peticion, fdproxy;
	char nombrefifoe[1024], nombrefifos[1024], nombrefifoproxy[1024];
	pid_t pidproxy;

	signal(SIGCHLD, mimanejador);

	sprintf(nombrefifoe, "%se", argv[1]);
	sprintf(nombrefifos, "%ss", argv[1]);

	umask(0);
	mkfifo(nombrefifoe, 0644);
	mkfifo(nombrefifos, 0644);

	fdfifoe = open(nombrefifoe, O_RDWR);
	fdfifos = open(nombrefifos, O_RDWR);
	fdbloqueo = open("bloqueo.txt", O_CREAT, S_IRWXG);

	while(read(fdfifoe, &peticion, sizeof(int))) {
		pidproxy = fork();

		if (pid == 0) {
			sprintf(nombrefifoproxy, "fifo.%d", getpid());	
			mkfifo(nombrefifoproxy, 0644);		

			write(fdfifos, &pidproxy, sizeof(int));

			fdproxy = open(nombrefifoproxy, O_RDONLY);

			dup2(fdproxy, STDIN_FILENO);

			execlp("./proxy", "proxy", NULL);
		}
	}

	unlink("bloqueo.txt");
	unlink(nombrefifoe);
	unlink(nombrefifos);	
}
