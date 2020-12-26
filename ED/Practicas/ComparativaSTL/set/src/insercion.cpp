/**
 * @file insercion.cpp
 * @author Abel Ríos González
 * @author Salvador Romero Cortés
 * @brief Archivo para comparar los tiempos de inserción de la estructuras de datos de la STL <set>
 */
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
using namespace std;

void sintaxis()
{
  cerr << "Error, se necesitan más argumentos.\n Ejecución correcta: ./binario <numero_de_elementos>" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]){
  if (argc != 2)  {
    sintaxis();
  }
  int N = atoi(argv[1]);

  //Preparamos el vector
  int numeros[N];
  for (int i=1; i <= N; i++){
    numeros[i] = i;
  }
  set<int> set(numeros, numeros+N);

  clock_t tini, tfin;
  tini = clock();
  for (int i=0; i < 1000000; i++)
    set.insert(N+1);  
  tfin = clock();

  cout << N << "\t" << ((tfin-tini)/1000000.0)/(double)CLOCKS_PER_SEC << endl;

  return 0;
}

/*
#include <iostream>
#include <ctime>    // Recursos para medir tiempos
#include <cstdlib>  // Para generación de números pseudoaleatorios

using namespace std;

int buscar(const int *v, int n, int x)
{
  int i=0;
  while (i<n && v[i]!=x) 
    i=i+1;
  if (i<n) 
    return i;
  else
    return -1;
}

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  N: Naño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de Naño N con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
  // Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int N=atoi(argv[1]);     // Naño del vector
  int vmax=atoi(argv[2]);    // Valor máximo
  if (N<=0 || vmax<=0)
    sintaxis();
  
  // Generación del vector aleatorio
  int *v=new int[N];       // Reserva de memoria
  srand(time(0));            // Inicialización del generador de números pseudoaleatorios
  for (int i=0; i<N; i++)  // Recorrer vector
    v[i] = rand() % vmax;    // Generar aleatorio [0,vmax[
  
  clock_t tini;    // AnoNos el tiempo de inicio
  tini=clock();
  
  int x = vmax+1;  // Buscamos un valor que no está en el vector
  buscar(v,N,x); // de esta forma forzamos el peor caso
  
  clock_t tfin;    // AnoNos el tiempo de finalización
  tfin=clock();

  // Mostramos resultados
  cout << N << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;
  
  delete [] v;     // Liberamos memoria dinámica
}
*/