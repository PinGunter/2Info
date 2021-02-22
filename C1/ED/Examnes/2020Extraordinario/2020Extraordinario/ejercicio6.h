#pragma once
#include <iostream>
#include <map>
#include <list>
using namespace std;

bool primo(int x) {
    bool es_primo = true;
    if (x == 0 || x == 1) {
        es_primo = false;
    }
    else {
        for (int i = 2; i <= x / 2; ++i) {
            if (x % i == 0) {
                es_primo = false;
                break;
            }
        }
    }
    return es_primo;
}

bool lista_de_primos(const list<int> & lista) {
    for (auto e : lista) {
        if (!primo(e))
            return false;
    }
    return true;
}

class Diccionario {
private:
	map<int, list<int>> datos;
public:
    list<int>& operator[](int i) {
        return datos[i];
    }

    void insertar(int pos, const list<int>& lista) {
        datos[pos] = lista;
    }

    friend ostream& operator<<(ostream& os, const Diccionario& dicc) {
        for (auto itd = dicc.datos.cbegin(); itd != dicc.datos.cend(); itd++) {
            os << itd->first << ": ";
            for (auto itl = itd->second.cbegin(); itl != itd->second.cend(); itl++)
                os << *itl << " ";
            os << endl;
        }
        return os;
    }
    class iterador_primos {
    private:
        map<int, list<int>>::iterator it;
        map<int, list<int>>::iterator fin;
    public:
        iterador_primos() = default;
        iterador_primos(const iterador_primos& otro):it(otro.it) {}
        ~iterador_primos() = default;
        iterador_primos& operator=(const iterador_primos& otro) = default;
        
        bool operator==(const iterador_primos& otro) {
            return it == otro.it;
        }

        bool operator!=(const iterador_primos& otro) {
            return it != otro.it;
        }

        iterador_primos& operator++() {
            ++it;
            while (it != fin && !lista_de_primos(it->second)) {
                ++it;
            }

            return *this;
        }

        pair<const int, list<int>>& operator*() {
            return *it;
        }
        friend class Diccionario;
    };
    iterador_primos begin() {
        iterador_primos nuevo;
        nuevo.it = datos.begin();
        nuevo.fin = datos.end();
        if (nuevo.it != nuevo.fin && !lista_de_primos(nuevo.it->second))
            ++nuevo;
        return nuevo;
    }

    iterador_primos end() {
        iterador_primos nuevo;
        nuevo.it = datos.end();
        nuevo.fin = datos.end();
        return nuevo;
    }

};