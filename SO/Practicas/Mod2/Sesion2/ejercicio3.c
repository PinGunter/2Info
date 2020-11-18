#include<sys/types.h>
#include<unistd.h> 
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#define TRUE 1
#define FALSE !TRUE

long int permisos = S_IXOTH | S_IXGRP; //Permisos de ejecucion de grupo y de otros
int tamanio = 0;
void recorrer(const char * path){
    struct dirent* file;
    struct stat atributo;
    DIR * directory = opendir(path);
    if (directory == NULL){
        printf("Error al leer el directorio\n");
        exit(EXIT_FAILURE);
    }
    while ((file = readdir(directory)) != NULL){
        if (!(file->d_name[0] == '.' && (file->d_name[1] == '.'  || file->d_name[1] == '\0'))){
            char * nuevo = malloc(sizeof(char)*strlen(path)+(2+strlen(file->d_name)));
            sprintf(nuevo,"%s/%s",path,file->d_name);
            if (stat(nuevo,&atributo) < 0){
                printf("Erro de stat\n");
                exit(EXIT_FAILURE);
            }
            long int perm = atributo.st_mode & 777;
            long int mascara = perm & permisos;
            // printf("%s\n",nuevo);
            // printf("permisos\n%ld\t%ld\n", perm, permisos);
            // printf("mascara\n%ld\n", mascara);

            if (S_ISDIR(atributo.st_mode)){
                recorrer(nuevo);
            }
            else if (mascara){
                printf("%s %lu\n", nuevo, atributo.st_ino);
                tamanio += atributo.st_size;
            }       
            free(nuevo);
        }

    }
}


int main(int argc, char * args[]){
    if (argc != 2){
        printf("Número de parámetros incorrecto.\nDebe introducir un directorio\n");
        exit(EXIT_FAILURE);
    }
    const char * path = args[1];
    recorrer(path);
    printf("Tamano de %d\n", tamanio);
}