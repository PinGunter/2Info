// Salvador Romero Cortés

#include <iostream>
#include "Pila.hpp"
using namespace std;

int main() {
	Pila<char> p,q;
	char dato;

	cout << "Escriba una frase" << endl;
	while ((dato = cin.get()) != '\n')
		p += dato;

	cout << "La escribimos del rev�s" << endl;
	while (!p.vacia()) {
		cout << p.tope();
		q += p.tope();
		p--;
	}

	cout << endl << "La frase original era" << endl;
	while (!q.vacia()) {
		cout << q.tope();
		q--;
	}

	cout << endl;
	return 0;
}