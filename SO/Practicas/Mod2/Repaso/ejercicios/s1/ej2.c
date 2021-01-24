#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define TAM 80
int main(int argc, char * argv[]){
    char salida [] = "salida.txt";
    char * archivo = argv[1];
    char bloque [] = "\nBloque %d\n";
    char total [] = "El número de bloques es %d\n";
    char mensaje [TAM];
    int nbloques = 1;
    char buff [TAM];
    int leidos;
    int fd_in, fd_out;

    lseek(fd_out,strlen(total+strlen(bloque)),SEEK_SET);
    fd_in = open(archivo,O_RDONLY);
    fd_out = open(salida, O_CREAT | O_WRONLY | O_TRUNC);
    while ((leidos = read(fd_in,buff,TAM)) > 0){
        sprintf(mensaje, bloque, nbloques);
        write(fd_out, mensaje, sizeof(bloque));
        write(fd_out, buff, leidos);
        nbloques++;
    }

    lseek(fd_out,0,SEEK_SET);
    sprintf(mensaje, total, nbloques);
    write(fd_out, mensaje, strlen(total));
}