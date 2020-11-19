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
int n_reg = 0;
void recorrer(const char * path){
    struct dirent* file;
    struct stat atributo;
    DIR * directory = opendir(path);
    if (directory == NULL){
        printf("Error al leer el directorio\n");
        exit(EXIT_FAILURE);
    }
    while ((file = readdir(directory)) != NULL){
        if (strcmp(file->d_name,".") && strcmp(file->d_name,"..")){
            char * nuevo = malloc(sizeof(char)*strlen(path)+(2+strlen(file->d_name)));
            sprintf(nuevo,"%s/%s",path,file->d_name);
           
            if (stat(nuevo,&atributo) < 0){
                printf("Erro de stat\n");
                exit(EXIT_FAILURE);
            }
            long int perm = atributo.st_mode & 777;
            long int mascara = perm & permisos;
       
            if (S_ISDIR(atributo.st_mode)){
                recorrer(nuevo);
                closedir(directory);
            }
            else if (mascara){
                printf("%s %lu\n", nuevo, atributo.st_ino);
                if (S_ISREG(atributo.st_mode)){
                    n_reg++;
                    tamanio += atributo.st_size;
                }
            }       
            free(nuevo);
        }

    }
}


int main(int argc, char * args[]){
    char * path;
    if (argc == 2)
        path = args[1];
    else
        path = ".";
    
    recorrer(path);
    printf("Hay %d archivos regulares con los permisos de ejecución para grupos y otros\n", n_reg);
    printf("Tamaño de %d bytes\n", tamanio);
}