#ifndef SOLUCION_BIBLIOTECA_H
#define SOLUCION_BIBLIOTECA_H

#include <stdio.h>
#include "Libro.h"
#define TDA_LISTA_IMPL_DINAMICA_VEC
#include "../TDALista/TDALista.h"


int generarArchLibros(const char* nombreArchLibros, const char* nombreArchLibrosIndice);
int generarArchMovimientosLibro(const char* nombreArchMovimientos);
void mostrarLibros(const char* nombreArchLibros);
int cargarListaMovimientosLibro(Lista* plistaMov, const char* nombreArchMov);
int actualizarArchivoLibros(const char* nombreArchivoLibros, const char* nombreArchivoLibrosIndice, Lista* plistaMov);
int normalizarNombresLibros(const char* nombreArchivoLibros);
void mostrarMovimientoLibro(void* pvmov, void*);


#endif // SOLUCION_BIBLIOTECA_H
