#include <iostream>
#include <thread>
#include <future>
using namespace std;

long factorial(int n){ return n > 0 ? n*factorial(n-1) : 1 ;}

void funcion_hebra(int n, long & resultado) { resultado = factorial(n);}

int main(){
    long resultado1, resultado2;
    thread hebra1(funcion_hebra, 5, ref(resultado1)), hebra2(funcion_hebra, 10,ref(resultado2));

    hebra1.join(); hebra2.join();

    cout << "factorial(5) == " << resultado1 << endl
         << "factorial(10) == " << resultado2 << endl;
}