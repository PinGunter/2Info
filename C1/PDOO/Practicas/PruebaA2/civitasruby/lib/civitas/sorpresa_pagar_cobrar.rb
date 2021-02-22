#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva

module Civitas
  class Sorpresa_pagar_cobrar < Sorpresa
    def initialize(valor, texto)
      super(texto)
      @valor = valor      
    end
    
    def aplicar_a_jugador(actual,todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        todos.at(actual).modificar_saldo(@valor)
      end
    end
    
  end
end
