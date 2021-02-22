//
// Created by salva on 17/1/21.
//

#ifndef INC_2020ORDINARIO_EJERCICIO5_H
#define INC_2020ORDINARIO_EJERCICIO5_H
#include <iostream>
#include <set>
#include <vector>
using namespace std;
ostream & operator <<(ostream &os, const set<int> &mi_set){
    os << "{ ";
    for(auto it=mi_set.cbegin(); it!=mi_set.end(); it++)
        os << *it << " " ;
    os << "} ";
    return os;
}
ostream & operator <<(ostream &os, const vector<set<int>> &VS){
    os << "[ ";
    for (int i=0; i<VS.size(); i++)
        os << VS[i];
    os << "]";
    return os;
}

bool tiene_interseccion_no_nula(const set<int> & uno, const set<int> & otro){
    bool tiene = false;
    for (auto it = uno.begin(); it != uno.end() && !tiene; ++it){
        if (otro.find(*it) != otro.end()){
            tiene = true;
        }
    }
    return tiene;
}

int mas_conectado(const vector<set<int>> &VS){
    int pos;
    int max, actual;
    max = -1;
    for (int i=0; i < VS.size(); i++){
        actual = 0;
        for (int j=0; j < VS.size(); j++){
            if (i!=j){
                int incremento = (tiene_interseccion_no_nula(VS[i],VS[j])) ? 1 : 0;
                actual +=incremento;
            }
        }
        if (actual > max) {
            max = actual;
            pos = i;
        }
    }
    return pos;
}
#endif //INC_2020ORDINARIO_EJERCICIO5_H
