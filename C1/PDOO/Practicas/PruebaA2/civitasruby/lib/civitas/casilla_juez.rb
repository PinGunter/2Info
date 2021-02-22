#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  
  class Casilla_juez < Casilla
    
    def initialize(carcel,nombre)
      super(nombre)
      @carcel = carcel
    end
    
    @override
    def to_s
      "#{super}   El jugador va a la carcel"
    end
    
    def recibe_jugador(actual, todos)
      if(jugador_correcto(actual, todos))
        super
        todos.at(actual).encarcelar(@carcel)
      end
    end
    
  end
  
end
