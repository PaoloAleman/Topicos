#ifndef MAPA_DINAMICO_H
#define MAPA_DINAMICO_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define EXITO 0
#define ERR_MEM 1
#define ERR_INGRESO 2

typedef struct{
    void** mat;
    size_t filas;
    size_t columnas;
}MapaDinamico_t;

int mapaDinamicoCrear(MapaDinamico_t* mapa, size_t filas, size_t columnas);
int mapaDinamicoDestruir(MapaDinamico_t* mapa);

int mapaDinamicoEscribir(MapaDinamico_t* mapa, size_t fila, size_t columna, int indice, int tamElem, uint64_t valor);
uint64_t mapaDinamicoLeer(MapaDinamico_t* mapa, size_t fila, size_t columna, int indice, int tamElem);

size_t mapaDinamicoFilas(MapaDinamico_t* mapa);
size_t mapaDinamicoColumnas(MapaDinamico_t* mapa);

void mapaDinamicoMostrar(MapaDinamico_t* mapa);

#endif