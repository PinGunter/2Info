
#Ejemplo para probar atributos y m�todos de instancia y clase y visibilidad de �stos

module Series

class Serie 
  
  #atributo de clase
  @@plataforma="Netflix"  
  
  #atributo de instancia de la clase, no confundir con atributo de instancia, est� fuera de un m�todo de instancia.
  @formato="digital"
  
  attr_accessor :nombre, :genero, :creadores #m�todos consultores y mofificadores de los atributos de instancia nombre y creadores
  
  #constructor
  def initialize(nombre, temporadas, genero, creadores)
    #atributos de instancia, todos son privados
      @nombre=nombre
      @temporadas=temporadas
      @genero=genero
      @creadores=creadores
  end 
  
   private  #para los m�todos de instancia que haya a continuaci�n
   
    #m�todo de instancia que modifica a un atributo de instancia
   def nueva_temporada
        temporadas+=1  
   end
    
   public #para los m�todos de instancia que haya a continuaci�n. No hace falta si se ponen los p�blicos antes
   
   def set_genero_de_otra_serie(otra_serie, otro_genero)
        #la instancia que ejecuta este m�todo le pide a otra instancia diferente que ejecute un m�todo privado
       otra_serie.genero=otro_genero  # Dar� error al ejecutar pues se trata de un m�todo privado de otra instancia
   end
    
   #m�todo de instancia to_s que genera un string legible con los valores de los atributos de instancia
   def to_s
        cadena=""
        for c  in @creadores
            cadena= cadena + "   "+ c
        end
        "Titulo: " + @nombre+ "\n Plataforma: "+ @@plataforma+ " \n Temporadas: " + @temporadas.to_s + "\n Genero: "+ @genero + "\n Creadores: "+ cadena
    #observar que este m�todo de instancia consulta un atributo de clase (plataforma)
    
   end
    
   #m�todo de instancia que cambia una variable de clase. No se deber�a poder hacer
   def cambia_plataforma(otra_plataforma)
        @@plataforma=otra_plataforma  
   end
    
   #/m�todo de clase para cambiar una variable de clase
   def self.set_plataforma(otra_plataforma)
        @@plataforma=otra_plataforma  #si se pone attr_writer :plataforma, se refiere a un atributo de instancia con el mismo nombre
   end
    
   #m�todo de clase, consultor de un atributo de clase
   def self.get_plataforma
     @@plataforma 
   end
   
   #m�todo de clase, consultor de un atributo de instancia de la clase
   def self.get_formato
     @formato
   end
   
   #m�todo de instancia, consultor de un atributo de instancia de la clase: Error, no se puede hacer!!
   def ver_formato
     @formato   #no accede al atributo de instancia de la clase, busca un atributo de instancia con ese nombre
   end
   
   private :genero=, :creadores=  # otra forma de indicar qu�  m�todo de instancia son privados. En este caso, es el m�todo modificador del atributo nombre
    
   private_class_method :get_plataforma   #para cambiar la visibilidad de m�todos de clase
   
   
   #C�digo en el �mbito de la clase para crear instancias y env�ar mensajes a �stas para invocar a m�todos p�blicos y privados
          
        # Pensar qu� hace este c�digo y qu� debe salir por pantalla antes de ejecutarlo.
        
        puts "Creando series y mostrandolas en pantalla"
        guionistas1= Array.new
        guionistas1<<"David Benioff"
        guionistas1<<"D.B.Weiss"
        serie1= Serie.new("Juego de Tronos", 8, "Fantasia", guionistas1)
        puts serie1 
        
        guionistas2= Array.new
        guionistas2<<"Carlos Montero"
        guionistas2<<"Dario Madrona"
        serie2= Serie.new("Elite", 3, "Drama Juvenil", guionistas2)
        puts serie2
        
        puts "Consultando y modificando las series creadas"
        
        #como este m�todo de clase est� dentro de la misma clase, en Java se puede hacer lo siguiente:
        
        #serie1.nueva_temporada # Desde el �mbito de clase no se puede invocar a un m�todo de instancia privado. En Java s�
        serie1.nombre="Mundo de Dragones" #s� se puede usar un  m�todo p�blico, claro
        serie1.creadores[0]="yo" #se puede acceder a atributos privados y cambiarlos. Cuidado!!!
        serie1.set_genero_de_otra_serie(serie2, "Humor")  #una instancia pretende cambiar un atributo de otra instancia
        serie1.cambia_plataforma("HBO") #observa que una instancia, serie1, ha cambiado la plataforma de todas las instancias de Serie existentes
        puts serie1
        puts serie2
        
        Serie.set_plataforma("Amazon Prime") #esto si tiene sentido, que la clase cambie la plataforma de todas sus instancias con un m�todo de clase
        puts serie1
        puts serie2
        
        puts Serie.getPlataforma  #dar� error porque es privado
        
        puts Serie.get_formato  #consultando un m�todo de instancia de la clase con un m�todo de clase
        puts serie1.ver_formato #igual pero con un m�todo de instancia
    
    
 
 
end

end

