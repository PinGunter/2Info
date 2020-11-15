
package ejemplodsecuencia;

//solo se implementa aquello directamente relacionado con el diagrama de secuencia del ejemplo

public class OrganizadoraConciertosBeneficos {
    
    public String comprarEntradas(String nombreCliente, String nombreConcierto, Date fecha, int numeroEntradas){
        
        //envío de mensaje 1 del diagrama. Es necesario declarar c como variable de la clase que devuelve el método
        ConciertoBenefico c= buscarConcierto(nombreConcierto);
        
        //envío de mensaje 2 del diagrama. Es necesario declarar mensaje como variable de la clase que devuelve el método
        String mensaje= c.comprarEntradas(nombreCliente, fecha, numeroEntradas);
        
        return mensaje; 
        
        //ver implementación de envío de mensajes 2.1 a 2.4 en ConciertoBenéfico, método comprarEntradas
    }
    
    public ConciertoBenefico buscarConcierto(String nombreConcierto){
        
    }
    
}
