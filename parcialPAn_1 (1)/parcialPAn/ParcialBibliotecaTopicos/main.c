/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: -------
*
* DNI: --
*
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Cadena/Cadena.h"

#define TDA_LISTA_IMPL_DINAMICA_VEC
#include "../TDALista/TDALista.h"

#include "../SolucionBibliotecaTopicos/SolucionBiblioteca.h"

#define NOMBRE_ARCH_LIBROS "Libros.dat"
#define NOMBRE_ARCH_LIBROS_INDICE "Libros.idx"
#define NOMBRE_ARCH_MOVIMIENTOS "Movimientos.txt"
#define NO_FILE -99
#define TAM_LINEA 100
typedef int(*cmp)(void*, void*);
typedef void(*m)(void*);
typedef void (*actualizar)(void*, void*);

bool listaCrear_ALU(Lista* pl, size_t tamElem);
int cargarListaMovimientosLibro_ALU(Lista* plistaMov, const char* nombreArchMov);
int tListaInsertarAlFinal(Lista* v, void* elem);

///Insertar ordenado
int insertarOrd(Lista * vec, void* elem, cmp comp, actualizar fusionar);
int compararInsert(void* a, void* b);
int ListaFusionar(Lista *vec);
///ORDENAMIENTO
void* buscarMm(void* inicio, void* fin, size_t tamTD, cmp comparacion);
void intercambio(void* a, void*b, size_t tamTD);
void ordenarSeleccion(Lista*, cmp comp);

///Mostrar
void mostrarV(void*);
void ListaMostrar(Lista* vec, m);

int main()
{
	generarArchMovimientosLibro(NOMBRE_ARCH_MOVIMIENTOS);
	generarArchLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE);

	mostrarLibros(NOMBRE_ARCH_LIBROS);
	Lista listaMov;
	listaCrear_ALU(&listaMov, sizeof(MovLibro));
	//listaCrear(&listaMov, sizeof(MovLibro));

	///Debe cargar la lista de movimientos, consolidando los movimientos de los libros, a fin de que quede 1 sólo elemento en la lista por cada libro.
	///Aumentando o disminuyendo la cantidad según se trate de una devolución o un préstamo respectivamente.
	cargarListaMovimientosLibro_ALU(&listaMov, NOMBRE_ARCH_MOVIMIENTOS);
	//cargarListaMovimientosLibro(&listaMov, NOMBRE_ARCH_MOVIMIENTOS);

	///Para test
	puts("Lista movimientos");
	puts("Cod. Libro | Cant.");
	listaRecorrer(&listaMov, mostrarMovimientoLibro, NULL);

	puts("");

	///Debe actualizar el archivo binario de Libros, sumando o restando la cantidad.
	///La cantidad en el archivo no puede quedar negativa. Si eso sucede, se deberá descartar el movimiento y continuar con el siguiente.
	///Para acceder a cada registro, debe hacer uso del archivo índice, que tiene cada registro, el código del libro y su ubicación en el archivo(Nro de registro empezando por el 0).
	///Debe cargar el índice en memoria, para trabajar con él.
	//actualizarArchivoLibros_ALU(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &listaMov);
	actualizarArchivoLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &listaMov);

	puts("");

	///Debe normalizar los nombres de los libros en el archivo.
	///Dejando sólo 1 espacio entre palabras, sin espacios ni caracteres antes de la primer palábra y después de la última.
	///Quedando la primer letra de cada palabra en mayúscula y el resto en minúscula.
	/// normalizarNombresLibros_ALU(NOMBRE_ARCH_LIBROS);
	//normalizarNombresLibros(NOMBRE_ARCH_LIBROS);

	//mostrarLibros(NOMBRE_ARCH_LIBROS);

    listaDestruir_ALU(&listaMov);
	//listaDestruir(&listaMov);

    return 0;
}
void mostrarV(void* a)
{
    MovLibro aux = *(MovLibro*)a;
    printf("%s|%d\n", aux.codigoLibro, aux.cantidad);
}

void ListaMostrar(Lista* vec, m mostrar)
{
    void *i, *ult = vec->vec + (vec->ce-1)* vec->tamElem;
    for(i = vec->vec; i <= ult; i += vec->tamElem)
    {
        mostrar(i);
    }
}
bool listaCrear_ALU(Lista* pl, size_t tamElem)
{
	///Inserte el código acá
	void* direccion = malloc(tamElem*50);
	if(!direccion)
    {
        printf("No se pudo crear el vector");
        return false;
    }
    pl->vec = direccion;
    pl->tamElem = tamElem;///
	pl->ce = 0;
	pl->cap = 50;
	return true;
}
void actualizarMovLibro(void* a, void* b)
{
    MovLibro* pos = (MovLibro*)a;
    MovLibro* aux = (MovLibro*)b;
    pos->cantidad += aux->cantidad;
    return;
}

