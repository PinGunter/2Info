module Basico

  
  class Peluqueria
    
  def initialize
    @citas=Array.new
  end
  
  def dar_cita
    year= 2020+rand(3) #hasta 2 años a partir de 2020
    dia= 1+ rand(31) 
    hora= 9+rand(9)
    cita= Time.new(year, 11, dia, hora)
    @citas<<cita
    cita
  end
  
end

end
