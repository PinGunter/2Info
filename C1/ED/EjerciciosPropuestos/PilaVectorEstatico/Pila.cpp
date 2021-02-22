// Salvador Romero Cortés
#include "Pila.h"
#include <cassert>

void Pila::copiar(const Pila& p)
{
	for (int i = 0; i < p.nelem; ++i) {
		this->datos[i] = p.datos[i];
	}
	this->nelem = p.nelem;
}

Pila::Pila()
{
	for (int i = 0; i < TAM; ++i)
		datos[i] = 0;
	nelem = 0;
}

Pila::Pila(const Pila& p)
{
	this->copiar(p);
}

Pila& Pila::operator=(const Pila& p)
{
	if (this != &p) {
		this->copiar(p);
		return *this;
	}
}

bool Pila::vacia() const{
	return nelem == 0;
}

void Pila::poner(const Tbase& c)
{
	assert(nelem < TAM);
	datos[nelem++] = c;
}

void Pila::quitar()
{
	assert(nelem > 0);
	nelem--;
}

Tbase& Pila::tope()
{
	assert(nelem > 0);
	return datos[nelem - 1];
}

const Tbase& Pila::tope() const
{
	assert(nelem > 0);
	return datos[nelem - 1];
}

Pila  Pila::operator--(int n)
{
	Pila copia(*this);
	quitar();
	return copia;
}

void Pila::operator+=(const Tbase& c)
{
	poner(c);
}
