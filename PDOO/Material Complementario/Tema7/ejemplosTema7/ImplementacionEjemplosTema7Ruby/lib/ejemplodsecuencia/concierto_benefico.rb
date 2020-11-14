class ConciertoBenefico
  
  attr_reader :lugar_celebracion
  
  
  def initialize(lc)
    @lugar_celebracion= lc
  end
  
    
 def comprar_entradas(nombre_cliente, fecha, numero_entradas){
        
        s= @lugar_celebracion #env�o de mensaje 2.1
        
        nReservas= s.obtener_numero_reservas(fecha) #env�o de mensaje 2.2
        
        aforo= s.aforo #env�o de mensaje 2.3
        
        if (nReservas+numero_entradas<aforo){ #inicio bloque alt
            
            s.reserva_plazas(nombre_cliente, fecha, numero_entradas) #env�o de mensaje 2.4
        
            return 'Compra efectuada: las reservas solicitadas est�n hechas a su nombre'
            
        else  #{}segunda parte del bloque alt
            
             return 'Compra denegada: no hay aforo suficiente';
        
        
        # ver 2.4.1 y 2.4.2 en la clase Sala, m�todo reserva_plazas
            
    }   
       
        
   

    
end
