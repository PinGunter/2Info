#include <sys/types.h>	
#include <sys/wait.h>	
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define TAM 256

/**
 * @brief Adapta la entrada en forma de agumento para la función exec
 * @param entrada Entrada del usuario a adaptar
 * @param argv Entrada adaptada
 * @return 0 si la entrada debe ejecutarse en fg
 * @return 1 si la entrada debe ejecutarse en bg
 *
 * @note Esta adaptación sirve más concretamente para la función execvp
 *
 */
int adapta(char *entrada, char **argv);

/**
 * @brief Crea un hijo que ejecuta argv según la función exec
 * @param argv Entrada adaptada para la ejecución
 * @param plano Tipo de plano de ejecucion del programa a ejecutar (fg o bg)
 *
 * @note Esta ejecución la realiza un hijo que crea el proceso padre
 * @note Si plano = 0 se ejecuta en fg, si plano = 1 se ejecuta en bg
 *
 */
void ejecuta(char **argv, int plano);

/**
 * @file ejercicio7.c
 *
 * Trabajo con llamadas al sistema del Subsistema de Procesos POSIX 2.10 compliant
 *
 *
 * Este programa acepta nombres de programas escritos en la entrada estándar, 
 * los ejecuta en background o foreground según lo desee el usuario, y 
 * proporciona en la salida estándar el resultado de la ejecución de dichos 
 * programas. Es decir, es un shell reducido a la funcionalidad de ejecución de
 * programas.
 *
 *
 * @author Francisco Carranza
 * @date 24 de noviembre de 2020
 *
 * @note Aparecen una serie de líneas comentadas, descomentar en función de si
 * 		 se quiere dar información sobre el estado de finalización o no 
 * 		 (concretamente en la función ejecuta).
 *
 */
int main(void){

	char entrada[TAM];
	char *argv[TAM];
	int plano; // modo de ejecución (bg o fg)

	printf("\nSHELL (exit para terminar la sesion)\n");
	while(1){
		printf("carranzafr-shell > ");
		gets(entrada); // scanf("%s",entrada);
		if(strcmp(entrada, "exit") == 0){ // fin de la sesión
			printf("\n");
			exit(0);
		}
		// adaptación de la entrada del usuario para su ejecución
		plano = adapta(entrada,argv);
		ejecuta(argv, plano);
	}

	return 0;
}

int adapta(char *entrada, char **argv)
{
	int plano = 0;

	while(*entrada != '\0'){   // mientras no sea el fin de entrada
		if(*entrada == ' ')    // si entrada es un ' ' la sustityo por un '\0'
			*entrada++ = '\0';

		if(*entrada != '&')
			*argv++ = entrada; // guarda el argumento y prepara el siguiente 
		else				   // comprobación de ejecución en bg
			plano = 1;

		// Desplazamiento hasta el siguiente argumento o al final
		while(*entrada != ' ' && *entrada != '\0')
			entrada++;
	}
	*argv = '\0'; 			   // fin de la adaptación

	return plano;
}

void ejecuta(char **argv, int plano)
{
	// int estado;
	pid_t pid;

	if((pid = fork()) < 0){
		perror("\nError en el fork");
		exit(-1);
	}
	else if(pid == 0){  // proceso hijo
		if((execvp(*argv,argv) < 0)){
			perror("\nError en el execvp");
			exit(-1);
		}
	}
	else if(plano == 0)	// proceso padre
		// wait(&estado);
		wait(NULL);
}