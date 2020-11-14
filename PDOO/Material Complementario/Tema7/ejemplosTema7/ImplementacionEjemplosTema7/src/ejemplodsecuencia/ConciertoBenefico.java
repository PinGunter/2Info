
package ejemplodsecuencia;

//solo se implementa aquello directamente relacionado con el diagrama de secuencia del ejemplo

public class ConciertoBenefico {
    private Sala lugarCelebracion;
    
    public String comprarEntradas(String nombreCliente, Date fecha, int numeroEntradas){
        
        Sala s= getLugarCelebracion(); //env�o de mensaje 2.1
        
        int nReservas= s.obtenerNumeroReservas(fecha); //env�o de mensaje 2.2
        
        int aforo= s.getAforo(); //env�o de mensaje 2.3
        
        if (nReservas+numeroEntradas<aforo){ //inicio bloque alt
            
            s.reservaPlazas(nombreCliente, fecha, numeroEntradas); //env�o de mensaje 2.4
        
            return "Compra efectuada: las reservas solicitadas est�n hechas a su nombre";}
            
        else  //segunda parte del bloque alt
            
             return "Compra denegada: no hay aforo suficiente";
        
        
        //ver 2.4.1 y 2.4.2 en la clase Sala, m�todo reservaPlazas
            
    }   
       
        
   
    public Sala getLugarCelebracion{
        return lugarCelebracion;
}
    
}
