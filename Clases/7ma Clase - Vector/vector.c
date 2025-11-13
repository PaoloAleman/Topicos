#include "vector.h"

static bool redimensionarVector(Vector* vec, size_t cap);
static void meminte(void* dest, void* src, size_t n);
static void memxor(void* dest, void* src, size_t n);
static void burbujeo(Vector* vec, int (*Cmp)(void*, void*));
static void seleccion(Vector* vec, int (*Cmp)(void*, void*));
static void insercion(Vector* vec, int (*Cmp)(void*, void*));

bool vectorCrear(Vector* vec, size_t tamElem)
{
    vec->vec = malloc(tamElem * DEFAULT_CAP);

    if(!(vec->vec)){
        vec->cap = 0;
        return false;
    }

    vec->tamElem = tamElem;
    vec->ce = 0;
    vec->cap = DEFAULT_CAP;

    return true;
}

bool vectorVaciar(Vector* vec)
{
    vec->tamElem = 0;
    vec->ce = 0;
    vec->cap = DEFAULT_CAP;
    redimensionarVector(vec, vec->cap);
    return true;
}

bool redimensionarVector(Vector* vec, size_t cap)
{
    int* vecTmp = realloc(vec->vec, cap * vec->tamElem);

    if(!(vecTmp)){
        return false;
    }

    printf("Redimension de %llu a %llu\n", vec->cap, cap);

    vec->vec = vecTmp;
    vec->cap = cap;

    return true;
}

void vectorDestruir(Vector* vec)
{
    free(vec->vec);
    vec->vec = NULL;
    vec->tamElem = 0;
    vec->ce = 0;
    vec->cap = 0;
}

int vectorInsertar(Vector* vec, void* elem, int (*Cmp)(void*, void*))
{
    if(vec->ce == vec->cap){
        if(!redimensionarVector(vec, vec->cap * INCR_FACTOR)){
            return ERROR;
        }
    }

    void* i = vec->vec;
    void* j = vec->vec + (vec->ce - 1) * vec->tamElem;

    

    while(Cmp(elem, i) > 0 && i <= j){
        i += vec->tamElem;
    }

    if(Cmp(elem, i) == 0 && i > j){
        return ERROR;
    }

    memmove(i + vec->tamElem, i, j - i);

    /*
    for(; i <= j; j--){
        *(j + 1) = *j;
    }
    */

    memcpy(i, elem, vec->tamElem);
    vec->ce++;

    return EXITO;
}

int vectorPush(Vector* vec, void* elem)
{
    if(vec->ce == vec->cap){
        if(!redimensionarVector(vec, vec->cap * INCR_FACTOR)){
            return ERROR;
        }
    }

    void* i = vec->vec + vec->ce * vec->tamElem;

    memcpy(i, elem, vec->tamElem);
    vec->ce++;

    return EXITO;
}

bool vectorOrdEliminarElem(Vector* vec, void* elem, int (*Cmp)(void*, void*))
{
    size_t pos = 0;

    if((pos = vectorBuscar(vec, elem, Cmp)) == -1){
        return false;
    }

    vectorEliminarPos(vec, pos);

    return true;
}

bool vectorEliminarPos(Vector* vec, size_t pos)
{
    if(pos < 0 || pos > vec->ce - 1){
        return false;
    }

    void* i = vec->vec + (pos + 1) * vec->tamElem;
    void* j = vec->vec + (vec->ce - 1) * vec->tamElem;

    memmove(i, i + vec->tamElem, j - i);

    /*
    for(; i <= j; i++){
        *i = *(i + 1);
    }
    */

    vec->ce--;

    if(((float)vec->ce / vec->cap) <= OCUP_FACTOR){
        redimensionarVector(vec, vec->cap * DECR_FACTOR);
    }

    return true;
}

int vectorBuscar(Vector* vec, void* elem, int (*Cmp)(void*, void*))
{
    void* ori = vec->vec;
    void* li = vec->vec;
    void* ls = vec->vec + vec->ce - 1;
    void* m = li + ((ls - li) / (2 * vec->tamElem)) * vec->tamElem;

    int cmp;

    while(li <= ls && (cmp = Cmp(m, elem)) != 0){
        if(cmp > 0){
            ls = m - vec->tamElem;
        }else{
            li = m + vec->tamElem;
        }

        m = li + ((ls - li) / (2 * vec->tamElem)) * vec->tamElem;
    }

    if(li > ls){
        return -1;
    }

    return ((m - ori) / vec->tamElem);
}

static void burbujeo(Vector* vec, int (*Cmp)(void*, void*))
{
    void* i = vec->vec;
    void* j = vec->vec;
    void* ult = vec->vec + (vec->ce - 2) * vec->tamElem;
    void* limJ = ult + vec->tamElem;

    for(; i < ult; i += vec->tamElem, limJ -= vec->tamElem){
        for(j = vec->vec; j < limJ; j += vec->tamElem){
            if(Cmp(j, j + vec->tamElem) >= 0){
                meminte(j, j + vec->tamElem, vec->tamElem);
            }
        }
    }
}

static void seleccion(Vector* vec, void* elem, int (*Cmp)(void*, void*))
{
    void* i = vec->vec;
    void* j = vec->vec;
    void* ult = vec->vec + (vec->ce - 1) * vec->tamElem;
    void* min = NULL;

    for(; i < ult; i += vec->tamElem){
        min = i;

        for(j = i + vec->tamElem; j <= ult; j += vec->tamElem){
            if(Cmp(min, j) > 0){
                min = j;
            }
        }

        meminte(i, min, vec->tamElem);
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

/*
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
*/

static void insercion(Vector* vec, int (*Cmp)(void*, void*))
{
    void* i = vec->vec + vec->tamElem;
    void* j = vec->vec;
    void* ult = vec->vec + (vec->ce - 1) * vec->tamElem;

    for(; i <= ult; i += vec->tamElem){
        j = i - vec->tamElem;

        while(Cmp(j, i) > 0 && j >= vec->vec){
            memmove(j, j + vec->tamElem, vec->tamElem);
            j -= vec->tamElem;
        }

        memmove(j + vec->tamElem, i, vec->tamElem);
    }
}


/*
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
*/

void vectorOrdenar(Vector* vec, int metodo, int (*Cmp)(void*, void*))
{
    switch(metodo){
        case BURBUJEO:
            burbujeo(vec, Cmp);
            break;
        case SELECCION:
            seleccion(vec, Cmp);
            break;
        case INSERCION:
            insercion(vec, Cmp);
            break;
        default:
            break;
    }
}

size_t vectorCantElem(Vector* vec)
{
    return vec->ce;
}

void* vectorObtener(Vector* vec, int pos)
{
    return (vec->vec + pos * vec->tamElem);
}

void vectorMostrar(Vector* vec, void (*Mostrar)(void*))
{
    void* i = vec->vec;
    void* ult = vec->vec + vec->ce;

    for(; i < ult; i += vec->tamElem){
        Mostrar(i);
    }
}
