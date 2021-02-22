# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Villanos
  class Objetivo_maligno
    attr_accessor :descripcion
    def initialize(d)
      @descripcion = d
    end

    # si quisieramos poner privados el lector y el escritor
    private :decripcion, :descripcion=
  end
end 