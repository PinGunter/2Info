#!/bin/csh
@ inicio = 100
@ fin = 30000
@ incremento = 100
set ejecutable = busqueda
set salida = tiempos_busqueda_arreglado.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `./{$ejecutable} $i` >> $salida
  @ i += $incremento
end
