# CFCC Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
OUT=libcfcc.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: cfcc build

build: 
	ar rcs $(OUT) $(SRC)buffer.o $(SRC)lexer.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o

cfcc: buffer.o lexer.o

buffer.o: $(SRC)buffer.cpp $(SRC)buffer.hpp
	$(CC) $(FLAG) -c $(SRC)buffer.cpp -o $(SRC)buffer.o

lexer.o: $(SRC)lexer.cpp $(SRC)lexer.hpp
	$(CC) $(FLAG) -c $(SRC)lexer.cpp -o $(SRC)lexer.o
