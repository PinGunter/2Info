/**
 * @file main.cpp
 * @brief archivo que ejecuta el programa principal
 * @author Salvador Romero Cortés
 **/
#include <iostream>
#include <imagenES.h>
#include <funciones_imagen.h>


/**
 * @todo mover funciones auxiliares y no miembros de imagen a otra cabecera
 **/
using namespace std;
/**
 * @brief funcion principal del programa. Se encarga de la ejecución del programa
 * @param argc el número de parametros pasados en la ejecucion
 * @param args el vector de los parametros pasados en la ejecucion, esto es imagen_entrada,imagen_salida,min,max
 **/
int main(int argc, char *args[]){   
   if (argc != 3){
       error("Numero de argumentos incorrecto.\nEl uso correcto es bin/main <nombre_archivo_entrada> <nombre_archivo_salida>");
   }
   TipoImagen tipo;
   tipo = LeerTipoImagen(args[1]);
   if (tipo != IMG_PGM){
       error("Imagenes no son de tipo PGM");
   }
    int eleccion;
    cout << "Bienvenido al programa de edición de fotos PGM:" << endl << 
            "Elige una de las siguientes opciones:" << endl << 
            "1. Umbralizar imagen en una escala de grises" << endl << 
            "2. Hacer zoom a un recorte cuadrado de la imagen" << endl << 
            "3. Aplicar una trasnformacion lineal sobre el contraste de la imagen" << endl << 
            "4. Realizar Morphing entre dos imagenes" << endl;

    cin >> eleccion;

    string base;
    int pasos;
    int min, max;
    int x1,x2,y1,y2;

    switch (eleccion){
        case 1:
            cout << "Introduce el mínimo y el máximo del umbral" << endl;
            cin >> min >> max;
            umbralizar_escala_grises(args[1],args[2],min,max);
            break;
        case 2:
            cout << "Introduce la fila y columna del pixel superior izquierdo: " << endl;
            cin >> x1 >> y1;
            cout << "Introduce la fila y columna del pixel inferior derecho: (recuerda que el recorte es cuadrado) " << endl;
            cin >> x2 >> y2;
            zoom(args[1],args[2],x1,y1,x2,y2);
            break;
        case 3:
            cout << "Introduce el minimo y el maximo del intervalo del nuevo rango de contraste" << endl;
            cin >> min >> max;
            contrastar(args[1],args[2],min,max);
            break;
        case 4:
            cout << "Introduce el nombre base de las imágenes intermedias." << endl;
            cin >> base;
            cout << "Introduce el numero de pasos intermedios" << endl;
            cin >> pasos;
            morphing(args[1],args[2],base.c_str(),pasos);
            break;
        default:
            error("Entrada no válida");
            break;

    }

    cout << "Completado. " << endl;
}
