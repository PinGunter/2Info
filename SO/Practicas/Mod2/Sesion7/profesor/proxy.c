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

int main(int argc, char **argv)
{
	int fdbloqueo, leidos;
	char buffer[1024], nombrefifoproxy[1024];
	FILE *tmp;
	struct flock cerrojo;

	tmp = tmpfile();

	fdbloqueo = open("bloqueo.txt", O_RDWR);

	while((leidos = read(STDIN_FILENO, buffer, 1024)) > 0) {
		fwrite(buffer, sizeof(char), leidos, tmp);
	}

	cerrojo.l_type = F_WRLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	fcntl(fdbloqueo, F_SETLKW, &cerrojo);
	// flock(fdbloqueo, F_WRLCK);

	while((leidos = fread(buffer, sizeof(char), 1024, tmp)) > 0) {
		write(STDOUT_FILENO, buffer, leidos);
	}

	// flock(fdbloqueo, F_UNLCK);
	cerrojo.l_type = F_UNLCK;
	cerrojo.l_whence = SEEK_SET;
	cerrojo.l_start = 0;
	cerrojo.l_len = 0;
	fcntl(fdbloqueo, F_SETLKW, &cerrojo);

	sprintf(nombrefifoproxy, "fifo.%d", getpid());	
	unlink(nombrefifoproxy);
}
