.PHONY: clean
CC=gcc
CFLAGS=-std=c99

main: parent child
child: child.o matrix.o -lrt
parent: parent.o matrix.o -lrt
matrix: matrix.o 
matrix.o: matrix.c
child.o: child.c
parent.o: parent.c


clean:
	rm -f *~ *.o *.hex
