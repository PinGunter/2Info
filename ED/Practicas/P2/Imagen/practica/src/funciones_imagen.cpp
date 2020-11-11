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
//Innecesaria teniendo el constructor con el vector 
// Imagen leerVectorPGM(byte * vector, int filas, int columnas){
//     Imagen imagen(filas,columnas);
//     for (int i=0; i < filas; i++){
//         for (int j=0; j < columnas; j++){
//             imagen.asigna_pixel(i,j,vector[i*columnas+j]);
//         }
//     }
//     return imagen;
// }
//----------------------------------------------------------------
Imagen leerVectorPPM(byte * vector, int filas, int columnas){
    byte * vector_gris = new byte[filas*columnas];
    int j=0; 
    for (int i=0; i < filas*columnas; i++)
        vector_gris[i] = vector[j++]*ROJO_GRIS + vector[j++] * VERDE_GRIS + vector[j++] * AZUL_GRIS;
    Imagen gris(filas,columnas,vector_gris);
    delete [] vector_gris;
    return gris;
}
//----------------------------------------------------------------
void escribirVectorPGM(const Imagen & img, byte * vector, int filas, int columnas){
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
    Imagen img_salida(filas,columnas,vector_original);

    //umbralizamos la funcion
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            if (!(img_salida.valor_pixel(i,j) >= umbral_min && img_salida.valor_pixel(i,j) <= umbral_max))
                img_salida.asigna_pixel(i,j,BLANCO);
        }
    }
    //escribimos la imagen de salida
    escribirImagen(img_salida,salida);
    delete [] vector_original;
}

//----------------------------------------------------------------

void contrastar(const char * original, const char * salida, int minimo, int maximo){
    //comprobamos que min y max sean valores validos
    if (minimo >= maximo)
        error("Intervalo de contraste incorrecto");
    
    //leemos y creamos las imagenes
    int filas, columnas;
    byte * vector_original = LeerImagenPGM(original,filas,columnas);
    Imagen img_salida(filas,columnas,vector_original);

    //transformacion lineal:
    // t(z) = min + [((max-min)/(b-a))*(z-a)]

    //vemos que el calculo de (max-min)/(b-a) es constante en toda la imagen, por tanto
    //podemos calcularlo una única vez
    byte a = 255;
    byte b = 0;
    for (int i=0; i < img_salida.num_filas(); i++){
        for (int j=0; j < img_salida.num_columnas(); j++){
            if (img_salida.valor_pixel(i,j) < a)
                a = img_salida.valor_pixel(i,j);
            if (img_salida.valor_pixel(i,j) > b)
                b = img_salida.valor_pixel(i,j);
        }
    }

    cout << "b: " << static_cast<int> (b) << endl;
    cout << "a: " << static_cast<int> (a) << endl;
    cout << "maximo: " << static_cast<int> (maximo) << endl;
    cout << "minimo: " << static_cast<int> (minimo) << endl;
    
    double constante = (maximo*1.0-minimo*1.0)/(b*1.0-a*1.0);
    cout << constante << endl;

    for (int i=0; i < img_salida.num_filas(); i++){
        for (int j=0; j < img_salida.num_columnas(); j++){
            double actual = img_salida.valor_pixel(i,j);
            double nuevo = (actual-a) * constante + minimo;
            if (nuevo > 255)
                nuevo = 255;
            img_salida.asigna_pixel(i,j,round(nuevo));
        }
    }


    //escribimos la imagen de salida
    if (!escribirImagen(img_salida,salida))
        error("Error escribiendo la imagen");
    delete [] vector_original;
}

//--------



//------------------------
bool escribirImagen(const Imagen & img, const char * nombre_archivo){
    byte * vector_salida = new byte [img.num_filas() * img.num_columnas()];
    escribirVectorPGM(img,vector_salida,img.num_filas(),img.num_columnas());
    bool ok = EscribirImagenPGM(nombre_archivo,vector_salida,img.num_filas(), img.num_columnas());
    delete [] vector_salida;
    return ok;
}


void zoom(const char * entrada, const char * salida, int x1, int y1, int x2, int y2){
    if (x1 >= x2 || y1 >= y2)
        error("Posiciones zoom incorrectas");
    else if ((x2-x1) != (y2-y1))
        error("El recorte no es cuadrado");


    int tam_recorte = x2-x1;            // N
    int dimension = 2*tam_recorte-1;    // 2N+1
    int filas, columnas;

    //lectura de datos
    byte * vector_original = LeerImagenPGM(entrada, filas, columnas);
    Imagen original(filas,columnas,vector_original);

    Imagen interpo_colum(tam_recorte,dimension);
    //Primero copiamos los valores originales
    for (int i=0,x_orig = x1; i < tam_recorte; i++){
        for (int j=0,y_orig = y1; j < dimension; j+=2){
            interpo_colum.asigna_pixel(i,j,original.valor_pixel(x_orig,y_orig++));
        }
        x_orig++;
    }

    //Ahora rellenamos las columnas con la media
    for (int i=0,x_orig = x1; i < tam_recorte; i++){
        for (int j=1,y_orig = y1; j < dimension; j+=2){
            int media = (original.valor_pixel(x_orig,y_orig-1) + original.valor_pixel(x_orig,y_orig+1)) / 2.0;
            interpo_colum.asigna_pixel(i,j,media);
            y_orig++;
        }
        x_orig++;
    }

    //terminamos la imagen con las filas
    Imagen zoom(dimension,dimension);
    //Primero copiamos los valores originales
    for (int i=0; i < dimension; i+=2){
        int y = 0;
        int x = 0;
        for (int j=0; j < dimension; j++){
            zoom.asigna_pixel(i,j,interpo_colum.valor_pixel(x,y++));
        }
        x++;
    }

    for (int i=1; i < dimension; i+=2){
        int y = 0;
        int x = 0;
        for (int j=0; j < dimension; j++){
            int media = (interpo_colum.valor_pixel(x-1,y) + interpo_colum.valor_pixel(x+1,y)) / 2.0;
            zoom.asigna_pixel(i,j,media);
            x++;
        }
        y++;
    }


    escribirImagen(zoom,salida);
    

    delete [] vector_original;
}
