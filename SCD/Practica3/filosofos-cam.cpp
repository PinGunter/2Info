/**
 * @author Salvador Romero Cortés
 */

// -----------------------------------------------------------------------------
//
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-plantilla.cpp
// Implementación del problema de los filósofos (sin camarero).
// Plantilla para completar.
//
// Historial:
// Actualizado a C++11 en Septiembre de 2017
// -----------------------------------------------------------------------------

#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

const int
    num_filosofos = 5,
    num_procesos = 2 * num_filosofos + 1;
const int id_camarero = 10;
const int
    etiq_sentarse = 0,
    etiq_levantarse = 1;
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

// ---------------------------------------------------------------------

void funcion_filosofos(int id)
{
    int id_ten_izq = (id + 1) % num_procesos,                //id. tenedor izq.
        id_ten_der = (id + num_procesos - 1) % num_procesos; //id. tenedor der.
    int valor;
    MPI_Status estado;
    while (true)
    {
        /** Sentarse       **/
        cout << "Filósofo " << id << " solicita sentarse" << endl;
        MPI_Ssend(&valor, 1, MPI_INT, id_camarero, etiq_sentarse, MPI_COMM_WORLD);
        // cout << "Filósofo " << id << " espera a sentarse" << endl;
        // MPI_Recv(&valor, 1, MPI_INT, id_camarero, etiq_sentarse, MPI_COMM_WORLD,&estado);
        cout << "Filósofo " << id << " se sienta" << endl;


        cout << "Filósofo " << id << " solicita ten. izq." << id_ten_izq << endl;
        // ... solicitar tenedor izquierdo (completar)
        MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq, id_ten_izq, MPI_COMM_WORLD);

        cout << "Filósofo " << id << " solicita ten. der." << id_ten_der << endl;
        // ... solicitar tenedor derecho (completar)
        MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, id_ten_der, MPI_COMM_WORLD);
        cout << "Filósofo " << id << " comienza a comer" << endl;
        sleep_for(milliseconds(aleatorio<50, 300>()));

        cout << "Filósofo " << id << " suelta ten. izq. " << id_ten_izq << endl;
        // ... soltar el tenedor izquierdo (completar)
        MPI_Ssend(&valor, 1, MPI_INT, id_ten_izq, id_ten_izq, MPI_COMM_WORLD);
        cout << "Filósofo " << id << " suelta ten. der. " << id_ten_der << endl;
        // ... soltar el tenedor derecho (completar)

        /** Levantarse  **/
        cout << "Filósofo " << id << " se va a levantar" << endl;
        MPI_Ssend(&valor,1, MPI_INT, id_camarero, etiq_levantarse, MPI_COMM_WORLD);
        // MPI_Recv(&valor, 1, MPI_INT, id_camarero, etiq_levantarse, MPI_COMM_WORLD,&estado);
        cout << "Filósofo " << id << " se levanta de la mesa" << endl;


        MPI_Ssend(&valor, 1, MPI_INT, id_ten_der, id_ten_der, MPI_COMM_WORLD);
        cout << "Filosofo " << id << " comienza a pensar" << endl;
        sleep_for(milliseconds(aleatorio<50, 300>()));
    }
}
// ---------------------------------------------------------------------

void funcion_tenedores(int id)
{
    int valor, id_filosofo; // valor recibido, identificador del filósofo
    MPI_Status estado;      // metadatos de las dos recepciones

    while (true)
    {
        // ...... recibir petición de cualquier filósofo (completar)
        MPI_Recv(&valor, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
        // ...... guardar en 'id_filosofo' el id. del emisor (completar)
        id_filosofo = estado.MPI_SOURCE;
        cout << "Ten. " << id << " ha sido cogido por filo. " << id_filosofo << endl;

        // ...... recibir liberación de filósofo 'id_filosofo' (completar)
        MPI_Recv(&valor, 1, MPI_INT, id_filosofo, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
        cout << "Ten. " << id << " ha sido liberado por filo. " << id_filosofo << endl;
    }
}
// ---------------------------------------------------------------------

void funcion_camarero()
{
    int num_filosofos_sentados = 0, valor;
    int flag;
    MPI_Status estado;
    int id_esperando;
    int tag_aceptable;
    while (true){
        // MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &flag, &estado);
        // if (flag > 0){
        //     switch (estado.MPI_TAG){
        //         case etiq_sentarse:
        //             if (num_filosofos_sentados < 4){
        //                 MPI_Recv(&valor, 1 , MPI_INT, estado.MPI_SOURCE, etiq_sentarse, MPI_COMM_WORLD, &estado);
        //                 num_filosofos_sentados++;
        //                 // MPI_Ssend(&valor, 1, MPI_INT, estado.MPI_SOURCE, etiq_sentarse, MPI_COMM_WORLD);
        //             }
        //         break;
        //         case etiq_levantarse:
        //             MPI_Recv(&valor, 1 , MPI_INT, estado.MPI_SOURCE, etiq_levantarse, MPI_COMM_WORLD, &estado);
        //             num_filosofos_sentados--;
        //             break;
        //     }
        // }

        if (num_filosofos_sentados < 4){
            tag_aceptable = MPI_ANY_SOURCE;
        } else
        {
            tag_aceptable = etiq_levantarse;
        }

        MPI_Recv(&valor, 1 , MPI_INT, MPI_ANY_SOURCE, tag_aceptable, MPI_COMM_WORLD, &estado);

        switch(estado.MPI_TAG){
            case etiq_sentarse:
            cout << "Camarero sienta al filósofo " << estado.MPI_SOURCE << endl;
            num_filosofos_sentados++;
            break;
            case etiq_levantarse:
            cout << "Camarero levanta al filósofo " << estado.MPI_SOURCE << endl;
            num_filosofos_sentados--;
            break;
        }
        


        // MPI_Recv(&valor,1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &estado);
        // switch(estado.MPI_TAG){
        //     case etiq_sentarse:
        //         if (num_filosofos_sentados < 4){
        //             MPI_Ssend(&valor, 1 , MPI_INT, estado.MPI_SOURCE, etiq_sentarse, MPI_COMM_WORLD);
        //             cout << "Camarero permite al filósofo " << estado.MPI_SOURCE << " sentarse en la mesa" << endl;
        //             num_filosofos_sentados++;
        //         } else
        //         {
        //             id_esperando = estado.MPI_SOURCE;
        //         }
                
        //     break;
        //     case etiq_levantarse:
        //         num_filosofos_sentados--;
        //         if (num_filosofos_sentados < 4){ //avisamos al que estaba esperando
        //             MPI_Ssend(&valor, 1 , MPI_INT, id_esperando, etiq_sentarse, MPI_COMM_WORLD);
        //         }
        //     break;
        // }

    }
}
// ---------------------------------------------------------------------

int main(int argc, char **argv)
{
    int id_propio, num_procesos_actual;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id_propio);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos_actual);

    if (num_procesos == num_procesos_actual)
    {
        // ejecutar la función correspondiente a 'id_propio'
        if (id_propio == id_camarero)
            funcion_camarero();
        else if (id_propio % 2 == 0)           // si es par
            funcion_filosofos(id_propio); //   es un filósofo
        else                              // si es impar
            funcion_tenedores(id_propio); //   es un tenedor
    }
    else
    {
        if (id_propio == 0) // solo el primero escribe error, indep. del rol
        {
            cout << "el número de procesos esperados es:    " << num_procesos << endl
                 << "el número de procesos en ejecución es: " << num_procesos_actual << endl
                 << "(programa abortado)" << endl;
        }
    }

    MPI_Finalize();
    return 0;
}

// ---------------------------------------------------------------------
