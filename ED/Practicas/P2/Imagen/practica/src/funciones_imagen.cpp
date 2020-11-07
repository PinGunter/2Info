/**
 * @file funciones_imagen.cpp
 * @author Salvador Romero Cortés
 * @brief Archivo con las definiciones de la suite de funciones sobre el @a TDA_Imagen
 */
#include <iostream> //E/S
#include <cmath> //round
#include <imagenES.h> //TDA Imagen
#include <funciones_imagen.h> //Declaraciones de las funciones

using namespace std;


// constantes para transformar de gris a color
const double ROJO_GRIS = 0.2989;
const double VERDE_GRIS = 0.587;
const double AZUL_GRIS = 0.114;


void error(string mensaje){
    cerr << mensaje << endl;
    exit(1);
}

/*     FUNCIONES SOBRE EL TIPO IMAGEN  */
Imagen leerVectorPGM(byte * vector, int filas, int columnas){
    Imagen imagen(filas,columnas);
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            imagen.asigna_pixel(i,j,vector[i*columnas+j]);
        }
    }
    return imagen;
}
//----------------------------------------------------------------
Imagen leerVectorPPM(byte * vector, int filas, int columnas){
    byte * vector_gris = new byte[filas*columnas];
    int j=0; 
    for (int i=0; i < filas*columnas; i++)
        vector_gris[i] = vector[j++]*ROJO_GRIS + vector[j++] * VERDE_GRIS + vector[j++] * AZUL_GRIS;
    Imagen gris = leerVectorPGM(vector_gris,filas,columnas);
    delete [] vector_gris;
    return gris;
}
//----------------------------------------------------------------
void escribirVectorPGM(const Imagen & img, byte * vector, int & filas, int & columnas){
    filas = img.num_filas();
    columnas = img.num_columnas();
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            vector[i*columnas+j] = img.valor_pixel(i,j);
        }
    }
}
//----------------------------------------------------------------
void colorAGris(const char * nombre_ppm, const char * nombre_pgm){
    TipoImagen primera;
    primera = LeerTipoImagen(nombre_ppm);
    if (primera != IMG_PPM)
        error("El archivo introducido no es de tipo PPM");

    int filas, columnas;
    byte *ppm = LeerImagenPPM(nombre_ppm,filas,columnas);
    Imagen color_a_gris = leerVectorPPM(ppm,filas,columnas);
    byte *pgm = new byte[filas*columnas];
    escribirVectorPGM(color_a_gris,pgm,filas,columnas);
    EscribirImagenPGM(nombre_pgm,pgm,filas,columnas);
    delete [] ppm;
    delete [] pgm;
}

//----------------------------------------------------------------

void umbralizar_escala_grises(const char* original, const char * salida,int umbral_min, int umbral_max){
    // comprobamos que el intervalo esté bien definido
    if (umbral_min >= umbral_max || umbral_min < 0 || umbral_max > 255)
        error("Intervalo de escala de grises incorrecto");

    //leemos y creamos las imagenes
    int filas, columnas;
    byte * vector_original = LeerImagenPGM(original,filas,columnas);
    Imagen img_original = leerVectorPGM(vector_original,filas,columnas);
    Imagen img_salida(img_original);

    //umbralizamos la funcion
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            if (!(img_salida.valor_pixel(i,j) >= umbral_min && img_salida.valor_pixel(i,j) <= umbral_max))
                img_salida.asigna_pixel(i,j,BLANCO);
        }
    }
    //escribimos la imagen de salida
    byte * vector_salida = new byte [filas*columnas];
    escribirVectorPGM(img_salida,vector_salida,filas,columnas);
    if (!EscribirImagenPGM(salida,vector_salida,filas,columnas)){
        delete [] vector_salida;
        delete [] vector_original;
        error("Error al escribir la imagen");
    }
    delete [] vector_salida;
    delete [] vector_original;
}

//----------------------------------------------------------------

void contrastar(const char * original, const char * salida, byte min, byte max){
    //comprobamos que min y max sean valores validos
    // if (min >= max)
    //     error("Intervalo de contraste incorrecto");
    
    //leemos y creamos las imagenes
    int filas, columnas;
    byte * vector_original = LeerImagenPGM(original,filas,columnas);
    Imagen img_original = leerVectorPGM(vector_original,filas,columnas);
    Imagen img_salida(img_original);

    //transformacion lineal:
    // t(z) = min + [((max-min)/(b-a))*(z-a)]

    //vemos que el calculo de (max-min)/(b-a) es constante en toda la imagen, por tanto
    //podemos calcularlo una única vez

    byte maximo = 0, minimo = 255;

    for (int i=0; i < img_salida.num_filas(); i++){
        for (int j=0; j < img_salida.num_columnas(); j++){
            if (img_salida.valor_pixel(i,j) > maximo) maximo = img_salida.valor_pixel(i,j);
            if (img_salida.valor_pixel(i,j) < minimo) minimo = img_salida.valor_pixel(i,j);
        }
    }

    double const_transformacion = (max-min)/(maximo-minimo);

    //aplicamos la transformacion a la imagen
    for (int i=0; i < img_salida.num_filas(); i++){
        for (int j=0; j < img_salida.num_columnas(); j++){
            byte actual = img_salida.valor_pixel(i,j);
            byte nuevo = (byte)(min + (const_transformacion*(actual-minimo)));
            img_salida.asigna_pixel(i,j,nuevo);
        }
    }

    //escribimos la imagen de salida
    byte * vector_salida = new byte [filas*columnas];
    escribirVectorPGM(img_salida,vector_salida,filas,columnas);
    if (!EscribirImagenPGM(salida,vector_salida,filas,columnas)){
        delete [] vector_salida;
        delete [] vector_original;
        error("Error al escribir la imagen");
    }
    delete [] vector_salida;
    delete [] vector_original;
}
