CFLAGS = -g -std=c99 -Wall -Wshadow -Wvla -pedantic -lm
GCC = gcc $(CFLAGS)

all: proj1

proj1: proj1.o
	$(GCC) proj1.o -o proj1
proj1.o: huff.c
	$(GCC) -c huff.c -o proj1.o




