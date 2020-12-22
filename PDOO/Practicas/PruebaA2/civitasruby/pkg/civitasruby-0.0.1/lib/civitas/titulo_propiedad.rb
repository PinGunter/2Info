#encoding:utf-8

# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Civitas
  class Titulo_propiedad
    #attr_reader :nombre, :precio_compra, :alquiler_base, :factor_revalorizacion,
    # :hipoteca_base, :precio_edificar, :num_hoteles, :num_casas
    attr_accessor :hipotecada, :propietario

    def initialize(nom, alquiler, factor, hipoteca, precioComp, precioEdif)
      @nombre = nom
      @precio_compra = precioComp
      @alquiler_base = alquiler
      @factor_revalorizacion = factor
      @hipoteca_base = hipoteca
      @precio_edificar = precioEdif
      @hipotecada = false
      @num_hoteles = 0
      @num_casas = 0
      @propietario = nil
    end

    @override
    def to_s()
      "\n-TituloPropiedad: \nNombre: #{@nombre} \nHipotecada: #{@hipotecada}
         \nPrecio compra: #{@precio_compra} \nAlquiler base: #{@alquiler_base}
         \nFactor revalorizacion: #{@factor_revalorizacion} \nHipoteca base: #{@hipoteca_base}
         \nPrecio edificar: #{@precio_edificar} \nNúmero de hoteles: #{@num_hoteles}
         \nNúmero de casas: #{@num_casas}\n\n"
    end

    def get_hipoteca_base
      @hipoteca_base
    end

    def get_num_casas
      @num_casas
    end

    def tiene_propietario
      @propietario != nil
    end

    def get_num_hoteles
      @num_hoteles
    end

    def get_alquiler_base
      @alquiler_base
    end

    def get_factor_revalorizacion
      @factor_revalorizacion
    end

    def get_precio_alquiler
      res = @alquiler_base * (1+(@num_casas*0.5) + (@num_hoteles*2.5))
      if @hipotecado || propietario_encarcelado
        res = 0
      end
      return res
    end

    def get_importe_hipoteca
      (@hipoteca_base*(1+(@num_casas*0.5) + (@num_hoteles*2.5)))
    end

    def get_importe_cancelar_hipoteca
      (get_importe_hipoteca * @@factor_intereses_hipoteca)
    end

    def actualiza_propietario_por_conversion(jugador)
      @propietario = jugador
    end

    def cancelar_hipoteca(jugador)
      result = false
      if(@hipotecado)
        if(es_este_el_propietaro(jugador))
          @propietario.paga(get_importe_cancelar_hipoteca)
          @hipotecado = false
          result =  true
        end
      end
      return result
    end


    def cantidad_casas_hoteles
      (get_num_casas + get_num_hoteles)
    end

    def comprar(jugador)
      result = false
      if (@propietario == nil)
        @propietario = jugador
        result = true
        @propietario.paga(@precio_compra)
      end
      return result
    end

    def construir_casa(jugador)
      result = false
      if(es_este_el_propietario(jugador))
        @propietario.paga(@precio_compra)
        @num_casas +=1
      end
    end

    def construir_hotel(jugador)
      result = false
      if (es_este_el_propietario(jugador))
        @propietario.paga(@precio_edificar)
        @num_hoteles = @num_hoteles + 1
        result = true
      end
      return result
    end

    def es_este_el_propietario(jugador)
      res = false
      if jugador == get_propietario
        res = true
      end
      return res
    end

    def get_hipotecado
      @hipotecado
    end

    def get_nombre
      @nombre
    end

    def get_num_casas
      @num_casas
    end

    def get_num_hoteles
      @num_hoteles
    end

    def get_precio_edificar
      @precio_edificar
    end

    def get_precio_compra
      @precio_compra
    end

    def get_precio_venta
      (get_precio_compra + get_precio_edificar*
        cantidad_casas_hoteles*@factor_revalorizacion)
    end

    def get_propietario
      @propietario
    end

    def hipotecar(jugador)
      salida = false
      if (!@hipotecado && es_este_el_propietario(jugador))
        @propietario.recibe(get_importe_hipoteca)
        @hipotecado = true
        salida = true
      end
      return salida
    end

    def tramitar_alquiler(jugador)
      if (@propietario != nil)
        if(es_este_el_propietario(jugador) == false)
          precio= get_precio_alquiler()
          jugador.paga_alquiler(precio)
          @propietario.recibe(precio)
        end
      end
    end

    def propietario_encarcelado
      res = false
      if @propietario.get_is_encarcelado == true
        res = true
      end
      return res
    end

    def cantidad_casas_hoteles
      (@num_casas + @num_hoteles)
    end

    def derruir_casas(n, jugador)
      res = false
      if es_este_el_propietario(jugador) && @num_casas >= n
        @num_casas = n
        res = true
      end
      return res
    end



    def vender(jugador)
      res = false
      if(!@hipotecado && es_este_el_propietario(jugador))
        jugador.recibe(get_precio_venta())
        derruir_casas(@num_casas,jugador)
        @num_hoteles = 0
        actualiza_propietario_por_conversion(nil)
        res = true
      end
      puts "\n**********\nvender de titulo: " + res.to_s + "\n**********\n"
      return res
    end

    private :es_este_el_propietario, :get_importe_hipoteca, :get_precio_venta #,  :get_precio_alquiler # este ultimo le cambiamos la visiblidad de private a public para mejorar la visibilidad del dato durante las partidas
  end
end
