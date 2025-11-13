#ifndef VECTORES_H
#define VECTORES_H

#include <stdio.h>
#include <string.h>

#define ERROR -1

int insertarElemInt(int* vec, int elem, int pos, int ce);
int insertarElemOrdenadoInt(int* vec, int elem, int ce);
int eliminarElemPosInt(int* vec, int pos, int ce);
int eliminarElemInt(int* vec, int elem, int ce);
int eliminarTodosElemInt(int* vec, int elem, int ce);

int insertarElemVoid(void* vec, void* elem, int pos, int ce, int tamElem);
int insertarElemOrdenadoVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*));
int eliminarElemPosVoid(void* vec, int pos, int ce, int tamElem);
int eliminarElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*));
int eliminarTodosElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*));

int ordenarElemInt(int* vec, int ce);
int buscarElemInt(int* vec, int elem, int ce);
void mostrarVecInt(int* vec, int ce);

int ordenarElemVoid(void* vec, int ce, int tamElem, int (*Cmp)(void*, void*));
int buscarElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*));
void mostrarVecVoid(void* vec, int ce, int tamElem, void (*Mostrar)(void*));

#endif