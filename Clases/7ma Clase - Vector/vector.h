#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INCR_FACTOR 2
#define DECR_FACTOR 0.5
#define OCUP_FACTOR 0.25
#define DEFAULT_CAP 10

#define BURBUJEO 0
#define SELECCION 1
#define INSERCION 2

#define EXITO 0
#define ERROR 1

typedef int (*Cmp)(void*, void*);

typedef struct{
    void* vec;
    size_t tamElem;
    size_t ce;
    size_t cap;
}Vector;

bool vectorCrear(Vector* vec, size_t tamElem);
bool vectorVaciar(Vector* vec);
void vectorDestruir(Vector* vec);

int vectorInsertar(Vector* vec, void* elem, int (*Cmp)(void*, void*));
int vectorPush(Vector* vec, void* elem);

bool vectorOrdEliminarElem(Vector* vec, void* elem, int (*Cmp)(void*, void*));
bool vectorEliminarPos(Vector* vec, size_t pos);

void vectorOrdenar(Vector* vec, int metodo, int (*Cmp)(void*, void*));
int vectorBuscar(Vector* vec, void* elem, int (*Cmp)(void*, void*));

size_t vectorCantElem(Vector* vec);
size_t vectorTamElem(Vector* vec);
int vectorObtener(Vector* vec, int pos);
void vectorMostrar(Vector* vec, void (*Mostrar)(void*));

#endif // VECTOR_H_INCLUDED
