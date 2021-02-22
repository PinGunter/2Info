// LAS PARTES NUEVAS DE ESTE EJERCICIO TENDRAN UN COMENTARIO //* 
// AL FINAL DE CADA LINEA NUEVA
// Este ejercicio esta hecho sobre una version no actualizada del ejercicio2.
// Igualmente, está hecho el ejercicio 3 sobre esta version

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/file.h>


struct calculo{  
    int a;
    int b;
    int op;
};


int main(int argc, char * argv[]){
    umask(0);
    struct calculo recibido;
    char nfifoe[] = "FIFOs"; //la entrada de calculadora era la salida del cliente
    mkfifo(nfifoe,0644);
    int fdfifoe = open(nfifoe,O_RDONLY);
    
    char nfifos[] = "FIFOe"; //la salida de la calculadora era la entrada del cliente
    mkfifo(nfifos,0644);
    int fdfifos = open(nfifos,O_RDONLY);
    
    int leidos;
    int res;
    umask(0); //*
    int fd_historico;//*
    if ((fd_historico = open("historico.txt",O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0){//*
        perror("Error creando historico");//*
        exit(EXIT_FAILURE);//*
    } //*

    char texto[512]; //*;
    while ((leidos = read(fdfifoe,&recibido,sizeof(recibido))) > 0){
        if (recibido.op == 1){
            res = recibido.a + recibido.b; 
        } else if (recibido.b == 2){
            res = recibido.a * recibido.b;
        }
        write(fdfifos,&res,sizeof(int));
        flock(fd_historico,F_WRLCK); //*
        char op = (recibido.op == 1) ? '+' : '*'; //*
        sprintf(texto,"%d%c%d = %d\n",recibido.a,op,recibido.b,res); //*
        write(fd_historico,texto,sizeof("%d%c%d = %d\n")); //*
        flock(fd_historico,F_UNLCK); //*
    }

    close(fdfifoe);
    close(fdfifos);
    close(fd_historico); //*
    return 0;

}