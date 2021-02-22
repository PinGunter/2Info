/**
 * @author Salvador Romero Cortés
 * */

 #include <cassert>

template <typename T>
void Cola<T>::reservar(const int n){
    assert(n>0);
    reservados = n;
    datos = new T[n];
}

template <typename T>
void Cola<T>::liberar(){
    delete [] datos;
    datos = 0;
    anterior = posterior = nelem = reservados = 0;
}

template <typename T>
void Cola<T>::copiar(const Cola &c){
    for (int i=c.anterior; i != c.posterior; i=(i+1)%reservados)
        datos[i] = c.datos[i];
    anterior = c.anterior;
    posterior = c.posterior;
    nelem = c.nelem;
}

template <typename T>
void Cola<T>::redimensionar(const int n){
    assert(n>0 && n>= nelem);
    T * aux = datos;
    int tam_aux = reservados;
    reservar(n);
    for (int i=0; i < nelem; i++)
        datos[i] = aux[(anterior+i)%tam_aux];
    anterior = 0;
    posterior = nelem;
    delete [] aux;
}

template <typename T>
Cola<T>::Cola(){
    reservar(10);
    anterior = posterior = nelem = 0;
}

template <typename T>
Cola<T>::Cola(const Cola &c){
    reservar(c.reservados);
    copiar(c);
}

template <typename T>
Cola<T> & Cola<T>::operator=(const Cola& c){ 
    if (this != &c){
        liberar();
        reservar(c.reservados);
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
    if (nelem == reservados)
        redimensionar(reservados*2);
    datos[posterior] = valor;
    posterior = (posterior+1) % reservados;
    nelem++;
}

template <typename T>
void Cola<T>::quitar(){
    assert(!vacia());
    anterior = (anterior+1)%reservados;
    nelem--;
    if (nelem < reservados/4)
        redimensionar(reservados/2);
}

template <typename T>
T Cola<T>::frente() const{
    assert(!vacia());
    return datos[anterior];
}

template <typename T>
bool Cola<T>::vacia() const{
    return nelem == 0;
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