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
   unique_lock<mutex> guarda(mtx);
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
   int mostrador;
   CondVar mostrador_vacio, esta_mio[num_fumadores];
public:
   Estanco();
   void ponerIngrediente(int ingre);
   void esperarRecogida();
   void obtenerIngrediente(int i);
};

Estanco::Estanco(){
   mostrador = -1;   //mostrador == -1 quiere decir que esta vacio
   mostrador_vacio = newCondVar();
   for (int i=0; i < num_fumadores; i++)
      esta_mio[i] = newCondVar();
}

void Estanco::ponerIngrediente(int ingre){
   mostrador = ingre;
   esta_mio[ingre].signal();
}

void Estanco::esperarRecogida(){
   if (mostrador != -1) //comprobamos que no este vacio
      mostrador_vacio.wait();
}

void Estanco::obtenerIngrediente(int i){
   if (mostrador != i)
      esta_mio[i].wait();
   cout << "                  Fumador " << i << "recoge ingrediente" << endl;
   mostrador = -1;      //marcamos el mostrador como vacia
   mostrador_vacio.signal();
}



/**
 * @brief monitor buffer donde se almacena la cantidad de cigarillos que van fumando los fumadores
 */ 
class Buffer : public HoareMonitor{
private:
   static const int num_plazas = 1;
   int vector[num_plazas];
   int n_items, pos_ins, pos_leer;
   CondVar ocupado, libre;
public:
   Buffer();
   void escribir(int dato);
   int leer();
};

Buffer::Buffer(){
   for (int i=0; i < num_plazas; i++)
      vector[i] = 0;
   n_items = pos_ins = pos_leer = 0;
   ocupado = newCondVar();
   libre = newCondVar();
}

void Buffer::escribir(int dato){
   if (n_items == num_plazas)
      libre.wait();
   vector[pos_ins] = dato;
   pos_ins = (pos_ins+1) % num_plazas;
   n_items++;
   ocupado.signal();
}

int Buffer::leer(){
   if (n_items == 0)
      ocupado.wait();
   int dato = vector[pos_leer];
   n_items--;
   pos_leer = (pos_leer+1) % num_plazas;
   libre.signal();
   return dato;
}


//funciones que ejecutan las hebras
void funcion_hebra_estanquera(MRef<Estanco> monitor)
{
   while (true){
      int ingrediente = producirIngrediente();
      monitor->ponerIngrediente(ingrediente);
      // mtx.lock();
      // cout << "Estanquero ha puesto ingrediente y espera que se recoja" << endl;
      // mtx.unlock();
      monitor->esperarRecogida();
   }
}

void funcion_hebra_fumadora(MRef<Estanco> monitor, MRef<Buffer> buffer, int indice)
{
   while (true){
      monitor->obtenerIngrediente(indice);
      fumar(indice);
      buffer->escribir(indice);
   }
}

void funcion_hebra_contadora(MRef<Buffer> buffer){
   int cigarros[num_fumadores] = {0,0,0};
   int cont = 0;
   while (true){
      int local_cigarro = buffer->leer();
      cigarros[local_cigarro]++;
      cont++;
      if (cont == 5){
         mtx.lock();
         for (int i=0; i < num_fumadores; i++)
            cout << "Fumador " << i << " ha fumado " << cigarros[i] << " cigarrillos" << endl;
         cont = 0;
         mtx.unlock();
      }
   }
}

int main()
{
   // crear monitor
   MRef<Estanco> monitor = Create<Estanco>();
   MRef<Buffer> buffer = Create<Buffer>();
   // creamos las hebras
   thread hebras_fumadoras[num_fumadores],
          hebra_estanquera;
   thread hebra_contadora;
   
   //lanzamos las hebras
   hebra_estanquera = thread(funcion_hebra_estanquera,monitor);
   hebra_contadora = thread(funcion_hebra_contadora,buffer);
   for (int i=0; i < num_fumadores; i++)
      hebras_fumadoras[i] = thread(funcion_hebra_fumadora,monitor,buffer,i);
   
   // esperar a que terminen las hebras
   hebra_estanquera.join();
   hebra_contadora.join();
   for (int i = 0; i < num_fumadores; i++)
      hebras_fumadoras[i].join();

}