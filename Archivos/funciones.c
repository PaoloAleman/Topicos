#include "funciones.h"

char* obtenerPrimeraPalabra(char *texto){
    char *palabra = malloc(1);
    if(!palabra) return NULL;

    int len = 0;

    while(!isspace(*texto) && *texto){
        palabra = realloc(palabra, len+2);
        if(!palabra) return NULL;
        palabra[len++] = *texto++;
    }
    palabra[len] = '\0';

    return palabra;
}

void obtenerCantidadRepeticiones(char *texto){

}

void obtenerCantidadPalabras(char *texto){

}

void obtenerLongitudPalabraMasLarga(char *texto){

}


