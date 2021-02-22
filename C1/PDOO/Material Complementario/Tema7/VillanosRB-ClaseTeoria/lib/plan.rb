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
      @pasos = Array.new  # set_pasos # asumiendo que exista
      @objetivo_maligno = nil

    end
    
    def get_terminado
      @terminado
    end
    
    def esta_activo
      
    end
    
    def dar_pasos_siguiente
      paso = @pasos.at(@posicion_paso_siguiente)
      paso.set_terminado(true)
      ganancia = paso.get_ganancia
      if @posicion_paso_siguiente != @pasos.size() -1
        posicion_paso_siguiente +=1
      else
        @terminado = true
      end
      ganancia
    end
    
    def inversion_paso_siguiente
      paso = @pasos.at(@posicion_paso_siguiente)
      gasto = paso.get_inversion
      return gasto
    end
  end
end