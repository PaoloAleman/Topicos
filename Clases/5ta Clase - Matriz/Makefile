CC = gcc
CFLAGS = -Wall -Werror -std=c99 -g -O0

all: main

main: main.c libmatrices.a
	$(CC) $(CFLAGS) main.c -L. -lmatrices -o pruebaMatrices

libmatrices.a: matrices.o
	ar rcs libmatrices.a matrices.o

matrices.o: matrices.c
	$(CC) $(CFLAGS) matrices.c -c matrices.o

clean:
	rm *.o libmatrices.a pruebaMatrices
