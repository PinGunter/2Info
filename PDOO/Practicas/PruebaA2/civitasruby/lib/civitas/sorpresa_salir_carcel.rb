#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva

module Civitas
  class Sorpresa_salir_carcel < Sorpresa
    def initialize(mazo)
      super("Quedas libre de la cárcel")
      @mazo = mazo
    end
    
    def aplicar_a_jugador(actual,todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        alguien_tiene_s_carcel = false
        indice = 0
        # preguntamos al resto de jugadores si tienen la carta que les libra de la carcel
        while indice < todos.length and not alguien_tiene_s_carcel
          if indice != actual
            alguien_tiene_s_carcel = todos.at(indice).tiene_salvoconducto
          end
          indice +=1
        end
        if not alguien_tiene_s_carcel
          todos.at(actual).obtener_salvoconducto(Sorpresa_salir_carcel.new(@mazo))
          salir_del_mazo
        end
      end
    end
    
    # metodo para sacar la carta actual(librarte de la carcel) del mazo
    def salir_del_mazo
      @mazo.inhabilitar_carta_especial(self)
    end

    # metodo para devolver la carta de salvoconducto al mazo
    def usada
      @mazo.habilitar_carta_especial(self)
    end
    
    
  end
end
