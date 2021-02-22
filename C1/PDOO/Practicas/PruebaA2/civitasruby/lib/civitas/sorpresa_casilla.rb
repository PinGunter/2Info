#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva
module Civitas
  class Sorpresa_casilla < Sorpresa  # sorpresa que manda a una casilla al jugador
    def initialize(tablero, valor, texto)
      super(texto)
      @tablero = tablero
      @valor = valor
    end
    
    def aplicar_a_jugador(actual,todos)
      casilla = -1
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        casilla = todos.at(actual).get_num_casilla_actual
        tirada = @tablero.calcular_tirada(casilla, @valor)
        nueva = @tablero.nueva_posicion(casilla,tirada)
        todos.at(actual).mover_a_casilla(nueva)
        @tablero.get_casilla(nueva).recibe_jugador(actual,todos)
      end
    end
    
    
  end
end
