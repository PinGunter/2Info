# encoding:utf-8
module Civitas
  module Tipo_casilla
    CALLE = :calle
    SORPRESA = :sorpresa
    JUEZ = :juez
    IMPUESTO = :impuesto
    DESCANSO = :descanso
  end
  
  module Tipo_sorpresa
    IR_CARCEL = :ir_carcel
    IR_CASILLA = :ir_casilla
    PAGAR_COBRAR = :pagar_cobrar
    POR_CASA_HOTEL = :por_casa_hotel
    POR_JUGADOR = :por_jugador
    SALIR_CARCEL = :salir_carcel
  end
  
  module Operaciones_juego
    AVANZAR = :avanzar
    COMPRAR = :comprar
    GESTIONAR = :gestionar
    SALIR_CARCEL = :salir_carcel
    PASAR_TURNO = :pasar_turno
  end


end

