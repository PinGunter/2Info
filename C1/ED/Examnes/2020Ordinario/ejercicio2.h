//
// Created by salva on 17/1/21.
//

#ifndef INC_2020ORDINARIO_EJERCICIO2_H
#define INC_2020ORDINARIO_EJERCICIO2_H
#include <map>
#include <vector>
#include <iostream>
class ejercicio2 {
private:
    std::map<char,int> mapa;
public:
    ejercicio2(std::vector<char> v){
        for (auto it = v.begin(); it != v.end(); ++it){
            mapa[(*it)] = 1;
        }
        char anterior = v[0];
        for (int i=1; i < v.size(); i++) {
            if (v[i] == anterior)
                mapa[anterior]++;
            anterior = v[i];
        }
    }

    void mostrar(){
        for (auto it = mapa.begin(); it != mapa.end(); ++it){
            std::cout << (*it).first << " " << (*it).second << std::endl;
        }
    }

    char getElementByPosition(int pos){
        int actual = 0;
        char resultado;
        bool encontrado = false;
        for (auto it = mapa.begin(); it != mapa.end() && !encontrado; ++it){
            actual += (*it).second;
            if (pos < actual) {
                encontrado = true;
                resultado = (*it).first;
            }
        }
        if (!encontrado){
            return '\0';
        } else{
            return resultado;
        }
    }

    class iterador_pares{
    private:
        std::map<char,int>::iterator it, fin;
    public:
        iterador_pares() = default;
        iterador_pares & operator=(const iterador_pares & otro) = default;
        bool operator==(const iterador_pares & otro){
            return it == otro.it;
        }
        bool operator!=(const iterador_pares & otro){
            return it != otro.it;
        }

        std::pair<char,int> operator*(){
            return *it;
        }

        iterador_pares & operator++(){
            ++it;
            while ((*it).second % 2 != 0 && it != fin){
                ++it;
            }
            return *this;
        }
        friend class ejercicio2;
    };

    iterador_pares begin(){
        iterador_pares nuevo;
        nuevo.it = mapa.begin();
        nuevo.fin = mapa.end();
        if ((*nuevo).second % 2 != 0){
            ++nuevo;
        }
        return nuevo;
    }

    iterador_pares end(){
        iterador_pares nuevo;
        nuevo.it = mapa.end();
        nuevo.fin = mapa.end();
        return nuevo;
    }
};


#endif //INC_2020ORDINARIO_EJERCICIO2_H
