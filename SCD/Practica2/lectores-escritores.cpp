/**
 * @file lectores-escritores.cpp
 * @author Salvador Romero Cortés
 * @brief ejercicio de lectores-escritores usando monitores SU
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "HoareMonitor.h" //clase para monitores SU

using namespace std;
using namespace HM; //espacio de nombres para los monitores

mutex mtx; //cerrojo para mostrar en pantalla


const int num_lector = 6;
const int num_escri = 6;

//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template <int min, int max>
int aleatorio()
{
   static default_random_engine generador((random_device())());
   static uniform_int_distribution<int> distribucion_uniforme(min, max);
   return distribucion_uniforme(generador);
}

//**********************************************************************
// funciones de lectura y escritura
//----------------------------------------------------------------------

void escribir(int indice)
{
   cout << "Escritor " << indice << " empieza a escribir en la estructura de datos" << endl;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 200>()));
   cout << "Escritor " << indice << " termina de escribir en la estructura de datos" << endl;
}

void leer(int indice)
{
   cout << "\tLector " << indice << " empieza a leer en la estructura de datos" << endl;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 200>()));
   cout << "\tLector " << indice << " termina de leer en la estructura de datos" << endl;
}

//----------------------------------------------------------------------

/**
 * @brief clase que representa el monitor de estanco
 */

class Lec_Esc : public HoareMonitor
{
private:
   bool escrib; //indica si un escritor esta escribiendo
   int n_lec;       //número de lectores simultaneos
   CondVar lectura,escritura;
public:
   Lec_Esc();
   void ini_lectura();
   void fin_lectura();
   void ini_escritura();
   void fin_escritura();
};

Lec_Esc::Lec_Esc(){
   escrib = false;
   n_lec = 0;
   lectura = newCondVar();
   escritura = newCondVar();
}

void Lec_Esc::ini_lectura(){
   if (escrib)
      lectura.wait();
   n_lec += 1;
   lectura.signal();
}

void Lec_Esc::fin_lectura(){
   n_lec -= 1;
   if (n_lec == 0)
      escritura.signal();
}

void Lec_Esc::ini_escritura(){
   if (n_lec > 0 || escrib)
      escritura.wait();
   escrib = true;
}

void Lec_Esc::fin_escritura(){
   escrib = false;
   if (lectura.empty())
      escritura.signal();
   else
      lectura.signal();
}

//funciones que ejecutan las hebras
void funcion_hebra_lectora(MRef<Lec_Esc> monitor, int indice)
{
   while (true){
      monitor->ini_lectura();
      leer(indice);
      monitor->fin_lectura();
      this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 200>()));
   }
}

void funcion_hebra_escritora(MRef<Lec_Esc> monitor, int indice)
{
   while (true){
      monitor->ini_escritura();
      escribir(indice);
      monitor->fin_escritura();
      this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 200>()));
   }
}

int main()
{
   // crear monitor
   MRef<Lec_Esc> monitor = Create<Lec_Esc>();
   // creamos las hebras
   thread lectores[num_lector],
          escritores[num_escri];
   
   //lanzamos las hebras
   for (int i=0; i < num_escri; i++){
      escritores[i] = thread(funcion_hebra_escritora,monitor,i);
   }   
   for (int i=0; i < num_lector; i++){
      lectores[i] = thread(funcion_hebra_lectora,monitor,i);
   }
   
   // esperar a que terminen las hebras
   for (int i=0; i < num_escri; i++){
      escritores[i].join();
   }   
   for (int i=0; i < num_lector; i++){
      lectores[i].join();
   }
}