# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Villanos
  class Paso
    def initialize(d,f,inv,gan, term = false)
      @descripcion = d
      @fecha_limte = f
      @inversion = inv
      @ganancia = gan
      @terminado = term
    end

    def get_inversion()

    end

    def get_ganancia()

    end

    def set_terminado(estado)

    end
  end
end