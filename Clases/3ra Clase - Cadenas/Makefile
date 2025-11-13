CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: main

main: main.o secuenciaPalabras.a
	$(CC) $(CFLAGS) main.c -L. secuenciaPalabras.a -o main

main.o: main.c
	$(CC) $(CFLAGS) main.c -c main.o

secuenciaPalabras.a: secuenciaPalabras.o palabra.o
	ar rcs secuenciaPalabras.a secuenciaPalabras.o palabra.o

secuenciaPalabras.o:
	$(CC) $(CFLAGS) secuenciaPalabras.c -c secuenciaPalabras.o

palabra.o: palabra.c
	$(CC) $(CFLAGS) palabra.c -c palabra.o

clean:
	rm *.o main secuenciaPalabras.a