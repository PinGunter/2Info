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
	Pila & operator--(int n);
	void operator+=(const T& c);
};


template <typename T>
void Pila<T>::copiar(const Pila<T>& p)
{
	for (int i = 0; i < p.nelem; ++i) {
		datos[i] = p.datos[i];
	}
	nelem = p.nelem;
}

template <typename T>
void Pila<T>::resize(int n)
{
	if (n + nelem > 0) {
		T* nuevo = new T[n + nelem];
		for (int i = 0; (i < nelem) && (i < nelem + n); ++i)
			nuevo[i] = datos[i];
		delete[] datos;
		datos = nuevo;
		reservados += n;
	}
}

template <typename T>
void Pila<T>::liberar()
{
	if (datos != nullptr) {
		delete[] datos;
		datos = nullptr;
	}
	reservados = nelem = 0;
}

template <typename T>
void Pila<T>::reservar(int n)
{
	if (datos != nullptr)
		liberar();

	datos = new T[n];
	reservados = n;
	nelem = 0;

	for (int i = 0; i < reservados; ++i)
		datos[i] = 0;
}

template <typename T>
Pila<T>::Pila(int tam)
{
	reservar(tam);
}

template <typename T>
Pila<T>::Pila(const Pila<T>& p)
{
	reservar(p.reservados);
	copiar(p);
}

template <typename T>
Pila<T>::~Pila()
{
	liberar();
}

template <typename T>
Pila<T>& Pila<T>::operator=(const Pila<T>& p)
{
	if (this != &p) {
		resize(nelem - p.nelem);
		copiar(p);
	}
	return *this;
}

template <typename T>
bool Pila<T>::vacia() const {
	return nelem == 0;
}

template <typename T>
void Pila<T>::poner(const T& c)
{
	if (nelem == reservados)
		resize(2 * reservados);
	datos[nelem++] = c;
}

template <typename T>
void Pila<T>::quitar()
{
	assert(nelem > 0);
	nelem--;
	if (nelem < reservados / 4)
		resize(reservados / 2);
}

template <typename T>
T& Pila<T>::tope()
{
	assert(nelem > 0);
	return datos[nelem - 1];
}

template <typename T>
const T& Pila<T>::tope() const
{
	assert(nelem > 0);
	return datos[nelem - 1];
}

template <typename T>
Pila<T>& Pila<T>::operator--(int n)
{
	quitar();
	return *this;
}

template <typename T>
void Pila<T>::operator+=(const T& c)
{
	poner(c);
}

#endif