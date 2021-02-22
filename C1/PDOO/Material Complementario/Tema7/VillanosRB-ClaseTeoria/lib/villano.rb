# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Villanos
  class Villano
    @@Asociacion = "VillanosSA"

    def initiliaze(n,e,f)
      @nombre = n
      @escondite_secreto = e
      @fortuna = f
      @planes = Array.new
      @mayordomo = nil
    end

    def set_fortuna(cantidad)

    end

    def seguir_plan_prioritario()
      terminado = false
      plan = primer_plan_activo
      if plan != nil
        puedo_continuar = true
        while !terminado and puedo_continuar do
          terminado = plan.get_terminado
          gasto = plan.inversion_paso_siguiente
          puedo_continuar = gasto <= @fortuna
          if puedo_continuar
            ganancia = plan.dar_paso_siguiente
            set_fortuna(@fortuna-gasto+ganancia)
          end
        end
      end
      terminado = plan != nil and terminado
      return terminado
    end

    def primer_plan_activo()

    end

    def self.set_asociacion(asociacion)

    end
    private :set_fortuna

    # si el set_asociacion fuera privado
    # private_class_method :set_asociacion
  end
end

