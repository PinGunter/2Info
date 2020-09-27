#include <iostream>
#include <thread>
#include <future>
using namespace std;

long factorial(int n){ return n > 0 ? n*factorial(n-1) : 1 ;}

int main(){

    future <long> futuro1 = async( launch::async, factorial, 5),
                futuro2 = async( launch::async, factorial, 10);

    cout << "factorial(5) == " << futuro1.get() << endl
    << "factorial(10) == " << futuro2.get() << endl; 
}