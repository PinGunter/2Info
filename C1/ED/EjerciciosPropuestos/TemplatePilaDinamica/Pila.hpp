// Salvador Romero Cortés

#ifndef PILA_H
#define PILA_H
#include <cassert>
const int TAM = 10;

template <typename T>
class Pila
{
private:
	T *datos;
	int reservados;
	int nelem;

	void copiar(const Pila& p);
	void resize(int n);
	void liberar();
	void reservar(int n); 
public:
	Pila(int tam=TAM);
	Pila(const Pila& p);
	~Pila();
	Pila & operator=(const Pila& p);

	bool vacia() const;
	void poner(const T& c);
	void quitar();
	T& tope();
	const T& tope() const;
	Pila operator--(int n);
	void operator+=(const T& c);
};

#include "Pila.tpp"
#endif
