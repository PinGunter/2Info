#!/bin/csh
@ inicio = 100
@ fin = 30000
@ incremento = 100
set ejecutable = burbuja_peor
set salida = tiempos_ordenacion_peor.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `./{$ejecutable} $i 10000` >> $salida
  @ i += $incremento
end
