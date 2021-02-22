/**
 * @author Salvador Romero Cortés
 * */

#include <iostream>
#include "Pila.hpp"
#include "Cola.hpp"

using namespace std;


int main(){
    Pila<char> p;
    Cola<char> c;
    char dato;
    cout << "Escriba una frase" << endl;
    while ((dato = cin.get()) != '\n')
    if (dato != ' '){
        p.poner(dato);
        c.poner(dato);
    }

    bool palindromo = true;
    while (!p.vacia() && palindromo){
        if (c.frente() != p.tope())
         palindromo = false;
    p.quitar();
    c.quitar();
    }
    cout << endl;

    cout << "La frase "
         << (palindromo ? "es" : "no es")
         << " un palindromo" << endl;
        
    return 0;
}