#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva
module Civitas
  class Sorpresa_ir_carcel < Sorpresa  ## Sorpresa ir a la carcel
    def initialize(tablero)
      super("Ve a la cárcel")
      @tablero = tablero
    end
    
    def aplicar_a_jugador(actual, todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        todos.at(actual).encarcelar(@tablero.num_casilla_carcel)
      end
    end
    
    
  end
end
