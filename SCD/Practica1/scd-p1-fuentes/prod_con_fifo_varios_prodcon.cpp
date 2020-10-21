// Salvador Romero Cortés
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "Semaphore.h"
using namespace std ;
using namespace SEM ;

//**********************************************************************
// variables compartidas
const int num_prod_cons = 2;

const int num_items = 40 ,   // número de items
	       tam_vec   = 2;   // tamaño del buffer
unsigned  cont_prod[num_items*num_prod_cons] = {0}, // contadores de verificación: producidos
          cont_cons[num_items] = {0}; // contadores de verificación: consumidos


/// VARIABLES GLOBALES 
Semaphore puede_producir = tam_vec;
Semaphore puede_consumir = 0;
int posicion_prod = 0, posicion_cons = 0;
int vec[tam_vec];
mutex prod;
mutex cons;
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

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato(int indice)
{
   prod.lock();
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "productor " << indice << " producido: " << contador << endl << flush ;

   // cont_prod[contador] ++ ;
   contador ++;
   prod.unlock();
   return contador ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato, int indice )
{
  // assert( dato < num_items*num_prod_cons);

   // cont_cons[dato] ++ ;
   cons.lock();
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  cosumidor " << indice << " consumido: " << dato << endl ;
   cons.unlock();
}


//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------

void  funcion_hebra_productora( int indice )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato(indice) ;
      sem_wait(puede_producir);
         vec[posicion_prod] = dato;
         posicion_prod = (posicion_prod+1)%tam_vec;
      sem_signal(puede_consumir);
   }
}

//----------------------------------------------------------------------

void funcion_hebra_consumidora( int indice)
{
   for( unsigned i = 0 ; i < num_items*2 ; i++ )
   {
      int dato ;
      sem_wait(puede_consumir);
         dato = vec[posicion_cons];
         posicion_cons = (posicion_cons+1) % tam_vec;
      sem_signal(puede_producir);
      consumir_dato( dato,indice ) ;

    }
}
//----------------------------------------------------------------------

int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread productores[num_prod_cons];
   thread consumidores[num_prod_cons];

   for (int i=0; i < num_prod_cons; i++){
      productores[i] = thread(funcion_hebra_productora,i);
      consumidores[i] = thread(funcion_hebra_consumidora,i);
   }

   for (int i=0; i < num_prod_cons; i++){
      productores[i].join();
      consumidores[i].join();
   }
  // test_contadores();
}
