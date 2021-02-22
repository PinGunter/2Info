BIN = bin
OBJ = obj
SRC = src
INC = inc
LIB = lib

$(BIN)/main: $(OBJ)/main.o -lfunciones
	echo Creando ejecutable
	g++ $^ -L$(LIB) -o $@
$(OBJ)/main.o: $(SRC)/main.cpp
	echo Creando main.o
	g++ -g -c -I./$(INC) $< -o $@
-lfunciones:	$(OBJ)/imagenES.o $(OBJ)/funciones_imagen.o $(OBJ)/imagen.o
	echo Creando biblioteca
	ar rvs $(LIB)/libfunciones.a $(OBJ)/imagenES.o $(OBJ)/funciones_imagen.o $(OBJ)/imagen.o

$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp
	echo Creando imagenES.o
	g++ -g -c -I./$(INC) $< -o $@
$(OBJ)/funciones_imagen.o: $(SRC)/funciones_imagen.cpp
	g++ -g -c -I./$(INC) $< -o $@

$(OBJ)/imagen.o: $(SRC)/imagen.cpp
	echo Creando imagen.o
	g++ -g -c -I./$(INC) $< -o $@

clean: 
	echo Limpiando
	-rm $(OBJ)/* $(BIN)/* $(LIB)/*
rebuild: clean $(BIN)/main
documentacion:
	echo Creando documentacion
	doxygen doxyfile

color_gris: $(BIN)/color_a_gris

$(BIN)/color_a_gris: $(OBJ)/color_a_gris.o $(OBJ)/imagenES.o $(OBJ)/funciones_imagen.o
	echo Creando Binario Color a Gris
	g++ $^ -o $@

$(OBJ)/color_a_gris.o: $(SRC)/color_a_gris.cpp 
	echo Compilando color_a_gris
	g++ -g -c -I./$(INC) $< -o $@
