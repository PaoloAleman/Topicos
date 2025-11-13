#include "matrices.h"

void** crearMatriz(int filas, int columnas, size_t tamElem)
{
    void** mat = malloc(filas * sizeof(void*));
    void** i = NULL;
    void** ult = NULL;


    if(!mat){
        return NULL;
    }

    ult = mat + filas - 1;

    for(i = mat; i <= ult; i++){
        *i = malloc(columnas * tamElem);

        if(!(*i)){
            destruirMatriz(i - mat, tamElem, mat);
        }
    }

    return mat;
}

void destruirMatriz(int filas, size_t tamElem, void** matriz)
{
    void** i = NULL;
    void** ult = matriz + filas;

    for(i = matriz; i < ult; i++){
        free(*i);
    }

    free(matriz);
}

void inicializarMatriz(int filas, int columnas, int** matriz, int (*Metodo)(int, int))
{
    int i, j;

    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas; j++){
            matriz[i][j] = Metodo(i, j);
        }
    }
}

void mostrarMatriz(int filas, int columnas, int** matriz)
{
    int i, j;

    for(i = 0; i < filas; i++){
        for(j = 0; j < columnas; j++){
            printf("[%03d]\t", matriz[i][j]);
        }
        puts("");
    }
}

int diagonalPrincipal(int orden, int** matriz)
{
    int i, tmp = 0;

    for(i = 0; i < orden; i++){
        tmp += matriz[i][i];
    }

    return tmp;
}

int diagonalSecundaria(int orden, int** matriz)
{
    int i, j, tmp = 0;

    for(i = 0, j = orden - 1; i < orden; i++, j--){
        tmp += matriz[i][j];
    }

    return tmp;
}

int triangularInferiorPrincipal(int orden, int** matriz)
{
    int i, j, tmp = 0;

    for(i = 1; i < orden; i++){
        for(j = 0; j < i; j++){
            tmp += matriz[i][j];
        }
    }

    return tmp;
}

int triangularSuperiorPrincipal(int orden, int** matriz)
{
    int i, j, tmp = 0;

    for(i = 0; i < orden - 1; i++){
        for(j = orden - 1; j > i; j--){
            tmp += matriz[i][j];
        }
    }

    return tmp;
}

int triangularInferiorSecundaria(int orden, int** matriz)
{
    int i, j, limJ, tmp = 0;

    for(i = 1, limJ = orden - 2; i < orden; i++, limJ--){
        for(j = orden - 1; j > limJ; j--){
            tmp += matriz[i][j];
        }
    }

    return tmp;
}

int triangularSuperiorSecundaria(int orden, int** matriz)
{
    int i, j, limJ, tmp = 0;

    for(i = 0, limJ = orden - 2; i <= orden - 2; i++, limJ--){
        for(j = 0; j <= limJ; j++){
            tmp += matriz[i][j];
        }
    }

    return tmp;
}

int** productoMatricial(int** a, int** b, int filasA, int columnasA, int filasB, int columnasB)
{
    if(columnasA != filasB){
        return NULL;
    }

    int** prod = (int**) crearMatriz(filasA, columnasB, sizeof(int));
    int tmp = 0;
    int i, j, limJ;

    for(i = 0; i < filasA; i++){
        for(j = 0; j < columnasA; j++){
            tmp += a[i][j] * b[j][i];
        }

        prod[i][limJ] = tmp;
        tmp = 0;
    }
    
    return prod;
}