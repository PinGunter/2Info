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
#include <string.h>

const int num_bytes = 80;

int main(int argc, char *argv[])
{
	int fdin;  // entrada.txt
	int fdout; // salida.txt
	char buffer[num_bytes];
	int leidos;
	char cont = '1';
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

	size = size / num_bytes;
	printf("%i",size);
	char tamanio = size + '0';
	leidos = read(fdin,buffer,num_bytes+1);
	if (leidos > 0){
		char total [] = "Numero total de bloques: ";
		write(fdout, total, sizeof(total)-1);
		write(fdout,&tamanio,1);
		write(fdout,"\n",1);
	}
	while (leidos > 0)	{
		char bloque [] = "Bloque ";
		write(fdout,bloque,sizeof(bloque)-1);
		write(fdout,&cont,1);
		write(fdout,"\n",1);

		int escritos =	write(fdout,buffer, leidos);
		cont++;
		leidos = read(fdin,buffer,num_bytes+1);
	}
	//ponemos al principio el puntero de escritura
	cont--;
	lseek(fdout,-cont*num_bytes,SEEK_CUR);
	char bloque [] = "El numero de bloque es ";
	write(fdout,bloque,sizeof(bloque)-1);
	write(fdout,&cont,1);
	write(fdout,"\n",1);	
	close(fdin);
	close(fdout);
	return 0;
}
