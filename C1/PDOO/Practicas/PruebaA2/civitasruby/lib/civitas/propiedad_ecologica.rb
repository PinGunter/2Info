# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas
  class Propiedad_ecologica < Titulo_propiedad
    def initialize(inversion, nom, alquiler, factor, hipoteca, precioComp, precioEdif)
      super(nom,alquiler,factor,hipoteca,precioComp, precioEdif)
      @porcentaje_inversion = inversion
      
    end
    
    def hacerme_sostenible(jugador)
      super(jugador)
    end
    
    def to_s
      info = super
      info += "Soy ecologica"
    end
    
    def get_precio_venta
      get_precio_venta*(1+@porcentaje_inversion)
    end
    
  end
end
