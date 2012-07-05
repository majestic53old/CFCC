# CFCC Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libcfcc.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: cfcc build

build: 
	ar rcs $(OUT) $(SRC)buffer.o $(SRC)lexer.o $(SRC)parser.o $(SRC)shared.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

cfcc: buffer.o lexer.o parser.o shared.o

buffer.o: $(SRC)buffer.cpp $(SRC)buffer.hpp
	$(CC) $(FLAG) -c $(SRC)buffer.cpp -o $(SRC)buffer.o

lexer.o: $(SRC)lexer.cpp $(SRC)lexer.hpp
	$(CC) $(FLAG) -c $(SRC)lexer.cpp -o $(SRC)lexer.o

parser.o: $(SRC)parser.cpp $(SRC)parser.hpp
	$(CC) $(FLAG) -c $(SRC)parser.cpp -o $(SRC)parser.o

shared.o: $(SRC)shared.cpp $(SRC)shared.hpp
	$(CC) $(FLAG) -c $(SRC)shared.cpp -o $(SRC)shared.o
