/**
 * @author Salvador Romero Cortés
 * */

#ifndef COLA_H
#define COLA_H

template <typename T>
class Cola{
public:
    T * datos;
    int reservados;
	int nelem;
    int anterior, posterior;

public:
    Cola();
    Cola(const Cola &c);
    ~Cola();
    Cola &operator=(const Cola &c);
    bool vacia() const;
    void poner(const T & valor);
    void quitar();
    T frente() const;
    Cola operator++(int n);
    void operator+=(const Cola &c);

private:
    void reservar(const int n);
    void liberar();
    void copiar(const Cola &c);
    void redimensionar(const int n);

};


#include "Cola.tpp"
#endif