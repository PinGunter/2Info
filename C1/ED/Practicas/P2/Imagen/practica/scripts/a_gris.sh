#! /bin/bash
# script para convetir todas las imagenes ppm a pgm
make color_gris
for i in `ls imagenes_entrada/*.ppm`; do
    salida="$(basename "$i" .ppm).pgm"
    bin/color_a_gris $i imagenes_salida/$salida
done
