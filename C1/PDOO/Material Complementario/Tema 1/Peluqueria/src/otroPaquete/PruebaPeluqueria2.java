
package otroPaquete ;


import basico.Persona;
import basico.ColorPelo; //¿qué ocurre aquí? Arréglalo

public class PruebaPeluqueria2 { // Clase con programa principal
    
public static void main ( String [] args ) {
     
   //se crea un objeto Persona y se muestra información
     
  Persona manolo = new Persona ( "Manolo " , 20 , ColorPelo.MORENO) ;

  System.out.println(manolo.toString()) ;   
 }
 }
