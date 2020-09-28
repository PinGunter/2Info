
package basico ;

import java.time.LocalDateTime;

 // Enumerado con visibilidad de paquete. Ver diferencias con visibilidad publica   
//public  enum ColorPelo { MORENO, CASTA�O, RUBIO, PELIROJO }


public class Persona { // Clase con visibilidad p�blica
 // Atributos de instancia privados
 private String nombre ; 
 private int edad ;
 public ColorPelo pelo ;
 private int altura;

 public Persona ( String n , int e , ColorPelo p ) { // "Constructor" p�blico
     nombre = n ;
     edad = e ;
     pelo = p ;
 }

 void saluda() { // Visibilidad de paquete. M�todo de instancia
 System.out.println( "Hola , soy "+nombre );
 }

 
LocalDateTime pedirCita(Peluqueria peluqueria) {// Visibilidad de paquete. M�todo de instancia
     saluda();
     return peluqueria.darCita(); //env�a mensaje a peluquer�a para que �sta le d� la cita
 }
 
boolean esAlto(){
     return altura >= 170;
}

 @Override
 public String toString(){
    String atributos = "Nombre: " + nombre + "\nEdad: " + edad + "\nColor de pelo: " + pelo.toString() + "\nAltura: " + altura;
    return atributos;
}

}