#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdio.h>
#include <stdbool.h>

#define EXITO 0
#define ERROR 1

#define TAM 100

typedef struct{
    int vec[TAM];
    size_t cantElem;
}VectorInt;

void vectorCrear(VectorInt* vec);
void vectorDestruir(VectorInt* vec);

int vectorInsertar(VectorInt* vec, int elem);
int vectorPush(VectorInt* vec, int elem);

bool vectorOrdEliminarElem(VectorInt* vec, int elem);
bool vectorEliminarPos(VectorInt* vec, size_t pos);

void vectorOrdenar(VectorInt* vec);
int vectorBuscar(VectorInt* vec, int elem);

int vectorObtener(VectorInt* vec, int pos);
void vectorMostrar(VectorInt* vec);

#endif // VECTOR_H_INCLUDED
