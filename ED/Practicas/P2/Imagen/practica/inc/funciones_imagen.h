/**
 * @file funciones_imagen.h
 * @author Salvador Romero Cortés
 * @brief Archivo con la suite de funciones sobre el @a TDA_Imagen
 */

#ifndef FUNCIONES_IMAGEN_H
#define FUNCIONES_IMAGEN_H

#include <iostream>
#include <imagenES.h>
#include <cmath>

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
void escribirVectorPGM(const Imagen &img, byte * vector, int filas, int columnas);

/**
 * @brief función que permite convertir una imagen PPM a una imagen PGM
 * @param nombre_ppm la imagen a color
 * @param nombre_pgm la imagen en escala de grises
 * @pre debe existir el archivo con el nombre @a nombre_ppm
 * @post se escribe directamente el archivo desde esta funcion
 **/
void colorAGris(const char * nombre_ppm, const char * nombre_pgm);

/**
 * @brief función para escribir en el disco un objeto de la clase imagen
 * @param img imagen a escribir en disco
 * @param nombre_archivo el nombre del archivo que se guarda
 * @pre @a img deber se una imagen inicializada y valida
 * @pre @a nombre_archivo debe ser un nombre valido
 * @return true si no ha habido fallos, false en caso contrario
 */
bool escribirImagen(const Imagen & img, const char * nombre_archivo);

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
 * @brief funcion para realizar zoom en una porción cuadrada de la imagen
 * @param entrada nombre del archivo de la imagen de entrada
 * @param salida nombre del archivo de la imagen de salida
 * @param x1 posicion x de la esquina superior izquierda
 * @param y1 posicion y de la esquina superior izquierda
 * @param x2 posicion x de la esquina inferior derecha
 * @param y2 posicion y de la esquina inferior derecha
 * @pre x1 < x2 y y1 < y2. Además debe ser cuadrado, |x1-x2| == |y1-y2|
 */
void zoom(const char * entrada, const char * salida, int x1, int y1, int x2, int y2);

/**
 * @brief funcion para contrastar una imagen basado en unos valores @a min y @a max
 * @pre @a min y @a max deben ser >0 y <255
 * @pre @a original debe ser una imagen valida
 * @param original nombre de la imagen original a partir de la cual se genera la imagen contrastada
 * @param salida nombre de la imagen contrastada
 * @param minimo inicio del intervalo 
 * @param maximo final del intervalo
 * @post se escribe en disco la imagen @a salida
 */
void contrastar(const char * original, const char * salida, int minimo, int maximo);

/**
 * @brief funcion para realizar una transicion entre dos imagnenes (morphing)
 * @param fuente imagen de la que se parte (nombre)
 * @param destino imagen a la que se va transicionando (nombre)
 * @param basename nombre basico de los archivos intermedios que se generan.
 * @param pasos numero de pasos intermedios (e imagenes) que se van a hacer para la transicion
 * @pre las imagenes deben ser imagenes validas, asi como que basename debe ser un nombre valido para nombre de archivo del so. paso > 0
 *      las imagenes deben tener tambien el mismo tamaño
 */
void morphing(const char * fuente, const char * destino, const char * basename, int pasos);

/**
 * @brief funcion que realiza la transformacion de un pixel
 * @param s pixel inicial
 * @param d pixel final
 * @param a_i cociente de transformacion
 * @return la transformacion
 */
double tranformacion_morph(byte s, byte d, double a_i);

#endif
// fin archivo