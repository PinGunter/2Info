#include <iostream>
#include <thread>
using namespace std;

void funcion_hebra_1(){
    for (unsigned long i = 0; i < 5000; i++)
        cout << "hebra 1, i == " << i << endl;
}

void funcion_hebra_2(){
    for (unsigned long i = 0; i < 5000; i++)
        cout << "hebra 2, i == " << i << endl;
}

int main(){
    thread hebra1, hebra2;

    hebra1 = thread(funcion_hebra_1);
    hebra2 = thread(funcion_hebra_2);

    hebra1.join();
    hebra2.join();
}