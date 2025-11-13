#ifndef PALABRA_H
#define PALABRA_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_PAL_TAM 51

typedef struct{
    char vPal[DEFAULT_PAL_TAM];
}Palabra;

void palabraATitulo(Palabra* pal);

#endif