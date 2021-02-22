//
// Created by salva on 25/11/20.
//

#include "ColaPrioridad.h"
using namespace std;

// clase tipo
template <typename Tbase>
ColaPrioridad<Tbase>::tipo::tipo():elemento(){}

template <typename Tbase>
ColaPrioridad<Tbase>::tipo::tipo(const Tbase &el, int pr):elemento(el){
    prioridad = pr;
}

template <typename Tbase>
ColaPrioridad<Tbase>::tipo::tipo(const tipo &otro):elemento(otro.elemento){}

template <typename Tbase>
Tbase ColaPrioridad<Tbase>::tipo::get_elemento() const {
    return elemento;
}

template <typename Tbase>
int ColaPrioridad<Tbase>::tipo::get_prioridad() const {
    return prioridad;
}

template <typename Tbase>
bool ColaPrioridad<Tbase>::tipo::operator<(const tipo &otro){
    return (prioridad < otro.get_prioridad());
}


// clase cola
template <typename Tbase>
ColaPrioridad<Tbase>::ColaPrioridad():cola() {}

template <typename Tbase>
ColaPrioridad<Tbase>::ColaPrioridad(const ColaPrioridad<Tbase> & otro):cola(otro.cola) {}

template <typename Tbase>
typename ColaPrioridad<Tbase>::tipo ColaPrioridad<Tbase>::frente() {
    return cola.raiz();
}

template <typename Tbase>
void ColaPrioridad<Tbase>::poner(const tipo &nuevo) {
    cola.insertar(nuevo);
}

template <typename Tbase>
void ColaPrioridad<Tbase>::quitar() {
    cola.borrar_raiz();
}

template <typename Tbase>
bool ColaPrioridad<Tbase>::vacia() {
    return cola.empty();
}