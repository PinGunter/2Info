SRC = src/
INC = inc/
OBJ = obj/
BIN = bin/

todo: main_guia usoguia

main_guia: $(OBJ)main_guia.o
	g++ -g -Wall $(OBJ)main_guia.o -I $(INC) -o $(BIN)main_guia
$(OBJ)main_guia.o: $(SRC)main_guia.cpp
	g++ -g -Wall -c $(SRC)main_guia.cpp -I $(INC) -o $(OBJ)main_guia.o
	
usoguia: $(SRC)usoguia.cpp
	g++ -g -Wall -o $(BIN)usoguia $(SRC)usoguia.cpp -I $(INC)
	
clean:
	-rm $(BIN)*
	-rm $(OBJ)*
documentacion:
	doxygen Doxyfile
