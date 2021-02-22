#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>

void manejador(int s){
    wait(NULL);    
}

struct calculo{  
    //Estos van a ser comunes para todos los clientes hijos
    // puesto que el directorio que se le pasa es el mismo a todos
    // y es siempre tambien el primer archivo regular
    // por tanto a y b son comunes. Los calcularemos antes de lanzar los hijos
    // para no repetir calculos.
    // El unico distinto es op

    int a;
    int b;
    int op;
};

int main(int argc, char * argv[]){
    if (argc != 3){
        perror("Error en el número de argumentos\n");
        exit(EXIT_FAILURE);
    }
    if (setvbuf(stdout,NULL,_IONBF,0)){
		perror("\nError en setvbuff");
		exit(EXIT_FAILURE);
	}
    int nclientes; 
    char * directorio;
    DIR * dir;
    struct dirent * actual;
    pid_t pid = getpid();
    pid_t mi_pid;
    struct stat atributos_dir, atributos_archivo;
    char nombre_actual [512];
    nclientes = strtol(argv[1],NULL,10);
    directorio = argv[2];
    dir = opendir(directorio);
    signal(SIGCHLD,manejador); // nos aseguramos de que no queden procesos zombies
    
    struct calculo datos;
    datos.b = -1;
    lstat(directorio, &atributos_dir);
    if (!(S_ISDIR(atributos_dir.st_mode))){
        perror("El segundo parametro no es un directorio correcto\n");
        closedir(dir);
        exit(EXIT_FAILURE);
    }
    datos.a = atributos_dir.st_ino;
    //recorremos ahora el directorio hasta encontrar un archivo regular
    while ((actual = readdir(dir)) != NULL && datos.b == -1){ //la segunda condicion es para detenernos en el primer archivo reg.
        sprintf(nombre_actual, "%s/%s", directorio, actual->d_name);
        lstat(nombre_actual,&atributos_archivo);
        if (S_ISREG(atributos_archivo.st_mode)){
            datos.b = atributos_archivo.st_size;
        }
    }

    if (datos.b == -1){ // no se ha actualizado, por lo que no ha encontrado un archivo regular
        perror("No se ha encontrado un archivo regular\n");
        closedir(dir);
        exit(EXIT_FAILURE);
    }
    
    //Creamos un fifo para enviar datos y otro para recibir
    printf("Antes de crear fifo\n");
    umask(0);
    char nfifoe[] = "FIFOe";
    if (mkfifo(nfifoe,0666)){
        perror("error creanfo fifo");
        exit(EXIT_FAILURE);
    }
    int fdfifoe;
    if ((fdfifoe = open(nfifoe,O_RDONLY)) < 0){
        perror("error abriendo fifo\n");
        exit(EXIT_FAILURE);
    }
    
    char nfifos[] = "FIFOs";
    if (mkfifo(nfifos,0666)){
        perror("error creanfo fifo");
        exit(EXIT_FAILURE);
    }
    int fdfifos;
    if ((fdfifos = open(nfifos,O_WRONLY)) < 0){
        perror("error abriendo fifo\n");
        exit(EXIT_FAILURE);
    }
    printf("FIFO creados\n");
    //ahora que ya tenemos a y b lanzamos los hijos que generaran la operacion
    //y se comunicaran con la calculadora.
    for (int i=0; i < nclientes && pid != 0; i++){
        pid = fork(); //lanzamos hijos
        if (pid == 0){
            mi_pid = getpid();
            printf("Soy hjjo: %d\n",mi_pid);
            // Cada hijo establece su propia semilla para los numeros aleatorios
            srand((unsigned)getpid());
            datos.op = rand() % 2 + 1; //generamos numero aleatorio entre 1 y 2
            if (write(fdfifos,&datos,sizeof(datos)) < 0){
                perror("error write de hijo\n");
                exit(EXIT_FAILURE);
            }
            printf("Soy %d, he escrito en fifo\n",mi_pid);
            //ahora lee del fifo de entrada
            int res;
            if (read(fdfifoe,&res, sizeof(int)) < 0){
                perror("error lectura de hijo\n");
                exit(EXIT_FAILURE);
            }
            printf("Soy %d, he leido de fifo\n",mi_pid);
            char op = (datos.op == 1) ? '+' : '*';
            printf("Cliente: %d, operación: %d%c%d = %d\n", mi_pid,datos.a,op,datos.b,res);
        }
    }
    printf("Finalizando\n");
    closedir(dir);
    close(fdfifoe);
    close(fdfifos);
    return 0;
}