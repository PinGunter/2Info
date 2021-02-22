## Se parte de nuevo de la clase Persona definida anteriormente, cuyo código es el que se muestra a continuación
## Realiza los ejercicios 1, 2, 3, 4 y 5
#
## No descomentes esta parte para probar los ejercicios 1 al 4


#class Persona  
#  attr_accessor :nombre, :edad 
#  
#  def initialize(unNombre, unaEdad)
#    @nombre=unNombre
#    @edad=unaEdad
#    @kilometros= 0
#  end
#  
#  def come
#    'rico'
#  end
#  
#  def habla
#    'bla bla bla'
#  end  
# 
#  def saludo
##    "hola, me llamo #{@nombre} y mi edad es  #{@edad}"
#  end
#  
#  def pasea (unLugar, distancia = 2)		 
#  		 @lugar=unLugar
#       @kilometros+=distancia			 
#    end
#
#end

#
## ---------------1. Define un atributo de clase ----------------------------
## 
#class Persona
#  @@planeta = 'Tierra' 
#end
#
## prueba el uso de un atributo de clase
##
# p1=Persona.new('Carmen', 22)
# puts p1.nombre
# puts p1.planeta # ¿Qué ocurre? ¿por qué da ese error?
#
##-------------------2. Define un método de clase-----------------------------
##
#class Persona
#    @@planeta= "Tierra"
#  def self.planeta      # método de clase, también def Persona.planeta
#    @@planeta
#  end
#end
## prueba el uso del método de clase
#
# puts Persona.planeta 
# p2=Persona.new("Juan",30)
# puts p2.planeta
 
#  

## -------------3. Define un método de instancia que acceda a un atributo de clase.
#
#class Persona
#  @@planeta ="Tierra"
#  def procedencia  # Método de instancia
#    @@planeta       # atributo de clase
#  end
#end
#
## Prueba el uso del método de instancia que accede al atributo de clase.
##
#p3 = Persona.new("Ana",25) 
#puts p3.procedencia
#

#

### --------- 4. Probando el método pasea con diferentes argumentos ----------------
#

#p4 = Persona.new("Ana",25) 
#p4.pasea('Granada', 5)
#puts p4.inspect
#
#p4.pasea("Parque") 
#puts p4.inspect  # plantea que pasa
#
#p4.pasea(10) 
#puts p4.inspect  # plantea que pasa
#
#p4 = Persona.new("Ana",25) 
#p4.pasea   # error, modifica el metodo correr para que no se produzca el error sin argumentos
#puts p4.inspect 

#
#
#
### Comenta todo el código anterior
#
###-----------------------------------------------------------------------------
### Dada la clase Persona siguiente (quita los comentarios y realiza el ejercicio 5) : 
###  ( 
##
#class Persona
#  
#  attr_accessor :nombre, :edad 
#  @@planeta = 'Tierra'
#  
#  def initialize(unNombre, unaEdad)
#    @nombre=unNombre
#    @edad=unaEdad    
#  end  
#  def come
#    'rico'
#  end  
#  def habla
#    'bla bla bla'
#  end 
#  def saludo
#    "hola, me llamo #{@nombre} y mi edad es  #{@edad}"
#  end
#  
#  def self.planeta     
#    @@planeta
#  end
#  def procedencia
#    @@planeta
#  end
#end 
## 

## --------- 5. Define el método to_s para la clase Persona. ----------------
#
## Redefinición del método to_s para que la información que se nos proporciona 
## sea más entendible que la que muestra inspect #
#
#class Persona
#  def to_s
#      puts "soy de la clase #{self.class.to_s} 
#          mi identifidad es: #{self.object_id} 
#          mi estado es: nombre = #{@nombre}, edad =#{@edad}, y 
#          planetav=#{self.procedencia}##"    
#  end
#end
#
#p1 = Persona.new("Pepe",15)
#puts p1.inspect
#puts p1.to_s 

 