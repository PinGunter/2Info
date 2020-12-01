#include <Pila_max_Cola.h>

using namespace std;

Pila_max::Pila_max(const Pila_max& otro):c(otro.c){}

    
void Pila_max::poner(int nuevo){
    Cola<elemento> c2;
    elemento n = {nuevo,nuevo};
    if (!vacia()){
        if (c.frente().maximo > nuevo)
            n.maximo = c.frente().maximo;
    }
    c2.poner(n);

    while (!vacia()){
        c2.poner(c.frente());
        quitar();
    }
    c = c2;
}
     
void Pila_max::quitar(){
   if (!vacia()){ 
       c.quitar(); 
   }
}
       
const elemento& Pila_max::tope() const{
    return c.frente();
}

elemento& Pila_max::tope(){
    return c.frente();
}
       
bool Pila_max::vacia() const{
    return c.vacia();
}

std::ostream & operator<<(std::ostream & os, elemento e){
    os << "\n   " << e.ele << "\t   " << e.maximo;
    return os;
}
