//
// Created by salva on 21/1/21.
//
#include <iostream>
#include <list>
#include <set>
using namespace std;

//funcion para comprobar que todos los elementos de interior esten en grande
bool conjuntoEnConjunto(const set<int> & interior, const set<int> & grande){
    bool esta = true;
    for (auto it = interior.begin(); it != interior.end() && esta; ++it){
        if (grande.find(*it) == grande.end())
            esta = false;
    }
    return esta;
}

bool proper_subset(const list<set<int>> & L){
    //tenemos que comprobar que cada set de la lista este dentro del siguiente
    //recorremos todos los sets y luego comprobamos que este ese set en los set siguientes
    bool sub_propio = true;
    set<int> actual;
    list<set<int>>::const_iterator jt;
    for (auto it = L.begin(); it != L.end() && sub_propio; ++it){
        //*it sera el set con el que estemos trabajando en este momento
        actual = *it;
        //recorremos los siguientes, si alguno no se encuentra en alguno de los siguientes,
        // sub_propio false y detenemos las iteraciones
        jt = it;
        ++jt;       //iterador que comienza en el siguiente set
        while(jt != L.end() && sub_propio){
            if (!conjuntoEnConjunto(actual,*jt))
                sub_propio = false;
            ++jt;
        }
    }
    return sub_propio;
}