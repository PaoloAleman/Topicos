#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"

#define FILAS 4
#define COLUMNAS 4
#define ORDEN 4

int sumaNormal(int i, int j);

int main()
{
    /*
    int mat[FILAS][COLUMNAS] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    */

    //int (*mat)[ORDEN] = malloc(sizeof(int) * ORDEN * ORDEN);

    int** mat = (int**)crearMatriz(ORDEN, ORDEN, sizeof(int));

    inicializarMatriz(ORDEN, ORDEN, mat, sumaNormal);

    mostrarMatriz(FILAS, COLUMNAS, mat);

    printf("Diagonal principal: %d\n", diagonalPrincipal(ORDEN, mat));
    printf("Diagonal secundaria: %d\n", diagonalSecundaria(ORDEN, mat));

    printf("Triangular principal inferior: %d\n", triangularInferiorPrincipal(ORDEN, mat));
    printf("Triangular principal superior: %d\n", triangularSuperiorPrincipal(ORDEN, mat));
    printf("Triangular secundaria inferior: %d\n", triangularInferiorSecundaria(ORDEN, mat));
    printf("Triangular secundaria superior: %d\n", triangularSuperiorSecundaria(ORDEN, mat));

    destruirMatriz(ORDEN, sizeof(int), (void**)mat);

    return 0;
}

int sumaNormal(int i, int j)
{
    static int tmp = 0;

    return ++tmp;
}