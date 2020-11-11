# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Villanos
  class Plan
    def initialize(n,f,p, pps = 0, t = false)
      @nombre = n
      @fecha_consecucion = f
      @prioridad = p
      @posicion_paso_siguiente = pps
      @terminado = t
      @pasos = set_pasos # asumiendo que exista
      @objetivo_maligno = nil

    end
  end
end