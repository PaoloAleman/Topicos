#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INCR_FACTOR 2
#define DECR_FACTOR 0.5
#define OCUP_FACTOR 0.25
#define DEFAULT_CAP 10

#define EXITO 0
#define ERROR 1

typedef struct{
    int* vec;
    size_t ce;
    size_t cap;
}VectorInt;

bool vectorCrear(VectorInt* vec);
bool vectorVaciar(VectorInt* vec);
void vectorDestruir(VectorInt* vec);

int vectorInsertar(VectorInt* vec, int elem);
int vectorPush(VectorInt* vec, int elem);

bool vectorOrdEliminarElem(VectorInt* vec, int elem);
bool vectorEliminarPos(VectorInt* vec, size_t pos);

void vectorOrdenar(VectorInt* vec);
int vectorBuscar(VectorInt* vec, int elem);

size_t vectorCantElem(VectorInt* vec);
int vectorObtener(VectorInt* vec, int pos);
void vectorMostrar(VectorInt* vec);

#endif // VECTOR_H_INCLUDED
