#encoding :utf-8
require_relative "diario"
require_relative "estados_juego"
require_relative "operaciones_juego"
require_relative "tipo_casilla"
require_relative "tipo_sorpresa"
require_relative "tablero"
require_relative "casilla"
module Civitas
  tablero = Tablero.new(2)
  tablero.añade_juez
  tablero.añade_casilla(Casilla.new("Primera"))
  puts tablero.get_casilla(2).nombre
 # puts tablero.casillas.inspect
end


