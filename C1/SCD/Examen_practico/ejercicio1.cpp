//Salvador Romero Cortés
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "Semaphore.h"

using namespace std ;
using namespace SEM ;

// ---- Variables Globales ----- 
const int num_fumadores = 5;
Semaphore materiales[num_fumadores] = {0,0,0,0,0};
Semaphore mostrador = 1;
int num_cigarros = 0;



//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------

template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)

int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero

void funcion_hebra_estanquero(  )
{
   int mostrado = 0;
   while (true){
      sem_wait(mostrador);
      mostrado = producir_ingrediente();
      cout << "Puesto ingrediente numero: " << mostrado << endl << flush;
      sem_signal(materiales[mostrado]);
   }
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra

void fumar( int num_fumador )
{

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
    num_cigarros++;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador )
{
   while( true )
   {
      sem_wait(materiales[num_fumador]);
      cout << "Numero de cigarrillos fumados en total: " << num_cigarros << endl << flush;
      cout << "Recogido material " << num_fumador << endl << flush;
      if (num_cigarros % 2 == 0){
          cout << "Se avisa al mostrador" << endl << flush;
          sem_signal(mostrador);
          fumar(num_fumador);
      }
      else {
          fumar(num_fumador);
          cout << "Se avisa al mostrador" << endl << flush;
          sem_signal(mostrador);
      }
   }
}

//----------------------------------------------------------------------

int main()
{
  cout << "--------------------------------------------------------" << endl
        << "-------- Problema del estanco y los fumadores ---------" << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread estanco(funcion_hebra_estanquero);
   thread fumadores[num_fumadores];
   for (int i=0; i < num_fumadores; i++)
      fumadores[i] = thread(funcion_hebra_fumador,i);
   estanco.join();
   for (int i=0; i < num_fumadores; i++)
      fumadores[i].join();

}
