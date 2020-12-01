#include <Pila_max_VD.h>
#include <vector>

using namespace std;



Pila_max::Pila_max(const Pila_max& otro):p(otro.p){}

Pila_max & Pila_max::operator=(const Pila_max& otro){
    if(this != &otro){
        p = otro.p;
    }
    return *this;
}
    
void Pila_max::poner(int nuevo){
    elemento n = {nuevo, nuevo};
    if (!vacia()){
        if (tope().maximo > nuevo)
            n.maximo = tope().maximo;
    } 
    p.push_back(n);
}
     
void Pila_max::quitar(){
    if (!vacia()){
        p.pop_back();
    }
}
       
const elemento & Pila_max::tope() const{
    return p.back();
}

elemento & Pila_max::tope(){
    return p.back();
}
       
bool Pila_max::vacia() const{
    return p.empty();
}

std::ostream & operator<<(std::ostream & os, elemento e){
    os << "\n   " << e.ele << "\t   " << e.maximo;
    return os;
}
