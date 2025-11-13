#include "vector.h"

void vectorCrear(VectorInt* vec)
{
    vec->cantElem = 0;
}

void vectorDestruir(VectorInt* vec)
{
    vec->cantElem = 0;
}

int vectorInsertar(VectorInt* vec, int elem)
{
    if(vec->cantElem == TAM){
        return ERROR;
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

    return EXITO;
}

int vectorPush(VectorInt* vec, int elem)
{
    if(vec->cantElem == TAM){
        return ERROR;
    }

    int* i = vec->vec + vec->cantElem;

    *i = elem;
    vec->cantElem++;

    return EXITO;
}

bool vectorOrdEliminarElem(VectorInt* vec, int elem)
{
    size_t pos = 0;

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

int vectorBuscar(VectorInt* vec, int elem)
{
    int* ori = vec->vec;
    int* li = vec->vec;
    int* ls = vec->vec + vec->cantElem - 1;
    int* m = li + ((ls - li) / 2);

    while(li <= ls && *m != elem){
        if(*m > elem){
            ls = m - 1;
        }else{
            li = m + 1;
        }

        m = li + ((ls - li) / 2);
    }

    if(li > ls){
        return -1;
    }

    return (m - ori);
}

void vectorOrdenar(VectorInt* vec)
{
    int* i = vec->vec;
    int* j = vec->vec;
    int* ult = vec->vec + vec->cantElem - 1;

    int limJ, tmp;

    for(limJ = 0; i < ult - 1; i++, limJ++){
        for(j = vec->vec; j < ult - 1 - limJ; j++){
            if(*j >= *(j + 1)){
                tmp = *j;
                *j = *(j + 1);
                *(j + 1) = tmp;
            }
        }
    }
}

int vectorObtener(VectorInt* vec, int pos)
{
    return *(vec->vec + pos);
}

void vectorMostrar(VectorInt* vec)
{
    int* i = vec->vec;
    int* ult = vec->vec + vec->cantElem;

    for(; i < ult; i++){
        printf("%02d\n", *i);
    }
}
