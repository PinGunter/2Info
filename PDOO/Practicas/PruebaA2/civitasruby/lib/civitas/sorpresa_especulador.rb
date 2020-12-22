#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva

module Civitas
  class Sorpresa_especulador < Sorpresa
    def initialize(fianza, texto)
      super(texto)
      @fianza = fianza
    end
    
    def aplicar_a_jugador(actual, todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        especulador = Jugador_especulador.nuevo_especulador(todos.at(actual), @fianza)
        todos[actual] = especulador
      end
    end
    
  end
end
