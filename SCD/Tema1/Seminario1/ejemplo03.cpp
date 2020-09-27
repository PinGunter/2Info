#include <iostream>
#include <thread>
#include <future>
using namespace std;

long factorial(int n){ return n > 0 ? n*factorial(n-1) : 1 ;}

long resultado1, resultado2;

void funcion_hebra_1(int n) { resultado1 = factorial(n);}
void funcion_hebra_2(int n) { resultado2 = factorial(n);}

int main(){
    thread hebra1(funcion_hebra_1, 5), hebra2(funcion_hebra_2, 10);

    hebra1.join(); hebra2.join();

    cout << "factorial(5) == " << resultado1 << endl
         << "factorial(10) == " << resultado2 << endl;
}