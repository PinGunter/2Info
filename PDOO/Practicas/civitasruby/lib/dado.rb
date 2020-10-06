# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


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
      if tirada >= @@tirada_carcel
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
    end
    
  end
end
