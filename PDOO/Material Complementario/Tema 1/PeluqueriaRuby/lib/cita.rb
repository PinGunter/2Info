# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Basico
  attr_reader :cita
  class Cita
    def initialize(client,fecha)
      @cliente = client
      @fecha = fecha
    end
  end
end
