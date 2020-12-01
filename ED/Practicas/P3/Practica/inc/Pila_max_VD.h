/**
 * @file Pila_max_VD.h
 * @brief Archivo con las cabeceras y la interfaz de la clase pila con máximo (vector)
 * @author Salvador Romero Cortés
 * @author Abel Ríos González
 */

#ifndef PILA_MAX_VD_H
#define PILA_MAX_VD_H
#include <vector>
#include <iostream>


/**
 * @brief estructura usada en la pila, almacena un entero y el máximo de la pila en el momento que se inserta
 */
struct elemento{
    /*@{*/
    int ele;    /**< el elemento en sí, un entero */
    int maximo; /**< el maximo de la pila */
    /*@}*/

};

class Pila_max{
    
private:
    
    std::vector<elemento> p;
    
public:
    
    /**
     * @brief Constructor sin parámetros
     */
    Pila_max() = default;
    
    /**
     * @brief Constructor de copia
     * @param otro la pila que se va a copiar
     */
    Pila_max(const Pila_max& otro);

    /**
     * @brief Operador de asignacion
     * @param otro la pila que asignamos a la actual
     * @return devuelve una referencia de la pila actual
     */
    Pila_max & operator=(const Pila_max& otro);
    
    /**
     * @brief Destructor de la clase, es el predeterminado
     */
    ~Pila_max()= default;
    
    /**
     * @brief Añade un elemento a la pila
     * @param nuevo el elemento a insertar
     */
    void poner(int nuevo);
    
    /**
     * @brief Elimina el elemento situado en el tope de la pila
     */
    void quitar();
    
    /**
     * @brief Método de consulta del elemento en el tope de la pila
     * @return una copia del elemento
     * @post Es el método constante, no modifica la pila.
     */
    const elemento & tope() const;

    /**
     * @brief Método de consulta del tope de la pila
     * @return una referencia del elemento tope
     * @post Es una referencia
    */
    elemento & tope();
    
    /**
     * @brief Indica si la pila está vacia o no
     * @return 
     *          @retval true si está vacia 
     *          @retval false en caso contrario
     */
    bool vacia() const;
};

                /* FUNCIONES EXTERNAS */

/**
 * @brief funcion para mostrar por pantalla el struct elemento
 * @param os el flujo de salida
 * @param e el elemento a mostrar
 * @return el flujo
*/

std::ostream & operator<<(std::ostream & os, elemento e);


#endif /* PILA_MAX_VD_H */
