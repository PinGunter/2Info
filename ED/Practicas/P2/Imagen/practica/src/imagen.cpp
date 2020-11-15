/**
 * @file imagen.cpp
 * @author Salvador Romero Cortés
 * @brief definiciones de los métodos de la clase Imagen
 */

#include <imagen.h>
#include <imagenES.h>
#include <funciones_imagen.h>
#include <cassert>

using namespace std;


Imagen::Imagen(int filas, int columnas){
    imagen = nullptr;
    reservar(filas,columnas);
    for (int i=0; i < filas; i++)
        for (int j=0; j < columnas; j++)
            asigna_pixel(i,j,0);
}
//----------------------------------------------------------------

Imagen::Imagen(const Imagen &otra){
    imagen = nullptr;
    reservar(otra.num_filas(),otra.num_columnas());
    copiar(otra);
}
//----------------------------------------------------------------

Imagen::Imagen (int filas, int columnas, byte * vector){
    imagen = nullptr;
    reservar(filas,columnas);
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            asigna_pixel(i,j,vector[i*columnas+j]);
        }
    }
}

//----------------------------------------------------------------

Imagen::~Imagen(){
    liberar();
}
//----------------------------------------------------------------

Imagen & Imagen::operator=(const Imagen &otra){
    if (this != &otra){
        liberar();
        reservar(otra.num_filas(), otra.num_columnas());
        copiar(otra);
    }
    return *this;
}
//----------------------------------------------------------------

int Imagen::num_filas() const{
    return filas;
}
//----------------------------------------------------------------

int Imagen::num_columnas() const{
    return columnas;
}
//----------------------------------------------------------------

void Imagen::asigna_pixel(int fila, int columna, byte valor){
    if (!(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas())){
        std::cout << "filas: " << num_filas() << endl << "columnas: " << num_columnas() << endl;
        std::cout << "falla fila:" << fila << endl << "falla columna:" << columna << endl;
    }
    assert(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas());
    assert(valor >= 0 && valor <= 255);
    imagen[fila][columna] = valor;
}
//----------------------------------------------------------------

byte Imagen::valor_pixel(int fila, int columna) const{
    if (!(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas())){
        std::cout << "filas: " << num_filas() << endl << "columnas: " << num_columnas() << endl;
        std::cout << "falla fila:" << fila << endl << "falla columna:" << columna << endl;
    }
    assert(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas());
    return imagen[fila][columna];
}
//----------------------------------------------------------------

void Imagen::reservar(int filas, int columnas){
    liberar();
    this->imagen = new byte * [filas];
    for (int i=0; i < filas; i++)
        this->imagen[i] = new byte[columnas];
    this->filas = filas;
    this->columnas = columnas;
}
//----------------------------------------------------------------

void Imagen::liberar(){
    if (imagen != nullptr){
        for (int i=0; i < filas; i++)
            delete [] imagen[i];
        delete [] imagen;
    }
}
//----------------------------------------------------------------

void Imagen::copiar(const Imagen &otra){
    for (int i=0; i < filas; i++)
        for (int j=0; j < columnas; j++)
            asigna_pixel(i,j,otra.valor_pixel(i,j));
}
