require_relative "persona"
require_relative "peluqueria"
require_relative "color_pelo"
require_relative "cita"

module Basico

  p= Persona.new( "Pepe" ,19 , ColorPelo::RUBIO, 180)
  j = Persona.new("Juan", 20, ColorPelo::MORENO,160)
  p.saluda
  pelu = Peluqueria.new
  puts p.inspect  #observa lo que aparece en pantalla
  cita=pelu.dar_cita(j)
  puts p.es_alto
  puts j.es_alto
  
  puts p.to_s
  pelu.poner_rubio(j)
  puts j.to_s
  
  j.anular_cita(pelu,cita)
  
  # puts p.get_planeta #uso de metodo de instancia que consulta un atributo de clase
  # 
  #  puts Persona.get_planeta
  #  
  #  Persona.set_planeta("Mercurio")
  #  
  #  puts p.get_planeta
  #  
  #  p.set_planeta("Neptuno")
  #  
  #  puts j.get_planeta
  # 
  #  puts j.inspect
  #  puts j.get_planeta
  #  puts p.inspect
  #  puts p.get_planeta
end

# Tareas: 
# 1 Prueba el código de este proyecto y asegúrate de que lo comprendes todo bien - ok
# 2 Añade a la clase Persona un atributo nuevo: altura - ok
# 3 Añade un método que devuelva si la persona es alta o baja, dependiendo de su altura - ok
# 4 Añade a la clase Persona el método to_s para que muestre los valores de los atributos de forma legible. - ok
# 5 Usa el método to_s en el main.  -ok
# 6 Añade a la peluqueria un método para cambiar el color de pelo del objeto Persona que reciba como argumento y pruébalo en el main - ok
# 7 Añade a la clase Persona un método anularCita que envíe un mensaje a la Peluquería pidiendo anular -ok
# 8 Añade un mensaje a Peluquería para anular la cita (el que es invocado en la tarea anterior), que muestre el mensaje en pantalla "cita anulada" -ok
# 9 Si te animas a complicar el ejemplo, crea una clase Cita que guarde información de la persona que pide la cita y la fecha y hora asignadas.
# Al aanular una cita, ésta deberá buscarse en la colección de citas y borrarse.
 