/*
* Salvador Romero Cortés - Aproximación de Pi a través de integral
*/


#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;
using namespace std::chrono;

const long M = 2147483646; //barras usadas para aproximar la integral, multiplo del numero de hebras

const int num_hebras = 6; //numero de hebras a utilizar

/**
 * @brief funcion que se integra
 * @param x valor de la variable en la funcion
 * @retval el valor de la funcion en x --> f(x)
 * */
double funcion(double x){
    return 4.0/(1+x*x);
}

/**
 * @brief funcion para calcular la integral de forma secuencial
 * @retval el resultado
 */
double calcular_integral_secuencial(){
    double suma = 0;
    for (long i=0; i < M; i++){     //vamos aproximando la integral
        double xi = (i+0.5)/M;
        suma += funcion(xi);
    }
    return suma/M;
}

double funcion_hebra(long ih){
    long muestras_por_hebra = M / num_hebras;
    double suma = 0.0;
    for (int i=ih*muestras_por_hebra; i < ih*muestras_por_hebra + muestras_por_hebra; i++){
        double xi = (i+0.5)/M;
        suma += funcion(xi);
    }
    return suma/M;
}

double calcular_integral_concurrente(){
    future<double> futuro [num_hebras];

    //calculamos las sumas parciales de cada hebra
    for (int i=0; i < num_hebras; i++)
        futuro[i] = async(launch::async, funcion_hebra, i);
    
    //sumamos todas las sumas parciales
    double suma = 0.0;
    for (int i=0; i < num_hebras; i++)
        suma += futuro[i].get();

    return suma;
}

int main(){
    const double pi = 3.1415926535897931;

    cout.precision(18);
    //comenzamos a medir el tiempo secuencial
    time_point<steady_clock> inicio_sec = steady_clock::now();
    //calculamos pi
    const double pi_sec = calcular_integral_secuencial();
    //paramos el cronometro
    time_point<steady_clock> fin_sec = steady_clock::now();
    //calculamos lo que ha tardado
    duration<float,milli> duracion_sec = fin_sec - inicio_sec;

    //realizamos lo mismo para el calculo concurrente
    time_point<steady_clock> inicio_conc = steady_clock::now();
    //calculamos pi
    const double pi_conc = calcular_integral_concurrente();
    //paramos el cronometro
    time_point<steady_clock> fin_conc = steady_clock::now();
    //calculamos lo que ha tardado
    duration<float,milli> duracion_conc = fin_conc - inicio_conc;

    //mostramos por pantalla el resultado
    cout << "Número de muestras (m)\t: " << M << endl
    << "Número de hebras (n) \t: " << num_hebras << endl
    << "Valor de PI\t\t: " << pi << endl
    << "Resultado secuencial\t: " << pi_sec << endl
    << "Resultado concurrente\t: " << pi_conc << endl
    << "Tiempo secuencial\t: " << duracion_sec.count() << " ms" << endl
    << "Tiempo concurrente\t: " << duracion_conc.count() << " ms" << endl
    << "Porcentaje t.con/t.sec.\t: " << duracion_conc.count()/duracion_sec.count() * 100.0 << "%" << endl;
}