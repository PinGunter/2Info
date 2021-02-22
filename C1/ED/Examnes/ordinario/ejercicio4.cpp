//
// Created by salva on 21/1/21.
//

#include <iostream>
#include <vector>
#include <list>

using namespace std;

bool hayPares(const list<int> & lista){
    for (auto item : lista){
        if (item % 2 == 0){
            return true;
        }
    }
    return false;
}

class Matriz_sesgada{
private:
    //un vector de listas
    //cada entrada del vector es una lista, cada lista es una fila de la matriz
    vector<list<int>> matriz;
public:
    int operator()(int fil, int col){
        //obtenemos la fila con la que trabajamos con el operador [] del vector
        list<int> fila_actual = matriz[fil];
        //ahora debemos recorrer la fila hasta el elemento col
        int i=0;
        list<int>::iterator it = fila_actual.end();
        int elemento;
        for (it = fila_actual.begin(); it != fila_actual.end() && i < col; ++it){
            ++it;
            ++i;
        }
        if (it != fila_actual.end())
            elemento = *it;
        return elemento;
    }

    class iterador{
    private:
        int i,j;
        int n_i, n_j;
        Matriz_sesgada * obj;
    public:
        iterador() = default; // el resto de operaciones básicas, operador asignacion, destructor y constructor de copia tambien las dejamos "default"

        bool operator==(const iterador & otro){
            return i == otro.i && j == otro.j;
        }

        bool operator!=(const iterador & otro){
            return i != otro.i || j != otro.j;
        }

        int operator*(){
            return (*obj)(i,j);
        }

        iterador & operator++(){ // no me ha dado tiempo a cambiarlo
            ++it;
            while (it != final && !hayPares(*it)){
                list<int>::iterator lit = (*it).begin();
                while ((*lit) % 2 != 0){
                    ++lit;
                }
                if (lit == (*it).end())
            }
            return *this;
        }


        friend class Matriz_sesgada;
    };

    iterador begin(){
        iterador nuevo;
        nuevo.i = 0;
        nuevo.j = 0;
        nuevo.n_j = matriz.begin()->size();
        nuevo.n_i = matriz.size();
        if (nuevo.i != nuevo.n_i && nuevo.j != nuevo.n_j && !hayPares(*(matriz.begin())))
            ++nuevo;
        return nuevo;
    }

    iterador end(){
        iterador nuevo;
        nuevo.i = matriz.size();
        nuevo.j = matriz.begin()->size();
        nuevo.n_j = matriz.begin()->size();
        nuevo.n_i = matriz.size();
        return nuevo;
    }
};