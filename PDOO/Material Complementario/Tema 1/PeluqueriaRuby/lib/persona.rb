module Basico
   
  require_relative "color_pelo"

  class Persona
   
    @@Planeta="Tierra" #atributo de clase
    @@Mayoria_Edad=18
    @@Contador_Personas=0
   
    @creacion=2020       #Atributo de instancia de la clase. exclusivo de ruby
   
    def initialize (n, e, p) # " constructor "
      # Atributos de instancia ( son siempre privados )
      @nombre=n
      @edad=e
      @pelo=p
      @@Contador_Personas+=1
    end

    public # no es necesario , pues los métodos son públicos por defecto
 
    def saluda # Método público de instancia
      puts "Hola , soy "+@nombre
    end
 
    def get_nombre  
      @apellido="Sanchez"       ### Se crea este atributo para el objeto que llama al metodo
      @nombre
    end
    
    
    def pedir_cita(peluqueria)  #Método de instancia
      saluda
      return peluqueria.dar_cita #envía mensaje a peluquería para que ésta le dé la cita 
 
    end

    #metodo de clase para consular el planeta
    def self.get_planeta     #teniendo el self indicamos que es un metodo de clase, no de instancia
      @@Planeta
    end
 
    #metodo de instancia para consultar el planeta
    def get_planeta
      @@Planeta
    end
 
    #metodo de clase para modificar el planeta, atributo de clase
    def self.set_planeta(otroPlaneta)
      @@Planeta=otroPlaneta
    end
 
    def set_planeta(otroPlaneta)
      if (@edad>@@Mayoria_Edad)
        @@Planeta=otroPlaneta
      end
    end
 
    #metodo de clase para consultar un atributo de instancia de la clase
    def self.get_creacion
      @creacion
    end
    
    #metodo de instancia para consular un atributo de instancia de la clase
    def get_creacion
      @creacion #busca un atributo de instancia que se llame creacion. No lo va a encontrar porque creacion es de instancia de clase. Devuelve nil
    end
  end

end
