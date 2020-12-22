#encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva

module Civitas
  class Sorpresa_casa_hotel < Sorpresa # sorpresa de pagar por tantas casas y hoteles se tengan
    def initialize(valor, texto)
      super(texto)
      @valor = valor
    end
    
    def aplicar_a_jugador(actual,todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        todos.at(actual).modificar_saldo(@valor*todos.at(actual).cantidad_casas_hoteles)
      end
    end
    
  end
end
