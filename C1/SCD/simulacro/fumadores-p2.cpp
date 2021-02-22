/**
 * @file fumadores.cpp
 * @author Salvador Romero Cortés
 * @brief ejercicio de estanquero-fumadores usando monitores SU
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


const int num_fumadores = 3;



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
// funciones estanqueras y fumadoras
//----------------------------------------------------------------------

int producirIngrediente()
{
   //this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));
   int ingrediente = aleatorio<0,num_fumadores-1>();
   unique_lock<mutex> guarda(mtx);
   cout << "Estanquera produce ingrediente: " << ingrediente << endl;
   return ingrediente;
}
//----------------------------------------------------------------------

void fumar(int indice)
{
   // mutex para que la salida no se mezcle
   // comentado para ver varios fumadores simultaneos
   //unique_lock<mutex> guarda(mtx);
   cout << "                  Fumador " << indice << " empieza a fumar" << endl;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<500, 700>()));
   cout << "                  Fumador " << indice << " deja de fumar" << endl;

}

//----------------------------------------------------------------------

/**
 * @brief clase que representa el monitor de estanco
 */

class Estanco : public HoareMonitor
{
private:
   //constantes que indican cuando se debe dormir y cuandos se debe despertar
   static const int toca_dormir = 3;
   static const int toca_despertar = 4;

   int mostrador;
   //vector para llevar la cuenta de los valores producidos
   int n_producido [num_fumadores];
   //variable condicion extra para cuando le toque dormir a cada fumador
   CondVar mostrador_vacio, esta_mio[num_fumadores], me_duermo[num_fumadores];
public:
   Estanco();
   void ponerIngrediente(int ingre);
   void esperarRecogida();
   void obtenerIngrediente(int i);
   void dormir(int num_fumador, int veces);
};

Estanco::Estanco(){
   mostrador = -1;   //mostrador == -1 quiere decir que esta vacio
   mostrador_vacio = newCondVar();
   for (int i=0; i < num_fumadores; i++){
      esta_mio[i] = newCondVar();
      n_producido[i] = 0; //inicializamos el vector de producidos
      me_duermo[i] = newCondVar(); //inicializamos las variables condicion
   }

}

void Estanco::ponerIngrediente(int ingre){
   mostrador = ingre;
   n_producido[mostrador]++;
   cout << "Estanquero ha puesto ingrediente : " << mostrador << endl << flush;
   if (n_producido[mostrador] == toca_despertar){
      cout << "Despertando al fumador: " << mostrador << endl << flush;
      me_duermo[mostrador].signal();
   }
   esta_mio[ingre].signal();
}

void Estanco::esperarRecogida(){
   if (mostrador != -1) //comprobamos que no este vacio
      mostrador_vacio.wait();
}

void Estanco::obtenerIngrediente(int i){
   if (mostrador != i)
      esta_mio[i].wait();
   cout << "                  Fumador " << i << " recoge ingrediente" << endl << flush;
   mostrador = -1;      //marcamos el mostrador como vacia
   mostrador_vacio.signal();
}

void Estanco::dormir(int num_fumador, int veces){
   if (veces == toca_dormir){
      cout << "                  Fumador " << num_fumador << " se va a dormir" << endl << flush;
      me_duermo[num_fumador].wait();
   }
}

//funciones que ejecutan las hebras
void funcion_hebra_estanquera(MRef<Estanco> monitor)
{
   while (true){
      int ingrediente = producirIngrediente();
      monitor->ponerIngrediente(ingrediente);
      monitor->esperarRecogida();
   }
}

void funcion_hebra_fumadora(MRef<Estanco> monitor, int indice)
{
   int veces_fumado = 0;
   while (true){
      monitor->obtenerIngrediente(indice);
      veces_fumado++;
      monitor->dormir(indice,veces_fumado);
      fumar(indice);
   }
}

int main()
{
   // crear monitor
   MRef<Estanco> monitor = Create<Estanco>();
   // creamos las hebras
   thread hebras_fumadoras[num_fumadores],
          hebra_estanquera;
   
   //lanzamos las hebras
   hebra_estanquera = thread(funcion_hebra_estanquera,monitor);
   for (int i=0; i < num_fumadores; i++)
      hebras_fumadoras[i] = thread(funcion_hebra_fumadora,monitor,i);
   
   // esperar a que terminen las hebras
   hebra_estanquera.join();
   for (int i = 0; i < num_fumadores; i++)
      hebras_fumadoras[i].join();

}