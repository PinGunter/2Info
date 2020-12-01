class Capitulo
  @@contador_numeros=0
#  attr_reader :numero, :titulo, :descripcion
  
#  def initialize  # da valores por defecto sin argumentos
#    @numero=1
#    @titulo="El comienzo"
#    @descripcion= "Llegan al aeropuerto"
#  end
#  
#  def initialize  # si se mantiene este constructor y el anterior, hace caso al último definido antes de usarlo
#    @numero = 4
#    @titulo = nil
#    @descripcion="ksksk"
#  end

#  def initialize (numero, titulo, descripcion) # construtor que da valores de los argumentos
#    @numero=numero
#    @titulo=titulo
#    @descripcion=descripcion
#  end
  

  
#  def initialize (titulo, descripcion) 
#  # constructor con menos argumentos pero da valor por defecto a las variables que faltan
#    @@contador_numeros=@@contador_numeros+1
#    @numero=@@contador_numeros
#    @titulo=titulo
#    @descripcion=descripcion
#    @elenco=Array.new 
#  end
  
#creando un método de clase para que funcione como un constructor, llama al initialize con tres argumentos
#  def self.otroConstructor(numero, descripcion)
#    new(numero, "capitulo interesante", descripcion)
#  end
  
#creando un constructor con valores por defecto en los argumentos
#en este caso, el constructor puede ser usado con dos o con tres argumentos
#  def initialize (numero, titulo, descripcion="siempre lo mismo") 
#    @numero=numero
#    @titulo=titulo
#    @descripcion=descripcion
#  end
#  
# # otra forma de hacer lo mismo
#  def initialize (*args) # cadena de valores
#    @numero, @titulo, @descripcion=*args
#    if args.size<3  # porque en otro caso sería nil
#      @descripcion=' '
#    end
#  end

  #Constructor de copia para usarlo con el initialize de tres argumentos 
  # y con attr_reader de numero, titulo y descripcion
#  def self.constructor_copia(otroCapitulo)
#    new(otroCapitulo.numero, otroCapitulo.titulo, otroCapitulo.descripcion)
#  end
#  
#  def to_s
#    if @titulo==nil
#      @titulo=' '
#    end
#    "numero: "+ @numero.to_s+ ", titulo: " + @titulo + ", descripcion: "+ @descripcion
#  end
  
  
  
# probando si no hay constructor o un constructor sin argumentos
#  capA= Capitulo.new  
#  puts capA

#  probando constructor que da valores a todos los argumentos
#  capB=Capitulo.new(1, "La isla", "llegan a la isla")
#  puts capB

#  probando constructor con menos argumentos 
#  capC=Capitulo.new("La isla", "llegan a la isla")
#  puts capC
#  capD=Capitulo.new("Otra isla", "Se mudan a otra isla")
#  puts capD

# probando constructor en método de clase
#  capE=Capitulo.otroConstructor(6, "Se pone interesante")
#  puts capE
#  capF=Capitulo.new(7, "El bicho", "Le pica el bicho")
#  puts capF

# probando constructor con diferentes argumentos (con = o con *args
#   capJ= Capitulo.new(8, "J", "pasan cosas")
#   puts capJ
#   capK=Capitulo.new(9, "B")  
#   puts capK

#  # probando constructor de copia y constructor con tres argumentos
#  capG= Capitulo.new(10, "G", "se marchan")
#  puts capG
#  capL= Capitulo.constructor_copia(capG)
#  puts capL
  
end
