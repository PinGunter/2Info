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

int main(int argc, char * args[]){
	if (argc != 3){
		printf("Número de parámetros incorrecto.\nDebe introducir un directorio y un número octal de 4 dígitos\n");
		exit(EXIT_FAILURE);
	}
	long int permisos = strtol(args[2],0,8);
	char * directorio = malloc(strlen(args[1])*sizeof(char));
	strcat(directorio,args[1]);

	DIR * dir;
	struct dirent * direntp;
	struct stat atributos;

	dir = opendir(directorio);
	if (dir == NULL){
		printf("Error, no se puede abrir el directorio\n");
		exit(EXIT_FAILURE);
	}
	direntp = readdir(dir);	//saltamos el primero porque es el "." por tanto haciendo chmod a el todos los archivos obtiene esos permisos
							//podriamos hacer chmod en a este en lugar de hacer un bucle.
	while ((direntp = readdir(dir)) != NULL){
		umask(022);
		char nombre[500] ;
		sprintf(nombre,"%s/%s", directorio,direntp->d_name);
		if (stat(nombre, &atributos) < 0){
			printf("\nError al intentar acceder a los atributos de %s",nombre);
			perror("\nError en lstat");
			exit(EXIT_FAILURE);
	
		}
		printf("%s\t%o\t",direntp->d_name,atributos.st_mode & 0777);
		if (chmod(nombre,permisos) < 0){
			printf("%s\n",nombre);
			perror("\nError en chmod\n");
			exit(EXIT_FAILURE);
		}
		long int nuevo_permiso = (stat(nombre,&atributos) >= 0) ? atributos.st_mode : -1;
		printf("%o\n",atributos.st_mode & 0777);
	}



	if (closedir(dir) == -1) {
		printf("Error %d\n", errno);
		printf("Error en closedir\n");
		exit(-1);
	}
	free(directorio);
	return EXIT_SUCCESS;
}

