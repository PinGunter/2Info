#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

static sig_atomic_t recibida = 0;
static int contador_signal[64] = {0};
static void handler(int signum)
{
    printf("\n La señal %d se ha recibido %d veces\n", signum, contador_signal[signum]);
    contador_signal[signum]++;
}

int main()
{
    if (setvbuf(stdout, NULL, _IONBF, 0))
    {
        perror("\nError en setvbuf");
    }
    for (int i = 0; i < 100; i++)
        contador_signal[i] = 1;
        
    struct sigaction sa;
    sa.sa_handler = handler; 

    printf("No manejo las señales 9 y 19\n");
    for (int i = 1; i <= 64; i++)
    {
        if (i != 9 && i != 19 && i != 20)
        sigaction(i,&sa,NULL);
    }
    while (1)
        ;
}