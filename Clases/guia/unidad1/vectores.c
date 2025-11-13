#include "vectores.h"

void intercambiar(void* src, void* dest, void* tmp, int tamElem);

void intercambiar(void* src, void* dest, void* tmp, int tamElem)
{
    memcpy(tmp, src, tamElem);
    memcpy(src, dest, tamElem);
    memcpy(dest, tmp, tamElem);
}

int insertarElemInt(int* vec, int elem, int pos, int ce)
{
    if(pos < 0 || pos > ce){
        return ERROR;
    }

    int* i = vec + pos;
    int* j = vec + ce;

    for(; i < j; j--){
        *(j + 1) = *j;
    }

    *i = elem;

    return ce + 1;
}

int insertarElemOrdenadoInt(int* vec, int elem, int ce)
{
    int* i = vec;
    int* j = vec + ce;

    while(*i != elem && i < j){
        i++;
    }

    if(*i != elem && i >= j){
        return  -1;
    }

    for(; i < j; j--){
        *(j + 1) = *j;
    }
    
    *i = elem;

    return ce + 1;
}

int eliminarElemPosInt(int* vec, int pos, int ce)
{
    if(pos < 1 || pos > ce){
        return -1;
    }

    int* i = vec + pos;
    int* j = vec + ce - 1;

    for(; i < j; i++){
        *i = *(i + 1);
    }

    return ce - 1;
}

int eliminarElemInt(int* vec, int elem, int ce)
{
    int pos;

    if((pos = buscarElemInt(vec, elem, ce)) == -1){
        return -1;
    }

    eliminarElemPosInt(vec, pos, ce);

    return ce - 1;
}

int eliminarTodosElemInt(int* vec, int elem, int ce)
{
    int pos;
    int ceTmp = ce;

    while((pos = buscarElemInt(vec, elem, ceTmp)) != -1){
        eliminarElemPosInt(vec, pos, ceTmp);
        ceTmp--;
    }

    return ceTmp;
}

int insertarElemVoid(void* vec, void* elem, int pos, int ce, int tamElem)
{
    if(pos < 1 || pos > ce){
        return -1;
    }

    void* i = vec + pos * tamElem;
    void* j = vec + ce * tamElem;

    for(; i < j; j - tamElem){
        memcpy(j + tamElem, j, tamElem);
    }

    memcpy(i, elem, tamElem);

    return ce + 1;
}

int insertarElemOrdenadoVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*))
{
    void* i = vec;
    void* j = vec + ce * tamElem;

    while(Cmp(i, elem) != 0 && i < j){
        i += tamElem;
    }

    if(Cmp(i, elem) != 0 && i >= j){
        return -1;
    }

    for(; i < j; j - tamElem){
        memcpy(j + tamElem, j, tamElem);
    }

    memcpy(i, elem, tamElem);

    return ce + 1;
}

int eliminarElemPosVoid(void* vec, int pos, int ce, int tamElem)
{
    void* i = vec + pos * tamElem;
    void* j = vec + ce * tamElem;

    for(; i < j; i + tamElem){
        memcpy(i, i + tamElem, tamElem);
    }

    return ce - 1;
}

int eliminarElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*))
{
    int pos;
    
    if((pos = buscarElemVoid(vec, elem, ce, tamElem, Cmp)) == -1){
        return -1;
    }

    eliminarElemPosVoid(vec, pos, ce, tamElem);

    return ce - 1;
}

int eliminarTodosElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*))
{
    int pos;
    int ceTmp = ce;

    while((pos = buscarElemVoid(vec, elem, ceTmp, tamElem, Cmp)) != -1){
        eliminarElemPosVoid(vec, pos, ceTmp, tamElem);
        ceTmp--;
    }

    return ceTmp;
}

int ordenarElemInt(int* vec, int ce)
{
    int* i = vec;
    int* j, limJ;
    int* ult = vec + ce - 1;
    int aux;

    for(limJ = ult; i < ult; i++, limJ--){
        for(j = vec; j < limJ; j++){
            if(*j > *(j + 1)){
                aux = *j;
                *j = *(j + 1);
                *(j + 1) = aux;
            }
        }
    }
    
    return 0;
}

int buscarElemInt(int* vec, int elem, int ce)
{  
    int* li = vec;
    int* ls = vec + ce;
    int* med = li + ((ls - li) / 2);

    while(li < ls && *med != elem){
        if(*med > elem){
            ls = med - 1;
        }else{
            li = med + 1;
        }

        med = li + ((ls - li) / 2);
    }

    if(li >= ls){
        return -1;
    }

    return (med - vec);
}

void mostrarVecInt(int* vec, int ce)
{
    int* i = vec;
    int* ult = vec + ce - 1;

    for(; i < ult; i++){
        printf("Elem: %d\n", *i);
    }
}

int ordenarElemVoid(void* vec, int ce, int tamElem, int (*Cmp)(void*, void*))
{
    void* i = vec + ce * tamElem;
    void* ult = vec + (ce - 1) * tamElem;
    void* limJ = ult - tamElem;
    void* j = NULL;
    void* tmp = NULL;

    for(; i < ult; i + tamElem, limJ - tamElem){
        for(j = vec; j < limJ; j + tamElem){
            if(Cmp(j, j + tamElem) > 0){
                intercambiar(j, j + tamElem, tmp, tamElem);   
            }
        }
    }
}

int buscarElemVoid(void* vec, void* elem, int ce, int tamElem, int (*Cmp)(void*, void*))
{
    void* li = vec;
    void* ls = vec + ce * tamElem;
    void* med = li + ((ls - li) / 2) * tamElem;

    int cmp;

    while(li < ls && (cmp = Cmp(med, elem)) != 0){
        if(cmp > 0){
            ls = med - tamElem;
        }else{
            li = med + tamElem;
        }

        med = li + ((ls - li) / 2) * tamElem;
    }

    if(li >= ls){
        return -1;
    }

    return (med - vec) / tamElem;
}

void mostrarVecVoid(void* vec, int ce, int tamElem, void (*Mostrar)(void*))
{
    void* i = vec;
    void* ult = vec + ce * tamElem;

    for(; i < ult; i + tamElem){
        Mostrar(i);
    }
}

