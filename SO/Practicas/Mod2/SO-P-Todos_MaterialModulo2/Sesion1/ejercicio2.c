/**
* Tarea 2: programa lee archivo pasado como argumento (o entrada estandar) y lo abre y lee en bloques de 80 bytes. 
* Crea un fichero que muestra los datos de la entrada de 80 bytes en 80 bytes
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
const int num_bytes = 80;

int main(int argc, char *argv[])
{
	int fdin;  // entrada.txt
	int fdout; // salida.txt
	char buffer[num_bytes];
	int leidos;
	int cont = 1;
	struct stat st;
	int size;


	if (argc == 2)
	{
		if ((fdin = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		{
			printf("\nError %d en open", errno);
			perror("\nError en open");
			exit(-1);
		} else{
			stat(argv[1],&st);
			size = st.st_size;
		}
	}
	else
	{
		fdin = STDIN_FILENO;
	}

	if ((fdout = open("salida.txt", O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)) < 0)
	{
		printf("\nError %d en open", errno);
		perror("\nError en open");
		exit(-1);
	}

	printf("%i",size);
	size = ceil(size*1.0/num_bytes);
	leidos = read(fdin,buffer,num_bytes+1);
	if (leidos > 0){
		char total [50];
		int tamanio = sprintf(total, "Numero total de bloques %i\n", size);
		write(fdout,total,tamanio);
	}
	while (leidos > 0)	{
		char bloque [50];
		int tamanio_bloque = sprintf(bloque, "Bloque: %i\n", cont);
		write(fdout, bloque, tamanio_bloque);
		int escritos =	write(fdout,buffer, leidos);
		cont++;
		leidos = read(fdin,buffer,num_bytes+1);
	}
	//ponemos al principio el puntero de escritura
	close(fdin);
	close(fdout);
	return 0;
}
