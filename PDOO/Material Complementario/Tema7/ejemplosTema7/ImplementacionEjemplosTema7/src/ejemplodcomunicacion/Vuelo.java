
package ejemplodcomunicacion;

import java.util.ArrayList;

public class Vuelo {
    
    //solo se implementa lo relativo al diagrama de comunicación proporcionado
    
    private ArrayList<Viaje> viajes; //por asociación <<A>>
    private Avion a; //por asociacion <<A>>
    
    public void reservar(Pasaporte pasajero){
        
        // envío de mensaje 1 del diagrama, <<S>>
        boolean plazas= plazasLibres();  
        
        if (plazas){
            //envío de mensaje 2 del diagrama. Implica declarar la variable s
            Asiento s= a.eligeAsientoLibre(); 

            //envío de mensaje 3 del diagrama, <<L>>. "crear" es el constructor
            Viaje elViaje= new Viaje(pasajero, s); 
            
            //el mensaje 3.1 se envía a la clase Viaje, verlo ahí.
            
            //envío de mensaje 4 del diagrama. "incluir" es "add" para ArrayList
            viajes.add(elViaje); 
        }
        
    }
    
    public boolean plazasLibres(){//pendiente de conocer cómo implementar
        
    }
    
}
