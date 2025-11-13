#include "vector.h"

static bool redimensionarVector(VectorInt* vec, size_t cap);

bool vectorCrear(VectorInt* vec)
{
    vec->vec = malloc(sizeof(int) * DEFAULT_CAP);

    if(!(vec->vec)){
        vec->cap = 0;
        return false;
    }

    vec->ce = 0;
    vec->cap = DEFAULT_CAP;

    return true;
}

bool vectorVaciar(VectorInt* vec)
{
    vec->ce = 0;
    vec->cap = DEFAULT_CAP;
    redimensionarVector(vec, vec->cap);
    return true;
}

bool redimensionarVector(VectorInt* vec, size_t cap)
{
    int* vecTmp = realloc(vec->vec, cap * sizeof(int));

    if(!(vecTmp)){
        return false;
    }

    printf("Redimension de %lu a %lu\n", vec->cap, cap);

    vec->vec = vecTmp;
    vec->cap = cap;

    return true;
}

void vectorDestruir(VectorInt* vec)
{
    free(vec->vec);
    vec->vec = NULL;
    vec->ce = 0;
    vec->cap = 0;
}

int vectorInsertar(VectorInt* vec, int elem)
{
    if(vec->ce == vec->cap){
        if(!redimensionarVector(vec, vec->cap * INCR_FACTOR)){
            return ERROR;
        }
    }

    int* i = vec->vec;
    int* j = vec->vec + vec->ce - 1;

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
    vec->ce++;

    return EXITO;
}

int vectorPush(VectorInt* vec, int elem)
{
    if(vec->ce == vec->cap){
        if(!redimensionarVector(vec, vec->cap * INCR_FACTOR)){
            return ERROR;
        }
    }

    int* i = vec->vec + vec->ce;

    *i = elem;
    vec->ce++;

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
    if(pos < 0 || pos > vec->ce - 1){
        return false;
    }

    int* i = vec->vec + pos + 1;
    int* j = vec->vec + vec->ce - 1;

    for(; i <= j; i++){
        *i = *(i + 1);
    }

    vec->ce--;

    if(((float)vec->ce / vec->cap) <= OCUP_FACTOR){
        redimensionarVector(vec, vec->cap * DECR_FACTOR);
    }

    return true;
}

int vectorBuscar(VectorInt* vec, int elem)
{
    int* ori = vec->vec;
    int* li = vec->vec;
    int* ls = vec->vec + vec->ce - 1;
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
    int* ult = vec->vec + vec->ce - 1;

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

size_t vectorCantElem(VectorInt* vec)
{
    return vec->ce;
}

int vectorObtener(VectorInt* vec, int pos)
{
    return *(vec->vec + pos);
}

void vectorMostrar(VectorInt* vec)
{
    int* i = vec->vec;
    int* ult = vec->vec + vec->ce;

    for(; i < ult; i++){
        printf("%02d\n", *i);
    }
}
