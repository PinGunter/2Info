#encoding :utf-8
require_relative "diario"
require_relative "estados_juego"
require_relative "operaciones_juego"
require_relative "tipo_casilla"
require_relative "tipo_sorpresa"
require_relative "tablero"
require_relative "casilla"
require_relative "dado"
require_relative "mazo_sorpresas"

module Civitas
  p1 = 0
  p2 = 0
  p3 = 0
  p4 = 0
  i = 0
  100.times do
    empieza=Dado.Instance.quien_empieza(4)
    puts "Iteracion" + i
    if empieza == 0
      p1 +=1
    elsif empieza == 1
      p2 +=1
    elsif empieza == 2
      p3 += 1
    elsif empieza == 3
      p4 += 1
    end
    i += 1
  end
  
  puts "Jugador 1:" + p1
  puts "Jugador 2:" + p2
  puts "Jugador 3:" + p3
  puts "Jugador 4:" + p4
  
end