/**
 * @author Salvador Romero Cortés
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

const int np = 4;
const int nc = 5;
//0 <-> np-1 son productores
// np es el buffer
// np+1 <-> np+nc son consumidores

const int tag_prod = 0;
const int tag_cons = 1;

const int
   id_buffer = np,
   num_procesos_esperado = np+nc+1 ,
   num_items             = np*nc,
   tam_vector            = 10;

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
   cout << "Productor ha producido valor " << contador << endl << flush;
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

void consumir( int valor_cons)
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "Consumidor ha consumido valor " << valor_cons << endl << flush ;
}
// ---------------------------------------------------------------------

void funcion_consumidor()
{
   int         peticion,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < (num_items/nc); i++ )
   {
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, tag_cons, MPI_COMM_WORLD);
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, tag_cons, MPI_COMM_WORLD,&estado );
      cout << "Consumidor ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec );
   }
}
// ---------------------------------------------------------------------

void funcion_buffer()
{
   int        buffer[tam_vector],      // buffer con celdas ocupadas y vacías
              valor,                   // valor recibido o enviado
              primera_libre       = 0, // índice de primera celda libre
              primera_ocupada     = 0, // índice de primera celda ocupada
              num_celdas_ocupadas = 0, // número de celdas ocupadas
              tag_emisor_aceptable,     // identificador de emisor aceptable
              id_productor = MPI_ANY_SOURCE;
    bool encontrado_emisor = false, acabar = false;
   MPI_Status estado, buffer_vacio ;                 // metadatos del mensaje recibido
    int flag;
   for( unsigned int i=0 ; i < num_items*2 ; i++ )
   {
       cout << "num_celdas_ocupadas " << num_celdas_ocupadas << endl;
      // 1. determinar si puede enviar solo prod., solo cons, o todos
      if ( num_celdas_ocupadas == 0 ){               // si buffer vacío
         // id_emisor_aceptable = id_productor ;       // $~~~$ solo prod.
         tag_emisor_aceptable = tag_prod;
         while (!encontrado_emisor && !acabar){
            for (int j=0; j <= np/2 && !encontrado_emisor; j+=2){
                MPI_Iprobe(j,tag_prod,MPI_COMM_WORLD,&flag,&buffer_vacio);
                if (flag > 0){
                    encontrado_emisor = true;
                    id_productor = j;
                }
            }
            for (int j=1; i < np && !encontrado_emisor; j+=2){
                MPI_Iprobe(j,tag_prod,MPI_COMM_WORLD,&flag,&buffer_vacio);
                if (flag > 0){
                    encontrado_emisor = true;
                    id_productor = j;
                }
            }
            acabar = true;          //variable acabar para que no se pueda bloquear      
         }

      }
      else if ( num_celdas_ocupadas == tam_vector ){ // si buffer lleno
         // id_emisor_aceptable = id_consumidor ;      // $~~~$ solo cons.
         tag_emisor_aceptable = tag_cons;
      }
      else{                                          // si no vacío ni lleno
        // id_emisor_aceptable = MPI_ANY_SOURCE ;     // $~~~$ cualquiera
         tag_emisor_aceptable = MPI_ANY_TAG;
      }
      // 2. recibir un mensaje del emisor o emisores aceptables
    if (num_celdas_ocupadas == 0)
      MPI_Recv( &valor, 1, MPI_INT, id_productor, tag_prod, MPI_COMM_WORLD, &estado );
    else
    {
      MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, tag_emisor_aceptable, MPI_COMM_WORLD, &estado );
    }
    
      // 3. procesar el mensaje recibido

      switch( estado.MPI_TAG ) // leer emisor del mensaje en metadatos
      {
         case tag_prod: // si ha sido el productor: insertar en buffer
            buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "Buffer ha recibido valor " << valor << endl ;
            break;

         case tag_cons: // si ha sido el consumidor: extraer y enviarle 
            valor = buffer[primera_ocupada] ;
            primera_ocupada = (primera_ocupada+1) % tam_vector ;
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
      if ( id_propio < np )
         funcion_productor(id_propio);
      else if ( id_propio == id_buffer )
         funcion_buffer();
      else if (id_propio > id_buffer)
         funcion_consumidor();
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
