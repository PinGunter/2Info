/**
 * @file insercion.cpp
 * @author Abel Ríos González
 * @author Salvador Romero Cortés
 * @brief Archivo para comparar los tiempos de busqueda de la estructuras de datos de la STL <vector>
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

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    sintaxis();
  }
  int N = atoi(argv[1]);

  //Preparamos el vector
  vector<int> vect(N);
  int aux, i;
  clock_t tini, tfin;
  //insertamos los elementos de 1 a N
  for (i = 1; i <= N; i++)
  {
    vect[i] = i;
  }

  cout << N << "\t" << (tfin - tini) / (double)CLOCKS_PER_SEC << endl;

  return 0;
}