
package ejemplodcomunicacion;

import java.util.ArrayList;

public class Vuelo {
    
    //solo se implementa lo relativo al diagrama de comunicaci�n proporcionado
    
    private ArrayList<Viaje> viajes; //por asociaci�n <<A>>
    private Avion a; //por asociacion <<A>>
    
    public void reservar(Pasaporte pasajero){
        
        // env�o de mensaje 1 del diagrama, <<S>>
        boolean plazas= plazasLibres();  
        
        if (plazas){
            //env�o de mensaje 2 del diagrama. Implica declarar la variable s
            Asiento s= a.eligeAsientoLibre(); 

            //env�o de mensaje 3 del diagrama, <<L>>. "crear" es el constructor
            Viaje elViaje= new Viaje(pasajero, s); 
            
            //el mensaje 3.1 se env�a a la clase Viaje, verlo ah�.
            
            //env�o de mensaje 4 del diagrama. "incluir" es "add" para ArrayList
            viajes.add(elViaje); 
        }
        
    }
    
    public boolean plazasLibres(){//pendiente de conocer c�mo implementar
        
    }
    
}
