#include "mapaDinamico.h"

static void destruirMatriz(size_t filas, void** matriz);
static uint64_t escribirCampo(uint64_t dest, uint64_t src, int indice, int tamElem);
static uint64_t leerCampo(uint64_t src, int indice, int tamElem);

static void destruirMatriz(size_t filas, void** matriz)
{
    void** i = NULL;
    void** ult = matriz + filas;

    for(i = matriz; i < ult; i ++){
        free(*i);
    }

    free(matriz);
}

static uint64_t escribirCampo(uint64_t dest, uint64_t src, int indice, int tamElem)
{
    int i;

    for(i = 0; i < tamElem; i++){
        if(src & (1 << i)){
            dest += (1 << (i + indice));
        }else{
            dest -= (0 << (i + indice));
        }
    }
    
    return dest;
}

static uint64_t leerCampo(uint64_t src, int indice, int tamElem)
{
    int i;
    uint64_t salida = 0;

    for(i = 0; i < tamElem; i++){
        if(src & (1 << (i + indice))){
            salida += (1 << i);
        }else{
            salida -= (0 << i);
        }
    }

    return salida;
}

int mapaDinamicoCrear(MapaDinamico_t* mapa, size_t filas, size_t columnas)
{
    mapa->mat = malloc(filas * sizeof(void*));

    if(!(mapa->mat)){
        return ERR_MEM;
    }

    void** i = mapa->mat;
    void** ult = mapa->mat + filas - 1;

    for(; i <= ult; i++){
        *i = calloc(columnas, sizeof(uint64_t));

        if(!(*i)){
            destruirMatriz(i - mapa->mat, mapa->mat);
        }
    }

    mapa->filas = filas;
    mapa->columnas = columnas;

    return EXITO;
}

int mapaDinamicoDestruir(MapaDinamico_t* mapa)
{
    destruirMatriz(mapa->filas, mapa->mat);

    mapa->filas = 0;
    mapa->columnas = 0;

    return 0;
}

int mapaDinamicoEscribir(MapaDinamico_t* mapa, size_t fila, size_t columna, int indice, int tamElem, uint64_t valor)
{
    uint64_t tmp = ((uint64_t**)(mapa->mat))[fila][columna];

    ((uint64_t**)(mapa->mat))[fila][columna] = escribirCampo(tmp, valor, indice, tamElem);

    return EXITO;
}

uint64_t mapaDinamicoLeer(MapaDinamico_t* mapa, size_t fila, size_t columna, int indice, int tamElem)
{
    uint64_t tmp = ((uint64_t**)(mapa->mat))[fila][columna];

    uint64_t salida = leerCampo(tmp, indice, tamElem);

    return salida;
}

size_t mapaDinamicoFilas(MapaDinamico_t* mapa)
{
    return mapa->filas;
}

size_t mapaDinamicoColumnas(MapaDinamico_t* mapa)
{
    return mapa->columnas;
}

void mapaDinamicoMostrar(MapaDinamico_t* mapa)
{
    uint64_t** tmp = (uint64_t**)(mapa->mat);
    size_t i, j;

    for(i = 0; i < mapa->filas; i++){
        for(j = 0; j < mapa->columnas; j++){
            printf("[%#lx] ", tmp[i][j]);
        }

        printf("\n");
    }
}