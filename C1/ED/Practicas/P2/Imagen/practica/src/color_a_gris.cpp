/**
 * @file main.cpp
 * @brief archivo que se encarga de transformar imagenes a color a escala de grises
 * @author Salvador Romero Cortés
 **/
#include <iostream>
#include <imagenES.h>
#include <funciones_imagen.h>
using namespace std;
/**
 * @brief funcion principal del programa. Se encarga de la ejecución del programa
 * @param argc numero de argumentos pasados por la terminal
 * @param args parejas de nombres de imagenes [imagen.ppm imagen.pgm]
 **/
int main(int argc, char *args[]){   
    //comprobamos que el número de argumentos sea válido
    //esto es un numero de argumentos impar
    if (argc % 2 == 0 || argc < 3)
        error("Número de argumentos incorrectos.\nLa ejecución debe ser color_a_gris imagen.ppm imagen.pgm...");
    for (int i=1; i < argc-1; i++){
        if (LeerTipoImagen(args[i]) == TipoImagen::IMG_PPM)
            colorAGris(args[i],args[i+1]);
        
    }
}

