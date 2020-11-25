#include <iostream>
#include "ColaPrioridad.h"

ostream & operator<<(ostream &os, const ColaPrioridad<char>::tipo &t){
    os << "Elemento: " << t.get_elemento() << " Prioridad: " << t.get_prioridad() << endl;
    return os;
}

int main() {
    srand(time(NULL));
    ColaPrioridad<char> cola;
    char base = 'a';


    cout << "Insertando datos" << endl;
    for (int i=0; i < 10; i++){
        char nc = rand () % 26 + base;
        typename ColaPrioridad<char>::tipo nuevo(nc,nc) ;
        cout << nuevo;
        cola.poner(nuevo);
    }
    cout << "Leyendo datos" << endl;
    for (int i=0; i< 10; i++){
        cout << cola.frente();
        cola.quitar();
    }

    return 0;
}
