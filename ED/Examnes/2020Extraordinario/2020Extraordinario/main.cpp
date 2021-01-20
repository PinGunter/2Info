#include <iostream>
#include "ejercicio2.h"
#include "ejercicio3.h"
#include "ejercicio4.h"
#include "ejercicio6.h"

using namespace std;

int main() {
    /*list<int> L1 = { 1,2,3,4,1,3,2,5,6,8,3 };
    list<int> L2 = { 6,10,5,6,11 };

    if (check_sum(L1, L2))
        cout << endl << "Los elementos de L2 sí se obtienen a partir de L1" << endl;
    else
        cout << endl << "Los elementos de L2 no se obtienen a partir de L1" << endl;*/

    //bintree<int> arbol(10);
    //arbol.insert_left(arbol.root(), 7);
    //arbol.insert_right(arbol.root(), 15);
    //arbol.insert_left(arbol.root().left(), 6);
    //arbol.insert_right(arbol.root().left(), 9);
    //arbol.insert_left(arbol.root().right(), 12);
    //arbol.insert_right(arbol.root().right(), 20);
    //arbol.insert_left(arbol.root().right().right(), 8);
    //arbol.insert_right(arbol.root().right().right(), 14);
    //arbol.insert_right(arbol.root().right().right().right(), 2);

    //prune_to_level(arbol, 1);

    //cout << "Preorden del arbol resultante: ";
    //for (bintree<int>::preorder_iterator i = arbol.begin_preorder(); i != arbol.end_preorder(); ++i)
    //    cout << *i << " ";
    //cout << endl;

    //cout << "Listado por niveles: ";
    //for (bintree<int>::level_iterator i = arbol.begin_level(); i != arbol.end_level(); ++i)
    //    cout << *i << " ";
    //cout << endl;
    
/*    cout << "Raiz: " << suma_nodos(arbol.root()) << endl;
    cout << "Izquierdo: " << suma_nodos(arbol.root().left()) << endl;
    cout << "Derecho: " << suma_nodos(arbol.root().right()) << endl;


    cout << "Recorrido por niveles" << endl;
    for (auto it = arbol.begin_level(); it != arbol.end_level(); ++it) {
        cout << *it << endl;
    }*/


    //Creamos el árbol:
//        10
//      /   \
  //     6     15
  //    / \   / \
  //   5   8 12  20
  //      /   \
  //     7     13


    //bintree<int> arbol(10);
    //arbol.insert_left(arbol.root(), 6);
    //arbol.insert_left(arbol.root().left(), 5);
    //arbol.insert_right(arbol.root().left(), 8);
    //arbol.insert_left(arbol.root().left().right(), 7);
    //arbol.insert_right(arbol.root(), 15);
    //arbol.insert_left(arbol.root().right(), 12);
    //arbol.insert_right(arbol.root().right(), 20);
    //arbol.insert_right(arbol.root().right().left(), 13);

    ////Para probar el algoritmo sobre este árbol,
    ////nos situamos el nodo con clave menor.
    ////Para ello, partimos de la raíz y
    ////descendemos por la izquierda mientras sea posible
    //bintree<int>::node n = arbol.root();
    //while (!n.left().null())
    //    n = n.left();

    ////Ahora usamos siguiente_inorden() para mostrar
    ////los nodos del árbol en orden creciente
    //while (!n.null()) {
    //    cout << *n << " ";
    //    n = siguiente_inorden(n);
    //}
    //cout << endl;

    ////Probamos la segunda versión del algoritmo
    //n = arbol.root();
    //while (!n.left().null())
    //    n = n.left();
    //while (!n.null()) {
    //    cout << *n << " ";
    //    n = siguiente_inorden(n);
    //}
    //cout << endl;

    Diccionario c;
    Diccionario::iterador_primos it;

    srand(time(NULL));



    for (int i = 1; i <= 1000; i++) {
        list<int> lista;
        for (int j = 0; j < 3; j++)
            lista.push_back(rand() % 100);
        c[i] = lista;
    }

    //cout << c;

    for (auto it = c.begin(); it != c.end(); ++it) {
        auto par = *it;
        //    if (AllPrimos(par.second)){
        cout << par.first << ": ";
        for (auto itl = par.second.begin(); itl != par.second.end(); ++itl)
            cout << *itl << " ";
        cout << endl;
        //    }
    }

}
