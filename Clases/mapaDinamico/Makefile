CC = gcc
CFLAGS = -std=c99 -Wall -Werror

all: libMapaDinamico.a 
	$(CC) $(CFLAGS) pruebaMapaDinamico.c -L. -lMapaDinamico -o pruebaMapaDinamico

libMapaDinamico.a: mapaDinamico.c
	$(CC) $(CFLAGS) mapaDinamico.c -c mapaDinamico.o
	ar -rcs libMapaDinamico.a mapaDinamico.o

clean:
	rm *.o *.a pruebaMapaDinamico