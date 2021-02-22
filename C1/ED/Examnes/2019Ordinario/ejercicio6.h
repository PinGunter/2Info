//
// Created by salva on 20/1/21.
//

#ifndef INC_2019ORDINARIO_EJERCICIO6_H
#define INC_2019ORDINARIO_EJERCICIO6_H
#include <iostream>
#include <unordered_map>
using namespace std;

bool todos_pares(const list<int> & l){
    for (auto item : l){
        if ((item & 1) != 0){
            return false;
        }
    }
    return true;
}

template <typename T>
class contenedor{
private:
    unordered_map<T,list<int>> datos;
public:
    contenedor() = default;
    contenedor(const contenedor & otro) = default;
    ~contenedor() = default;
    contenedor & operator=(const contenedor & otro) = default;
    class iterador{
    private:
        typename unordered_map<T,list<int>>::iterator it, fin;
        iterador() = default;
        iterador(const iterador & otro) = default;
        ~iterador() = default;
        iterador & operator=(const iterador & otro) = default;

        bool operator==(const iterador & otro){
            return it == otro.it;
        }
        bool operator!=(const iterador & otro){
            return it != otro.it;
        }
        pair<T,list<int>> operator*(){
            return *it;
        }

        iterador & operator++(){
            ++it;
            while (it != fin && !todos_pares(it->second)){
                ++it;
            }
            return *this;
        }
        friend class contenedor<T>;
    };

    iterador begin(){
        iterador nuevo;
        nuevo.it = datos.begin();
        nuevo.fin = datos.end();
        if (nuevo.it != nuevo.fin && !todos_pares(nuevo.it->second))
            ++nuevo;
        return nuevo;
    }

    iterador end(){
        iterador nuevo;
        nuevo.it = datos.end();
        nuevo.fin = datos.end();
        return nuevo;
    }
};
#endif //INC_2019ORDINARIO_EJERCICIO6_H
