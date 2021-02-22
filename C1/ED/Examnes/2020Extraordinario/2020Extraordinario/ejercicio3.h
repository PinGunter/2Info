#pragma once
#include "bintree.h"

// funcion que devuelve la suma de las etiquetas de el subarbol con raiz nodo
int suma_nodos(bintree<int>::node nodo) {
	//Casos base
	if (nodo.null())
		return 0;
	else if (nodo.left().null() && nodo.right().null())
		return *nodo;
	else { //caso general
		int suma_izquierda = suma_nodos(nodo.left());
		int suma_derecha = suma_nodos(nodo.right());
		return suma_izquierda + suma_derecha + *nodo;
	}
}

void prune_to_level(bintree<int>& A, int level) {
	queue<pair<bintree<int>::node, int>> cola;
	pair<bintree<int>::node, int> p(A.root(), 0);
	pair<bintree<int>::node, int> aux;
	bintree<int>destino;

	cola.push(p);

	while (!cola.empty()) {
		p = cola.front();
		cola.pop();

		if (p.second == level) {
			*(p.first) = suma_nodos(p.first);
			A.prune_left(p.first, destino);
			A.prune_right(p.first, destino);
		}

		else {
			if (!p.first.left().null()) {
				aux.first = p.first.left();
				aux.second = p.second + 1;
				cola.push(aux);
			}
			if (!p.first.right().null()) {
				aux.first = p.first.right();
				aux.second = p.second + 1;
				cola.push(aux);
			}
		}
	}

}

