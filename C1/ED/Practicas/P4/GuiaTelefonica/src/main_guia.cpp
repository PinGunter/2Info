/**
 * @file main_guia.cpp
 * @author Salvador Romero Cortés
 * @brief archivo de prueba de la clase guia
 */
#include <iostream>
#include <fstream>
#include <guiatlf.h>
using namespace std;

/**
 * @brief programa principal. Los archivos que contengan las guias se deben pasar por la terminal con el nombre de archivo
 * @param argc numero de parametros pasados por la terminal
 * @param args vector de los parametros
 * 
 */
int main(int argc, char * args[]){
    if (argc != 3){
        cerr << "Uso incorrecto. El uso es: main_guia <archivo_guia1> <archivo_guia2>" << endl;
        exit(1);
    }

    ifstream archivo1(args[1]);
    ifstream archivo2(args[2]);
    Guia_Tlf guia1, guia2, intersecc, filtrada, entre_dos;
    string nombre, nombre2, telefono;
    char letra;

    //leemos los datos
    archivo1 >> guia1;
    archivo2 >> guia2;
    cout << "--------- Intersección -----------"  << endl;
    intersecc = guia1.interseccion(guia2);
    cout << intersecc;

    cout << "-------- Modificación de número ----------" << endl;
    cout << guia1;
    cout << "Introduce el nombre de la persona cuyo telefono quieres modificar: " << endl;
    getline(cin, nombre);
    if (guia1.estaClave(nombre)){
        cout << "Introduce el número de teléfono nuevo: " << endl;
        cin >> telefono;
        guia1.modificarTelefono(nombre,telefono);
        cout << "Ahora la guia queda como: " << endl;
        cout << guia1;
    } else{
        cerr << "Nombre no encontrado en la guia de teléfono. Pasando al siguiente método" << endl;
    }

    cout << "--------- Números de teléfono que empiecen por una determinada letra -----------"  << endl;
    cout << "--- Guia 1 sin filtrar:" << endl;
    cout << guia1;
    cout << "Introduce la letra por la que deben empezar los nombres de la lista(\"case sensitive\") " << endl;
    cin >> letra;
    cin.ignore();
    filtrada = guia1.telefonosEmpiezanCon(letra);
    cout << "--- Guia 1 filtrada: " << endl;
    cout << filtrada;

    cout << "--------- Números de teléfono entre dos nombres -----------"  << endl;
    cout << "--- Guia actual: " << endl;
    cout << guia1;
    cout << "Introduce el primer nombre:" << endl;
    getline(cin, nombre);
    if (guia1.estaClave(nombre)){
        cout << "Introduce el segundo nombre:" << endl;
        getline(cin, nombre2);
        if (guia1.estaClave(nombre2)){
            entre_dos = guia1.numerosEntre(nombre,nombre2);
            cout << "--- Nueva lista" << endl;
            cout << entre_dos;
        } else{
            cerr << nombre2 << " no está en la lista, se omite el método" << endl; 
        }
    } else{
        cerr << nombre << " no está en la lista, se omite el método" << endl;
    }

    archivo1.close();
    archivo2.close();


}