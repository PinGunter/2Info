#! /bin/bash

## script para generar la documentación necesaria del proyecto
## dependencias:
    # doxygen  --> programa principal para generar la documentación
    # graphviz  --> paquete para generar grafos de dependencia entre los distintos objetos y ficheros
    # pdflatex --> paquete para generar la documentacion en pdf

#primero borramos la anterior y se genera la documentacion actualizada con doxygen
rm -rf doc/*
doxygen doxyfile

# ahora creamos un enlace simbolico al index.html de la documentacion
ln -s doc/html/index.html doc.html

# ahora generamos la documentacion en pdf
cd doc/latex && make
cp refman.pdf ../../
cd ../../
mv refman.pdf doc.pdf

# mensaje de fin
echo Acabado