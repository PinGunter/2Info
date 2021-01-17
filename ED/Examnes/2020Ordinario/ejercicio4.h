//
// Created by salva on 17/1/21.
//

#ifndef INC_2020ORDINARIO_EJERCICIO4_H
#define INC_2020ORDINARIO_EJERCICIO4_H
#include <iostream>
#include <list>
#include <utility>
#include "bintree.h"
using namespace std;

pair<int,list<int>> caminodemenores_nodo(const bintree<int>::node & nodo){
    //caso base, no tenga hijos o sea nulo
    if (nodo.null()){
        return pair<int,list<int>>(1<<31 -1, list<int>());
    }
    else if (nodo.left().null() && nodo.right().null()) {
            return pair<int, list<int>>(*nodo, list<int>(1, *nodo));
    }
    else{
        pair<int,list<int>> cam_izq = caminodemenores_nodo(nodo.left());
        pair<int,list<int>> cam_der = caminodemenores_nodo(nodo.right());

        if (cam_izq.first < cam_der.first){
            cam_izq.second.push_front(*nodo);
            cam_izq.first+=*nodo;
            return cam_izq;
        }else{
            cam_der.second.push_front(*nodo);
            cam_der.first+=*nodo;
            return cam_der;
        }
    }
}


list<int> caminodemenores(const bintree<int> & A){
    return caminodemenores_nodo(A.root()).second;
}


#endif //INC_2020ORDINARIO_EJERCICIO4_H
