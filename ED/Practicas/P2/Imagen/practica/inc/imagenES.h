/**
  * @file imagenES.h
  * @brief Fichero cabecera para la E/S de imágenes
  * @author Salvador Romero Cortés
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#ifndef _IMAGEN_ES_H_
#define _IMAGEN_ES_H_

/**
  * @brief Tipo de imagen
  *
  * Declara una serie de constantes para representar los distintos tipos
  * de imágenes que se pueden manejar.
  *
  * @see LeerTipoImagen
  */
enum TipoImagen {IMG_DESCONOCIDO, IMG_PGM, IMG_PPM};

/**
  * @brief Devuelve el tipo de imagen del archivo
  *
  * @param nombre indica el archivo de disco que consultar
  * @return Devuelve el tipo de la imagen en el archivo
  *
  * @see TipoImagen
  */
TipoImagen LeerTipoImagen (const char *nombre);

/**
  * @brief Lee una imagen de tipo PPM
  *
  * @param nombre archivo a leer
  * @param filas Parámetro de salida con las filas de la imagen.
  * @param columnas Parámetro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas x 3
  * bytes que corresponden a los colores de todos los píxeles en formato
  * RGB (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de éxito, el puntero apunta a una zona de memoria reservada en
  * memoria dinámica. Será el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPPM (const char *nombre, int& filas, int& columnas);

/**
  * @brief Escribe una imagen de tipo PPM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c x 3 bytes que corresponden a los valores
  *    de los píxeles de la imagen en formato RGB.
  * @param filas filas de la imagen
  * @param columnas columnas de la imagen
  * @return si ha tenido éxito en la escritura.
  */
bool EscribirImagenPPM (const char *nombre, const unsigned char *datos, 
                        const int filas, const int columnas);

/**
  * @brief Lee una imagen de tipo PGM
  *
  * @param nombre archivo a leer
  * @param filas Parámetro de salida con las filas de la imagen.
  * @param columnas Parámetro de salida con las columnas de la imagen.
  * @return puntero a una nueva zona de memoria que contiene @a filas x @a columnas
  * bytes que corresponden a los grises de todos los píxeles
  * (desde la esquina superior izqda a la inferior drcha). En caso de que no
  * no se pueda leer, se devuelve cero. (0).
  * @post En caso de éxito, el puntero apunta a una zona de memoria reservada en
  * memoria dinámica. Será el usuario el responsable de liberarla.
  */
unsigned char *LeerImagenPGM (const char *nombre, int& filas, int& columnas);

/**
  * @brief Escribe una imagen de tipo PGM
  *
  * @param nombre archivo a escribir
  * @param datos punteros a los @a f x @a c bytes que corresponden a los valores
  *    de los píxeles de la imagen de grises.
  * @param filas filas de la imagen
  * @param columnas columnas de la imagen
  * @return si ha tenido éxito en la escritura.
  */
bool EscribirImagenPGM (const char *nombre, const unsigned char *datos, 
                        const int filas, const int columnas);


/**   COMIENZA TDA IMAGEN   */
typedef unsigned char byte;
/**
 * @brief clase que representa una imagen digital en escala de grises
 * @section operaciones
 * Se definen una serie de operaciones:
 * 1. Creación de una imagen
 * 2. Destrucción de una imagen
 * 3. Consultar el número de filas
 * 4. Consultar el número de columnas
 * 5. Asignar un valor a un punto de la imagen
 * 6. Consultar el valor de un punto de la imagen
**/
class Imagen{
private:
/**
 * @section invariante de representacion
 * El invariante es valor >= 0 && valor <= 255
 * @section Tipo rep
 * El tipo rep del tda es una matriz bidimensional dinámica
 * Esta matriz se representa a través un vector de punteros que apuntan a cada fila
 * Para controlar y conocer el tamño de la matriz se utilizan dos variables enteras:
 * filas, cols
 **/
  int filas;  //número de filas de la imagen
  int columnas;   //número de columnas de la imagen
  byte **imagen; //la imagen en sí, representada en una matriz 2d dinámica

public:

  /**
   * @brief constructor de la clase Imagen. 
   * @param filas el número de filas que tendrá la imagen
   * @param columnas el número de columnas que tendrá la imagen
   * @return el objeto nuevo de imagen esta inicializado a una imagen en negro
   **/
  Imagen(int filas, int columnas);

  /**
   * @brief constructor de copia de la clase Imagen
   * @param otra la imagen que copiamos 
   * @return el nuevo objeto, copia de \e otra
   **/
  Imagen(const Imagen & otra);

  /**
   * @brief destructor de la clase Imagen.
   * @post destruye la imagen, libera la memoria, volverá a usarse con una llamada al constructor
   **/
  ~Imagen();

  /**
   * @brief operador de asignación entre imagenes.
   * @param otra la imagen que asignamos a la que llama al operador
   * @return una referencia al objeto que llama el operador
   * @post el objeto es una copia del pasado por referencia
   **/
  Imagen & operator=(const Imagen &otra);

  /**
   * @brief Calcula el número de filas de la imagen
   * @return el número de filas de la imagen
   * @post la imagen no se modifica
   **/
  int num_filas() const;

  /**
   * @brief Calcula el número de columnas de la imagen
   * @return el número de columnas que tienen la imagen
   * @post no se modifica la imagen
   **/
  int num_columnas() const;

  /**
   * @brief Asigna el valor @a valor al pixel indicado por @a fila y @a columna de la imagen
   * @param fila la fila del pixel a modificar
   * @param columna la columna del pixel a modificar
   * @param valor el valor que se asigna a la posicion ( @a fila, @a columna )
   * @pre @a fila y @a columna deben ser valores válidos [0, num_filas()] para @a fila y [0,num_columnas()] para @a columnas @a valor debe ser [0,255]
   * @post Imagen( @a fila, @a columna ) = @a valor . El resto de pixeles no se modifica
   **/
  void asigna_pixel(int fila, int columna, byte valor);

  /**
   * @brief Consulta el valor de un pixel de la imagen
   * @param fila la fila del pixel a consultar
   * @param columna la columna del pixel a consultar
   * @pre @a fila y @a columna deben ser valores válidos. [0, num_filas()] para @a fila y [0,num_columnas()] para @a columnas.
   * @post no se modifica la imagen
   **/
  byte valor_pixel(int fila, int columna) const;

private:
  /**
   * @section Métodos privados auxiliares
   * @brief Métodos privados auxiliares para gestionar la memoria dinámica de la matriz
   **/

  /**
   * @brief método para reservar el tamaño en memoria necesario para almacenar la imagen de @a filas y @a columnas
   * @param filas el número de filas que tendrá la imagen
   * @param columnas el número de columnas que tendrá la imagen
   * @post la imagen tiene reservada la cantidad de memoria necesaria para almacenar @a filas * @a columnas píxeles.
   **/
  void reservar(int filas, int columnas);

  /**
   * @brief método para eliminar de memoria la imagen
   * @post la imagen queda destruida y borrada
   **/
  void liberar();

  /**
   * @brief método para copiar una imagen @a otra en la actual
   * @pre la imagen debe tener reservada la cantidad de memoria antes de la copia
   * @param otra la imagen que se copia
   * @post la imagen queda como copia de @a otra
   **/
  void copiar(const Imagen &otra);
};
#endif

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


/* Fin Fichero: imagenES.h */
