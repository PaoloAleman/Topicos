CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: main

main: main.c libarreglos.a
	$(CC) $(CFLAGS) main.c -L. -larreglos.a -o main

libarreglos.a: vectores.o matrices.o cadenas.o
	ar rcs libarreglos.a vectores.o matrices.o cadenas.o

vectores.o: vectores.c
	$(CC) $(CFLAGS) vectores.c -c vectores.o

matrices.o: matrices.c
	$(CC) $(CFLAGS) matrices.c -c matrices.o

cadenas.o: cadenas.c
	$(CC) $(CFLAGS) cadenas.c -c cadenas.o

clean:
	rm *.o libarreglos.a main