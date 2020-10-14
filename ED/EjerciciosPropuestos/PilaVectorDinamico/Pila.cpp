// Salvador Romero Cortés
#include "Pila.h"
#include <cassert>

void Pila::copiar(const Pila& p)
{
	for (int i = 0; i < p.nelem; ++i) {
		datos[i] = p.datos[i];
	}
	nelem = p.nelem;
}

void Pila::resize(int n)
{
	if (n + nelem > 0) {
		Tbase* nuevo = new Tbase[n + nelem];
		for (int i = 0; (i < nelem) && (i < nelem + n); ++i)
			nuevo[i] = datos[i];
		delete[] datos;
		datos = nuevo;
		reservados += n;
	}
}

void Pila::liberar()
{
	if (datos != nullptr) {
		delete[] datos;
		datos = nullptr;
	}
	reservados = nelem = 0;
}

void Pila::reservar(int n)
{
	if (datos != nullptr)
		liberar();
	
	datos = new Tbase[n];
	reservados = n;
	nelem = 0;

	for (int i = 0; i < reservados; ++i)
		datos[i] = 0;
}

Pila::Pila(int tam)
{
	datos = nullptr;
	reservar(tam);
}

Pila::Pila(const Pila& p)
{
	datos = nullptr;
	reservar(p.reservados);
	copiar(p);
}

Pila::~Pila()
{
	liberar();
}

Pila& Pila::operator=(const Pila& p)
{
	if (this != &p) {
		resize(nelem-p.nelem);
		copiar(p);
	}
	return *this;
}

bool Pila::vacia() const{
	return nelem == 0;
}

void Pila::poner(const Tbase& c)
{
	if (nelem == reservados)
		resize(2 * reservados);
	datos[nelem++] = c;
}

void Pila::quitar()
{
	assert(nelem > 0);
	nelem--;
	if (nelem < reservados / 4)
		resize(reservados / 2);
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

Pila & Pila::operator--(int n)
{
	quitar();
	return *this;
}

void Pila::operator+=(const Tbase& c)
{
	poner(c);
}
