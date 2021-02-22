/**
 * @file imagen.h
 * @author Salvador Romero Cortés
 * @brief contiene las declaraciones de la clase y de los metódos de Imagen
 */
#ifndef IMAGEN_H
#define IMAGEN_H
/**
 * @brief Macro para definir el color blanco
 */
#define BLANCO 255
/**
 * @brief Macro para definir el color negro
 */
#define NEGRO 0

typedef unsigned char byte;
/**
 * @brief clase que representa una imagen digital en escala de grises
 * @section Operaciones
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
   * @brief constructor de la clase imagen
   * @param filas el numero de filas que va a tener
   * @param columnas el numero de columnas que va a tener la imagen
   * @param vector vector unidimensional donde se almacenan todos los pixeles
   * @return la imagen creada a partir del vector
   */
  Imagen (int filas, int columnas, byte * vector);

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