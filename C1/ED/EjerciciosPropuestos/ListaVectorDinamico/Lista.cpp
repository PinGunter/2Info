/**
 * @file Lista.cpp
 * @author Salvador Romero Cortés
 */

#include "Lista.hpp"
#include <cassert>

using namespace std;

/**     CLASE POSICION      **/

Posicion::Posicion(){
    i = 0;
}

Posicion & Posicion::operator++(){
    i++;
    return *this;
}

Posicion Posicion::operator++(int){
    Posicion aux(*this);
    i++;
    return aux;
}

Posicion & Posicion::operator--(){
    i--;
    return *this;
}

Posicion Posicion::operator--(int){
    Posicion aux(*this);
    i--;
    return aux;
}

bool Posicion::operator==(const Posicion& p) const{
    return i==p.get();
}

bool Posicion::operator!=(const Posicion& p) const{
    return i!=p.get();
}

int Posicion::get() const{
    return i;
}

int & Posicion::get(){
    return i;
}

/**     CLASE LISTA      **/
template <typename T>
Lista<T>::Lista(){
    nelementos = 0;
    reservar(1);
}

template <typename T>
Lista<T>::Lista(const Lista &l){
    reservar(l.nelementos);
    copiar(l);
}

template <typename T>
Lista<T>::~Lista(){
    liberar();
}

template <typename T>
Lista<T> & Lista<T>::operator=(const Lista &l){
    if (this != &l){
        liberar();
        reservar(l.nelementos);
        copiar(l);
    }
    return *this;
}

template <typename T>
void Lista<T>::set(const Posicion &p, const T &e){
    assert(p.get() >= 0 && p.get()< nelementos);
    datos[p.get()] = e;
}

template <typename T>
T Lista<T>::get(const Posicion &p) const{
    assert(p.get()>=0 && p.get() < nelementos);
    return datos[p.get()];
}

template <typename T>
Posicion Lista<T>::insert(const Posicion &p, const T &e){
    if (nelementos == reservados)
        redimensionar(reservados*2);
    for (int j=nelementos; j > p.get(); j--)
        datos[j] = datos[j-1];
    datos[p.get()] = e;
    nelementos++;
    return p;
}

template <typename T>
Posicion Lista<T>::erase(const Posicion &p){
    assert(p!=end());
    for (int j=p.get();j < nelementos -1; j++)
        datos[j] = datos[j+1];
    nelementos--;
    if (nelementos < reservados/4)
        redimensionar(reservados/2);
    return p;
}

template <typename T>
int Lista<T>::size() const{
    return nelementos;
}

template <typename T>
Posicion Lista<T>::begin() const{
    return Posicion();
}

template <typename T>
Posicion Lista<T>::end() const{
    Posicion p;
    p.get() = nelementos;
    return p;
}

template <typename T>
void Lista<T>::liberar(){
    delete[] datos;
    reservados = nelementos = 0;
}

template <typename T>
void Lista<T>::reservar(int n){
    assert(n>0);
    reservados = n;
    datos = new T[reservados];    
}

template <typename T>
void Lista<T>::copiar(const Lista &l){
    nelementos = l.nelementos;
    for (int i=0; i < nelementos; i++)
        datos[i] = l.datos[i];
}

template <typename T>
void Lista<T>::redimensionar(int n){
    assert(n > 0 && n>=nelementos);
    T* aux = datos;
    reservar(n);
    for (int i=0; i < nelementos; i++)
        datos[i] = aux[i];
    delete [] aux;
}