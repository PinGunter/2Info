
package ejemplodsecuencia;

//solo se implementa aquello directamente relacionado con el diagrama de secuencia del ejemplo

public class OrganizadoraConciertosBeneficos {
    
    public String comprarEntradas(String nombreCliente, String nombreConcierto, Date fecha, int numeroEntradas){
        
        //env�o de mensaje 1 del diagrama. Es necesario declarar c como variable de la clase que devuelve el m�todo
        ConciertoBenefico c= buscarConcierto(nombreConcierto);
        
        //env�o de mensaje 2 del diagrama. Es necesario declarar mensaje como variable de la clase que devuelve el m�todo
        String mensaje= c.comprarEntradas(nombreCliente, fecha, numeroEntradas);
        
        return mensaje; 
        
        //ver implementaci�n de env�o de mensajes 2.1 a 2.4 en ConciertoBen�fico, m�todo comprarEntradas
    }
    
    public ConciertoBenefico buscarConcierto(String nombreConcierto){
        
    }
    
}
