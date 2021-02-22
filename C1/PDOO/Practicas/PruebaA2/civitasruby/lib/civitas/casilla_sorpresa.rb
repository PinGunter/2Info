#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas

  class Casilla_sorpresa < Casilla
    
    def initialize(mazo, nombre) # deberiamos pasarle nombre como parametro?
      super(nombre) 
      @mazo = mazo
      #@sorpresa = nil
    end
    
    @override
    def to_s
      #if @sorpresa == nil
      #  @sorpresa = @mazo.siguiente
      #end
      super
      #"#{super} {#@sorpresa.to_s}"
    end
    
    def recibe_jugador(actual, todos)
      if(jugador_correcto(actual, todos))
        sorpresa = @mazo.siguiente
        super
        sorpresa.aplicar_a_jugador(actual, todos)
      end
    end
    
  end

end
