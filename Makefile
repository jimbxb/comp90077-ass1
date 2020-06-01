# COMP90077 - Assignment 1 - James Barnes (820946)
# Makefile for testing prgram

CC     = gcc
CFLAGS = -Wall -std=c99 -O2
EXE    = prog
OBJ    = main.o gen.o treap.o array.o

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: main.h gen.h treap.h array.h
gen.o: gen.h main.h
treap.o: treap.h main.h
array.o: array.h main.h

.PHONY: clean cleanly all CLEAN

clean:
	rm -f $(OBJ)
CLEAN: clean
	rm -f $(EXE)
cleanly: all clean
