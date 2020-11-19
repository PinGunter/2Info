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
   cout << "Suministradora produce ingrediente: " << ingrediente << endl;
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
   cout << "                  Fumador " << i << " recoge ingrediente" << endl;
   mostrador = -1;      //marcamos el mostrador como vacia
   mostrador_vacio.signal();
}

class Buffer : public HoareMonitor{
private:
    static const int capacidad = 3;
    int vector[capacidad];
    int n_items;
    int pos_lectura;
    int pos_escritura;
    CondVar lectura, escritura;
public:
    Buffer();
    int leer();
    void escribir(int dato);
};

Buffer::Buffer(){
    for (int i=0; i < capacidad; i++)
        vector[i] = 0;
    pos_escritura = pos_lectura = 0;
    lectura = newCondVar();
    escritura = newCondVar();
}

int Buffer::leer(){
    if (n_items == 0)
        lectura.wait();
    int dato = vector[pos_lectura];
    n_items--;
    pos_lectura = (pos_lectura+1) % capacidad;
    escritura.signal();
    return dato;
}

void Buffer::escribir(int dato){
    if (n_items == capacidad-1)
        escritura.wait();
    vector[pos_escritura] = dato;
    pos_escritura = (pos_escritura+1) % capacidad;
    n_items++;
    lectura.signal();
}



//funciones que ejecutan las hebras
void funcion_hebra_estanquera(MRef<Estanco> monitor, MRef<Buffer> buffer)
{
   while (true){
      int ingrediente = buffer->leer();
      cout << "Estanquera recibe suministro del buffer " << ingrediente << endl << flush;
      cout << "Estanquero ha puesto ingrediente y espera que se recoja" << endl;
      monitor->ponerIngrediente(ingrediente);
      monitor->esperarRecogida();
   }
}

void funcion_hebra_fumadora(MRef<Estanco> monitor, int indice)
{
   while (true){
      monitor->obtenerIngrediente(indice);
      fumar(indice);
   }
}

void funcion_hebra_suministradora(MRef<Buffer> monitor){
    while (true){
        int ingrediente = producirIngrediente();
        cout << "Se suministra al buffer " << ingrediente << endl << flush;
        monitor->escribir(ingrediente);
    }
}

int main()
{
   // crear monitor
   MRef<Estanco> monitor = Create<Estanco>();
   MRef<Buffer> buffer = Create<Buffer>();
   // creamos las hebras
   thread hebras_fumadoras[num_fumadores],
          hebra_estanquera,
          hebra_suministradora;
   
   //lanzamos las hebras
   hebra_estanquera = thread(funcion_hebra_estanquera,monitor,buffer);
   hebra_suministradora = thread(funcion_hebra_suministradora,buffer);
   for (int i=0; i < num_fumadores; i++)
      hebras_fumadoras[i] = thread(funcion_hebra_fumadora,monitor,i);
   
   // esperar a que terminen las hebras
   hebra_estanquera.join();
   hebra_suministradora.join();
   for (int i = 0; i < num_fumadores; i++)
      hebras_fumadoras[i].join();

}