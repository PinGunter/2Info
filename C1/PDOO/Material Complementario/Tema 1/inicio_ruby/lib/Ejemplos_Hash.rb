#encoding: utf-8
##  Proceder como se ha indicado main.rb
#
##-------------------------------------------------------------------------
##-------------- Ejemplos de uso de Hash en Ruby
##-------------------------------------------------------------------------
#

##-------------------1. Creando y recorriendo un hash -------------------------
#
#edificio ={"uno"=> "Ana", "dos"=>"Luis", "tres"=>"Pepe"}
#puts edificio
#piso=""
#edificio.each {|k, v| piso << "en el piso #{k} vive #{v} \n"}
#puts piso

##------------------2. Creando y accediendo a elementos de un hash -----------
#
numeros={'uno'=>1, 'dos'=>2, 'tres'=>3}
puts numeros.inspect
numerosx=Hash['uno', 1, 'dos', 2, 'tres',3]
puts numerosx.inspect

puts numeros['uno']
numeros['veinte']=20
numeros['tres']=33
numeros['cuatro'] = 4
puts numeros.inspect

puts numeros.keys
puts numeros.values

puts numeros.to_a.inspect

puts numeros['nada']
puts numeros.keys.grep /o/  # muestra los que contengan la letra 'o' en key

