//
// Created by salva on 15/11/20.
//

#include "Lista.h"
#include <cassert>
#include <utility>
template <typename T>
Lista<T>::iterator::iterator() {
	puntero = nullptr;
}

template <typename T>
typename Lista<T>::iterator & Lista<T>::iterator::operator++() {
    puntero = puntero->siguiente;
    return *this;
}

template <typename T>
typename Lista<T>::iterator  Lista<T>::iterator::operator++(int) {
    iterator p(*this);
    ++(*this);
    return p;
}

template <typename T>
typename Lista<T>::iterator & Lista<T>::iterator::operator--() {
    puntero = puntero->anterior;
    return *this;
}

template <typename T>
typename Lista<T>::iterator  Lista<T>::iterator::operator--(int) {
    iterator p(*this);
    --(*this);
    return p;
}

template <typename T>
bool Lista<T>::iterator::operator==(const Lista<T>::iterator p) const {
    return (puntero==p.puntero);
}

template <typename T>
bool Lista<T>::iterator::operator!=(const Lista<T>::iterator p) const {
    return (puntero!=p.puntero);
}

template<typename T>
T Lista<T>::iterator::operator*() const {
    return puntero->elemento;
}

/***    CLASE LISTA         ***/
template <typename T>
Lista<T>::Lista(){
    cabecera = new CeldaLista<T>;
    cabecera->siguiente = cabecera;
    cabecera->anterior = cabecera;
}
template <typename T>
Lista<T>::Lista(const Lista<T> &l){
    cabecera = new CeldaLista<T>;
    cabecera->siguiente = cabecera;
    cabecera->anterior = cabecera;

    CeldaLista<T> * p = l.cabecera->siguiente;
    while (p!=l.cabecera){
        CeldaLista<T> * q = new CeldaLista<T>;
        q->elemento = p->elemento;
        q->anterior = cabecera->anterior;
        cabecera->anterior->siguiente = q;
        cabecera->anterior = q;
        q->siguiente = cabecera;
        p = p->siguiente;
    }
}

template <typename T>
Lista<T>::~Lista(){
    while (begin() != end())
        erase(begin());
    delete cabecera;
}

template <typename T>
Lista<T> & Lista<T>::operator=(const Lista<T> &l){
    Lista aux(l);
    swap(this->cabecera, aux.cabecera);
    return *this;
}

template <typename T>
void Lista<T>::set(const iterator &p, const T &e) {
    p.puntero->elemento = e;
}

template <typename T>
T Lista<T>::get(const iterator &p) const {
    return p.puntero->elemento;
}

template <typename T>
typename Lista<T>::iterator Lista<T>::insert(iterator p, const T &e) {
    CeldaLista<T> * q = new CeldaLista<T>;
    q->elemento = e;
    q->anterior = p.puntero-> anterior;
    q->siguiente = p.puntero;
    p.puntero-> anterior = q;
    q->anterior->siguiente = q;
    p.puntero = q;
    return p;
}
template <typename T>
typename Lista<T>::iterator Lista<T>::erase(iterator p) {
    assert(p!=end());
    CeldaLista<T> * q = p.puntero;
    q->anterior->siguiente = q->siguiente;
    q->siguiente->anterior = q->anterior;
    p.puntero = q->siguiente;
    delete q;
    return p;
}
template <typename T>
int Lista<T>::size() const {
    int n = 0;
    for (iterator p = begin(); p != end(); ++p){
        n++;
    }
    return n;
}

template <typename T>
typename Lista<T>::iterator Lista<T>::begin() const {
    iterator p;
    p.puntero = cabecera->siguiente;
    return p;
}

template <typename T>
typename Lista<T>::iterator Lista<T>::end() const {
    iterator p;
    p.puntero = cabecera;
    return p;
}

