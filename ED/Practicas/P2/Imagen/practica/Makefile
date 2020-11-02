BIN = bin
OBJ = obj
SRC = src
INC = inc

$(BIN)/main: $(OBJ)/main.o $(OBJ)/imagenES.o
	echo Creando ejecutable
	g++ $^ -o $@
$(OBJ)/main.o: $(SRC)/main.cpp
	echo Creando main.o
	g++ -g -c -I./$(INC) $< -o $@
$(OBJ)/imagenES.o: $(SRC)/imagenES.cpp
	echo Creando imagenES.o
	g++ -g -c -I./$(INC) $< -o $@
clean: 
	echo Limpiando
	-rm $(OBJ)/* $(BIN)/*
rebuild: clean $(BIN)/main
documentacion:
	echo Creando documentacion
	doxygen doxyfile
