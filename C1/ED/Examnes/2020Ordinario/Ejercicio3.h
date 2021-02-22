//
// Created by salva on 17/1/21.
//

#ifndef INC_2020ORDINARIO_EJERCICIO3_H
#define INC_2020ORDINARIO_EJERCICIO3_H
#include <iostream>
#include <list>
#include <algorithm>
std::ostream & operator<<(std::ostream & os, const std::list<int> &l){
    os << "{ ";
    for (int n : l)
        os << n << " ";
    os << "}";
    return os;
}

int suma(const std::list<int> &L){
    int suma = 0;
    for (auto it = L.begin(); it != L.end(); ++it){
        suma += *it;
    }
    return suma;
}

int minsum(const std::list<int> &L){
    int suma_minima = (*L.begin());
    std::list<int> test;
    for (auto it = L.begin(); it != L.end(); ++it){
        test.push_back(*it);
        if (suma(test) > 0){
            test.clear();
        } else{
            if (suma(test) < suma_minima){
                suma_minima = suma(test);
            }
        }
    }
    return suma_minima;
}

std::list<int> generar_sublista(const std::list<int> & l, std::list<int>::const_iterator inicio){
    std::list<int> sub;
    for (auto it = inicio; it != l.end(); ++it){
        sub.push_back(*it);
    }
    return sub;
}

int minsum_generico(const std::list<int> & L){
    int suma_minima = (*L.begin());
    int minimo = suma_minima;
    bool negativo = false;
    for (auto n : L){
        if (n < 0)
            negativo = true;
        if (n < minimo)
            minimo = n;
    }
    if (negativo){
        suma_minima = minsum(L);
    } else{
        suma_minima = minimo;
    }
    return suma_minima;
}
#endif //INC_2020ORDINARIO_EJERCICIO3_H
