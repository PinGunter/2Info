#encoding :utf-8
require_relative "diario"
require_relative "estados_juego"
require_relative "operaciones_juego"
require_relative "tipo_casilla"
require_relative "tipo_sorpresa"
require_relative "tablero"
require_relative "casilla"
require_relative "dado"

module Civitas
#  tablero = Tablero.new(2)
#  tablero.añade_juez
#  tablero.añade_casilla(Casilla.new("Primera"))
#  for i in 0..tablero.casillas.length-1
#    puts tablero.get_casilla(i).nombre
#  end

  for i in 0..20
    puts Random.rand(6)+1
  end
end


