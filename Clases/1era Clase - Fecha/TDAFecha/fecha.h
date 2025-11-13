#ifndef FECHA_H
#define FECHA_H

#include <stdio.h>
#include <stdbool.h>

typedef struct{
    int dia, mes, anio;
}Fecha;

//Primitivas
bool _setFecha(Fecha* fecha, int d, int m, int a);
void _getFecha(Fecha* fecha, int* d, int* m, int* a);
Fecha _sumarDias(Fecha* fecha, unsigned int dias);
Fecha _restarDias(Fecha* fecha, unsigned int dias);
int _diferenciaFechas(Fecha* fechaA, Fecha* fechaB);
Fecha _fechaDeDiasEnAnio(int diasALaFecha, int a);

//Auxiliares
bool validarFecha(int d, int m, int a);
int diasEnMes(int m, int a);
int diasEnAnio(int a);
int diasALaFecha(Fecha* fecha);
bool esBisiesto(int a);

//No primitivas
void ingresarFechaConsola(Fecha* fecha);
void mostrarFecha(Fecha* fecha);
void mostrarFechaFormato(Fecha* fecha, void (*fechaFormato)(Fecha*)); //Rompe el encapsulamiento?
int diaDeLaSemana(Fecha* fecha); //Empezando desde el sabado 1ro de Enero del 1600

#endif