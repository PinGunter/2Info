/**
 * @file main.cpp
 * @brief archivo que ejecuta el programa principal
 * @author Salvador Romero Cortés
 **/
#include <iostream>
#include <imagenES.h>

/**
 * @todo mover funciones auxiliares y no miembros de imagen a otra cabecera
 **/
using namespace std;
/**
 * @brief funcion principal del programa. Se encarga de la ejecución del programa
 * @param argc el número de parametros pasados en la ejecucion
 * @param args el vector de los parametros pasados en la ejecucion
 **/
int main(int argc, char *args[]){   
    const char * ppm = "imagenes_entrada/peppers.ppm";
    const char * out = "imagenes_salida/prueba.pgm";
   colorAGris(ppm,out);
//    int f,c;
//    if (LeerTipoImagen(pgm) == TipoImagen::IMG_PGM){
//     byte * entrada = LeerImagenPGM(pgm,f,c);
//     Imagen in = leerVectorPGM(entrada,f,c);
//     byte * salida = new byte [f*c];
//     escribirVectorPGM(in,salida,f,c);
//     EscribirImagenPGM(out,salida,f,c);
//     delete [] entrada;
//     delete [] salida;
//    } else{
//        error("no existe el archivo");
//    }
}

