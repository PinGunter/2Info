class Vuelo
  def initialize(a)
    @viajes= Array.new
    @a=a
  end
  
  def reservar(pasajero)
     # env�o de mensaje 1 del diagrama, <<S>>
     plazas= plazasLibres
        
        if (plazas)
           #env�o de mensaje 2 del diagrama. 
            s= @a.eligeAsientoLibre() 

            #env�o de mensaje 3 del diagrama, <<L>>. "crear" es el constructor
            elViaje= Viaje.new(pasajero, s) 
            
            #el mensaje 3.1 se env�a a la clase Viaje, verlo ah�.
            
            #env�o de mensaje 4 del diagrama. "incluir" es << para Array
            @viajes<<elViaje 
        end
        
  end
    
  def plazasLibres
    #pendiente de conocer c�mo implementar
  end
    
end
