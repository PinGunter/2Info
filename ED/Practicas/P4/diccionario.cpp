/**
 * @file diccionario.cpp
 * @author Salvador Romero Cortés
 */
#include "diccionario.h"
#include <cassert>
// iterador no constante
template <typename T, typename U>
Diccionario<T,U>::iterator::iterator():it(){}

template <typename T, typename U>
Diccionario<T,U>::iterator::iterator(const iterator & otro):it(otro.it){}

template <typename T, typename U>
Diccionario<T,U>::iterator::iterator(typename list<data<T,U>>::iterator otro):it(otro){}

template <typename T, typename U>
typename Diccionario<T,U>::iterator & Diccionario<T,U>::iterator::operator++(){
    return ++it;
}

template <typename T, typename U>
typename Diccionario<T,U>::iterator Diccionario<T,U>::iterator::operator++(int){
    return it++;
}

template <typename T, typename U>
typename Diccionario<T,U>::iterator & Diccionario<T,U>::iterator::operator=(const iterator & otro){
    it = otro.it;
}

template <typename T, typename U>
list<data<T,U>> & Diccionario<T,U>::iterator::operator*(){
    return (*it);
}

template <typename T, typename U>
list<data<T,U>> Diccionario<T,U>::const_iterator::operator*() const {
    return (*it);
}

// iterador constante
template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator():it(){}

template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator(const const_iterator & otro):it(otro.it){}

template <typename T, typename U>
Diccionario<T,U>::const_iterator::const_iterator(typename list<data<T,U>>::const_iterator otro):it(otro){}

template <typename T, typename U>
typename Diccionario<T,U>::const_iterator & Diccionario<T,U>::const_iterator::operator++(){
    return ++it;
}

template <typename T, typename U>
typename Diccionario<T,U>::const_iterator Diccionario<T,U>::const_iterator::operator++(int){
    return it++;
}

template <typename T, typename U>
typename Diccionario<T,U>::const_iterator & Diccionario<T,U>::const_iterator::operator=(const const_iterator & otro){
    it = otro.it;
}

template <typename T, typename U>
bool operator!=(const typename Diccionario<T,U>::iterator & uno, const typename Diccionario<T,U>::iterator & otro){
    return uno.it != otro.it;
}


template <typename T, typename U>
bool operator!=(const typename Diccionario<T,U>::const_iterator & uno, const typename Diccionario<T,U>::const_iterator & otro){
    return uno.it != otro.it;
}

// metodos nuevos
template <typename T, typename U>
T Diccionario<T,U>::getClave(const typename Diccionario<T,U>::iterator & iterador)const{
    return (*iterador.it).clave;
}

template <typename T, typename U>
T Diccionario<T,U>::getClave(const typename Diccionario<T,U>::const_iterator & iterador)const{
    return (*iterador.it).clave;
}

template <typename T, typename U>
bool Diccionario<T,U>::borrar_por_clave(const T & clave){
    //primero comprobamos que realmente esté la clave en el diccionario
    typename list<data<T, U>>::iterator posicion;
    bool esta_clave = Esta_Clave(clave,posicion);
    if (esta_clave){
        datos.erase(posicion);
    }
    return esta_clave;
}

template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::union_dic( Diccionario<T,U> nuevo){
    Diccionario<T,U> aux(*this);
    typename list<data<U,T>>::iterator it_aux;
    for (auto it=nuevo.cbegin(); it != nuevo.cend(); ++it){
        typename Diccionario<T,U>::const_iterator it_dic(it);
        T clave = nuevo.getClave(it_dic);
        list<U> definiciones(nuevo.getInfo_Asoc(clave));
        if (aux.Esta_Clave(clave,it_aux)){
            for (typename list<U>::const_iterator iterador_def = definiciones.cbegin(); iterador_def != definiciones.cend(); ++iterador_def){
                if (!esta_dentro((*it_aux).info_asoci,(*iterador_def)))
                   aux.AddSignificado_Palabra((*iterador_def),clave);
            }
        }
        else{
            aux.Insertar(clave,nuevo.getInfo_Asoc(clave));
        }
    }   
    return aux;
}


template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::subdiccionario_entre(const T & inicio, const T & fin) const{
    typename list<data<T,U>>::iterator inicio_it;
    typename list<data<T,U>>::iterator fin_it;
    assert(Esta_Clave(inicio,inicio_it));
    assert(Esta_Clave(fin,fin_it));
    Diccionario<T,U> nuevo;
    for (typename list<data<T,U>>::iterator it=inicio_it; it != fin_it; ++it){
        nuevo.Insertar((*it).clave,(*it).info_asoci);
    }
    nuevo.Insertar((*fin_it).clave,(*fin_it).info_asoci);
    return nuevo;
}

template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::diferencia(const Diccionario<T,U> & otro) const{

}


template <typename U>
bool esta_dentro(const list<U> & lista, const U & elemento){
    typename list<U>::const_iterator it;
    bool encontrado = false;
    for (it=lista.cbegin(); it != lista.cend() && !encontrado; ++it){
        if ((*it) == elemento)
            encontrado = true;
    }
    return encontrado;
}
