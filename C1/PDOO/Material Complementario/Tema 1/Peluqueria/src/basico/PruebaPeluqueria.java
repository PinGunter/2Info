
package basico ;

public class PruebaPeluqueria { // Clase con programa principal
    
 public static void main ( String [] args ) {
     
   //se crea un objeto Persona y otro Peluquer�a, que se comunican entre s� mediante env�o de mensajes
     
   Persona p=new Persona ( "Pepe" ,19 , ColorPelo.RUBIO) ;
   p.saluda ( ) ;
    
   Peluqueria pelu= new Peluqueria();
   System.out.println ("Cita en la peluqueria: ");
   Cita cita = p.pedirCita(pelu);
   
   
   System.out.println(p.toString());
   
   pelu.cambiarColorPelo(p, ColorPelo.MORENO);
   
   System.out.println(p.toString());
   
   p.anularCita(pelu,cita);
 }
 
}
 
 /* Tareas:
 1 Prueba el c�digo de este proyecto y aseg�rate de que lo comprendes todo bien OK
 2 A�ade a la clase Persona un atributo nuevo: altura OK
 3 A�ade un m�todo que devuelva si la persona es alta o baja, dependiendo de su altura  OK
 4 A�ade a la clase Persona el m�todo toString para que muestre los valores de los atributos de forma legible.  OK
 5 Usa el m�todo toString en el main.   OK
 6 A�ade a la peluqueria un m�todo para cambiar el color de pelo del objeto Persona que reciba como argumento y pru�balo en el main OK
 7 A�ade a la clase Persona un m�todo anularCita que env�e un mensaje a la Peluquer�a pidiendo anular   OK  
 8 A�ade un mensaje a Peluquer�a para anular la cita (el que es invocado en la tarea anterior), que muestre el mensaje en pantalla "cita anulada"   OK
 9 Si te animas a complicar el ejemplo, crea una clase Cita que guarde informaci�n de la persona que pide la cita y la fecha y hora asignadas.
 Al aanular una cita, �sta deber� buscarse en la colecci�n de citas y borrarse. OK
 */
 