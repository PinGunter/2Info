#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas

  class Casilla_calle < Casilla

    attr_reader :titulo

    def initialize(titulo)
      super(titulo.nombre)
      @titulo = titulo
    end
    
    @override
    def to_s
      "#{super}  #{@titulo.to_s}"
    end

    def recibe_jugador(actual, todos)
      if(jugador_correcto(actual, todos))
        super
        jugador = todos.at(actual)
        if(!@titulo.tiene_propietario)
          jugador.puede_comprar_casilla
        else
          @titulo.tramitar_alquiler(jugador)
        end
      end
    end

  end
  
end

