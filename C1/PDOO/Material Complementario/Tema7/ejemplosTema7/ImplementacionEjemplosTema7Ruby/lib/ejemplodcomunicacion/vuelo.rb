class Vuelo
  def initialize(a)
    @viajes= Array.new
    @a=a
  end
  
  def reservar(pasajero)
     # envío de mensaje 1 del diagrama, <<S>>
     plazas= plazasLibres
        
        if (plazas)
           #envío de mensaje 2 del diagrama. 
            s= @a.eligeAsientoLibre() 

            #envío de mensaje 3 del diagrama, <<L>>. "crear" es el constructor
            elViaje= Viaje.new(pasajero, s) 
            
            #el mensaje 3.1 se envía a la clase Viaje, verlo ahí.
            
            #envío de mensaje 4 del diagrama. "incluir" es << para Array
            @viajes<<elViaje 
        end
        
  end
    
  def plazasLibres
    #pendiente de conocer cómo implementar
  end
    
end
