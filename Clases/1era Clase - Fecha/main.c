#include "TDAFecha/fecha.c"
#include <stdio.h>


void formatoYankee(Fecha* fecha);

int main()
{
    Fecha fechaA, fechaB;

    ingresarFechaConsola(&fechaA);
    mostrarFecha(&fechaA);
    printf("%d\n", diaDeLaSemana(&fechaA));

    ingresarFechaConsola(&fechaB);
    mostrarFechaFormato(&fechaB, formatoYankee);

    fechaA = _sumarDias(&fechaA, 10);
    mostrarFecha(&fechaA);

    fechaB = _restarDias(&fechaB, 10);
    mostrarFecha(&fechaB);

    int dias = _diferenciaFechas(&fechaB, &fechaA);

    printf("Entre la Fecha A y la fecha B hay un total de %d dias de diferencia\n", dias);

    return 0;
}

void formatoYankee(Fecha* fecha)
{
    printf("%02d/%02d/%04d\n", fecha->mes, fecha->dia, fecha->anio);
}