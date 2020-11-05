 /**
  * @file imagenES.cpp
  * @brief Fichero con definiciones para la E/S de imágenes
  * @author Salvador Romero Cortés
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <imagenES.h>
#include <cmath>

using namespace std;

// constantes para transformar de gris a color
const double ROJO_GRIS = 0.2989;
const double VERDE_GRIS = 0.587;
const double AZUL_GRIS = 0.114;

TipoImagen LeerTipo(ifstream& f){
  char c1,c2;
  TipoImagen res= IMG_DESCONOCIDO;

  if (f){
    c1=f.get();
    c2=f.get();
    if (f && c1=='P')
      switch (c2) {
        case '5': res= IMG_PGM; break;
        case '6': res= IMG_PPM; break;
        default: res= IMG_DESCONOCIDO;
      }
  }
  return res;
}

// _____________________________________________________________________________

TipoImagen LeerTipoImagen(const char *nombre){
  ifstream f(nombre);
  return LeerTipo(f);
}


// _____________________________________________________________________________

char SaltarSeparadores (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
} 

// _____________________________________________________________________________

bool LeerCabecera (ifstream& f, int& fils, int& cols){
    int maxvalor;
    string linea;
    while (SaltarSeparadores(f)=='#')
      getline(f,linea);
    f >> cols >> fils >> maxvalor;
    
    if (/*str &&*/ f && fils>0 && fils<5000 && cols>0 && cols<5000){
        f.get(); // Saltamos separador
        return true;
    }
    else 
      return false;
}



// _____________________________________________________________________________

unsigned char *LeerImagenPPM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);
  
  if (LeerTipo(f)==IMG_PPM){
    if (LeerCabecera (f, fils, cols)){
        res= new unsigned char[fils*cols*3];
        f.read(reinterpret_cast<char *>(res),fils*cols*3);
        if (!f){
          delete[] res;
          res= 0;
        }
    }
  }
  return res;
}

// _____________________________________________________________________________

unsigned char *LeerImagenPGM (const char *nombre, int& fils, int& cols){
  unsigned char *res=0;
  fils=0;
  cols=0;
  ifstream f(nombre);
  
  if (LeerTipo(f)==IMG_PGM){
    if (LeerCabecera (f, fils, cols)){
      res= new unsigned char[fils*cols];
      f.read(reinterpret_cast<char *>(res),fils*cols);
      if (!f){
        delete[] res;
        res= 0;
      }
    }
  }
  return res;
}

// _____________________________________________________________________________

bool EscribirImagenPPM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;
  
  if (f){
    f << "P6" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols*3);
    if (!f)
      res=false;
  }
  return res;
}
// _____________________________________________________________________________

bool EscribirImagenPGM (const char *nombre, const unsigned char *datos, 
                        const int fils, const int cols){
  ofstream f(nombre);
  bool res= true;
  
  if (f){
    f << "P5" << endl;
    f << cols << ' ' << fils << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),fils*cols);
    if (!f)
      res=false;
  }
  return res;
}

/** MÉTODOS DE LA CLASE IMAGEN */
Imagen::Imagen(int filas, int columnas){
    imagen = nullptr;
    reservar(filas,columnas);
    for (int i=0; i < filas; i++)
        for (int j=0; j < columnas; j++)
            asigna_pixel(i,j,0);
}

Imagen::Imagen(const Imagen &otra){
    imagen = nullptr;
    reservar(otra.num_filas(),otra.num_columnas());
    copiar(otra);
}

Imagen::~Imagen(){
    liberar();
}

Imagen & Imagen::operator=(const Imagen &otra){
    if (this != &otra){
        liberar();
        reservar(otra.num_filas(), otra.num_columnas());
        copiar(otra);
    }
    return *this;
}

int Imagen::num_filas() const{
    return filas;
}

int Imagen::num_columnas() const{
    return columnas;
}

void Imagen::asigna_pixel(int fila, int columna, byte valor){
    if (!(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas()))
        std::cout << "fila:" << fila << endl << "columna:" << columna << endl;
    assert(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas());
    assert(valor >= 0 && valor <= 255);
    imagen[fila][columna] = valor;
}

byte Imagen::valor_pixel(int fila, int columna) const{
    assert(fila >= 0 && fila < num_filas() && columna >= 0 && columna < num_columnas());
    return imagen[fila][columna];
}

void Imagen::reservar(int filas, int columnas){
   // liberar();
    this->imagen = new byte * [filas];
    for (int i=0; i < filas; i++)
        this->imagen[i] = new byte[columnas];
    this->filas = filas;
    this->columnas = columnas;
}

void Imagen::liberar(){
    if (imagen != nullptr){
        for (int i=0; i < filas; i++)
            delete [] imagen[i];
        delete [] imagen;
    }
}

void Imagen::copiar(const Imagen &otra){
    this->filas = otra.num_filas();
    this->columnas = otra.num_columnas();
    for (int i=0; i < filas; i++)
        for (int j=0; j < filas; j++)
            asigna_pixel(i,j,otra.valor_pixel(i,j));
}

/** FUNCIONES AUXILIARES **/

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

Imagen leerVectorPPM(byte * vector, int filas, int columnas){
    byte * vector_gris = new byte[filas*columnas];
    int j=0; 
    for (int i=0; i < filas*columnas; i++)
        vector_gris[i] = vector[j++]*ROJO_GRIS + vector[j++] * VERDE_GRIS + vector[j++] * AZUL_GRIS;
    Imagen gris = leerVectorPGM(vector_gris,filas,columnas);
    delete [] vector_gris;
    return gris;
}

void escribirVectorPGM(const Imagen & img, byte * vector, int & filas, int & columnas){
    filas = img.num_filas();
    columnas = img.num_columnas();
    for (int i=0; i < filas; i++){
        for (int j=0; j < columnas; j++){
            vector[i*columnas+j] = img.valor_pixel(i,j);
        }
    }
}

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

/* Fin Fichero: imagenES.cpp */