int insertarOrd(Lista * vec, void* elem, cmp comp, actualizar fusionar)
{
    if(vec->cap == vec->ce)
    {
        size_t nuevoCap = vec->cap + 20;
        void *dir = realloc(vec->vec,vec->tamElem * nuevoCap);
        if(!dir)
            return SIN_MEM;
        vec->vec = dir;
        vec->cap = nuevoCap;
    }
    void *j;
    void *i = vec->vec;
    void *ult = vec->vec + (vec->ce-1) * (vec->tamElem);
    while(i <= ult && comp(elem, i) > 0) ///elem es aux, e i es la posicion del vector
        i += vec->tamElem;

    if(i <= ult && comp(elem, i) == 0)
    {
        fusionar(i, elem);
        return TODO_OK;
    }

    for(j = ult ; j >= i ; j-= vec->tamElem)
        memcpy(j+vec->tamElem, j, vec->tamElem);
    memcpy(i, elem, vec->tamElem);
    vec->ce++;
    return TODO_OK;
}


int compararInsert(void* a, void* b)
{
    MovLibro *elem = (MovLibro*)b;
    MovLibro *aux = (MovLibro*)a;
    int ret = strcmpi(aux->codigoLibro, elem->codigoLibro);
    return ret;

}
int cargarListaMovimientosLibro_ALU(Lista* plistaMov, const char* nombreArchMov)
{
	///Inserte el código acá
	FILE* archivoMov = fopen(nombreArchMov, "rt");
	if(!archivoMov)
    {
        printf("No se pudo abrir el archivo");
        return NO_FILE;
    }

    char letra;
    MovLibro aux;
    fscanf(archivoMov, "%[^|]|%[^|]|%c\n", aux.codigoLibro, aux.codigoSocio,&letra);
    aux.cantidad = (letra == 'P')? -1: 1;
    insertarOrd(plistaMov, &aux, compararInsert, actualizarMovLibro);
    while(!feof(archivoMov))
    {
        fscanf(archivoMov, "%[^|]|%[^|]|%c\n", aux.codigoLibro, aux.codigoSocio,&letra);
        aux.cantidad = (letra == 'P')? -1: 1;
        insertarOrd(plistaMov, &aux, compararInsert, actualizarMovLibro);
    }
    printf("\t\t\n\n");
    ListaMostrar(plistaMov, mostrarV);

    fclose(archivoMov);
	return TODO_OK;
}

int ListaFusionar(Lista *vec)
{
    void* vecAux = malloc(vec->ce * vec->tamElem); ///vector auxiliar, en este cargo los resumenes
    if(!vecAux)
    {
        printf("no se pudo fusionar1");
        return SIN_MEM;
    }
    MovLibro* aux = (MovLibro*)vec->vec;
    int i = 0;
    int eliminar = 0;
    while(i < 10)//vec->ce - eliminar
    {
        char codLib[7];
        strcpy(codLib,aux->codigoLibro);
        int cont = 0;
        while(i < vec->ce - eliminar && strcmpi(aux->codigoLibro,codLib) == 0)
        {
            cont += aux->cantidad;
            aux++;
        }
        //eliminar++;
        aux--;
        aux->cantidad = cont;
        memcpy(vecAux, aux, vec->tamElem);
        i++;
        aux++;
        vecAux += vec->tamElem;
    }
    vecAux = realloc(vecAux, vec->tamElem * 10);///aca achico el vectorAux, defino vecNuevo por si el realloc no se pudo hacer
    if(!vecAux)
    {
        printf("no se pudo fusionar2");
        return SIN_MEM;
    }
    vec->vec = vecAux;
    vec->ce = 10;
    return TODO_OK;
}
int actualizarArchivoLibros_ALU(const char* nombreArchLibros, Lista* plistaMov)
{
	///Inserte el código acá
	return TODO_OK;
}


int normalizarNombresLibros_ALU(const char* nombreArchLibros)
{
	///Inserte el código acá
	return TODO_OK;
}


void listaDestruir_ALU(Lista* pl)
{
	///Inserte el código acá
	free(pl->vec);
}

void intercambio(void* a, void*b, size_t tamTD)
{
    char aux[tamTD];
    memcpy(aux, a, tamTD);
    memcpy(a, b, tamTD);
    memcpy(b, aux, tamTD);
}

int compara(void* a, void* b)
{
    MovLibro *mov1 =(MovLibro*)a;
    MovLibro *mov2 =(MovLibro*)b;
    return strcmpi(mov1->codigoLibro, mov2->codigoLibro);
}

void* buscarMm(void* inicio, void* fin, size_t tamTD, cmp comparacion)
{
    void* Mm = inicio, *i;
    for(i = inicio + tamTD; i <= fin; i+= tamTD)
    {
        if(comparacion(i, Mm) < 0)
            Mm = i;
    }
    return Mm;
}


void ordenarSeleccion(Lista* vec, cmp comparacion)
{
    void* inicio, *ult = vec->vec + (vec->ce-1)* vec->tamElem;
    void* elem;

    for(inicio = vec->vec; inicio <= ult; inicio += vec->tamElem)
    {
        elem = buscarMm(inicio, ult, vec->tamElem,comparacion);
        intercambio(inicio, elem, vec->tamElem);
    }
}
