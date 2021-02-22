#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *entrada;
	struct stat atributos;
	char pathname[512];
	int permisosNuevos, permisosAntiguos;

	dir = opendir(argv[1]);

	permisosNuevos = strtol(argv[2], NULL, 8);

	while((entrada = readdir(dir)) != 0) {
		sprintf(pathname, "%s/%s", argv[1], entrada->d_name);
		lstat(pathname, &atributos);

		permisosAntiguos = atributos.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);
		
		if (strcmp(entrada->d_name, ".") && strcmp(entrada->d_name, "..")) {
			if (chmod(pathname, permisosNuevos) == 0) {
				printf("%s : %o %o\n", entrada->d_name, permisosAntiguos, permisosNuevos);
			} else {
				printf("%s : %d %o\n", entrada->d_name, errno, permisosNuevos);
			}
		}
	}

	closedir(dir);
}