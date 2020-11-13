#!/bin/bash
# script para animar las fotos resultantes del morphing en un gif
# depende de imagemagick
_ayuda(){
    echo "Script para animar imagenes."
    echo "Uso: ./script <directorio-imagenes> <archivo-salida> <tiempo-en-ms-entre-frame>"
    exit 1;
}

## comprobacion de argumetentos
if [ $# -ne 3 ]; then
    _ayuda
fi

if [ ! -d "$1" ]; then
    echo "$1 no es un directorio"
    exit 1;
fi

extension=".pgm"
gif=".gif"
directorio=$1
salida=$2$gif
delay=$3

convert -delay $delay -loop 0 `ls -v1 $directorio/*$extension` $salida

