#include <iostream>
#include <thread>
#include <future>
using namespace std;

long factorial(int n){ return n > 0 ? n*factorial(n-1) : 1 ;}

const int num_hebras = 8;

void funcion_hebra(int i){
    int fac = factorial(i+1);
    cout << "hebra numero " << i << ", factorial(" << i+1 << ") = " << fac << endl;
}

int main(){
    thread hebras[num_hebras];

    for (int i=0; i < num_hebras; i++)
        hebras[i] = thread(funcion_hebra, i);
    for (int i=0; i < num_hebras; i++)
        hebras[i].join();
}