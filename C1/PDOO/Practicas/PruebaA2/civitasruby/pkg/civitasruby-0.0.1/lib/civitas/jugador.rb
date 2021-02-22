#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

module Civitas

  require_relative 'diario'
  require_relative 'titulo_propiedad.rb'

  class Jugador
    @@casas_max = 4
    @@casas_por_hotel = 4
    @@hoteles_max = 4
    @@paso_por_salida = 1000
    @@precio_libertad = 200
    @@saldo_inicial = 7500

    def initialize(encarcelado,nombre,num_casilla_actual,puede_comprar,
        saldo ,salvoconducto,propiedades)
      @nombre = nombre
      @encarcelado = encarcelado
      @num_casilla_actual = num_casilla_actual
      @puede_comprar = puede_comprar
      @saldo = saldo
      @salvoconducto = salvoconducto #sorpresa
      @propiedades = propiedades # array de titulopropiedad
    end

    def self.new_nombre(n)
      #@nombre = nombre
      #@puede_comprar = false
      #@saldo = -1
      #@encarcelado = false
      #@num_casilla_actual = -1
      #@propiedades = Array.new
      #@salvo_conductor = nil
      self.new(false,n,0,false,@@saldo_inicial,nil,[])
    end


    def cancelar_hipoteca(ip)
      result = false
      if(@encarcelado)
        return result
      end

      if(existe_la_propiedad(ip))
        propiedad = @propiedades.at(ip)
        cantidad = propiedad.get_importe_cancelar_hipoteca
        gastar_puedo = puedo_gastar(cantidad)
      end

      if(gastar_puedo)
        result = propiedad.cancelar_hipoteca(self)
        if(result)
          Diario.instance.ocurre_evento("#{@nombre} cancela hipoteca de
            propiedad #{propiedad.get_nombre}")
        end
      end

      return result
    end

    def comprar(titulo)
      result = false
      if(@encarcelado)
        return result
      end

      if(@puede_comprar)
        precio = titulo.get_precio_compra

        if(puedo_gastar(precio))
          result = titulo.comprar(self)

          if(result)
            @propiedades<<titulo #@propiedades<<titulo
            Diario.instance.ocurre_evento("#{@nombre} compra propiedad #{titulo.get_nombre}")
          end
          @puede_comprar = false
        end
      end
      return result
    end

    def construir_casa(ip)
      result = false
      puedo_casa_edificar = false
      if (@encarcelado)
        return result
      else
        existe = existe_la_propiedad(ip)
        propiedad = @propiedades.at(ip)
        puedo_casa_edificar = puedo_edificar_casa(propiedad)
        if (puedo_casa_edificar)
          result = propiedad.construir_casa(self)
          if (result)
            Diario.instance.ocurre_evento("El jugador #{@nombre} construye una casa en la propiedad #{@propiedades.at(ip).get_nombre}")
          end
        end
      end

    end

    def construir_hotel(ip)
      result = false
      if(@encarcelado)
        return result
      end
      if(existe_la_propiedad(ip))
        propiedad = @propiedades.at(ip)
        puedo_edificar_hotel = puedo_edificar_hotel(propiedad)
        if(puedo_edificar_hotel)
          result = propiedad.construir_hotel(self)
          @propiedades.at(ip).derruir_casas(@@casas_por_hotel, self)
          if(result)
            Diario.instance.ocurre_evento("El jugador  #{@nombre}  construye hotel en la propiedad #{@propiedades.at(ip).get_nombre}")
          end
        end
      end
      return result
    end


    def hipotecar(ip)
      result = false
      if(@encarcelad)
        return result
      end

      if(existe_la_propiedad(ip))
        propiedad=@propiedades.at(ip)
        result = propiedad.hipotecar(self)
      end

      if(result)
        Diario.instance.ocurre_evento("#{@nombre} hipoteca la propiedad #{@propiedades.at(ip).get_nombre}")
      end
    end

    def encarcelar(num_casilla_carcel)
      if debe_ser_encarcelado == true
        mover_a_casilla(num_casilla_carcel)
        @encarcelado = true
        Diario.instance.ocurre_evento("#{@nombre} va a la carcel")
      else
        Diario.instance.ocurre_evento("#{@nombre} no va a la carcel")
      end
    end

    def obtener_salvoconducto(sorpresa)
      if @encarcelado == true
        res = false
      else
        @salvoconducto = sorpresa
        @devolver = true
      end
      return res
    end

    def perder_salvoconducto
      @salvoconducto.usada
      @salvoconducto = nil
    end

    def tiene_salvoconducto
      res = false
      if @salvoconducto != nil
        res = true
      end
      return res
    end

    def puede_comprar_casilla
      @puede_comprar = true
      if @encarcelado == true
        @puede_comprar = false
      end
      return @puede_comprar
    end

    def paga(cantidad)
      (modificar_saldo(cantidad*-1))
    end

    def paga_impuesto(cantidad)
      if @encarcelado == true
        res = false
      else
        res = paga(cantidad)
      end
      return res
    end

    def paga_alquiler(cantidad)
      (paga_impuesto(cantidad))
    end

    def recibe(cantidad)
      if @encarcelado == true
        res = false
      else
        res = modificar_saldo(cantidad)
      end
      return res
    end

    def modificar_saldo(cantidad)
      @saldo += cantidad
      if(cantidad >= 0)
        Diario.instance.ocurre_evento("Se incrementa el saldo del jugador #{@nombre} en #{cantidad}")
      else
        Diario.instance.ocurre_evento("Se decrementa el saldo del jugador #{@nombre} en #{-1*cantidad}")
      end
      return true
    end

    def mover_a_casilla(num_casilla)
      if @encarcelado == true
        res = false
      else
        @num_casilla_actual = num_casilla
        Diario.instance.ocurre_evento("#{@nombre} se mueve a casilla: #{@num_casilla_actual}")
        res = true
        @puede_comprar = false
      end
      return res
    end

    def puedo_gastar(precio)
      if @encarcelado == true
        res = false
      elsif @saldo >= precio
        res = true
      end
      return res
    end

    def vender(ip)
      res = false;
      if @encarcelado
        res = false
      else
        if (existe_la_propiedad(ip) && !@propiedades.at(ip).get_hipotecado())
          propiedad = @propiedades.at(ip)
          res = propiedad.vender(self)
          Diario.instance.ocurre_evento("#{@nombre} vende la casilla #{@propiedades.at(ip).get_nombre()}")
          @propiedades.delete_at(ip)
        end
      end
      return res
    end

    def tiene_algo_que_gestionar
      res = false
      if @propiedades.size > 0
        res = true
      end
      return res
    end

    def salir_carcel_pagando
      res = false
      if @saldo >= @@precio_libertad
        res = true
      end
      return res
    end

    def salir_carcel_tirando
      res = false
      if Dado.instance.salgo_de_la_carcel == true
        res = true
        @encarcelado = false
        Diario.instance.ocurre_evento("#{@nombre} sale de la carcel tirando")
      end
      return res
    end

    def pasa_por_salida
      modificar_saldo(@@paso_por_salida)
      Diario.instance.ocurre_evento("#{@nombre} pasa por salida")
      return true
    end

    def compare_to(otro)
      res = @saldo <=> otro.get_saldo
    end

    def cantidad_casas_hoteles
      total = 0
      for i in (0..@propiedades.size-1)
        total+=@propiedades.at(i).num_casas
        total+=@propiedades.at(i).num_hoteles
      end
      return total
    end

    def en_bancarrota
      res = false
      if @saldo <= 0
        res = true
      end
      return res
    end

    def existe_la_propiedad(ip)
      return ip >= 0 && ip < @propiedades.size
    end

    def get_casas_max
      @@casas_max
    end

    def get_casas_por_hotel
      @@casas_por_hotel
    end

    def get_hoteles_max
      @@hoteles_max
    end

    def get_num_casilla_actual
      @num_casilla_actual
    end

    def get_precio_libertad
      @@precio_libertad
    end

    def get_premio_por_salida
      @@paso_por_salida
    end

    def get_propiedades
      @propiedades
    end

    def get_puede_comprar
      @puede_comprar
    end

    def get_is_encarcelado
      @encarcelado
    end

    def puedo_edificar_casa(propiedad)
      #if @saldo >= propiedad.get_precio_edificar && propiedad.get_num_casas < casas_max
      # return true
      #end
      #return false
      precio = propiedad.get_precio_edificar
      puedo_edificar_casa = false
      if(puedo_gastar(precio) && propiedad.get_num_casas < get_casas_max)
        puedo_edificar_casa = true
      end
      return puedo_edificar_casa
    end

    def puedo_edificar_hotel(propiedad)
      precio = propiedad.get_precio_edificar
      puedo_edificar_hotel = false
      if(puedo_gastar(precio) && propiedad.get_num_hoteles < get_hoteles_max && propiedad.get_num_casas >= get_casas_por_hotel)
        puedo_edificar_hotel = true
      end
      return puedo_edificar_hotel
    end

    @override
    def to_s
      propiedades = get_propiedades
      nombres_propiedades = []
      propiedades.each do |nombres|
        nombres_propiedades << nombres.get_nombre
      end
      info = "**********\n"
      info +=  "Nombre: #{@nombre}
      \nEncarcelado: #{@encarcelado}
      \nNumero casilla actual: #{@num_casilla_actual}
      \nSaldo: #{@saldo}
      \nPropiedades #{nombres_propiedades}"
      info += "\n*********"
      return info
    end


    def get_propiedades #cambiada visibilidad protected->public para usar en opciones de gestion
      @propiedades
    end

    def get_saldo  #cambiamos la visibilidad de protected a public para facilitar la accesibilidad de la partida. Consultado al construir
      @saldo
    end

    def get_nombre  #cambiamos la visibilidad de protected a public para facilitar la accesibilidad de la partida.
      @nombre
    end
    private :existe_la_propiedad, :get_casas_max, :get_hoteles_max, :get_precio_libertad, :get_premio_por_salida, :perder_salvoconducto, :salir_carcel_pagando,
      :puedo_edificar_casa, :puedo_edificar_hotel, :puedo_gastar
    protected #:debe_ser_encarcelado, :get_nombre, :get_propiedades, :get_saldo, :jugador

    def debe_ser_encarcelado
      if @encarcelado == true
        res = false
      elsif tiene_salvoconducto == true
        perder_salvoconducto
        res = false
        Diario.instance.ocurre_evento("#{@nombre} utiliza carta salvoconducto y no va a la carcel")
      else
        res = true
      end
      return res
    end


    def self.new_copia(otro)
      new(otro.encarcelado, otro.nombre, otro.num_casilla_actual, otro.get_puede_comprar,
        otro.saldo, otro.salvoconducto, otro.propiedades)
    end



  end
end
