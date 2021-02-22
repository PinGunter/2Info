#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

# Salva

module Civitas
  class Sorpresa_por_jugador < Sorpresa
    def initialize(valor, texto)
      super(texto)
      @valor = valor
    end
    
    def aplicar_a_jugador(actual,todos)
      if jugador_correcto(actual,todos)
        informe(actual,todos)
        texto_dinero = ""
        if @valor < 0
          texto_dinero = "Recibes del jugador #{todos.at(actual).get_nombre} : #{-1*@valor}"
        else
          texto_dinero = "Pagas al jugador #{todos.at(actual).get_nombre} : #{@valor}"
        end
        a_pagar = Sorpresa_pagar_cobrar.new(@valor*-1,texto_dinero)
        todos.length.times do |indice|
          if indice != actual
            #puts todos.at(indice).get_nombre
            a_pagar.aplicar_a_jugador(indice, todos)
          end
        end
        if @valor > 0
          texto_dinero = "Recibes del resto de los jugadores: #{@valor}"
        else
          texto_dinero = "Pagas al resto de jugadores #{todos.at(actual).get_nombre} : #{-1*@valor}"
        end
        recibe_dinero = Sorpresa_pagar_cobrar.new(@valor*(todos.length-1),texto_dinero)
        recibe_dinero.aplicar_a_jugador(actual,todos)
      end
    end
  end
end
