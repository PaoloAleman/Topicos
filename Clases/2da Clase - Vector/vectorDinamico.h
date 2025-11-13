#ifndef VECTOR_DINAMICO_H
#define VECTOR_DINAMICO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_CAP 10
#define FACTOR_INCR 2

#define TODO_OK 0
#define ERROR 1

typedef struct{
    int* vec;
    size_t cap;
    size_t cantElem;
}VectorInt;

int vectorCrear(VectorInt* vec);
void vectorDestruir(VectorInt* vec);
int vectorRedimensionar(VectorInt* vec, size_t nuevaCap);

int vectorInsertar(VectorInt* vec, int elem);
int vectorPush(VectorInt* vec, int elem);

bool vectorOrdEliminarElem(VectorInt* vec, int elem);
bool vectorEliminarPos(VectorInt* vec, size_t pos);

void vectorOrdenar(VectorInt* vec);
int vectorBuscar(VectorInt* vec, int elem);

int vectorObtener(VectorInt* vec, int pos);
void vectorMostrar(VectorInt* vec);

#endif