#include <iostream>
#include "Lista.hpp"

using namespace std;

bool vacia(Lista<char> &l);
void todo_minuscula(Lista<char> &l);
void escribir(const Lista<char> &l);
void escribir_minuscula(const Lista<char> &l);
void borrar_caracter(Lista<char> &l, char c);
Lista<char> al_reves(const Lista<char> &l);
Posicion localizar(const Lista<char> &l, char c);
bool palindromo(const Lista<char> &l);

int main()
{
    char dato;
    Lista<char> l;
    cout << "Escriba una frase" << endl;
    while ((dato = cin.get()) != '\n')
        l.insert(l.end(), dato);
    cout << "La frase introducida es:" << endl;
    escribir(l);
    cout << "La frase en minúsculas:" << endl;
    escribir_minuscula(l);
    if (localizar(l, ' ') == l.end())
        cout << "La frase no tiene espacios" << endl;
    else
    {
        cout << "La frase sin espacios:" << endl;
        Lista<char> aux(l);
        borrar_caracter(aux, ' ');
        escribir(aux);
    }
    cout << "La frase al revés: " << endl;
    escribir(al_reves(l));
    cout << (palindromo(l) ? "Es " : "No es ") << "un palíndromo" << endl;
    return 0;
}


bool vacia(Lista<char> &l)
{
    return (l.begin() == l.end());
}
void todo_minuscula(Lista<char> &l)
{
    for (Posicion p = l.begin(); p != l.end(); ++p)
        l.set(p, tolower(l.get(p)));
}
void escribir(const Lista<char> &l)
{
    for (Posicion p = l.begin(); p != l.end(); ++p)
        cout << l.get(p);
    cout << endl;
}
void escribir_minuscula(const Lista<char> &l)
{
    Lista<char> l2(l);
    todo_minuscula(l2);
    escribir(l2);
}
void borrar_caracter(Lista<char> &l, char c)
{
    Posicion p = l.begin();
    while (p != l.end())
        if (l.get(p) == c)
            p = l.erase(p);
        else
            ++p;
}
Lista<char> al_reves(const Lista<char> &l)
{
    Lista<char> aux;
    for (Posicion p = l.begin(); p != l.end(); ++p)
        aux.insert(aux.begin(), l.get(p));
    return aux;
}
Posicion localizar(const Lista<char> &l, char c)
{
    for (Posicion p = l.begin(); p != l.end(); ++p)
        if (l.get(p) == c)
            return (p);
    return l.end();
}
bool palindromo(const Lista<char> &l)
{
    bool es_palindromo = true;
    Lista<char> aux(l);
    int n = l.size();
    if (n >= 2)
    {
        borrar_caracter(aux, ' ');
        todo_minuscula(aux);
        Posicion p1, p2;
        p1 = aux.begin();
        p2 = aux.end();
        p2--;
        for (int i = 0; i < n / 2 && es_palindromo; i++)
        {
            if (aux.get(p1) != aux.get(p2))
                es_palindromo = false;
            p1++;
            p2--;
        }
    }
    return es_palindromo;
}