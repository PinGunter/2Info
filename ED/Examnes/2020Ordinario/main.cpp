//
// Created by salva on 17/1/21.
//
#include "ejercicio2.h"
#include "Ejercicio3.h"
#include "ejercicio4.h"
#include "ejercicio5.h"
#include <iostream>

using namespace std;

int main(){
//    char a[]={'a', 'a', 'a', 'a', 'a',
//              'b', 'b', 'b',
//              'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c',
//              'd', 'd', 'd', 'd', 'd', 'd'};
//    int tam = sizeof(a)/sizeof (a[0]);
//    vector<char> v (a,a+tam);
//    ejercicio2 prueba(v);
//    for (int i=0; i < tam; i++){
//        cout << "Letra: " << v[i] << " - Posicion: " << i << " Letra obtenida " << prueba.getElementByPosition(i) << endl;
//    }
//    cout << " == Iterador par == " << endl;
//    for (auto it = prueba.begin(); it != prueba.end(); ++it){
//        cout << (*it).first << " " << (*it).second << endl;
//    }
//    list<int> lista;
//    int l [] = {
//            1, -2, 3, -3, -1, 2, 5
//    };
//    int tam = sizeof (l) / sizeof (l[0]);
//    for (int i=1; i < tam; i++){
//        lista.push_back(i);
//    }
//    int minimo = minsum(lista);
//    int min_generico = minsum_generico(lista);
//    cout << lista << endl;
//    cout << minimo << endl;
//    cout << min_generico << endl;
//

    // Creamos el árbol:

    //        3
    //      /  \
    //     6    8
    //     \   / \
    //     8  5   4
    //    /   \
    //   3    4

//    list<int> listanodos;
//    bintree<int> Arb(3);
//    Arb.insert_left(Arb.root(), 6);
//    Arb.insert_right(Arb.root(), 8);
//    Arb.insert_right(Arb.root().left(), 8);
//    Arb.insert_left(Arb.root().left().right(), 3);
//    Arb.insert_left(Arb.root().right(), 5);
//    Arb.insert_right(Arb.root().right(),4);
//    Arb.insert_right(Arb.root().right().left(),4);
//
//
//    cout << "caminosminimos:" <<endl;
//    listanodos=caminodemenores(Arb);
//
//    cout << listanodos;
//
//    bintree<int> arbol2(1);
//    arbol2.insert_left(arbol2.root(), 14);
//    arbol2.insert_right(arbol2.root(), 5);
//    arbol2.insert_left(arbol2.root().left(), 77);
//    arbol2.insert_right(arbol2.root().left(), 6);
//    arbol2.insert_left(arbol2.root().right(), 109);
//    arbol2.insert_left(arbol2.root().left().right(), 3);
//    arbol2.insert_right(arbol2.root().left().right(), 8);
//
//    listanodos = caminodemenores(arbol2);
//
//    cout <<listanodos;


    vector<set<int>> vs1({{0}, {1}, {2}, {0,1,2}});
    cout << vs1 << " ==> " <<vs1[mas_conectado(vs1)] << endl;
    cout<<"El conjunto mas conectado es "<<mas_conectado(vs1)<<endl;

    vector<set<int>> vs2({{0,1,2},{0},{1},{2}});

    cout << vs2 << " ==> " <<vs2[mas_conectado(vs2)] << endl;
    cout<<"El conjunto mas conectado es "<<mas_conectado(vs2)<<endl;

    vector<set<int>> vs3({{0,6,9}, {5,6,9}, {5}, {1}, {5,9}, {5}, {1,5,7}});

    cout << vs3 << " ==> " <<vs3[mas_conectado(vs3)] << endl;
    cout<<"El conjunto mas conectado es "<<mas_conectado(vs3)<<endl;
}