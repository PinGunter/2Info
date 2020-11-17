//
// Created by salva on 15/11/20.
//

#ifndef LISTA_H
#define LISTA_H

template <typename T>
struct CeldaLista{
    T elemento;
    CeldaLista * anterior;
    CeldaLista * siguiente;
};
template <typename T>
class Lista{
    public:
    class iterator{
        CeldaLista<T> * puntero;
    public:
        iterator();
        iterator(const iterator &p) = default;
        ~iterator() = default;
        iterator & operator=(const iterator &p) = default;
        iterator & operator++();
        iterator operator++(int);
        iterator & operator--();
        iterator operator--(int);
        bool operator==(const iterator p) const;
        bool operator!=(const iterator p) const;
        T operator*() const;
    };
private:
    CeldaLista<T> * cabecera;
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
    T get(const iterator &p) const;
    /**
     * @brief metodo para modificar el elemento p-esimo de la lista
     * @param p la posicion donde se modifica
     * @param e el nuevo elemento en esa posicion
     * @pre p debe ser una posicion valida
     */
    void set(const iterator &p, const T &e);
    /**
     * @brief metodo para insertar un elemento en la posicion p,
     * el elemento que se encontraba antes en esa posicion
     * ahora se encuentra a la siguiente de la insertada
     * @param p posicion donde se inserta
     * @param e elemento nuevo
     * @pre p debe ser una posicion valida
     * @return la posicion donde se inserta
     */
    iterator insert(const iterator &p, const T &e);

    /**
     * @brief metodo que borra el elemento p-esimo de la lista
     * @param p la posicion donde se borra
     * @pre p debe ser una posicion valida
     * @return la posicion que se elimina
     */
    iterator erase(const iterator &p);

    /**
     * @brief metodo que devuelve el tamaño de la lista
     * @return tamaño de la lista
     */
    int size() const;

    /**
     * @brief metodo para obtener la posicion inicial de la lista
     * @return la primera posicion
     */
    iterator begin() const;

    /**
     * @brief metodo para obtener la ultima posicion de la lista, para poder insertar
     * @return la posicion final
     */
    iterator end() const;
};



#endif //LISTAS_LISTASDOBLES_LISTA_H
