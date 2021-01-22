//
// Created by salva on 20/1/21.
//

#ifndef INC_2019ORDINARIO_EJERCICIO2_H
#define INC_2019ORDINARIO_EJERCICIO2_H
#include <iostream>
#include <map>
#include <list>
using namespace std;

ostream & operator<<(ostream & os, const list<int> & lista){
    for (auto e : lista){
        os << e << " ";
    }
    return os;
}

ostream & operator<<(ostream & os, const map<string,list<int>>  & datos){
    for (auto palabra : datos){
        os << "Palabra: " << palabra.first << " - Posiciones: " << palabra.second << endl;
    }
    return os;
}


bool enLista(int i, const list<int> & lista){
    for (auto item : lista){
        if (item == i){
            return true;
        }
    }
    return false;
}

// tmb se puede hacer mas eficiente con set en lugar de list
class Documento{
private:
    map<string,list<int>> datos;
public:
    Documento(const list<string> & texto){
        int posicion = 0;
        for (auto palabra : texto){
            datos[palabra].push_back(posicion);
            posicion++;
        }
    }

    list<int>posiciones(string palabra){
        return datos[palabra];
    }

    string palabra(int i){
        for (auto parejas : datos){
            if (enLista(i,parejas.second)){
                return parejas.first;
            }
        }
        return "";
    }

    friend ostream & operator<<(ostream & os, const Documento & d){
        os << d.datos;
        return os;
    }
};
#endif //INC_2019ORDINARIO_EJERCICIO2_H
