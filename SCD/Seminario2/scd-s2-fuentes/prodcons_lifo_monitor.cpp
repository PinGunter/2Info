/**
 * @file prodcons_lifo_monitor.cpp
 * @author Salvador Romero Cortés
 * @brief ejercicio de productores-consumidores usando monitores SU y varios productores/consumidores [LIFO]
 */

#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "HoareMonitor.h"   //clase para monitores SU

using namespace std;
using namespace HM;         //espacio de nombres para los monitores

mutex mtx; //cerrojo para mostrar en pantalla

// ========================================================================
/* FUNCIONES PRODUCTORAS/CONSUMIDORAS Y DE COMPROBACION*/

const int num_items = 40;
unsigned
   cont_prod[num_items], // contadores de verificación: producidos
   cont_cons[num_items]; // contadores de verificación: consumidos

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

int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "producido: " << contador << endl << flush ;
   mtx.unlock();
   cont_prod[contador] ++ ;
   return contador++ ;
}
//----------------------------------------------------------------------

void consumir_dato( unsigned dato )
{
   if ( num_items <= dato )
   {
      cout << " dato === " << dato << ", num_items == " << num_items << endl ;
      assert( dato < num_items );
   }
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "                  consumido: " << dato << endl ;
   mtx.unlock();
}
//----------------------------------------------------------------------

void ini_contadores()
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//=====================================================================000

/**
 * @brief clase que representa el monitor de productores-consumidores
 */

class ProdConsLIFO : public HoareMonitor{
private:
    static const int num_celdas_total = 10;
    int buffer[num_celdas_total];
    int primera_libre;
    // int n_ocupadas, n_libres;
    CondVar ocupadas, libres;

public:
    ProdConsLIFO();
    void insertar(int dato);
    int extraer();
};

ProdConsLIFO::ProdConsLIFO(){
    primera_libre = 0;
    ocupadas = newCondVar();
    libres = newCondVar();
    // n_ocupadas = 0;
    // n_libres = num_celdas_total;
}

//metodo para insertar valores en el buffer 
void ProdConsLIFO::insertar(int dato){
    if (primera_libre >= num_celdas_total)
        libres.wait();
    else{
        buffer[primera_libre] = dato;
        primera_libre ++;
        ocupadas.signal();
        mtx.lock();
        cout << "Se inserta " << dato << " en buffer" << endl;
        mtx.unlock();
    }
}

//metodo para leer valores del buffer
int ProdConsLIFO::extraer(){
    if (primera_libre == 0)
        ocupadas.wait();
    else{
        primera_libre--;
        int valor = buffer[primera_libre];
        libres.signal();
        return valor;
    }
}

//funciones que ejecutan las hebras
void funcion_hebra_productora( ProdConsLIFO * monitor,int indice )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int valor = producir_dato() ;
      monitor->insertar( valor );
   }
}

void funcion_hebra_consumidora( ProdConsLIFO * monitor ,int indice)
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int valor = monitor->extraer();
      consumir_dato( valor ) ;
   }
}

int main()
{
   const int num_hebras = 100,
             num_hebras_cita = 5 ;

   // crear monitor
   ProdConsLIFO monitor();

   // crear y lanzar hebras
   thread hebra_prod[num_hebras], hebra_prod[num_hebras];
   for( unsigned i = 0 ; i < num_hebras ; i++ ){
      hebra[i] = thread( funcion_hebra_productora, &monitor, i );
      hebra[i]

   // esperar a que terminen las hebras (no pasa nunca)
   for( unsigned i = 0 ; i < num_hebras ; i++ )
      hebra[i].join();
}