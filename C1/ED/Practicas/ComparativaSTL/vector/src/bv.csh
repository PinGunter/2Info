#!/bin/csh
@ inicio = 100
@ fin = 500000
@ incremento = 100
set ejecutable = bin/borrado
set salida = data/borrado.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `./{$ejecutable} $i` >> $salida
  @ i += $incremento
end
