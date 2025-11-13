#ifndef LIBRO_H
#define LIBRO_H


typedef struct
{
	char codigoSocio[11];
	char codigoLibro[7];
	int cantidad; ///Positivo: m�s devoluciones, Negativo: m�s pr�stamos, Cero: Misma cant. de pr�st. que dev.
}
MovLibro; ///El tipo de los elementos de la lista.


typedef struct
{
	char codigo[7];
	char nombre[101];
	int cantidad; ///STOCK
}
Libro;



typedef struct
{
	char codigo[7];
	long nroReg;
}
IndLibro;


#endif // LIBRO_H
