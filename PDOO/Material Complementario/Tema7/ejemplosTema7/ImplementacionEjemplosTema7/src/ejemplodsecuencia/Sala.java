
package ejemplodsecuencia;

//solo se implementa aquello directamente relacionado con el diagrama de secuencia del ejemplo

import java.util.ArrayList;



class Sala {
    
    ArrayList <PlazaReservada> plazasReservadas;  //atributo de referencia, decido qué nombre ponerle
    int aforo;
    
    public void reservaPlazas(String nombreCliente, Date fecha, int numeroEntradas){
        
        for( int i=1; i<=numeroEntradas; i++){ //bucle loop
            
            //envío de mensaje 2.4.1 ,  crear es new, r es una variable local
            PlazaReservada r= new PlazaReservada(nombreCliente, fecha); 
            
            //envío de mensaje 2.4.2, incluir es add, plazas reservadas es un atributo (ver diagrama de clases)
            plazasReservadas.add(r); 
            
        }
        
        
    }
    
    public int getAforo(){
        
    }
    
    public int obtenerNumeroReservas(Date fecha){
        
    }
    
}
