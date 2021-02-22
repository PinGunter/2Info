class Sala
  
  attr_reader :aforo
  
  def initialize(a)
    @plazas_reservadas= Array.new
    @aforo=a
  end
  
  def reservaPlazas(nombre_cliente, fecha, numero_entradas)
        
        for i in 1..numero_entradas do #bucle loop
            
            #envío de mensaje 2.4.1 ,  crear es new, r es una variable local
            r= PlazaReservada.new(nombre_cliente, fecha)
            
            #envío de mensaje 2.4.2, incluir es <<, plazas reservadas es un atributo (ver diagrama de clases)
            @plazas_reservadas<<r 
            
        end
        
        
  end
    
    def obtener_numero_reservas(fecha)
      
    end
end
