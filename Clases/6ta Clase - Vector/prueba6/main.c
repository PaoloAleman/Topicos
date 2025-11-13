#include "../Vector/vector.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAM 100000

int cmp(const void*, const void*);

int main()
{
    VectorInt vec;
    int i;
    srand(time(NULL));

    vectorCrear(&vec);

    for(i = 0; i < TAM; i++){
        vectorPush(&vec, rand() % 100);
    }



    //vectorMostrar(&vec);

    puts("");

    int segIni = time(NULL);

    vectorOrdenar(&vec, INSERCION);

    int segFin = time(NULL);

    puts("");

    //vectorMostrar(&vec);

    while(vectorCantElem(&vec) > 0){
        vectorEliminarPos(&vec, 0);
    }

    vectorDestruir(&vec);

    printf("Ordenar tardo %d segundos\n", segFin - segIni);

    return 0;
}

int cmp(const void* a, const void* b)
{
    int* tmpA = (void*) a;
    int* tmpB = (void*) b;

    return *tmpA - *tmpB;
}
