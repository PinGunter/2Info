#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ftw.h>

int tamanio = 0;
unsigned permisos = S_IXOTH | S_IXGRP;

int visitar(const char *path, const struct stat *stat
            , int flags, struct FTW *ftw)
{
    struct stat * atributos = stat;
    unsigned mascara = atributos->st_mode & 777;
    mascara = mascara & permisos;
    if (mascara){
        printf("%s\t\t\t %lu\n",path,atributos->st_ino);
        tamanio += atributos->st_size;
    }
    return 0;
}

int main(int argc, char * argv[]){
     if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0){
        perror("ntfw");
    }
    printf("Tamaño de %d bytes\n", tamanio);
}