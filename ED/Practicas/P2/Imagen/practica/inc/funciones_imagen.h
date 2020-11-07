/**
 * @file funciones_imagen.h
 * @author Salvador Romero Cortés
 * @brief Archivo con la suite de funciones sobre el @a TDA_Imagen
 */

#ifndef FUNCIONES_IMAGEN_H
#define FUNCIONES_IMAGEN_H

#include <iostream>
#include <imagenES.h>

/** FUNCIONES AUXILIARES **/
/**
 * @brief funcion para mostrar los mensajes de error
 * @param mensaje el mensaje de error
 **/
void error(std::string mensaje);



/*     FUNCIONES SOBRE EL TIPO IMAGEN  */
/**
 * @brief funcion para obtener una imagen a partir de un vector 1d de una imagen PGM
 * @param vector el vector unidimensional que contiene los pixeles de la imagen
 * @param filas el número de filas que tendrá la imagen
 * @param columnas el número de columnas que tendrá la imagen
 * @return objeto imagen con los datos del vector
 **/
Imagen leerVectorPGM(byte * vector, int filas, int columnas);
/**
 * @brief funcion para obtener una imagen a partir de un vector 1d de una imagen PPM
 * @param vector el vector unidimensional que contiene los pixeles de la imagen
 * @param filas el número de filas que tendrá la imagen
 * @param columnas el número de columnas que tendrá la imagen
 * @return objeto imagen con los datos del vector (en escala de grises)
 **/
Imagen leerVectorPPM(byte * vector, int filas, int columnas);
/**
 * @brief funcion para transformar un objeto imagen en un vector unidimensional
 * @param img la imagen que se va a convertir
 * @param vector el vector donde se escribe la imagen
 * @param filas el número de filas de la imagen
 * @param columnas el número de columnas de la imagen
 * @pre 
 * @post todos los parámetros se modifican menos @a img
 **/
void escribirVectorPGM(const Imagen &img, byte * vector, int &filas, int &columnas);

/**
 * @brief función que permite convertir una imagen PPM a una imagen PGM
 * @param nombre_ppm la imagen a color
 * @param nombre_pgm la imagen en escala de grises
 * @pre debe existir el archivo con el nombre @a nombre_ppm
 * @post se escribe directamente el archivo desde esta funcion
 **/
void colorAGris(const char * nombre_ppm, const char * nombre_pgm);

/**
 * @brief funcion para generar una imagen nueva a partir de una original,
 * basado en un umbral de escala de grises.
 * Si el pixel se encuentra en el intervalo, conserva su color, en caso contrario se vuelve negro
 * @param original el nombre de la imagen de la que se parte
 * @param salida el nombre de la imagen nueva
 * @param umbral_min el minimo del intervalo umbral
 * @param umbral_max el maximo del intervalo umbral
 * @pre @a original debe ser una imagen valida
 * @pre @a umbral_min < @a umbral_max además de ser ambos entre 0 y 255
 * @post @a salida se guarda como imagen valida en disco
 */
void umbralizar_escala_grises(const char* original, const char * salida,int umbral_min, int umbral_max);

/**
 * @brief funcion para contrastar una imagen basado en unos valores @a min y @a max
 * @pre @a min y @a max deben ser >0 y <255
 * @pre @a original debe ser una imagen valida
 * @param original nombre de la imagen original a partir de la cual se genera la imagen contrastada
 * @param salida nombre de la imagen contrastada
 * @param min inicio del intervalo 
 * @param max final del intervalo
 * @post se escribe en disco la imagen @a salida
 */
void contrastar(const char * original, const char * salida, byte min, byte max);

#endif
// fin archivo