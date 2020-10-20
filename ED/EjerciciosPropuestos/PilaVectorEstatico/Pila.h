// Salvador Romero Cortés
#ifndef PILA_H
#define PILA_H
typedef char Tbase;
const int TAM = 500;
class Pila
{
private:
	Tbase datos[TAM];
	int nelem;

	void copiar(const Pila& p);
public:
	Pila();
	Pila(const Pila& p);
	~Pila() = default;
	Pila & operator=(const Pila& p);

	bool vacia() const;
	void poner(const Tbase& c);
	void quitar();
	Tbase& tope();
	const Tbase& tope() const;
	Pila  operator--(int n);
	void operator+=(const Tbase& c);
};

#endif