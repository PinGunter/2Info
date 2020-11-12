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
#include <string.h>
const int num_bytes = 80;

int main(int argc, char *argv[])
{
	int fdin;  // entrada.txt
	int fdout; // salida.txt
	char buffer[num_bytes];
	int leidos;
	int cont = 1;
	char bloque[20];
	char cadena[] = "El numero de bloques es %d\n";
	char salida[strlen(cadena)+1];


	if (argc == 2)
	{
		if ((fdin = open(argv[1], O_RDONLY, S_IRUSR | S_IWUSR)) < 0)
		{
			printf("\nError %d en open", errno);
			perror("\nError en open");
			exit(-1);
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

	lseek(fdout,strlen(cadena)+2,SEEK_SET);

	while ((leidos = read(fdin,buffer,num_bytes+1)) != 0){
		sprintf(bloque,"\nBloque %d\n",cont);
		write(fdout,bloque,strlen(bloque));
		write(fdout,buffer,leidos);
		cont++;
	}

	lseek(fdout,0,SEEK_SET);
	sprintf(salida,cadena,cont-1);
	write(fdout,salida,strlen(salida));


	close(fdin);
	close(fdout);
	return 0;
}
