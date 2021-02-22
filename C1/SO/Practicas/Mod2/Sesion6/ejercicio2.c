#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    if (argc != 4){
        printf("Error en la llamada.\nEjecución correcta: binario programa1 \"|\" archivo\n");
        exit(EXIT_FAILURE);
    }

    int fd_in, fd_out;

    if (strcmp(argv[2],"|") == 0){
        close(STDOUT_FILENO);
        fcntl(fd_out, F_DUPFD, STDOUT_FILENO);
        execlp(argv[1],argv[1],NULL);
        close(STDIN_FILENO);
        fcntl(fd_in, F_DUPFD, fd_out);
        execlp(argv[3],argv[3],NULL);
    }
    else{
        printf("%s no es un carácter de operación válido.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
}