#include "fechaRel.h"

//Primitivas

bool _setFecha(Fecha* fecha, int d, int m, int a)
{
    if(!validarFecha(d, m, a)){
        return false;
    }

    fecha->diasRel += d;
    fecha->diasRel += diasHastaElMes(m, a);
    fecha->diasRel += diasHastaElAnio(a);

    return true;   
}

void _getFecha(Fecha* fecha, int* d, int* m, int* a)
{
   int diasTmp;

   *a = calcularAnio(fecha, &diasTmp);
   *m = calcularMes(&diasTmp, a);
   *d = diasTmp;
}

Fecha _sumarDias(Fecha* fecha, unsigned int dias)
{
    Fecha tmp = *(fecha);
    tmp.diasRel += dias;

    return tmp;
}

Fecha _restarDias(Fecha* fecha, unsigned int dias)
{
    Fecha tmp = *(fecha);
    tmp.diasRel -= dias;

    return tmp;
}

int _diferenciaFechas(Fecha* fechaA, Fecha* fechaB)
{
    return fechaB->diasRel - fechaA->diasRel;
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
    int d, m, a;

    _getFecha(fecha, &d, &m, &a);

    printf("%02d/%02d/%04d\n", d, m, a);
}

//Auxiliares

int diasHastaElMes(int mes, int anio)
{
    int ayuda[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

    if(mes >= 2 && esBisiesto(anio)){
        return ayuda[mes] + 1;
    }

    return ayuda[mes];
}

bool esBisiesto(int a)
{
    return ((a % 4 == 0) || (a % 100 != 0 && a % 400 == 0));
}

int diasHastaElAnio(int anio)
{
    int origen = 1600, diasTmp = 0;

    int dif = anio - origen;

    int bisiestos = contarAniosBisiestos(anio, origen);

    diasTmp = (dif - bisiestos) * 365 + bisiestos * 366;
    
    return diasTmp;
}

int contarAniosBisiestos(int a, int b)
{
    int res = a/4 - a/100 + a/400 - b/4 + b/100 - b/400;

    return res;
}

int calcularAnio(Fecha* fecha, int* resto)
{
    float anio = fecha / 365.25;

    *

    return (int)anio;
}