
package basico ;

public class PruebaPeluqueria { // Clase con programa principal
    
 public static void main ( String [] args ) {
     
   //se crea un objeto Persona y otro Peluquería, que se comunican entre sí mediante envío de mensajes
     
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
 1 Prueba el código de este proyecto y asegúrate de que lo comprendes todo bien OK
 2 Añade a la clase Persona un atributo nuevo: altura OK
 3 Añade un método que devuelva si la persona es alta o baja, dependiendo de su altura  OK
 4 Añade a la clase Persona el método toString para que muestre los valores de los atributos de forma legible.  OK
 5 Usa el método toString en el main.   OK
 6 Añade a la peluqueria un método para cambiar el color de pelo del objeto Persona que reciba como argumento y pruébalo en el main OK
 7 Añade a la clase Persona un método anularCita que envíe un mensaje a la Peluquería pidiendo anular   OK  
 8 Añade un mensaje a Peluquería para anular la cita (el que es invocado en la tarea anterior), que muestre el mensaje en pantalla "cita anulada"   OK
 9 Si te animas a complicar el ejemplo, crea una clase Cita que guarde información de la persona que pide la cita y la fecha y hora asignadas.
 Al aanular una cita, ésta deberá buscarse en la colección de citas y borrarse. OK
 */
 