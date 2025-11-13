#include "vectorDinamico.h"

int vectorCrear(VectorInt* vec)
{
    vec->vec = malloc(DEFAULT_CAP * sizeof(int));

    if(!(vec->vec)){
        return ERROR;
    }

    vec->cap = DEFAULT_CAP;
    vec->cantElem = 0;

    return TODO_OK;
}

void vectorDestruir(VectorInt* vec)
{
    free(vec->vec);
    
    vec->cap = 0;
    vec->cantElem = 0;
}

int vectorRedimensionar(VectorInt* vec, size_t nuevaCap)
{
    int* tmpVec = realloc(vec->vec, nuevaCap * sizeof(int));

    if(!tmpVec){
        return ERROR;
    }

    vec->vec = tmpVec;
    vec->cap = nuevaCap;

    return TODO_OK;
}

int vectorInsertar(VectorInt* vec, int elem)
{
    if(vec->cantElem == vec->cap){
        if(vectorRedimensionar(vec, vec->cap * FACTOR_INCR)){
            return ERROR;
        }
    }

    int* i = vec->vec;
    int* j = vec->vec + vec->cantElem - 1;

    while(elem > *i && i <= j){
        i++;
    }

    if(elem == *i && i > j){
        return ERROR;
    }

    for(; i <= j; j--){
        *(j + 1) = *j;
    }

    *i = elem;
    vec->cantElem++;

    return TODO_OK;
}

int vectorPush(VectorInt* vec, int elem)
{
    if(vec->cantElem == vec->cap){
        if(vectorRedimensionar(vec, vec->cap * FACTOR_INCR)){
            return ERROR;
        }
    }

    int* i = vec->vec + vec->cantElem;

    *i = elem;
    vec->cantElem++;

    return TODO_OK;
}

bool vectorOrdEliminarElem(VectorInt* vec, int elem)
{
    size_t pos;

    if((pos = vectorBuscar(vec, elem)) == -1){
        return false;
    }

    vectorEliminarPos(vec, pos);

    return true;
}

bool vectorEliminarPos(VectorInt* vec, size_t pos)
{
    if(pos < 0 || pos > vec->cantElem - 1){
        return false;
    }

    int* i = vec->vec + pos + 1;
    int* j = vec->vec + vec->cantElem - 1;

    for(; i <= j; i++){
        *i = *(i + 1);
    }

    vec->cantElem--;

    return true;
}

void vectorOrdenar(VectorInt* vec)
{
    int* i = vec->vec;
    int* j = NULL;
    int* ult = vec->vec + vec->cantElem -1;
    int limJ = 1;

    int aux;

    for(; i < ult - 1; i++, limJ++){
        for(j = vec->vec; j < ult - limJ - 1; j++){
            if(*j >= *(j + 1)){
                aux = *j;
                *j = *(j + 1);
                *(j + 1) = aux;
            }
        }
    }  
}

int vectorBuscar(VectorInt* vec, int elem)
{
    int* ori = vec->vec;
    int* li = vec->vec;
    int* ls = vec->vec + vec->cantElem - 1;
    int* med = li + ((ls - li) / 2);

    while(li <= ls && *med != elem){
        if(*med < elem){
            li = med + 1;
        }else{
            ls = med - 1;
        }

        med = li + ((ls - li) / 2);
    }

    if(li > ls){
        return -1;
    }

    return (med - ori);
}

int vectorObtener(VectorInt* vec, int pos)
{
    return *(vec->vec + pos);
}

void vectorMostrar(VectorInt* vec)
{
    int i = 0;

    for(; i < vec->cantElem; i++){
        printf("%02d\n", *(vec->vec + i));
    }
}