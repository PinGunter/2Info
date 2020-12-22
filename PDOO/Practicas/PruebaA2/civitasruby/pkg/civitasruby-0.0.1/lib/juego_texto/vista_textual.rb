#encoding:utf-8
require_relative '../civitas/operaciones_juego'
require 'io/console'
require_relative '../civitas/civitas_juego'
require_relative '../civitas/salidas_carcel'
require_relative '../civitas/respuestas'
require_relative '../civitas/gestiones_inmobiliarias'
require_relative '../civitas/diario'
module Civitas

  class Vista_textual

    def initialize()
      @iPropiedad
      @iGestion
      @juegoModel
    end

    def mostrar_estado(estado)
      puts estado
    end


    def pausa
      print "Pulsa una tecla"
      STDIN.getch
      print "\n"
    end

    def lee_entero(max,msg1,msg2)
      ok = false
      begin
        print msg1
        cadena = gets.chomp
        begin
          if (cadena =~ /\A\d+\Z/)
            numero = cadena.to_i
            ok = true
          else
            raise IOError
          end
        rescue IOError
          puts msg2
        end
        if (ok)
          if (numero >= max)
            ok = false
          end
        end
      end while (!ok)

      return numero
    end



    def menu(titulo,lista)
      tab = "  "
      puts titulo
      index = 0
      lista.each { |l|
        puts tab+index.to_s+"-"+l.to_s
        index += 1
      }

      opcion = lee_entero(lista.length,
        "\n"+tab+"Elige una opción: ",
        tab+"Valor erróneo")
      return opcion
    end


    def comprar
      opcion=menu("¿Deseas comprar la calle?", ["No", "Si"])
      Respuestas::Lista_respuestas.at(opcion)
    end

    def gestionar
      opciones = ["Vender", "Hipotecar", "Cancelar Hipoteca", "Construir Casa", "Construir Hotel", "Terminar" ]
      elegido = menu("Elige la gestión inmobiliaria",opciones)
      @iGestion=elegido
      if elegido != 5
        propiedad = menu("Elige la propiedad que quieres gestionar",@juegoModel.get_jugador_actual.get_propiedades )
        @iPropiedad = propiedad
      end
    end

    def get_gestion
      @iGestion
    end

    def get_propiedad
      @iPropiedad
    end

    def mostrar_siguiente_operacion(operacion)
      print "Siguiente operacion #{operacion}\n"
    end

    def mostrar_eventos
      while Diario.instance.eventos_pendientes
        puts Diario.instance.leer_evento
      end
    end

    def set_civitas_juego(civitas)
      @juegoModel=civitas
      actualizar_vista
    end

    def actualizar_vista
      jugador = @juegoModel.get_jugador_actual
      casilla = @juegoModel.get_casilla_actual
      puts "Jugador actual"
      puts jugador.to_s
      puts "Casilla actual"
      puts casilla.to_s
    end

    def salir_carcel
      opcion=menu("¿Cómo quieres salir de la cárcel",["Pagando","Tirando"])
      Salidas_carcel::Lista_salidas_carcel.at(opcion)
    end

  end

end
