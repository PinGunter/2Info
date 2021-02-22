//
// Created by salva on 20/1/21.
//

#ifndef INC_2019ORDINARIO_EJERICICO3_H
#define INC_2019ORDINARIO_EJERICICO3_H
#include <iostream>

pair<list<int>::const_iterator,list<int>::const_iterator> lista_en_lista(const list<int> & buscado, const list<int> & lista){
    bool encontrado = false;
    list<int>::const_iterator lit = lista.begin();
    list<int>::const_iterator bit = buscado.begin();
    list<int>::const_iterator posicion, fin;
    while (lit != lista.end() && !encontrado){
        if (*lit == *bit){  // si coinciden aumenta la posicion del buscado
            if (bit == buscado.begin()) {   //si es la primera coincidencia guarda la posicion
                posicion = lit;
            }
            ++bit;
            if (bit == buscado.end()){  //cuando se acabe la lista buscada es que se ha encontrado y guarda la posicion final
                encontrado = true;
                fin = lit;
                ++fin;
            }
        }else{
            bit = buscado.begin();      // si se rompe la cadena se resetea la posicion buscada
        }
        ++lit;
    }
    if (!encontrado){
        posicion = lista.end();
        fin = lista.end();
    }

    return pair<list<int>::const_iterator,list<int>::const_iterator>(posicion,fin);
}

void reemplaza(list<int> & l, const list<int> & seq, const list<int> & reemp){
    list<int>::const_iterator posicion, fin;
    pair<list<int>::const_iterator,list<int>::const_iterator> pareja = lista_en_lista(seq,l);
    posicion = pareja.first; fin = pareja.second;
    int borrados = 0;
    while (posicion != l.cend()){
        posicion = l.erase(posicion,fin);
        l.insert(posicion,reemp.begin(),reemp.end());
        pareja = lista_en_lista(seq,l);
        posicion = pareja.first; fin = pareja.second;
    }
}
#endif //INC_2019ORDINARIO_EJERICICO3_H
