#encoding :utf-8
require_relative "diario"
require_relative "estados_juego"
require_relative "operaciones_juego"
require_relative "tipo_casilla"
require_relative "tipo_sorpresa"
require_relative "tablero"
require_relative "casilla"
require_relative "dado"
require_relative "mazo_sorpresas"

module Civitas
  p1 = 0
  p2 = 0
  p3 = 0
  p4 = 0
  100.times do
    empieza=Dado.instance.quien_empieza(4);
    if empieza == 0
      p1 +=1
    elsif empieza == 1
      p2 +=1
    elsif empieza == 2
      p3 += 1
    elsif empieza == 3
      p4 += 1
    end
  end
  
  puts "Jugador 1:" + p1.to_s
  puts "Jugador 2:" + p2.to_s
  puts "Jugador 3:" + p3.to_s
  puts "Jugador 4:" + p4.to_s
  
  Dado.instance.set_debug(true)
  puts Diario.instance.leer_evento
  10.times do
    puts Dado.instance.tirar
  end
  
  Dado.instance.set_debug(false)
  puts Diario.instance.leer_evento
  10.times do
    puts Dado.instance.tirar
  end
  
  puts "Ultimo resultado: " + Dado.instance.ultimo_resultado.to_s
  puts "Salgo de la carcel?"
  puts Dado.instance.salgo_de_la_carcel.to_s + " <- " + Dado.instance.ultimo_resultado.to_s
  
  puts "Enumerados"
  puts Tipo_casilla::DESCANSO
  puts Tipo_sorpresa::PAGAR_COBRAR
  puts Operaciones_juego::COMPRAR
  puts Estados_juego::INICIO_TURNO


  mazo_sorpresas = MazoSorpresas.new
  sorpresa1 = Sorpresa.new("Primera")
  sorpresa2 = Sorpresa.new("Segunda")
  mazo_sorpresas.al_mazo(sorpresa1)
  mazo_sorpresas.al_mazo(sorpresa2)
  puts "Siguiente sorpresa: "  + mazo_sorpresas.siguiente.nombre
  mazo_sorpresas.inhabilitar_carta_especial(sorpresa2)
  puts Diario.instance.leer_evento
  mazo_sorpresas.habilitar_carta_especial(sorpresa2)
  puts Diario.instance.leer_evento
  
  # tablero
  tablero = Tablero.new(3)
  casillas = Array.new
  indice = 0
  
  6.times do
    casillas << (Casilla.new("Casilla " + indice.to_s))
    tablero.añade_casilla(casillas.at(indice))
    indice += 1
  end
  tablero.añade_juez
  destino = 0
  origen = 0
  indice = 0
  15.times do
    puts tablero.inspect
    if indice == 0
      destino = tablero.nueva_posicion(indice, Dado.instance.tirar)
      puts "Origen:" + indice.to_s + " Destino: " + destino.to_s + "\tDado: " + Dado.instance.ultimo_resultado.to_s
    else
      origen = destino
      destino = tablero.nueva_posicion(origen, Dado.instance.tirar)
      puts "Origen:" + origen.to_s + " Destino: " + destino.to_s + "\tDado: " + Dado.instance.ultimo_resultado.to_s
      
    end
    indice += 1
  end
end

