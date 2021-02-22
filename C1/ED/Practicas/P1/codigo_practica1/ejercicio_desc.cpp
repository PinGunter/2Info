//Salvador Romero Cortés
#include <iostream>
#include <ctime>   // Recursos para medir tiempos
#include <cstdlib> // Para generación de números pseudoaleatorios
using namespace std;

void ordenar(int *v, int n)
{                                       // ----------------------------------------
  for (int i = 0; i < n - 1; i++)       // O(1) ---------------------			  |
    for (int j = 0; j < n - i - 1; j++) // O(1) ---------			|			  |
      if (v[j] > v[j + 1])
      {                  // O(1) |		|			| O(n-1) *    |
        int aux = v[j];  // O(1) |O(1)  | O(n-i+1)	| O(n-i-1) 	  | O(n^2)
        v[j] = v[j + 1]; // O(1) |		|			|			  |
        v[j + 1] = aux;  // O(1) |		|			|			  |
      }
}

int operacion(int *v, int n, int x, int inf, int sup) {
  int med;
  bool enc=false;
  while ((inf<=sup) && (!enc)) {
    med = (inf+sup)/2; 
    if (v[med]==x) 
      enc = true;
    else if (v[med] < x) 
      inf = med+1;
    else
      sup = med-1;
  }
  if (enc) 
    return med;
  else 
    return -1;
}


void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

  // Lectura de parámetros
  if (argc != 2)
    sintaxis();
  int tam = atoi(argv[1]); // Tamaño del vector
  if (tam <= 0)
    sintaxis();

  // Generación del vector aleatorio
  int *v = new int[tam];        // Reserva de memoria
  srand(time(0));               // Inicialización del generador de números pseudoaleatorios
  for (int i = 0; i < tam; i++) // Recorrer vector
    v[i] = rand() % tam;

  ordenar(v,tam);
  clock_t tini; // Anotamos el tiempo de inicio
  tini = clock();

  // Algoritmo a evaluar
  for (int i=0; i < 1000000; i++)
    bool enc = operacion(v,tam, tam+1, 0, tam - 1) == -1;

  clock_t tfin; // Anotamos el tiempo de finalización
  tfin = clock();

  // Mostramos resultados
  
  cout << tam << "\t" << ((tfin - tini)/1000000.0) / (double)CLOCKS_PER_SEC << endl;

  delete[] v; // Liberamos memoria dinámica
}
