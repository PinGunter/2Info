#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){
    struct stat atributos;
    lstat(argv[1],&atributos);
    if (S_ISDIR(atributos.st_mode)){
        printf("%s es un directorio\n",argv[1]);
        printf("Ultima modificación: %ld\n", atributos.st_mtim.tv_sec);
    } else{
        printf("%s no es un directorio\n", argv[1]);
    }
}