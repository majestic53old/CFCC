# CFCC Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libcfcc.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: cfcc build

build: 
	ar rcs $(OUT) $(SRC)cfcc_buff.o $(SRC)cfcc_common.o $(SRC)cfcc_empty_node.o $(SRC)cfcc_identifier_node.o $(SRC)cfcc_lex.o $(SRC)cfcc_node.o $(SRC)cfcc_par.o $(SRC)cfcc_special_node.o $(SRC)cfcc_terminal_node.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

cfcc: cfcc_buff.o cfcc_common.o cfcc_empty_node.o cfcc_identifier_node.o cfcc_lex.o cfcc_node.o cfcc_par.o cfcc_special_node.o cfcc_terminal_node.o


cfcc_buff.o: $(SRC)cfcc_buff.cpp $(SRC)cfcc_buff.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_buff.cpp -o $(SRC)cfcc_buff.o

cfcc_common.o: $(SRC)cfcc_common.cpp $(SRC)cfcc_common.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_common.cpp -o $(SRC)cfcc_common.o

cfcc_empty_node.o: $(SRC)cfcc_empty_node.cpp $(SRC)cfcc_empty_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_empty_node.cpp -o $(SRC)cfcc_empty_node.o

cfcc_identifier_node.o: $(SRC)cfcc_identifier_node.cpp $(SRC)cfcc_identifier_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_identifier_node.cpp -o $(SRC)cfcc_identifier_node.o

cfcc_lex.o: $(SRC)cfcc_lex.cpp $(SRC)cfcc_lex.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_lex.cpp -o $(SRC)cfcc_lex.o

cfcc_node.o: $(SRC)cfcc_node.cpp $(SRC)cfcc_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_node.cpp -o $(SRC)cfcc_node.o

cfcc_par.o: $(SRC)cfcc_par.cpp $(SRC)cfcc_par.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_par.cpp -o $(SRC)cfcc_par.o

cfcc_special_node.o: $(SRC)cfcc_special_node.cpp $(SRC)cfcc_special_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_special_node.cpp -o $(SRC)cfcc_special_node.o

cfcc_terminal_node.o: $(SRC)cfcc_terminal_node.cpp $(SRC)cfcc_terminal_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_terminal_node.cpp -o $(SRC)cfcc_terminal_node.o
