#ifndef TDALISTA_H
#define TDALISTA_H

#include <stdbool.h>
#include "../Comun/Comun.h"

#ifdef TDA_LISTA_IMPL_DINAMICA_VEC
    #include "../TDAListaImplDinamicaVec/TDAListaImplDinamicaVec.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA
    #include "../TDAListaImplDinamica/TDAListaImplDinamica.h"
#endif

#ifdef TDA_LISTA_IMPL_DINAMICA_DOBLE
    #include "../TDAListaImplDinamicaDoble/TDAListaImplDinamicaDoble.h"
#endif

/** Sentido Ordanamiento **/
#define ASC     1
#define DESC    -1

/** Método de Ordenamiento **/
#define SELECCION   1
#define BURBUJEO    2
#define INSERCION   3


bool listaCrear(Lista* pl, size_t tamElem);
bool listaCrearRandom(Lista* pl, int ce);
bool listaCrearDeArchivo(Lista* pl, const char* nomArch, size_t tamElem);
int listaInsertarOrd(Lista* pl, const void* elem, size_t tamElem, Cmp cmp, Actualizar actualizar);
int listaInsertarOrdCDup(Lista* pl, const void* elem, size_t tamElem, Cmp cmp);
int listaInsertarAlInicio(Lista* pl, const void* elem, size_t tamElem);
int listaInsertarAlFinal(Lista* pl, const void* elem, size_t tamElem);
int listaInsertarEnPosicion(Lista* pl, const void* elem, size_t tamElem, unsigned pos);
bool listaBuscarOrd(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);
bool listaBuscarDesord(const Lista* pl, void* elem, size_t tamElem, Cmp cmp);
bool listaVerPrimero(const Lista* pl, void* elem, size_t tamElem);
void listaRecorrer(Lista* pl, Accion accion, void* extra);
bool listaEliminarOrdPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
bool listaEliminarDesordPorValor(Lista* pl, void* elem, size_t tamElem, Cmp cmp);
int listaEliminarOrdPorCondicion(Lista* pl, Condicion condicion);
bool listaEliminarPrimero(Lista* pl, void* elem, size_t tamElem);
bool listaEliminarUltimo(Lista* pl, void* elem, size_t tamElem);
int listaEliminarOrdDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar);
int listaEliminarDesordDuplicados(Lista* pl, Cmp cmp, Actualizar actualizar);
void listaOrdenar(Lista* pl, Cmp cmp, int sentidoOrdenamiento);
bool listaGrabarEnArchivo(Lista* pl, const char* nomArch);
bool listaVacia(const Lista* pl);
bool listaLlena(const Lista* pl, size_t tamElem);
void listaVaciar(Lista* pl);
void listaDestruir(Lista* pl);

void listaIteradorCrear(ListaIterador* pi, Lista* pl);
void* listaIteradorPrimero(ListaIterador* pi);
void* listaIteradorSiguiente(ListaIterador* pi);
void* listaIteradorAnterior(ListaIterador* pi);
void* listaIteradorUltimo(ListaIterador* pi);
void* listaIteradorActual(ListaIterador* pi);

#endif // TDALISTA_H
