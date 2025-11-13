#include "palabra.h"

void palabraATitulo(Palabra* pal)
{
    char* i = pal->vPal;

    *i = toupper(*i);

    i++;

    while(*i != '\0'){
        *i = tolower(*i);
        i++;
    }
}
