#ifndef SECUENCIA_PALABRAS_H
#define SECUENCIA_PALABRAS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "palabra.h"

typedef struct{
    char* cursor;
    bool esFin;
}SecuenciaPalabras;

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, char* cadena);
bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal);
void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, Palabra* pal);
bool secuenciaPalabrasEscribirChar(SecuenciaPalabras* sec, int ch);
bool secuenciaPalabrasFin(SecuenciaPalabras* sec);
void secuenciaPalabrasCerrar(SecuenciaPalabras* sec);

bool esLetra(int ch);

#endif