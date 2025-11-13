#include "vector.h"

static bool redimensionarVector(VectorInt* vec, size_t cap);
static void burbujeo(VectorInt* vec);
static void seleccion(VectorInt* vec);
static void insercion(VectorInt* vec);

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

    printf("Redimension de %llu a %llu\n", vec->cap, cap);

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

static void burbujeo(VectorInt* vec)
{
    int* i = vec->vec;
    int* j = vec->vec;
    int* ult = vec->vec + vec->ce - 2;
    int* limJ = ult + 1;

    int tmp;

    for(; i < ult; i++, limJ--){
        for(j = vec->vec; j < limJ; j++){
            if(*j >= *(j + 1)){
                tmp = *j;
                *j = *(j + 1);
                *(j + 1) = tmp;
            }
        }
    }
}

/*
static void seleccion(VectorInt* vec)
{
    int* i = vec->vec;
    int* j = vec->vec;
    int* ult = vec->vec + vec->ce - 1;
    int* min = NULL;

    int tmp = 0;

    for(; i < ult; i++){

        min = i;

        for(j = i + 1; j <= ult; j++){
            if(*min < *j){
                min = j;
            }
        }

        tmp = *i;
        *i = *min;
        *min = tmp;
    }
}
*/


static void seleccion(VectorInt* vec)
{
    int* iMin = vec->vec;
    int* iMax = vec->vec + vec->ce - 1;
    int* j = vec->vec;
    int* min = NULL;
    int* max = NULL;

    int tmp = 0;

    for(; iMin <= iMax; iMin++, iMax--){

        min = iMin;
        max = iMax;

        for(j = iMin + 1; j <= iMax; j++){
            if(*min > *j){
                min = j;
            }
            if(*max < *j){
                max = j;
            }
        }

        if((iMax - iMin)){
            tmp = *iMin;
            *iMin = *min;
            *min = tmp;

            tmp = *iMax;
            *iMax = *max;
            *max = tmp;
        }

    }
}

static void insercion(VectorInt* vec)
{
    int* i = vec->vec + 1;
    int* j = vec->vec;
    int* ult = vec->vec + vec->ce - 1;
    int tmp;

    for(; i <= ult; i++){

       j = i - 1;
       tmp = *i;

       while(*j > tmp && j >= vec->vec){
            *(j + 1) = *j;
            j--;
       }

       *(j + 1) = tmp;
    }
}

void vectorOrdenar(VectorInt* vec, int metodo)
{
    switch(metodo){
        case BURBUJEO:
            burbujeo(vec);
            break;
        case SELECCION:
            seleccion(vec);
            break;
        case INSERCION:
            insercion(vec);
            break;
        default:
            break;
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
