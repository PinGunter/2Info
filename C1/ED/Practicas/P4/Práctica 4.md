#### Práctica 4

###### Salvador Romero Cortés

---

**Diccionario**

* Los métodos extras realizados son los sugeridos en el pdf de la práctica.

* Hay métodos y funciones extras que sirven para facilitar la implementación, vienen propiamente documentadas con doxygen.
* Se incluyen dos archivos para probar la clase diccionario, una es "usodiccionario.cpp" incluida en el propio material de prácticas. La otra es "main_dic.cpp" que prueba la lectura de un diccionario, la unión de diccionarios, la diferencia de ellos y obtener un subdiccionario.
* Para facilitar el uso de estos binarios se pueden usar los archivos de prueba en data/. El archivo data.txt es material de práctica, sirve para probar "usodiccionario.cpp". El archivo "test_union_dif.txt" sirve como entrada para el binario main_dic.
 - El makefile genera automáticamente los dos binarios por defecto, incluye también opción para generar documentación (make documentacion) y para limpiar (make clean). Si se desea compilar uno de los dos binarios se puede elegir como regla de construcción ("make main_dic" o "make usodiccionario").

* Se han documentado con doxygen todas la funciones y métodos, incluidas las proporcionadas por los profesores

**Guía Telefónica**

* Los métodos que se añaden a la clase son los sugeridos en el pdf: intersección, modificar el teléfono asocidado a un nombre (sin repeticiones, map), subguía con los nombres de los que empiecen por una determinada letra y subguía entre dos nombres.
* Todo está implementado y documentado con doxygen.
* Se han usado funciones extras y métodos para facitilizar la implementación, también están documentados con doxygen.
* Se incluyen dos ficheros de prueba: "usoguia.cpp" proporcionada por los profesores y "main_guia" que prueba los métodos que se han añadido a la clase. 
* Para usar el programa de "main_guia" es necesario pasar como parámetros de ejecución dos nombres de archivos con guías de teléfonos.
* El makefile genera por defecto los dos binarios, se puede elegir uno solo con "make main_guia" o "make usoguia". También incluye opción de limpieza ("make clean") y para generar la documentación ("make documentación").