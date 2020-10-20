/**
 * @file Racional.cpp
 * @author [Modificado por Salva Romero, proporcionado por profesor]
 * @brief Implementación de los métodos y funciones declarados en @ref Cabeceras
 * @anchor Definiciones
*/
#include<iostream>
#include <cassert>
#include "Racional.h"

using namespace std;

//Constructor por defecto
Racional::Racional(){
  num = 0;
  den = 1;
} 

//Constructor
Racional::Racional(int n, int d ){
  assert(d != 0);
  num = n;
  den = d;
} 

//Constructor de copia
Racional::Racional (const Racional& c){
  num = c.num;
  den = c.den;
}

//Asignaci�n
void Racional::asignar(int n, int d){
  assert(d != 0);
  num = n;
  den = d;
}

//Comparaci�n
bool Racional::comparar(Racional r){
  return ((num*r.den == den*r.num)?1:0);
}

//Impresi�n en cout
void Racional::print(){
  cout << '(' << this->num << '/' << this->den << ')';
}

//Operador +
Racional Racional::operator+(const Racional &r){
  return Racional(num*r.den+den*r.num, den*r.den);
}

//Operador *
Racional Racional::operator*(const Racional &r){
  return Racional(num*r.num, den*r.den);
}

//Operador +=
void Racional::operator+=(const Racional &r){
  num = num*r.den+den*r.num;
  den = den*r.den;
}

//Operador ==
bool Racional::operator==(const Racional & l){
  return ((num*l.den == den*l.num)?1:0); 
}

//Operador <<
ostream& operator<< (ostream & os, const Racional & r){
  return os << '(' << r.num << ',' << r.den << ')';
}

//Operador >>
istream& operator>> (istream& is, Racional& r){
  char caracter;
  int numerador, denominador;
  is >> caracter >> numerador >> caracter >> denominador >> caracter;
  r= Racional(numerador,denominador);
  return is;
}

//Simplificaci�n a forma irreducible
Racional Racional::simplifica(){
   int a, b;

   /* Casos base */
   if (num == 0)
       return Racional(0,den);
   else if (num == den)
       return Racional(num,den);
   else if (num > den){
       a = num;
       b = den;
   }
   else{
       a = den;
       b = num;
   };

   /* Algoritmo de Euclides */
   int r;
   do{
     r = a % b;
     a = b;
     b = r;
   } while (r > 0);

   return Racional(num/=a, den/=a);
}

//funciones getters
int Racional::numerador(){
  return num;
}

int Racional::denominador(){
  return den;
}

//funcion para calcular el MCD
int getMaxComDiv(int primero, int segundo){
  //caso base
  if (segundo == 0)
    return primero;
  
  getMaxComDiv(segundo,primero%segundo);
}


//metodo para reducir el racional
void Racional::reducir(){
  //primero obtenemos el MCD
  int mcd = getMaxComDiv(numerador(),denominador());
  int nuevo_num = numerador() / mcd;
  int nuevo_den = denominador() / mcd;
  asignar(nuevo_num,nuevo_den); 
}

//metodo para obtener el valor real
double Racional::getReal(){
  return ((numerador()*1.0)/(denominador()*1.0));
}
