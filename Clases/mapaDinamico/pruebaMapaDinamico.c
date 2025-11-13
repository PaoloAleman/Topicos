#include "mapaDinamico.h"
#include <stdlib.h>

int main()
{
    MapaDinamico_t mapa;
    
    mapaDinamicoCrear(&mapa, 5, 5);

    int filas = mapaDinamicoFilas(&mapa);
    int cols = mapaDinamicoColumnas(&mapa);

    printf("Filas: %d \t Columnas: %d\n", filas, cols);
    
    mapaDinamicoEscribir(&mapa, 1, 1, 0, 4, 2);
    mapaDinamicoEscribir(&mapa, 1, 1, 4, 8, 5);
    mapaDinamicoEscribir(&mapa, 1, 2, 12, 4, 2);

    uint64_t a = mapaDinamicoLeer(&mapa, 1, 1, 4, 8);

    printf("%lu\n", a);

    mapaDinamicoMostrar(&mapa);

    mapaDinamicoDestruir(&mapa);

    return 0;
}