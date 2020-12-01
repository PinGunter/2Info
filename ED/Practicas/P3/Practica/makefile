INC = inc
SRC = src
LIB = lib
OBJ = obj
BIN = bin
DOC = doc
INC_TEMP = src

all:	vector	cola

vector: $(BIN)/main_vd
$(BIN)/main_vd:	$(OBJ)/main_vd.o $(LIB)/vector.a
	g++ $(OBJ)/main_vd.o -lvd -L$(LIB)  -o $(BIN)/main_vd
$(OBJ)/main_vd.o:	
	g++ -g -c -I$(INC) $(SRC)/main_vd.cpp -o $(OBJ)/main_vd.o
$(LIB)/vector.a:	$(OBJ)/Pila_max_VD.o
	ar rvs $(LIB)/libvd.a $(OBJ)/Pila_max_VD.o
$(OBJ)/Pila_max_VD.o:	
	g++ -g -c -I$(INC) $(SRC)/Pila_max_VD.cpp -o $(OBJ)/Pila_max_VD.o

cola: $(BIN)/main_cola
$(BIN)/main_cola:	$(OBJ)/main_cola.o $(LIB)/cola.a
	g++ $(OBJ)/main_cola.o -lcola -L$(LIB)  -o $(BIN)/main_cola
$(OBJ)/main_cola.o:	
	g++ -g -c -I$(INC) $(SRC)/main_cola.cpp -o $(OBJ)/main_cola.o
$(LIB)/cola.a:	$(OBJ)/Pila_max_Cola.o
	ar rvs $(LIB)/libcola.a $(OBJ)/Pila_max_Cola.o
$(OBJ)/Pila_max_Cola.o:	
	g++ -g -c -I$(INC) -I$(INC_TEMP) $(SRC)/Pila_max_Cola.cpp -o $(OBJ)/Pila_max_Cola.o
clean:
	echo "Limpiando"
	-rm $(OBJ)/* $(BIN)/* $(LIB)/*
documentacion:
	echo "Creando documentacion"
	doxygen Doxyfile