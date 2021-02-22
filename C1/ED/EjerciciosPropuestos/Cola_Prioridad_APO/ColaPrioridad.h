//
// Created by salva on 25/11/20.
//

#ifndef COLA_PRIORIDAD_APO_COLAPRIORIDAD_H
#define COLA_PRIORIDAD_APO_COLAPRIORIDAD_H
#include "APO.hpp"
#include <iostream>

template <typename Tbase>
class ColaPrioridad{
public:
    class tipo{
    private:
        Tbase elemento;
        int prioridad;
    public:
        tipo();
        tipo(const Tbase &el, int pr);
        tipo(const tipo &otro);
        ~tipo()=default;

        Tbase get_elemento() const;
        int get_prioridad() const;
        bool operator<(const tipo &otro);
        //friend std::ostream & operator<<(std::ostream & os, const tipo& t);
    };

    ColaPrioridad();

    ColaPrioridad(const ColaPrioridad<Tbase> & otro);

    ~ColaPrioridad()=default;

    tipo frente();

    void poner(const tipo & nuevo);

    void quitar();

    bool vacia();
private:
    APO<tipo> cola;
};
#include "ColaPrioridad.cpp"

#endif //COLA_PRIORIDAD_APO_COLAPRIORIDAD_H
