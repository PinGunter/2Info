#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char * argv[]){
    if (argc != 3){
        perror("Número de argumentos incorrecto\n");
        exit(EXIT_FAILURE);
    }

    struct dirent * entrada;
    struct stat atributos;
    char nombre[512];
    DIR * dir = opendir(argv[1]);
    unsigned nuevos = strtol(argv[2],NULL,8);
    unsigned antiguos;
    while ((entrada = readdir(dir))!=0){
        sprintf(nombre,"%s/%s",argv[1],entrada->d_name);
        lstat(nombre,&atributos);
        antiguos = atributos.st_mode & (S_IRWXU | S_IRWXO | S_IRWXG); // & 0777

        if (strcmp(entrada->d_name, ".") && strcmp(entrada->d_name, "..")){
            if (chmod(nombre, nuevos) == 0){
                printf("%s : %o -> %o\n", entrada->d_name, antiguos, nuevos);
            } else{
                printf("%s : %d  %o\n", entrada->d_name, errno, nuevos);
            }
        }


    }

    closedir(dir);
    
}