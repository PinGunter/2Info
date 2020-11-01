/**
 * @file Lista.hpp
 * @author Salvador Romero Cortés
 */
#ifndef LISTA_H
#define LISTA_H

/**
 * @brief clase genérica que representa una lista
 * @param T el tipo usado dentro de la lista
 */
template <typename T>
class Lista;

/**
 * @brief clase que representa las posiciones dentro de la clase lista
 *        de manera abstracta.
 */

class Posicion{
private:
    int i;
public:
    /**
    *@brief constructor por defecto de la posicion
    *@post el indice es 0
    */ 
    Posicion();
    /**
     * @brief Constructor de copia. Es el predeterminado
     */
    Posicion(const Posicion &p) = default;
    /**
     * @brief Detructor de la clase. Es el predeterminado
     */
    ~Posicion() = default;

    /**
     * @brief operador de asignacion
     * @param p el objeto que se copia
     * @return una referencia al objeto this
     */
    Posicion & operator=(const Posicion &p) = default;
    /**
     * @brief operador de preincremento
     * @return una referencia al objeto this tras incrementar el valor
     */
    Posicion & operator++();
    /**
     * @brief operador de post incremento
     * @return una copia del objeto antes de incrementar su valor
     */
    Posicion operator++(int);
    /**
     * @brief operador de predecremento
     * @return una referencia al objeto this tras decrementar el valor
     */
    Posicion & operator--();
    /**
     * @brief operador de postdecremento
     * @return una copia del objeto this antes de decrementar el valor
     */
    Posicion operator--(int);
    /**
     * @brief operador de comparacion de igualdad
     * @param p el objeto que se compara
     * @return true si son iguales
     *         false si son distintos
     */
    bool operator==(const Posicion &p) const;
    /**
     * @brief operador de desigualdad
     * @param p el objeto que se compara
     * @return true si son distintos
     *         false si son iguales
     */
    bool operator!=(const Posicion &p) const;

    /**
     * @brief metodo para obtener el indice
     * @return el entero que representa el indice
     * @post no se modifica el indice
     */
    int get() const;
    /**
     * @brief metodo para obtener el indice
     * @return el entero que representa el indice
     * @post puede modificar el indice
     */
    int & get() ;
};

template <typename T>
class Lista{
private:
    T *  datos;
    int nelementos;
    int reservados;
public:
    /**
     * @brief constructor por defecto de la clase lista
    */
    Lista();
    /**
     * @brief constructor de copia de lista
     * @param l la lista que se copia
     */
    Lista(const Lista &l);
    /**
     * @brief destructor de la clase lista 
     * @post el objeto no se vuelve a usar
     */
    ~Lista();

    /**
     * @brief operador de asignacion
     * @param l el objeto que se copia
     * @return una referencia al objeto this tras copiarse
     */
    Lista & operator=(const Lista &l);

    /**
     * @brief metodo para obtener un elemento en la posicion p
     * @param p posicion de la lista donde esta el elemento que queremos
     * @pre p debe ser una posicion valida
     * @return el elemento en esa posicion
     */
    T get(const Posicion &p) const;
    /**
     * @brief metodo para modificar el elemento p-esimo de la lista
     * @param p la posicion donde se modifica
     * @param e el nuevo elemento en esa posicion
     * @pre p debe ser una posicion valida
     */
    void set(const Posicion &p, const T &e);
    /**
     * @brief metodo para insertar un elemento en la posicion p,
     * el elemento que se encontraba antes en esa posicion 
     * ahora se encuentra a la siguiente de la insertada
     * @param p posicion donde se inserta
     * @param e elemento nuevo
     * @pre p debe ser una posicion valida
     * @return la posicion donde se inserta
     */
    Posicion insert(const Posicion &p, const T &e);

    /**
     * @brief metodo que borra el elemento p-esimo de la lista
     * @param p la posicion donde se borra
     * @pre p debe ser una posicion valida
     * @return la posicion que se elimina
     */
    Posicion erase(const Posicion &p);

    /**
     * @brief metodo que devuelve el tamaño de la lista
     * @return tamaño de la lista
     */
    int size() const;

    /**
     * @brief metodo para obtener la posicion inicial de la lista
     * @return la primera posicion
     */
    Posicion begin() const;

    /**
     * @brief metodo para obtener la ultima posicion de la lista, para poder insertar
     * @return la posicion final
     */
    Posicion end() const;
private:
    /**
     * @brief metodo para liberar la memoria usada por la lista
     */
    void liberar();
    /**
     * @brief metodo para cambiar el tamaño de la lista
     * @param n el nuevo tamaño
     * @pre n debe ser un tamaño valido
     * @post la lista queda igual con un tamaño nuevo
     */
    void redimensionar(int n);
    /**
     * @brief metodo interno para copiar un objeto lista
     * @param l el objeto a copiar
     * @pre el objeto this debe tener un tamaño de memoria suficiente para la copia
     */
    void copiar(const Lista &l);
    /**
     * @brief metodo para reservar la memoria necesaria para la lista
     * @param n el tamño de la lista para el que se va a reservar
     * @pre debe ser un tamaño valido
     */
    void reservar(int n);
};

#include "Lista.cpp"
#endif
