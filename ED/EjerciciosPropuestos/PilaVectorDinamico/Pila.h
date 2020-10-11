#ifndef PILA_H
#define PILA_H
typedef char Tbase;
const int TAM = 10;
class Pila
{
private:
	Tbase *datos;
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
	void poner(const Tbase& c);
	void quitar();
	Tbase& tope();
	const Tbase& tope() const;
	Pila & operator--(int n);
	void operator+=(const Tbase& c);
};

#endif