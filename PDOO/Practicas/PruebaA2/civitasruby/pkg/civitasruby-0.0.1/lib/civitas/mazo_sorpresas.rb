#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
#require_relative "sorpresa"
require_relative "diario"
module Civitas
  class Mazo_sorpresas
    def initialize(d=false)
      init
      @ultima_sorpresa
      @debug = d
      if @debug
        Diario.instance.ocurre_evento("Activado modo debug MazoSorpresas")
      end
    end

    def init
      @sorpresas = Array.new
      @cartas_especiales = Array.new
      @barajada = false
      @usadas = 0
    end

    def al_mazo(sorpresa)
      if not @barajada
        @sorpresas << sorpresa
      end
    end

    def siguiente
      if not @barajada or @usadas == @sorpresas.length
        @usadas = 0
        if not @debug
          @sorpresas.shuffle
          @barajada = true
        end
      end

      @usadas += 1
      @ultima_sorpresa= @sorpresas.shift
      @sorpresas << @ultima_sorpresa
      return @ultima_sorpresa
    end

    def inhabilitar_carta_especial(sorpresa)
      if @sorpresas.include?(sorpresa)
        @sorpresas.delete(sorpresa)
        @cartas_especiales << sorpresa
        Diario.instance.ocurre_evento("Inhabilitada carta especial")
      end
    end

    def habilitar_carta_especial(sorpresa)
      if @cartas_especiales.include?(sorpresa)
        @cartas_especiales.delete(sorpresa)
        @sorpresas << sorpresa
        Diario.instance.ocurre_evento("Se habilita la sorpresa " + sorpresa.to_s)
      end
    end

    private :init
  end
end
