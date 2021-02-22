#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static sig_atomic_t recibida = 0;
static int contador_signal[NSIG] = {0};
static void handler(int signum)
{
    contador_signal[signum]++;
    printf("\n La señal %d se ha recibido %d veces\n", signum, contador_signal[signum]);
}

int main()
{
    if (setvbuf(stdout, NULL, _IONBF, 0))
    {
        perror("\nError en setvbuf");
    }

    struct sigaction sa;
    sa.sa_handler = handler; 

    printf("No manejo las señales 9, 19 y 20\n");
    for (int i = 1; i <= NSIG ; i++)
    {
        if (i != 9 && i != 19 && i != 20)
        sigaction(i,&sa,NULL);
    }
    while (1)
        ;
}