#include <iostream>
#include <thread>
#include <future>
using namespace std;

long factorial(int n){ return n > 0 ? n*factorial(n-1) : 1 ;}

const int num_hebras = 8;

int main(){

    future<long> futuros[num_hebras];

    for (int i=0; i < num_hebras; i++)
        futuros[i] = async (launch::async, factorial, i+1);

    for (int i=0; i < num_hebras; i++)
        cout << "factorial (" << i+1 << ") = " << futuros[i].get() << endl;
}