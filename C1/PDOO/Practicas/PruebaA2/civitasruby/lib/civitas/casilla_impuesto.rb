#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas

  class Casilla_impuesto < Casilla

    def initialize(importe, nombre)
      super(nombre)
      @importe = importe # debe ser positivo porque en paga (jugador) lo multiplica por *-1
    end
    
    @override
    def to_s
      "#{super}   Importe: #{@importe}"
    end

    def recibe_jugador(actual, todos)
      if(jugador_correcto(actual, todos))
        super
        todos.at(actual).paga_impuesto(@importe)
      end
    end

  end
  
end
