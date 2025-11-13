#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {
    int day;
    int month;
    int year;
} Fecha;


void validarFecha(Fecha fecha);

void obtenerDiaSiguiente(Fecha fecha);

void obtenerFechaMasNDias(Fecha fecha);

void obtenerFechaMenosNDias(Fecha fecha);

int obtenerCantidadDeDiasEntreDosFechas(Fecha desde, Fecha hasta);

int obtenerDiaTextual(Fecha fecha);

#endif // FUNCIONES_H_INCLUDED
