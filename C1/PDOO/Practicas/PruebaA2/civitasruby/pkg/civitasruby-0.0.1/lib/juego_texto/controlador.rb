#encoding:utf-8
# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.


require_relative "../civitas/civitas_juego"
require_relative "../civitas/operaciones_juego"
require_relative "../civitas/operacion_inmobiliaria"


module Civitas
  class Controlador
    def initialize(c, v)
      @juego = c
      @vista = v
    end

    def juega
      @vista.set_civitas_juego(@juego)
      while(!@juego.final_del_juego)
        @vista.actualizar_vista
        @vista.pausa
        op = @juego.siguiente_paso
        @vista.mostrar_siguiente_operacion(op)

        if(op != Operaciones_juego::PASAR_TURNO)
          @vista.mostrar_eventos
        end

        if(!@juego.final_del_juego)

          case op
          when Operaciones_juego::COMPRAR
            if(@vista.comprar == Respuestas::Lista_respuestas.at(1))
              @juego.comprar
            end
            @juego.siguiente_paso_completado(op)

          when Civitas::Operaciones_juego::GESTIONAR
            @vista.gestionar
            gest = Gestiones_inmobiliarias::Lista_gestiones_inmobiliarias[@vista.get_gestion]
            ip = @vista.get_propiedad

            operacion_inm = Operacion_inmobiliaria.new(gest,ip)

            case operacion_inm.gestion
            when Civitas::Gestiones_inmobiliarias::VENDER    #me lo asocia con el método vender de juego en vez de con el enum
              #              puts "SELECCIONADA OPCION VENDER"
              @juego.vender(ip)
            when Civitas::Gestiones_inmobiliarias::HIPOTECAR
              #              puts "SELECCIONADA OPCION HIPOTECAR"
              @juego.hipotecar(ip)
            when Civitas::Gestiones_inmobiliarias::CANCELAR_HIPOTECA
              #              puts "SELECCIONADA OPCION CANCELAR_HIPOTECA"
              @juego.cancelar_hipoteca(ip)
            when Civitas::Gestiones_inmobiliarias::CONSTRUIR_CASA
              #              puts "SELECCIONADA OPCION CONSTRUIR CASA"
              @juego.construir_casa(ip)
            when Civitas::Gestiones_inmobiliarias::CONSTRUIR_HOTEL
              #              puts "SELECCIONADA OPCION CONSTRUIR HOTEL"
              @juego.construir_hotel(ip)
            when Civitas::Gestiones_inmobiliarias::TERMINAR
              #              puts "SELECCIONADA OPCION TERMINAR"
              @juego.siguiente_paso_completado(op)
            end

          when Operaciones_juego::SALIR_CARCEL
            if(@vista.salir_carcel == salidas_carcel::PAGANDO)
              @juego.salir_carcel_pagando
            else
              @juego.salir_carcel_tirando
            end
            @juego.siguiente_paso_completado(op)
          end

        else
          puts "======== RANKING =========="
          @juego.mostrar_ranking
        end
      end
    end




  end
end
