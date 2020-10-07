// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 1. Programación Multihebra y Semáforos.
//
// Ejemplo 9 (ejemplo9.cpp)
// Calculo concurrente de una integral. Plantilla para completar.
//
// Historial:
// Creado en Abril de 2017
// Completado Septiembre de 2020
// Alumno: Salvador Romero Cortés
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <chrono>  // incluye now, time\_point, duration
#include <future>
#include <vector>
#include <cmath>

using namespace std ;
using namespace std::chrono;

const long m  = 1024l*1024l*1024l, // número de muestras (del orden de mil millones)
           n  = 4  ;               // número de hebras concurrentes (divisor de 'm')


// -----------------------------------------------------------------------------
// evalua la función $f$ a integrar ($f(x)=4/(1+x^2)$)
double f( double x )
{
  return 4.0/(1.0+x*x) ;
}
// -----------------------------------------------------------------------------
// calcula la integral de forma secuencial, devuelve resultado:
double calcular_integral_secuencial(  )
{
   double suma = 0.0 ;                        // inicializar suma
   for( long j = 0 ; j < m ; j++ )            // para cada $j$ entre $0$ y $m-1$:
   {  const double xj = double(j+0.5)/m ;     //      calcular $x_j$
      suma += f( xj );                        //      añadir $f(x_j)$ a la suma actual
   }
   return suma/m ;                            // devolver valor promedio de $f$
}

// -----------------------------------------------------------------------------
// función que ejecuta cada hebra: recibe $i$ ==índice de la hebra, ($0\leq i<n$)
/**
 * @brief funcion que ejecuta cada hebra, se calcula su punto de inicio y se le asignan un número de secciones a calcular (intervalo)
 * @param ih el indice de la hebra 
 * @return el valor de la media de los puntos del intervalo calculado por la hebra
*/
double funcion_hebra( long ih )
{
    long muestras_por_hebra = m / n;
    double suma = 0.0;
    for (int i=ih*muestras_por_hebra; i < ih*muestras_por_hebra + muestras_por_hebra; i++){
        double xi = (i+0.5)/m;
        suma += f(xi);
    }
    return suma/m;
}

// -----------------------------------------------------------------------------
// calculo de la integral de forma concurrente

/**
 * @brief funcion que se encarga de aproximar el resultao de la integral. Usamos un vector de tipo future para almacenar los resultados de cada hebra
 * @return el valor numerico de la integral
*/
double calcular_integral_concurrente( )
{
    future<double> futuro [n];

    //calculamos las sumas parciales de cada hebra
    for (int i=0; i < n; i++)
        futuro[i] = async(launch::async, funcion_hebra, i);
    
    //sumamos todas las sumas parciales
    double suma = 0.0;
    for (int i=0; i < n; i++)
        suma += futuro[i].get();

    return suma;
}
// -----------------------------------------------------------------------------

int main()
{

// comenzamos las mediciones de cada función. Primero la secuencial
  time_point<steady_clock> inicio_sec  = steady_clock::now() ;  //comienza el cronometro
  const double             result_sec  = calcular_integral_secuencial(  );      //se calcula la integral secuencialmente
  time_point<steady_clock> fin_sec     = steady_clock::now() ;  //se detiene el cronometro
  double x = sin(0.4567);
  time_point<steady_clock> inicio_conc = steady_clock::now() ;  //comenzamos el cronometro
  const double             result_conc = calcular_integral_concurrente(  );     //se calcula la integral, ahora de manera concurrente
  time_point<steady_clock> fin_conc    = steady_clock::now() ;  //se detiene el cronometro
  duration<float,milli>    tiempo_sec  = fin_sec  - inicio_sec ,
                           tiempo_conc = fin_conc - inicio_conc ;
  const float              porc        = 100.0*tiempo_conc.count()/tiempo_sec.count() ;


  constexpr double pi = 3.14159265358979323846l ;

//mostramos por pantalla el resultado
  cout << "Número de muestras (m)   : " << m << endl
       << "Número de hebras (n)     : " << n << endl
       << setprecision(18)
       << "Valor de PI              : " << pi << endl
       << "Resultado secuencial     : " << result_sec  << endl
       << "Resultado concurrente    : " << result_conc << endl
       << setprecision(5)
       << "Tiempo secuencial        : " << tiempo_sec.count()  << " milisegundos. " << endl
       << "Tiempo concurrente       : " << tiempo_conc.count() << " milisegundos. " << endl
       << setprecision(4)
       << "Porcentaje t.conc/t.sec. : " << porc << "%" << endl;
}
