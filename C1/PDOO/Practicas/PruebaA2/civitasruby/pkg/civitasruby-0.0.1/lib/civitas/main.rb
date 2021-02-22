#encoding :utf-8
require_relative "diario"
require_relative "../juego_texto/vista_textual"
require_relative "../juego_texto/controlador"
require_relative "civitas_juego"

module Civitas
  jugadores = ["Salva", "Abel"]
  vista = Vista_textual.new
  juego = Civitas_juego.new(jugadores)
  controlador = Controlador.new(juego,vista)
  controlador.juega

end
