# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Compania_aerea
  class Vuelo
    def initialize
      @viajes = Array.new
      @a = nil
    end

    def reservar(pasajero)
      plazas = plazas_libres
      if plazas
        s = a.elige_asiento_libre
        el_viaje = Viaje.new(pasajero,@a)
        if plazas # esto estaba mal en el diagrama
          @viajes << el_viaje
        end
      end
    end
  end
end
