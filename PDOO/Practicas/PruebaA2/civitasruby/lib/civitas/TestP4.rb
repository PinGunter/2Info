#encoding :utf-8
require_relative "casilla"
require_relative "casilla_calle"
require_relative "casilla_impuesto"
require_relative "casilla_juez"
require_relative "casilla_sorpresa"
require_relative "civitas_juego"
require_relative "dado"
require_relative "diario"
require_relative "estados_juego"
require_relative "gestiones_inmobiliarias"
require_relative "gestor_estados"
require_relative "jugador"
require_relative "jugador_especulador"
require_relative "mazo_sorpresas"
require_relative "operacion_inmobiliaria"
require_relative "operaciones_juego"
require_relative "respuestas"
require_relative "salidas_carcel"
require_relative "sorpresa"
require_relative "sorpresa"
require_relative "sorpresa_casa_hotel"
require_relative "sorpresa_casilla"
require_relative "sorpresa_especulador"
require_relative "sorpresa_ir_carcel"
require_relative "sorpresa_pagar_cobrar"
require_relative "sorpresa_por_jugador"
require_relative "sorpresa_salir_carcel"
require_relative "tablero"
require_relative "titulo_propiedad"
require_relative "propiedad_ecologica"
require_relative "../juego_texto/controlador"
require_relative "../juego_texto/vista_textual"


module Civitas
  jugadores = ["Salva", "Abel"]
  Dado.instance.set_debug(true)
  vista = Vista_textual.new
  juego = Civitas_juego.new(jugadores)
  controlador = Controlador.new(juego,vista)
  controlador.juega

end
