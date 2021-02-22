#encoding:utf-8

#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
# @author salva
#require_relative "dado"
#require_relative "tablero"
#require_relative "mazo_sorpresas"
#require_relative "gestor_estados"
#require_relative "sorpresa"
#require_relative "jugador"
#require_relative "titulo_propiedad"
module Civitas
  #clase Civitas::Civitas_juego que representa la partida de civitas
  class Civitas_juego
    @@num_jugadores = 4
    @@casilla_carcel = 5
    @@num_casillas = 20
    # constructor de la clase
    # añade los jugadores pasados por parametro, decide quien empieza y inicializa el mazo y el tablero
    def initialize(nombres)
      @jugadores = Array.new
      nombres.each do |nombre|
        @jugadores << Jugador.new_nombre(nombre)
      end

      @gestor_estados = Gestor_estados.new
      @estado = @gestor_estados.estado_inicial
      @indice_jugador_actual = Dado.instance.quien_empieza(nombres.length)
      @mazo = nil
      @tablero = nil


      @tablero = Tablero.new(@@casilla_carcel)
      @mazo = Mazo_sorpresas.new(true)
      inicializar_mazo_sorpresas(@tablero)
      inicializar_tablero(@mazo)
    end

    # metodo para inicialiar el tablero
    def inicializar_tablero(mazo)
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Huerta Los Patos", 100, 0.27, 300, 300, 300)))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Rodahuevo", 200, 0.53, 300, 300, 300)))
      @tablero.añade_casilla(Casilla_sorpresa.new(mazo, "Suerte!"))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Recogidas", 400, 0.51, 600, 600, 600)))
      # carcel, ya añadida
      @tablero.añade_casilla(Casilla_calle.new(Propiedad_ecologica.new(0.05,"Avenida de la Constitución", 500, 0.11, 700, 700, 700)))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Huerta Jorobado", 600, 0.6, 800, 800, 800)))
      @tablero.añade_casilla(Casilla_sorpresa.new(mazo, "Suerte!"))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Hierbabuena", 800, 0.08, 1000, 1000, 1000)))
      @tablero.añade_casilla(Casilla.new("Parking Gratuito"))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Estación de Autobuses", 1000, 0.75, 1200, 1200, 1200)))
      @tablero.añade_casilla(Casilla_sorpresa.new(mazo, "Suerte!"))
      @tablero.añade_casilla(Casilla_calle.new(Propiedad_ecologica.new(0.05,"Calle Periodista Daniel Saucedo Aranda", 1100, 0.59, 1300, 1300, 1300)))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Periodista Rafael Gómez", 1200, 0.9, 1400, 1400, 1400)))
      @tablero.añade_juez
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Real de la Alhambra", 1300, 0.18, 1500, 1500, 1500)))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Pedro Antonio de Alarcón", 1340, 0.77, 1540, 1540, 1540)))
      @tablero.añade_casilla(Casilla_impuesto.new(1000, "Impuesto"))
      @tablero.añade_casilla(Casilla_calle.new(Titulo_propiedad.new("Calle Marqués de Larios", 1800, 0.64, 2000, 2000, 2000)))
    end

    def inicializar_mazo_sorpresas(tablero)
      @mazo.al_mazo(Sorpresa_especulador.new(500, "Te conviertes en jugador especulador, ahora pagarás menos impuestos y podrás evitar la cárcel"))
      @mazo.al_mazo(Sorpresa_pagar_cobrar.new(-300, "Multa por exceso de velocidad. Paga 300"))
      @mazo.al_mazo(Sorpresa_salir_carcel.new(@mazo))
      @mazo.al_mazo(Sorpresa_casa_hotel.new(-300, "La nueva PS5 ocupa demasiado espacio, debes hacer reformas. Paga 300 por cada casa u hotel"))
      @mazo.al_mazo(Sorpresa_casilla.new(tablero, 19, "Es la feria de Málaga y no te la puedes perder. Avanza hasta Calle Marqués de Larios"))
      @mazo.al_mazo(Sorpresa_ir_carcel.new(tablero))
      @mazo.al_mazo(Sorpresa_por_jugador.new(250, "Vas a cenar con tus amigos pero se les olvida la cartera. Cada jugador te paga 250"))
      @mazo.al_mazo(Sorpresa_casilla.new(tablero, 13, "Suspendes el examen de PDOO y tienes que ir a revisión. Ve a la ETSIIT"))
      @mazo.al_mazo(Sorpresa_casa_hotel.new(350, "Hay un terremoto y el seguro te paga 350 por cada casa y hotel "))
      @mazo.al_mazo(Sorpresa_pagar_cobrar.new(600, "Te conviertes en tu propio jefe y ganas 600"))
      @mazo.al_mazo(Sorpresa_por_jugador.new(-350, "\nVas de fiesta con tus amigos sin medidas de seguridad y ahora debes pagarle la PCR"))
    end


    # metodo para añadir el dinero al jugador segun el numero de veces que pasa por salida
    def contabilizar_pasos_por_salida(jugador_actual)
      while @tablero.get_por_salida > 0
        jugador_actual.pasa_por_salida # cambiamos get_por_salida ----> pasa_por_salida
      end
    end

    # metodo para pasar al siguiente jugador
    def pasar_turno
      @indice_jugador_actual = (@indice_jugador_actual + 1) % @jugadores.length
    end

    # metodo para obtener el siguiente estado del juego
    def siguiente_paso_completado(operacion)
      @estado = @gestor_estados.siguiente_estado(get_jugador_actual, @estado, operacion)
    end

    # metodo que delega la operacion de construir casas
    def construir_casa(ip)
      @jugadores.at(@indice_jugador_actual).construir_casa(ip)
    end

    # metodo que delega la operacion de construir hoteles
    def construir_hotel(ip)
      @jugadores.at(@indice_jugador_actual).construir_hotel(ip)
    end

    # metodo que delega la operacion de vender
    def vender(ip)
      @jugadores.at(@indice_jugador_actual).vender(ip)
    end

    #metodo que delega la operacion de hipotecar

    def hipotecar(ip)
      @jugadores.at(@indice_jugador_actual).hipotecar(ip)
    end

    # metodo que delega la operacion de cancelar hipoteca
    def cancelar_hipoteca(ip)
      @jugadores.at(@indice_jugador_actual).cancelar_hipoteca(ip)
    end

    # metodo que delega la operacion de salir de la carcel pagando
    def salir_carcel_pagando
      @jugadores.at(@indice_jugador_actual).salir_carcel_pagando
    end

    # metodo que delega la operacion de salir de la carcel tirando
    def salir_carcel_tirando
      @jugadores.at(@indice_jugador_actual).salir_carcel_tirando
    end

    # metodo que devuelve:
    # true si la partida debe acabar (alguien ha entrado en bancarrota)
    # false si todos los jugadores tiene dinero
    def final_del_juego
      bancarrota = false
      indice = 0
      while indice < @jugadores.length and not bancarrota
        bancarrota = @jugadores.at(indice).en_bancarrota
        indice += 1
      end
      return bancarrota
    end

    def compare_to(jugador)
      @saldo <=> jugador.get_saldo
    end
    # metodo que produce la lista ordenada de jugadores en funcion de su saldo
    def ranking
      clasificacion = []
      jugador_aux = @jugadores.clone

      for i in 0..@jugadores.size
        max = jugador_aux.at(0)
        pos = 0

        for j in 1..jugador_aux.size-1
          if max.compare_to(jugador_aux[j]) < 0
            max = jugador_aux.at(j)
            pos = j
          end
        end

        clasificacion << max
        jugador_aux.delete_at(pos)

      end
      return clasificacion
    end


    def mostrar_ranking
      rango = ranking
      puts rango
      #      posicion = 0
      #      rango.each do |jugador|
      #        puts "Posicion: " + posicion.to_s + " " +  jugador.get_nombre + "\n\tSaldo: " + jugador.get_saldo.to_s
      #        posicion += 1
      #      end
    end

    #metodo que devuelve el jugador actual
    def get_jugador_actual
      return @jugadores.at(@indice_jugador_actual)
    end

    #metodo que devuelve la casilla actual
    def get_casilla_actual
      #puts get_jugador_actual.get_num_casilla_actual
      @tablero.get_casilla(get_jugador_actual.get_num_casilla_actual)
    end

    # metodo que proporciona informacion sobre el jugador actual
    def info_jugador_texto
      return @jugadores.at(@indice_jugador_actual).to_s
    end

    def avanza_jugador
      jugador_actual = @jugadores.at(@indice_jugador_actual)
      posicion_actual = jugador_actual.get_num_casilla_actual
      #      puts "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
      #      puts @jugadores
      #      puts "indice actual"
      #      puts @indice_jugador_actual
      #      puts jugador_actual
      #      puts posicion_actual
      #      puts "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ"
      tirada = Dado.instance.tirar
      posicion_nueva = @tablero.nueva_posicion(posicion_actual, tirada)
      casilla = @tablero.get_casilla(posicion_nueva)
      contabilizar_pasos_por_salida(jugador_actual)
      jugador_actual.mover_a_casilla(posicion_nueva)
      casilla.recibe_jugador(@indice_jugador_actual, @jugadores)
      contabilizar_pasos_por_salida(jugador_actual)

    end

    def comprar
      jugador_actual = @jugadores.at(@indice_jugador_actual)
      num_casilla_actual = jugador_actual.get_num_casilla_actual
      casilla = @tablero.get_casilla(num_casilla_actual)
      titulo = casilla.titulo
      res = jugador_actual.comprar(titulo)
      res
    end

    def siguiente_paso
      jugador_actual = @jugadores.at(@indice_jugador_actual)
      operacion = @gestor_estados.operaciones_permitidas(jugador_actual, @estado)
      case operacion
      when Operaciones_juego::PASAR_TURNO
        pasar_turno
        siguiente_paso_completado(operacion)
      when Operaciones_juego::AVANZAR
        avanza_jugador
        siguiente_paso_completado(operacion)
      end
      return operacion
    end

    def hacer_sostenible(ip)
#      puts "@@@@@@@@\nLlamada hacer_sostenible civitas_juego\n@@@@@@@@@@@@@@@"
      result = false
      jugador = @jugadores.at(@indice_jugador_actual)
      propiedad_sostenible = jugador.hacer_sostenible(ip)
      if (!propiedad_sostenible.nil?)
        casillas = @tablero.get_casillas
        num_casilla_actual = jugador.get_num_casilla_actual
        casilla_actual = casillas.at(num_casilla_actual)
        result = true
      end
      return result
    end
    
    
    private :avanza_jugador, :contabilizar_pasos_por_salida, :inicializar_mazo_sorpresas, :inicializar_tablero, :pasar_turno, :ranking
  end
end
