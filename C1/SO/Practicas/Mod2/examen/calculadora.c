#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>


struct calculo{  
    int a;
    int b;
    int op;
};


int main(int argc, char * argv[]){
    if (setvbuf(stdout,NULL,_IONBF,0)){
		perror("\nError en setvbuff");
		exit(EXIT_FAILURE);
	}
    printf("calculadora: empieza\n");
    umask(0);
    struct calculo recibido;
    char nfifoe[] = "FIFOs"; //la entrada de calculadora era la salida del cliente
    if (mkfifo(nfifoe,0666) < 0){
        perror("error creanfo fifo");
        exit(EXIT_FAILURE);
    }
    int fdfifoe;
    if ((fdfifoe = open(nfifoe,O_RDONLY)) < 0){
        perror("error abriendo fifo\n");
        exit(EXIT_FAILURE);
    }
    
    char nfifos[] = "FIFOe"; //la salida de la calculadora era la entrada del cliente
    if (mkfifo(nfifos,0666)){
        perror("error creanfo fifo");
        exit(EXIT_FAILURE);
    }
    int fdfifos;
    if ((fdfifos = open(nfifoe,O_RDONLY)) < 0){
        perror("error abriendo fifo\n");
        exit(EXIT_FAILURE);
    }
    printf("FIFO creados\n");
    int leidos;
    int res;
    while (1){
        leidos = read(fdfifoe,&recibido,sizeof(recibido));
        printf("leyendo datos del fifo\n");
        if (recibido.op == 1){
            res = recibido.a + recibido.b; 
        } else if (recibido.b == 2){
            res = recibido.a * recibido.b;
        }
        printf("voy a escribir en el fifo\n");
        write(fdfifos,&res,sizeof(int));
        printf("he escrito en el fifo\n");
    }
    
    printf("finalizando\n");
    close(fdfifoe);
    close(fdfifos);
    return 0;

}