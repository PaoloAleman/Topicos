#include "funciones.h"
#define DIAMAXIMO(mes) ((mes) == 4 || (mes) == 6 || (mes) == 9 || (mes) == 11 ? 30 : ((mes) == 2 ? 28 : 31))

bool validarFecha(Fecha fecha){
    return (fecha.year > 0 && fecha.year <= 2025) &&
                (fecha.month > 0 && fecha.month <= 12) &&
                    (fecha.day > 0 && fecha.day <= DIAMAXIMO(fecha.month));
}

Fecha obtenerDiaSiguiente(Fecha fecha){
    Fecha fechaNueva = fecha;

    if (fechaNueva.day < diaMaximo) {
            fechaNueva.day++;
    } else {
        fechaNueva.day = 1;
        if (fechaNueva.month < 12)
            fechaNueva.month++;
        else {
            fechaNueva.month = 1;
            fechaNueva.year++;
        }
    }

    return fechaNueva;
}

Fecha obtenerFechaMasNDias(Fecha fecha. int cantidad){
    Fecha fechaNueva = fecha;

    while (cantidad > 0) {
        int diaMaximo = DIAMAXIMO(fechaNueva.month, fechaNueva.year);

        if (fechaNueva.day < diaMaximo) {
            fechaNueva.day++;
        } else {
            fechaNueva.day = 1;
            if (fechaNueva.month < 12)
                fechaNueva.month++;
            else {
                fechaNueva.month = 1;
                fechaNueva.year++;
            }
        }

        cantidad--;
    }

    return fechaNueva;
}

Fecha obtenerFechaMenosNDias(Fecha fecha, int cantidad){
    Fecha fechaNueva = fecha;

    while (cantidad > 0) {
        if (fechaNueva.day > 1) {
            fechaNueva.day--;
        } else {
            fechaNueva.day = DIAMAXIMO(fechaNueva.month);
            if (fechaNueva.month > 1)
                fechaNueva.month--;
            else {
                fechaNueva.month = 12;
                fechaNueva.year--;
            }
        }

        cantidad--;
    }

    return fechaNueva;
}

int obtenerCantidadDeDiasEntreDosFechas(Fecha desde, Fecha hasta){
    int cantidad = (DIAMAXIMO(desde.month) - desde.day) + (hasta.day);
    int cantidadMeses = (12 - desde.month) + hasta.month;

    while(desde.month != hasta.month && desde.year != hasta.year){
        if (desde.month < 12)
            desde.month++;
        else {
            desde.month = 1;
            desde.year++;
        }
        ca
    }

    for(){

    }

    return 0;
}

int obtenerDiaTextual(Fecha fecha){
    return 0;
}
