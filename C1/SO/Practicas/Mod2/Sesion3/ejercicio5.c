#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define NUMHIJOS 5

int main(int argc, char *argv[])
{
	int i, j, k;
	int buffer[NUMHIJOS];
	pid_t pid = getpid();

	if(setvbuf(stdout, NULL, _IONBF, 0)){
        perror("\nError en setvbuf");
    }

    for (i = 0; i < NUMHIJOS && pid != 0; i++) {
    	pid = fork();
    	buffer[i] = pid;
    }

    if (pid == 0) { // hijos
    	printf("Soy el hijo %d\n", getpid());
    } else {		// padre
    	for (j = k = 0; j < 2; j++) {
    		for (; k < NUMHIJOS; k += 2)
    		{
    			// pid = waitpid(buffer[k], &estado, NULL);
    			pid = waitpid(buffer[k], NULL, 0);
    			i--;

    			printf("Acaba de finalizar mi hijo con PID: %d\n", pid);
        		printf("Sólo me queda %d hijos vivos\n", i);
    		}
    		k = 1;
    	}
    }

    return 0;
}