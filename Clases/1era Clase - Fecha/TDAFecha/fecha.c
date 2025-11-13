#include "fecha.h"

//Primitivas

bool _setFecha(Fecha* fecha, int d, int m, int a)
{
    if(!validarFecha(d, m, a)){
        return false;
    }

    fecha->dia = d;
    fecha->mes = m;
    fecha->anio = a;

    return true;
}

void _getFecha(Fecha* fecha, int* d, int* m, int* a)
{
    *d = fecha->dia;
    *m = fecha->mes;
    *a = fecha->anio;
}

Fecha _sumarDias(Fecha* fecha, unsigned int dias)
{
    Fecha tmp = *(fecha);
    int diasTmp;

    tmp.dia += dias;

    while(tmp.dia > (diasTmp = diasEnMes(tmp.mes, tmp.anio))){
        tmp.dia -= diasTmp;
        tmp.mes++;

        if(tmp.mes > 12){
            tmp.mes = 1;
            tmp.anio++;
        }
    }

    return tmp;
}

Fecha _restarDias(Fecha* fecha, unsigned int dias)
{
    Fecha tmp = *(fecha);
    int diasTmp;

    tmp.dia -= dias;

    while(tmp.dia < 1){
        tmp.mes--;

        if(tmp.mes < 1){
            tmp.anio--;
            tmp.mes = 12;
        }

        tmp.dia += diasEnMes(tmp.mes, tmp.anio);
    }

    return tmp;
}

//Que elegante solucion!!
int _diferenciaFechas(Fecha* fechaA, Fecha* fechaB)
{
    int dif = 0;

    for(int anioAct = fechaA->anio; anioAct < fechaB->anio; anioAct++){
        dif += diasEnAnio(anioAct);
    }

    return dif - diasALaFecha(fechaA) + diasALaFecha(fechaB);
}

Fecha _fechaDeDiasEnAnio(int diasALaFecha, int a)
{
    if(diasALaFecha == 365 && !esBisiesto(a)){
        return (Fecha){-1, -1, -1}; //Literal compuesto, de C99 en adelante
    }else if(diasALaFecha == 366 && esBisiesto(a)){
        return (Fecha){-1, -1, -1};
    }

    Fecha tmp;
    int diasTmp = 0;

    tmp.anio = a;
    tmp.dia = diasALaFecha;
    tmp.mes = 1;

    while(tmp.dia > (diasTmp = diasEnMes(tmp.mes, a))){
        tmp.dia -= diasTmp;
        tmp.mes++;
    }

    return tmp;
}

//No primitivas

void ingresarFechaConsola(Fecha* fecha)
{
    int d, m, a;

    puts("Ingrese fecha con formato dd/mm/aaaa");
    scanf("%d/%d/%d", &d, &m, &a);

    while(!_setFecha(fecha, d, m, a)){
        puts("Error al ingresar fecha; Intente de nuevo");
        scanf("%d/%d/%d", &d, &m, &a);
    }
}

void mostrarFecha(Fecha* fecha)
{
    printf("%02d/%02d/%04d\n", fecha->dia, fecha->mes, fecha->anio);
}

//La subrutina mas berreta del mundo
void mostrarFechaFormato(Fecha* fecha, void (*fechaFormato)(Fecha*)){
    fechaFormato(fecha);
}

int diaDeLaSemana(Fecha* fecha)
{
    Fecha base = {.dia = 1, .mes = 1, .anio = 1600};

    int dif = _diferenciaFechas(&base, fecha);

    return dif % 7;
}

//Auxiliares

bool validarFecha(int d, int m, int a)
{
    if(a < 1600){
        return false;
    }

    if(m < 1 || m > 12){
        return false;
    }

    if(d < 1 || d > diasEnMes(m, a)){
        return false;
    }

    return true;
}

int diasEnAnio(int a)
{
    if(esBisiesto(a)){
        return 366;
    }

    return 365;
}

int diasEnMes(int m, int a)
{
    int ayuda[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(m == 2 && esBisiesto(a)){
        return 29;
    }

    return ayuda[m];
}


int diasALaFecha(Fecha* fecha)
{
    Fecha tmp = *(fecha);
    int res = 0;

    while(tmp.mes != 1){
        res += diasEnMes(tmp.mes, tmp.anio);
        tmp.mes--;
    }

    return res + tmp.dia;
}

bool esBisiesto(int a)
{
    return ((a % 4 == 0) || (a % 100 != 0 && a % 400 == 0));
}