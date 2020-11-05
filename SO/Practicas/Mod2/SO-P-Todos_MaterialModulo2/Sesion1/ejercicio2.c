/**
* Tarea 2: programa lee archivo pasado como argumento (o entrada estandar) y lo abre y lee en bloques de 80 bytes. 
* Crea un fichero que muestra los datos de la entrada de 80 bytes en 80 bytes
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

const int num_bytes = 80;

int main(int argc, char * argv[]){
	int fdind; // entrada.txt
	int fdout; // salida.txt
	char buffer[num_bytes];
	int leidos; 
	int cont = 1;
	const char * mensaje = "Bloque ";
	char numero;
	if (argc == 2){
		if ((fdin = open(argv[1], 0_RDONLY, S_IRUSR | S_IWUSR)) < 0){
			printf("\nError %d en open", errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);		
		}
	}
	else{
		fdin = STDIN_FILENO;
	}
	
	if ((fdout = open("salida.txt", 0_CREAT | O_TRUNC | O_WRONGLY, S_IRUSR | S_IWUSR)) < 0){
		printf("\nError %d en open", errno);
			perror("\nError en open");
			exit(EXIT_FAILURE);
	}
	
	while (leidos = read(fdin,buffer,num_bytes) < 1){ // 0 es EOF y -1 es error
		
		write(fdout,buffer, leidos);	
	}
}	
