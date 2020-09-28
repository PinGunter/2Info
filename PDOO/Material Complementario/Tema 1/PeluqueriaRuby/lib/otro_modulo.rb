#Ejecutar este fichero con Run-File o May-F6

require_relative "persona"

module Otro_Modulo

  manolo = Basico::Persona.new( "Manolo " , 20 , Basico::ColorPelo::MORENO)  
  
  # ¿qué pasa si quitamos Basico::?
  
  puts manolo.inspect
    
end
