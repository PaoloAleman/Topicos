#ifndef MATRICES_H
#define MATRICES_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void** crearMatriz(int filas, int columnas, size_t tamElem);
void destruirMatriz(int filas, size_t tamElem, void** matriz);
void inicializarMatriz(int filas, int columnas, int** matriz, int (*Metodo)(int, int));

void mostrarMatriz(int filas, int columnas, int** matriz);

int diagonalPrincipal(int orden, int** matriz);
int diagonalSecundaria(int orden, int** matriz);

int triangularInferiorPrincipal(int orden, int** matriz);
int triangularSuperiorPrincipal(int orden, int** matriz);

int triangularInferiorSecundaria(int orden, int** matriz);
int triangularSuperiorSecundaria(int orden, int** matriz);

int triangularSuperiorAbsoluta(int orden, int** matriz);
int triangularInferiorAbsoluta(int orden, int** matriz);
int triangularIzquierdaAbsoluta(int orden, int** matriz);
int triangularDerechaAbsoluta(int orden, int** matriz);

void mostrarMatrizEnEspiral(int orden, int** matriz);

int** productoMatricial(int** a, int** b, int filasA, int columnasA, int filasB, int columnasB);

#endif