//Salvador Romero Cortés
// -----------------------------------------------------------------------------
//   Datos de las tareas:
//   -------------
//   Ta.  T     C
//   -------------
//   A  500    100
//   B  500    150
//   C  1000   200
//   D  2000   240
//  ---------------
// 
//  Planificación (con Ts == 500 ms)
//  *---------*----------*---------*--------*
//  | A B C   | A B D    | A B C   | A B    |
//  *---------*----------*---------*--------*
// T es el mcm de los tiempos por lo que es 2000ms
// Se elige un Ts de 500 ms porque es divisor de 2000 y además coincide con el período más pequeño de las tareas
// PREGUNTAS:
// ¿cual es el mínimo tiempo de espera que queda al final de las iteraciones del ciclo secundario con tu solución?
// La mínima espera es de 10ms en el segundo ciclo (ABD)
// ¿ Sería planificable si la tarea D tuviese un tiempo cómputo de 250 ms ?
// Teóricamente sí, pero no habría ninguna espera en ese ciclo secundario.
// Si dejasemos la planificación actual pero con C_d = 250ms no habría tiempo de espera, el proceso acaba justo en el deadline
// Tarda A(100)+B(150)+D(250)=500.
// Sin embargo, en la práctica hay retrasos por lo que no se podría planificar D con la planificación actual.
// No se puede porque A y B siempre se tienen que ejecutar cada 500 ms. Por lo que da igual donde pongamos D, la suma será como mínimo 500
// como el mínimo es 500 ms y hay retrasos, esto produciría un incumplimiento en los plazos de A y B puesto que su periodo (y deadline) se superaría
// Por lo tanto, el la práctica o en el mundo real no es planificable.
// Además he incluido en la planificación el calculo de los tiempos (comentado) para probar que siempre hay un pequeño retraso ( el sleep_for de las tareas)
// ejecutando el programa se puede ver que siempre hay retraso, por lo que si ponemos c_d como 250, nos pasaríamos de 500, 
// haciendo que A incumpla su deadline
// -----------------------------------------------------------------------------

#include <string>
#include <iostream> // cout, cerr
#include <thread>
#include <chrono>   // utilidades de tiempo
#include <ratio>    // std::ratio_divide

using namespace std ;
using namespace std::chrono ;
using namespace std::this_thread ;

// tipo para duraciones en segundos y milisegundos, en coma flotante:
typedef duration<float,ratio<1,1>>    seconds_f ;
typedef duration<float,ratio<1,1000>> milliseconds_f ;

// -----------------------------------------------------------------------------
// tarea genérica: duerme durante un intervalo de tiempo (de determinada duración)

void Tarea( const std::string & nombre, milliseconds tcomputo )
{
   cout << "   Comienza tarea " << nombre << " (C == " << tcomputo.count() << " ms.) ... " ;
   sleep_for( tcomputo );
   cout << "fin." << endl ;
}


// -----------------------------------------------------------------------------
// tareas concretas del problema:

void TareaA() { Tarea( "A", milliseconds(100) );  }
void TareaB() { Tarea( "B", milliseconds(150) );  }
void TareaC() { Tarea( "C", milliseconds(200) );  }
void TareaD() { Tarea( "D", milliseconds(240) );  }


// -----------------------------------------------------------------------------
// implementación del ejecutivo cíclico:

int main( int argc, char *argv[] )
{
   // Ts = duración del ciclo secundario
   const milliseconds Ts( 500 );

   // ini_sec = instante de inicio de la iteración actual del ciclo secundario
   time_point<steady_clock> ini_sec = steady_clock::now();
   time_point<steady_clock> inicio, fin;
   int ideal;
   milliseconds_f duracion_real;
   float  retraso;
   while( true ) // ciclo principal
   {
      cout << endl
           << "---------------------------------------" << endl
           << "Comienza iteración del ciclo principal." << endl ;

      for( int i = 1 ; i <= 4 ; i++ ) // ciclo secundario (4 iteraciones)
      {
         cout << endl << "Comienza iteración " << i << " del ciclo secundario." << endl ;
        inicio = steady_clock::now();
         switch( i )
         {
            case 1 : TareaA(); TareaB(); TareaC();      ideal = 450;        break ;
            case 2 : TareaA(); TareaB(); TareaD();      ideal = 490;        break ;
            case 3 : TareaA(); TareaB(); TareaC();      ideal = 450;        break ;
            case 4 : TareaA(); TareaB();                ideal = 250;        break ;
         }
         fin = steady_clock::now();
         /*
         cout << " ----- Tiempos reales vs ideales de la ejecución de las tareas: -----" << endl;
        duracion_real = fin - inicio;
        retraso = duracion_real.count() - ideal;
         cout << "Duracion teorica: " << ideal << " ms" << endl;
         cout << "Duración real: " << duracion_real.count() << " ms" << endl;
         cout << "Retraso: " << retraso  << " ms" << endl;
         */
         // calcular el siguiente instante de inicio del ciclo secundario
         ini_sec += Ts ;
         // esperar hasta el inicio de la siguiente iteración del ciclo secundario
         sleep_until( ini_sec );
         /*
         fin = steady_clock::now();
         duracion_real = fin - inicio;
         retraso = duracion_real.count() - Ts.count();
         cout << " ----- Tiempos del ciclo secundario: -----" << endl;
         cout << "Duración teórica máxima: " << Ts.count() << " ms" << endl;
         cout << "Duración real: " << duracion_real.count() <<  " ms" << endl;
         cout << "Retraso: " << retraso << " ms" << endl;
        */
      
      }
   }
}
