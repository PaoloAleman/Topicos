#include <stdio.h>
#include "vectorDinamico.h"

int main()
{   
    VectorInt vecA;

    vectorCrear(&vecA);

    vectorInsertar(&vecA, 20);
    vectorInsertar(&vecA, 240);
    vectorInsertar(&vecA, -1);
    vectorInsertar(&vecA, 43);
    vectorInsertar(&vecA, 2);

    vectorOrdenar(&vecA);
    int pos = vectorBuscar(&vecA, 20);

    printf("\n %d \n", vectorObtener(&vecA, pos));

    vectorMostrar(&vecA);

    vectorDestruir(&vecA);

    return 0;
}