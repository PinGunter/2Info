
package basico ;

import java.time.LocalDateTime;

 // Enumerado con visibilidad de paquete. Ver diferencias con visibilidad publica   
//public  enum ColorPelo { MORENO, CASTAÑO, RUBIO, PELIROJO }


public class Persona { // Clase con visibilidad pública
 // Atributos de instancia privados
 private String nombre ; 
 private int edad ;
 public ColorPelo pelo ;
 private int altura;

 public Persona ( String n , int e , ColorPelo p ) { // "Constructor" público
     nombre = n ;
     edad = e ;
     pelo = p ;
 }

 void saluda() { // Visibilidad de paquete. Método de instancia
 System.out.println( "Hola , soy "+nombre );
 }

 
Cita pedirCita(Peluqueria peluqueria) {// Visibilidad de paquete. Método de instancia
     saluda();
     return peluqueria.darCita(this); //envía mensaje a peluquería para que ésta le dé la cita
 }
 
boolean esAlto(){
     return altura >= 170;
}

 @Override
 public String toString(){
    String atributos = "Nombre: " + nombre + "\nEdad: " + edad + "\nColor de pelo: " + pelo.toString() + "\nAltura: " + altura;
    return atributos;
}

 void anularCita(Peluqueria pelu, Cita cita){
     System.out.println(this.nombre+": Deseo anular la cita");
     pelu.anularCita(cita);
 }
 
}