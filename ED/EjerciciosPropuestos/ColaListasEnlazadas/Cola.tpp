/**
 * @author Salvador Romero Cortés
 * */

 #include <cassert>

template <typename T>
void Cola<T>::liberar(){
    CeldaCola<T> * aux;
    while (primera != 0){
        aux = primera;
        primera = primera->sig;
        delete aux;
    }
    ultima = 0;
}

template <typename T>
void Cola<T>::copiar(const Cola &c){
    if (c.primera == 0)
        primera = ultima = 0;
    else{
        primera = new CeldaCola<T>;
        primera->elemento = c.primera->elemento;
        ultima = primera;
        CeldaCola<T>* orig = c.primera;
        while (orig->sig != 0){
            orig = orig->sig;
            ultima->sig = new CeldaCola<T>;
            ultima = ultima->sig;
            ultima->elemento = orig->elemento;
        }
        ultima->sig = 0;
    }
}


template <typename T>
Cola<T>::Cola(){
    primera = ultima = 0;
}

template <typename T>
Cola<T>::Cola(const Cola &c){
    copiar(c);
}

template <typename T>
Cola<T> & Cola<T>::operator=(const Cola& c){ 
    if (this != &c){
        liberar();
        copiar(c);
    }
    return *this;
}

template <typename T>
Cola<T>::~Cola(){
    liberar();
}

template <typename T>
void Cola<T>::poner(const T & valor){
    CeldaCola<T> * nueva = new CeldaCola<T>;
    nueva->elemento = valor;
    nueva->sig = 0;
    if (primera == 0)
        primera = ultima = nueva;
    else{
        ultima->sig = nueva;
        ultima = nueva;
    }
}

template <typename T>
void Cola<T>::quitar(){
    assert(primera!=0);
    CeldaCola<T> * aux = primera;
    primera = primera->sig;
    delete aux;
    if (primera == 0)
        ultima = 0;
}

template <typename T>
T Cola<T>::frente() const{
    assert(primera != 0);
    return primera->elemento;
}

template <typename T>
bool Cola<T>::vacia() const{
    return primera == 0;
}

template <typename T>
Cola<T> Cola<T>::operator++(int n){
    Cola<T> copia(*this);
    quitar();
    return copia;
}

template <typename T>
void Cola<T>::operator+=(const Cola &c){
    poner(c);
}