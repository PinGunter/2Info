class OrganizadoraConciertosBeneficos
  def initialize
    
  end
def comprar_entradas(nombre_cliente, nombre_concierto, fecha, numero_entradas)
        
       #envío de mensaje 1 del diagrama. 
       c= buscarConcierto(nombre_concierto)
        
       #envío de mensaje 2 del diagrama. 
       mensaje= c.comprarEntradas(nombre_cliente, fecha, numero_entradas)
        
       mensaje 
        
       #ver implementación de envío de mensajes 2.1 a 2.4 en ConciertoBenéfico, método comprar_entradas
end

def buscarConcierto(nombre_concierto)
  
end
    

end
