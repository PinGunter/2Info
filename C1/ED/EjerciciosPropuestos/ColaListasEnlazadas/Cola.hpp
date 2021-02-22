/**
 * @author Salvador Romero Cortés
 * */

#ifndef COLA_H
#define COLA_H

template <typename T>
struct CeldaCola{
    T elemento;
    CeldaCola * sig;
};

template <typename T>
class Cola{
public:
    CeldaCola<T> * primera, *ultima;

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
    void liberar();
    void copiar(const Cola &c);
};


#include "Cola.tpp"
#endif