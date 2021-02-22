//
// Created by salva on 20/1/21.
//

#ifndef INC_2019ORDINARIO_EJERCICIO4_H
#define INC_2019ORDINARIO_EJERCICIO4_H
#include <iostream>
#include <list>
#include "bintree.h"
using namespace std;
list<int>nivel(const bintree<int> & A){
    queue<pair<bintree<int>::node, int>> cola;
    pair<bintree<int>::node, int> p(A.root(),0); // pareja con el nodo y el nivel en el que se encuentra
    bintree<int>::node nodo_actual;
    list<int> resultado;
    list<int> l_aux;
    int nivel = 0;
    cola.push(p);
    while (!cola.empty()){
        p = cola.front();
        if (p.second == nivel){
            l_aux.push_back(*(p.first));
        }else {
            if (l_aux.size() > resultado.size()) {
                resultado = l_aux;
                nivel++;
            }
            l_aux.clear();
            l_aux.push_back(*(p.first));
        }
        cola.pop();
        nodo_actual = p.first;
        int nivel_aux = p.second+1;
        if (!nodo_actual.left().null()){
            p.first = nodo_actual.left();
            p.second = nivel_aux;
            cola.push(p);
        }
        if (!nodo_actual.right().null()){
            p.first = nodo_actual.right();
            p.second = nivel_aux;
            cola.push(p);
        }
    }

    if (l_aux.size() > resultado.size()){
        resultado = l_aux;
    }

    return resultado;

}
#endif //INC_2019ORDINARIO_EJERCICIO4_H
