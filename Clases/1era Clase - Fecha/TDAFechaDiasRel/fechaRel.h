#ifndef FECHA_DIAS_REL_H
#define FECHA_DIAS_REL_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int diasRel;
}Fecha;

//Primitivas
bool _setFecha(Fecha* fecha, int d, int m, int a);
void _getFecha(Fecha* fecha, int* d, int* m, int* a);
Fecha _sumarDias(Fecha* fecha, int dias);
Fecha _restarDias(Fecha* fecha, int dias);
int _diferenciaFechas(Fecha* fechaA, Fecha* fechaB);

//Auxiliares
int diasHastaElMes(int m, int a);
int diasHastaElAnio(int a);
bool esBisiesto(int a);
int contarAniosBisiestos(int a, int b);
int calcularAnio(Fecha* fecha, int* resto);
int calcularMes(int* resto, int* anio);

//No Primitivas
void ingresarFechaConsola(Fecha* fecha);
void mostrarFecha(Fecha* fecha);

#endif