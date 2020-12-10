#include "diccionario.h"

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
list<data<T,U>> Diccionario<T,U>::const_iterator::operator*(){
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
bool operator==(const typename Diccionario<T,U>::iterator & uno, const typename Diccionario<T,U>::iterator & otro){
    return uno.it == otro.it;
}


template <typename T, typename U>
bool operator==(const typename Diccionario<T,U>::const_iterator & uno, const typename Diccionario<T,U>::const_iterator & otro){
    return uno.it == otro.it;
}

// metodos nuevos
template <typename T, typename U>
T Diccionario<T,U>::getClave(const typename Diccionario<T,U>::iterator & it){
    return (*it).clave;
}

template <typename T, typename U>
bool Diccionario<T,U>::borrar_por_clave(T clave){
    //primero comprobamos que realmente esté la clave en el diccionario
    typename list<data<T, U>>::iterator posicion;
    bool esta_clave = Esta_Clave(clave,posicion);
    if (esta_clave){
        datos.remove(clave);
    }
    return esta_clave;
}


template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::union_dic(const Diccionario<T,U> & nuevo){
    Diccionario<T,U> aux(*this);
    typename list<data<U,T>>::iterator it;
    for (it=nuevo.datos.begin(); it != nuevo.datos.end(); ++it){
        list<U> definiciones;
        if (aux.Esta_Clave(aux.getClave(it),NULL)){
            definiciones = aux.getInfo_Asoc(aux.getClave(it));
            for (typename list<U>::iterator iterador_def = definiciones.begin(); iterador_def != definiciones.end(); ++iterador_def)
                aux.AddSignificado_Palabra((*iterador_def),aux.getClave(it));
        }
        else{
            aux.Insertar(aux.getClave(it),aux.getInfo_Asoc(aux.getClave(it)));
        }
    }   
    return aux;
}


template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::subdiccionario_entre(const T & inicio, const T & fin){

}

template <typename T, typename U>
Diccionario<T,U> Diccionario<T,U>::diferencia(const Diccionario<T,U> & otro){

}
