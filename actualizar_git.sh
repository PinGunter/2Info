#! /bin/bash

## Script para actualizar cambios
# Parametro 1 = nombre de la rama a trabajar [salva|abel|main]

if [ $# -ne 1 ]; then
	echo "Falta nombre de rama"
	exit
fi


echo "---- Git pull ----"
git pull

echo "---- Cambio de rama a $1 ----"
git checkout $1

echo "---- Añadiendo cambios -----"
git add actualizar_git.sh

echo "---- Haciendo commit ----"
read -p "Mensaje del commit:" mensaje
git commit -m "$mensaje"

echo "---- Git push ----"
git push
