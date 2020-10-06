# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require_relative "sorpresa"
require_relative "diario"
class MazoSorpresas
  def initialize(d=false)
    init
    @ultima_sorpresa
    @debug = d
    if @debug
      Diario.Instance.ocurre_evento("Activado modo debug dado")
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
      @barajada = true
      @usadas = 0
      if not @debug
        @sorpresas.shuffle
      end
    end
    
    @usadas += 1
    @ultima_sorpresa= @sorpresas.shift
    @sorpresas << sorpresa
    return @ultima_sorpresa
  end
  
  def inhabilitar_carta_especial(sorpresa)
    if @sorpresas.include?(sorpresa)
      @sorpresas.delete(sorpresa)
      @cartas_especiales << sorpresa
      Diario.Instance.ocurre_evento("Se inhabilita la sopresa" + sorpresa.nombre)
    end
  end
  
  def habilitar_carta_especial(sorpresa)
    if @sorpresas_especiales.include?(sorpresa)
      @sorpresas_especiales.delete(sorpresa)
      @sorpresas << sorpresa
      Diario.Instance.ocurre_evento("Se habilita la sorpresa " + sorpresa.nombre)
    end
  end
  
  private :init
end
