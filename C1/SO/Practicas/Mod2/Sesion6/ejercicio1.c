#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){
    if (argc != 4){
        printf("Error en la llamada.\nEjecución correcta: binario programa1 \"<\" | \">\" archivo\n");
        exit(EXIT_FAILURE);
    }

    int fd;
    fd = open(argv[3], O_CREAT | O_RDWR);

    if (strcmp(argv[2],"<") == 0){
        close(STDIN_FILENO);
        fcntl(fd,F_DUPFD, STDIN_FILENO);
        execlp(argv[1], argv[1], NULL);
    }
    else if (strcmp(argv[2],">") == 0){
        close(STDOUT_FILENO);
        fcntl(fd,F_DUPFD, STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);
    }
    else{
        printf("%s no es un carácter de operación válido.\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    close(fd);
}