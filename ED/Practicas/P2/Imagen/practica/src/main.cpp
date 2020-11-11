/**
 * @file main.cpp
 * @brief archivo que ejecuta el programa principal
 * @author Salvador Romero Cortés
 **/
#include <iostream>
#include <imagenES.h>
#include <funciones_imagen.h>


/**
 * @todo mover funciones auxiliares y no miembros de imagen a otra cabecera
 **/
using namespace std;
/**
 * @brief funcion principal del programa. Se encarga de la ejecución del programa
 * @param argc el número de parametros pasados en la ejecucion
 * @param args el vector de los parametros pasados en la ejecucion, esto es imagen_entrada,imagen_salida,min,max
 **/
int main(int argc, char *args[]){   
    // int min =  atoi(args[3]);
    // int max =  atoi(args[4]);
    // umbralizar_escala_grises(args[1],args[2],atoi(args[3]),atoi(args[4]));
    //contrastar(args[1],args[2],min,max);
    zoom(args[1],args[2],atoi(args[3]),atoi(args[4]),atoi(args[5]),atoi(args[6]));
}

