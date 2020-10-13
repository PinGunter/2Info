# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require 'singleton'

module Civitas
  class Dado
    include Singleton
    
    attr_reader :ultimo_resultado
    
    @@salida_carcel = 5
    
    def initialize
      @random = Random.new
      @ultimo_resultado 
      @debug = false
    end
    
    def tirar
      tirada = @random.rand(6)+1
      if @debug
        tirada = 1
      end
      @ultimo_resultado = tirada
      return tirada
    end
    
    def salgo_de_la_carcel
      tirada = tirar
      @ultimo_resultado = tirada
      if tirada >= @@salida_carcel
        return true
      else
        return false
      end
    end
    
    def quien_empieza(n)
      return @random.rand(n)
    end
    
    def set_debug(d)
      @debug = d
      if @debug
        Diario.instance.ocurre_evento("Activado modo debug de Dado")
      else
        Diario.instance.ocurre_evento("Desactivado modo debug del Dado")
      end
    end
    
    private :initialize
  end
end
