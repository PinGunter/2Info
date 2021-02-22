/**
 * @author Salvador Romero Cortés
 * @file practica3.cpp
 * @brief ejercicio de exanen de la practica 3
 */

// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2.cpp
// Implementación del problema del productor-consumidor con
// un proceso intermedio que gestiona un buffer finito y recibe peticiones
// en orden arbitrario
// (versión con un único productor y un único consumidor)
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int np = 1;
const int nc = 2;
//0 <-> np-1 son productores
// np es el buffer
// np+1 <-> np+nc son consumidores

const int tag_prod = 0;
const int tag_cons = 1;

const int
   id_buffer = np,
   num_procesos_esperado = np+nc+1 ,
   num_items             = 10,
   tam_vector            = 3;

// ------
// En este ejercicio los ids seran
// rango 0 -> productor
// rango 1 -> buffer
// rango 2 -> consumidor 0
// rango 3 -> consumiror 1

const int id_cons_0 = 2;
const int id_cons_1 = 3;

int modo = 0;       // modo del buffer, inicialmente a 0


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
// ---------------------------------------------------------------------
// ptoducir produce los numeros en secuencia (1,2,3,....)
// y lleva espera aleatorio
int producir(int orden)
{
   static int contador = orden*(num_items/np) ;
   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   cout << "Productor " << orden << " ha producido valor " << contador << endl << flush;
   return contador ;
}
// ---------------------------------------------------------------------

void funcion_productor(int orden)
{
   for ( int i=0; i < (num_items/np) ; i++ )
   {
      // producir valor
      int valor_prod = producir(orden);
      // enviar valor
      cout << "Productor " << orden << " va a enviar valor " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, tag_prod, MPI_COMM_WORLD );
   }
}
// ---------------------------------------------------------------------

void consumir( int valor_cons, int id_propio)
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "Consumidor " << id_propio << " ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor(int id_propio)
{
   int         peticion,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < (num_items/nc); i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, tag_cons, MPI_COMM_WORLD);
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, tag_cons, MPI_COMM_WORLD,&estado );
      cout << "Consumidor " << id_propio << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, id_propio );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer() // buffer con estrategia lifo
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              tag_emisor_aceptable ;    // identificador de emisor aceptable
   MPI_Status estado ;                 // metadatos del mensaje recibido
   int id_emisor_aceptable = -1;
   MPI_Status sondeo;
   int flag;
    bool hay_mensaje = false;
   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
      // 1. determinar si puede enviar solo prod., solo cons, o todos
      if ( num_celdas_ocupadas == 0 ){               // si buffer vacío
         id_emisor_aceptable = 0 ;       // $~~~$ solo prod.
         tag_emisor_aceptable = tag_prod;
      }
      else if ( num_celdas_ocupadas == tam_vector ){ // si buffer lleno
         tag_emisor_aceptable = tag_cons;
        //hacemos el sondeo en funcion del modo del buffer
        if (modo == 0){
            id_emisor_aceptable = id_cons_0;
            modo = 1;
        } else if (modo == 1){
            id_emisor_aceptable = id_cons_1;
            modo = 0;
        }
      }
      else{                                          // si no vacío ni lleno
        id_emisor_aceptable = MPI_ANY_SOURCE ;     // $~~~$ cualquiera
         tag_emisor_aceptable = MPI_ANY_TAG;
         //ahora sondeamos si hay del productor, en caso de que no haya elegimos consumidor en funcion del modo
        while (!hay_mensaje) {
            MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &sondeo);
            if (flag > 0){
                hay_mensaje = true;
                if (sondeo.MPI_TAG == tag_prod){
                    tag_emisor_aceptable = tag_prod;
                    id_emisor_aceptable = 0;
                } else{
                    tag_emisor_aceptable = tag_cons;
                    if (modo == 0){
                        id_emisor_aceptable = id_cons_0;
                        modo = 1;
                    } else if (modo == 1){
                        id_emisor_aceptable = id_cons_1;
                        modo = 0;
                    }
                }
            }
         
        }
      }
      // 2. recibir un mensaje del emisor o emisores aceptables

      MPI_Recv( &valor, 1, MPI_INT, id_emisor_aceptable, tag_emisor_aceptable, MPI_COMM_WORLD, &estado );

      // 3. procesar el mensaje recibido

      switch( estado.MPI_TAG ) // leer emisor del mensaje en metadatos
      {
         case tag_prod: // si ha sido el productor: insertar en buffer
            buffer[primera_libre] = valor ;
            primera_libre++;
            num_celdas_ocupadas++ ;
            cout << "Buffer ha recibido valor " << valor << endl ;
            break;

         case tag_cons: // si ha sido el consumidor: extraer y enviarle 
            primera_libre--;
            valor = buffer[primera_libre] ;
            num_celdas_ocupadas-- ;
            cout << "Buffer va a enviar valor " << valor << endl ;
            MPI_Ssend( &valor, 1, MPI_INT, estado.MPI_SOURCE, tag_cons, MPI_COMM_WORLD);
            break;
      }
   }
}

// ---------------------------------------------------------------------

int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;
   int orden = 0;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual )
   {
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < np ){
         funcion_productor(id_propio);
      }
      else if ( id_propio == id_buffer ){
         funcion_buffer();
      }
      else if (id_propio > id_buffer){
         funcion_consumidor(id_propio-id_buffer-1);
      }
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
