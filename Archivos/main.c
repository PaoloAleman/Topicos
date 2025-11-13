#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main(){

    char texto[] = "Hola mundo dinamico";
    char *primera = obtenerPrimeraPalabra(texto);

    if (primera) {
        printf("Primera palabra: %s\n", primera);
        free(primera);
    }

    return 0;
}
