//
// Created by salva on 21/1/21.
//

#include <iostream>
#include "bintree.h"
#include <vector>
#include <list>
using namespace std;
//funcion que devuelve un conjunto de listas con los nodos que recorre hasta encontrar una hoja
vector<list<int>> camino_hasta_hoja(bintree<int>::node n) {
    //caso base, nodo nulo
    if (n.null()) {
        return vector<list<int>>();
    } else if (n.left().null() && n.right().null()) { //si es una hoja
        list<int> aux(1, *n);
        vector<list<int>> v;
        v.push_back(aux);
        return v;
    } else { // caso general
        vector<list<int>> todos;
        vector<list<int>> izquierda;
        vector<list<int>> derecha;
        if (!n.left().null())
            izquierda = camino_hasta_hoja(n.left());
        if (!n.right().null())
            derecha = camino_hasta_hoja(n.right());
        todos = izquierda;
        for (auto e : izquierda){
            e.push_front(*n);
            for (auto j  : e)
                cout << j << " ";
        }
        cout << endl;
        for (auto e : derecha){
            e.push_front(*n);
            for (auto j  : e){
                cout << j << " ";
            }
        }
        cout << endl;

        for (auto e : derecha) {
            if (!e.empty())
                todos.push_back(e);
        }
        return todos;
    }
}


vector<list<int>> secuenciascaminos(bintree<int> A, int nivel){
    vector<list<int>> caminos;
    vector<list<int>> actual;
    list<bintree<int>::node> nodos_nivel;
    //tenemos una pareja de datos en la que almacenamos los nodos y su nivel
    pair<bintree<int>::node, int> pareja(A.root(), 0);
    pair<bintree<int>::node, int> p_aux;
    queue<pair<bintree<int>::node,int>> cola;
    cola.push(pareja);
    // lo que queremos es obtener una lista de los nodos que visitamos que esten en el nivel que queremos
    // para despues obtener su camino hacia las hojas
    while (!cola.empty()){
        pareja = cola.front();
        cola.pop();
        if (pareja.second == nivel){
            nodos_nivel.push_back(pareja.first);
        }
        else{
            if (!pareja.first.left().null()){
                p_aux.first = pareja.first.left();
                p_aux.second = pareja.second + 1;
                cola.push(p_aux);
            }
            if (!pareja.first.right().null()){
                p_aux.first = pareja.first.right();
                p_aux.second = pareja.second + 1;
                cola.push(p_aux);
            }
        }
    }
    //ahora que tenemos la lista de nodos, encontramos los caminos hasta las hojas
    for (auto nodo : nodos_nivel){
        actual = camino_hasta_hoja(nodo);
        for (auto e : actual){
            caminos.push_back(e);
        }
    }
    return caminos;
}

int main(int argc, char * args[]){
    bintree<int> arbol(1);
    arbol.insert_left(arbol.root(),4);
    arbol.insert_right(arbol.root(),7);
    arbol.insert_left(arbol.root().left(),8);
    arbol.insert_right(arbol.root().left(),9);
    arbol.insert_left(arbol.root().left().right(),6);
    arbol.insert_left(arbol.root().right(),11);
    arbol.insert_right(arbol.root().right(),10);
    arbol.insert_right(arbol.root().right().left(),14);
    arbol.insert_left(arbol.root().right().left().right(),12);
    arbol.insert_right(arbol.root().right().left().right(),13);

    vector<list<int>> lista = secuenciascaminos(arbol,atoi(args[1]));
    for (auto i : lista){
        for (auto j : i){
            cout << j << " ";
        }
        cout << endl;
    }

}