module Basico
   
 module ColorPelo
 MORENO= :moreno
 CASTANO= :castano
 RUBIO= :rubio
 PELIROJO= :pelirojo
 end

 class Persona
   
 def initialize (n, e, p) # " constructor "
    # Atributos de instancia ( son siempre privados )
    @nombre=n
    @edad=e
    @pelo=p
 end

 public # no es necesario , pues los métodos son públicos por defecto
 
 def saluda # Método público de instancia
     puts "Hola , soy "+@nombre
 end
 
 def pedir_cita(peluqueria)  #Método de instancia
     saluda
     return peluqueria.dar_cita #envía mensaje a peluquería para que ésta le dé la cita 
 
 end

end

end
