#ifndef CADENAS_H
#define CADENAS_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool esPalindromo(char* str);
int valorNumericoDeCadena(char* str);
int stringSubstring(char* src, char* dest);
int normalizarString(char* str);
int desofuscarString(char* str, char* cifra);

#endif