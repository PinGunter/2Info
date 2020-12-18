SRC = src/
INC = inc/
OBJ = obj/
BIN = bin/

todo: main_dic usodiccionario

main_dic: $(OBJ)main_dic.o
	g++ -g -Wall $(OBJ)main_dic.o -I $(INC) -o $(BIN)main_dic
$(OBJ)main_dic.o: $(SRC)main_dic.cpp
	g++ -g -Wall -c $(SRC)main_dic.cpp -I $(INC) -o $(OBJ)main_dic.o
	
usodiccionario: $(SRC)usodiccionario.cpp
	g++ -g -Wall -o $(BIN)usodiccionario $(SRC)usodiccionario.cpp -I $(INC)
	
clean:
	-rm $(BIN)*
	-rm $(OBJ)*
documentacion:
	doxygen Doxyfile
