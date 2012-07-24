# CFCC Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libcfcc.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: cfcc build

build: 
	ar rcs $(OUT) $(SRC)cfcc_buffer.o $(SRC)cfcc_common.o $(SRC)cfcc_empty_node.o $(SRC)cfcc_identifier_node.o $(SRC)cfcc_lexer.o $(SRC)cfcc_node.o $(SRC)cfcc_parser.o $(SRC)cfcc_special_node.o $(SRC)cfcc_syntax_tree.o $(SRC)cfcc_terminal_node.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

cfcc: cfcc_buffer.o cfcc_common.o cfcc_empty_node.o cfcc_identifier_node.o cfcc_lexer.o cfcc_node.o cfcc_parser.o cfcc_special_node.o cfcc_syntax_tree.o cfcc_terminal_node.o


cfcc_buffer.o: $(SRC)cfcc_buffer.cpp $(SRC)cfcc_buffer.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_buffer.cpp -o $(SRC)cfcc_buffer.o

cfcc_common.o: $(SRC)cfcc_common.cpp $(SRC)cfcc_common.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_common.cpp -o $(SRC)cfcc_common.o

cfcc_empty_node.o: $(SRC)cfcc_empty_node.cpp $(SRC)cfcc_empty_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_empty_node.cpp -o $(SRC)cfcc_empty_node.o

cfcc_identifier_node.o: $(SRC)cfcc_identifier_node.cpp $(SRC)cfcc_identifier_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_identifier_node.cpp -o $(SRC)cfcc_identifier_node.o

cfcc_lexer.o: $(SRC)cfcc_lexer.cpp $(SRC)cfcc_lexer.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_lexer.cpp -o $(SRC)cfcc_lexer.o

cfcc_node.o: $(SRC)cfcc_node.cpp $(SRC)cfcc_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_node.cpp -o $(SRC)cfcc_node.o

cfcc_parser.o: $(SRC)cfcc_parser.cpp $(SRC)cfcc_parser.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_parser.cpp -o $(SRC)cfcc_parser.o

cfcc_special_node.o: $(SRC)cfcc_special_node.cpp $(SRC)cfcc_special_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_special_node.cpp -o $(SRC)cfcc_special_node.o

cfcc_syntax_tree.o: $(SRC)cfcc_syntax_tree.cpp $(SRC)cfcc_syntax_tree.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_syntax_tree.cpp -o $(SRC)cfcc_syntax_tree.o

cfcc_terminal_node.o: $(SRC)cfcc_terminal_node.cpp $(SRC)cfcc_terminal_node.hpp
	$(CC) $(FLAG) -c $(SRC)cfcc_terminal_node.cpp -o $(SRC)cfcc_terminal_node.o
