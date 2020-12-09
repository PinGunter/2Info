#include <diccionario.h>

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
