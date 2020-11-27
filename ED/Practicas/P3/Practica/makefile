INCLUDE = inc/
SOURCE = src/
LIB = lib/
OBJ = obj/
BIN = bin/
DOC = doc/

$(BIN)/main:	$(OBJ)/main.o
	g++ -o $(BIN)/main $(OBJ)/main.

$(OBJ)/main.o:	$(SRC)/main.cpp
	g++ -g -c -I.$(INC)
clean:
	echo "Limpiando"
	-rm $(OBJ)/* $(BIN)/* $(LIB)/*
documentacion:
	echo "Creando documentacion"
	doxygen Doxyfile