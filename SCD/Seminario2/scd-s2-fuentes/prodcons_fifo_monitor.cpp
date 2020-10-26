/**
 * @file prodcons_fifo_monitor.cpp
 * @author Salvador Romero Cortés
 * @brief ejercicio de productores-consumidores usando monitores SU y varios productores/consumidores [FIFO]
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

// ========================================================================
/* FUNCIONES PRODUCTORAS/CONSUMIDORAS Y DE COMPROBACION*/

const int num_hebras = 4;
const int num_items = 40;
unsigned
    cont_prod[num_items * num_hebras], // contadores de verificación: producidos
    cont_cons[num_items * num_hebras]; // contadores de verificación: consumidos

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
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------

int producir_dato(int indice)
{
   static int contador = 0;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));
   unique_lock<mutex> guarda(mtx);
   cout << "productor " << indice << " produce: " << contador << endl
        << flush;
   cont_prod[contador]++;
   return contador++;
}
//----------------------------------------------------------------------

void consumir_dato(unsigned dato, int indice)
{
   if (num_items * num_hebras <= dato)
   {
      cout << " dato === " << dato << ", num_items == " << num_items << endl;
      assert(dato < num_items*num_hebras);
   }
   cont_cons[dato]++;
   this_thread::sleep_for(chrono::milliseconds(aleatorio<20, 100>()));
   unique_lock<mutex> guarda(mtx);
   cout << "                  consumidor " << indice << " consume: " << dato << endl;
}
//----------------------------------------------------------------------

void ini_contadores()
{
   for (unsigned i = 0; i < num_items * num_hebras; i++)
   {
      cont_prod[i] = 0;
      cont_cons[i] = 0;
   }
}

//----------------------------------------------------------------------

void test_contadores()
{
   bool ok = true;
   cout << "comprobando contadores ...." << flush;

   for (unsigned i = 0; i < num_items; i++)
   {
      if (cont_prod[i] != 1)
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl;
         ok = false;
      }
      if (cont_cons[i] != 1)
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl;
         ok = false;
      }
   }
   if (ok)
      cout << endl
           << flush << "solución (aparentemente) correcta." << endl
           << flush;
}

//=====================================================================000

/**
 * @brief clase que representa el monitor de productores-consumidores
 */

class ProdConsFIFO : public HoareMonitor
{
private:
   static const int num_celdas_total = 10;
   int buffer[num_celdas_total];
   int posicion_prod, posicion_cons; //contadores de las posiciones de escritura/lectura
   int num_items;
   // int n_ocupadas, n_libres;
   CondVar ocupadas, libres;

public:
   ProdConsFIFO();
   void insertar(int dato);
   int extraer();
};

ProdConsFIFO::ProdConsFIFO()
{
   posicion_cons = posicion_prod = num_items = 0;
   ocupadas = newCondVar();
   libres = newCondVar();
   for (int i = 0; i < num_celdas_total; i++)
      buffer[i] = 0;
}

//metodo para insertar valores en el buffer
void ProdConsFIFO::insertar(int dato)
{
   if (num_items == num_celdas_total)
      libres.wait();

   buffer[posicion_prod] = dato;
   //ocupadas.signal();
   posicion_prod  = (posicion_prod+1) % num_celdas_total;
   num_items++;
   ocupadas.signal();
}

//metodo para leer valores del buffer
int ProdConsFIFO::extraer()
{
   if (num_items == 0)
      ocupadas.wait();
   int valor = buffer[posicion_cons];
   //libres.signal();
   num_items--;
   posicion_cons = (posicion_cons+1) % num_celdas_total;
   libres.signal();
   return valor;
}

//funciones que ejecutan las hebras
void funcion_hebra_productora(MRef<ProdConsFIFO> monitor, int indice)
{
   for (unsigned i = 0; i < num_items; i++)
   {
      int valor = producir_dato(indice);
      monitor->insertar(valor);
   }
}

void funcion_hebra_consumidora(MRef<ProdConsFIFO> monitor, int indice)
{
   for (unsigned i = 0; i < num_items; i++)
   {
      int valor = monitor->extraer();
      consumir_dato(valor, indice);
   }
}

int main()
{
   // crear monitor
   MRef<ProdConsFIFO> monitor = Create<ProdConsFIFO>();
   // crear y lanzar hebras
   thread hebra_prod[num_hebras], hebra_cons[num_hebras];
   for (int i = 0; i < num_hebras; i++)
   {
      hebra_prod[i] = thread(funcion_hebra_productora, monitor, i);
      hebra_cons[i] = thread(funcion_hebra_consumidora, monitor, i);
   }
   // esperar a que terminen las hebras
   for (unsigned i = 0; i < num_hebras; i++)
   {
      hebra_prod[i].join();
      hebra_cons[i].join();
   }

   test_contadores();
}