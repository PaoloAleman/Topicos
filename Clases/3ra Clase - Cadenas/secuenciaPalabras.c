#include "secuenciaPalabras.h"

void secuenciaPalabrasCrear(SecuenciaPalabras* sec, char* cadena)
{
    sec->cursor = cadena;
    sec->esFin = false;
}

bool secuenciaPalabrasLeer(SecuenciaPalabras* sec, Palabra* pal)
{
    while(*(sec->cursor) != '\0' && !esLetra(*(sec->cursor))){
        sec->cursor++;
    }

    if(*(sec->cursor) == '\0'){
        sec->esFin = true;
        return false;
    }

    char* tmp = pal->vPal;

    do
    {
        *tmp = *(sec->cursor);
        tmp++;
        sec->cursor++;
    }while(*(sec->cursor) != '\0' && esLetra(*(sec->cursor)));
    
    *tmp = '\0';

    return true;
}

void secuenciaPalabrasEscribir(SecuenciaPalabras* sec, Palabra* pal)
{
    char* i = pal->vPal;

    while(*i != '\0'){
        *(sec->cursor) = *i;
        i++;
        sec->cursor++;
    }
}

bool secuenciaPalabrasEscribirChar(SecuenciaPalabras* sec, int ch)
{
    *(sec->cursor) = ch;
    sec->cursor++;
    return true;
}

bool secuenciaPalabrasFin(SecuenciaPalabras* sec)
{
    return sec->esFin;
}

void secuenciaPalabrasCerrar(SecuenciaPalabras* sec)
{
    *(sec->cursor) = '\0';
}

bool esLetra(int ch)
{
    return ((ch > 'a' && ch < 'z') || (ch > 'A' && ch < 'Z'));
}