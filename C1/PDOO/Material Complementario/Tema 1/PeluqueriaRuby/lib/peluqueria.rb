module Basico

  require_relative "cita"
  
  class Peluqueria
    
  def initialize
    @citas=Array.new
  end
  
  def dar_cita(persona)
    year= 2020+rand(3) #hasta 2 años a partir de 2020
    dia= 1+ rand(31) 
    hora= 9+rand(9)
    fecha= Time.new(year, 11, dia, hora)
    cita = Cita.new(persona, fecha)
    @citas<<cita
    cita
  end
  
  def poner_rubio(p)
    p.pelo=ColorPelo::RUBIO
  end
  
  def anular_cita(cita)
    @citas.delete(cita)
    puts "Cita anulada"
  end
end

end
