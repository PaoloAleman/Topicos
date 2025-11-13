#include "vector.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAM 500000000

int main()
{  
    VectorInt vec;
    int i;
    srand(time(NULL));

    vectorCrear(&vec);

    for(; i < TAM; i++){
        vectorInsertar(&vec, rand() % 100);
    }

    while(vectorCantElem(&vec) > 0){
        vectorEliminarPos(&vec, 0);
    }

    vectorDestruir(&vec);

    return 0;
}