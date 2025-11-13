#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../SolucionParcialBonificacionClientesTopicos/UtilitariasParcialBonificacionClientes.h"
#include "../SolucionParcialBonificacionClientesTopicos/SolucionParcialBonificacionClientes.h"
#include "../SolucionParcialBonificacionClientesTopicos/TiposArchivos.h"

#define TDA_LISTA_IMPL_DINAMICA_VEC
#include "../TDALista/TDALista.h"

#define NO_FILE -999

///DATOS: CORONEL; THIAGO MARTIN 44834604
typedef struct
{
    void* dirI;
    size_t ce;
    size_t tam;
    size_t tamTD;
} tVector;

typedef void (*accion_ALU)(void*);
typedef int (*cpm_ALU)(void*, void*);
typedef void (*Actualizar_ALU)(void*, void*);
///Primitivas de TDA VECTOR
int tVectorCrear_ALU(tVector* vec, size_t tamElem, int cant);
int tVectorInsertarAlFinal_ALU(tVector* vec, void* elem);
int tVectorInsertarOrdenadoyActualizar_ALU(tVector * vec, void* elem, cpm_ALU comp, Actualizar_ALU fusionar);
void tVectorMostrar_ALU(tVector* vec, accion_ALU mostrar);
void tVectorDestruir_ALU(tVector* vec);
void* busquedaBinaria_ALU(tVector* vecVentas, void* elem, cpm_ALU comp);
///Funciones particulares
void mostrarIdx_ALU(void* a);
void mostrarVentas_ALU(void* i);
void mostrarClientes_ALU(void* a);
int compararVentas_ALU(void* a, void* b);
int compararBusquedaBin_ALU(void* a, void* b);
int compararOrdenamiento_ALU(void* a, void* b);

///Ordenamiento
void intercambiar_ALU(void* a, void*b, size_t tamTD);
void ordenarSeleccionGen_ALU(tVector* vec, cpm_ALU comparacion);
void* buscarMm_ALU(void* inicio, void* fin, size_t tamTD, cpm_ALU comparacion);
///PARCIAL
int bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas);
void listarClientesOrdXBonifDesc_ALU(const char* clientes);

int main()
{
    generarArchivoClientes();
    generarIndiceArchivoClientes();
    generarArchivoVentas();

    mostrarArchivoClientes();
    puts("\n");

    mostrarArchivoVentas();
    puts("\n");


    bonificarClientes_ALU("Clientes.dat", "Clientes.idx", "Ventas.dat");
    //bonificarClientes("Clientes.dat", "Clientes.idx", "Ventas.dat");

	puts("Clientes Bonificados");
	mostrarArchivoClientes();
	puts("\n");

    listarClientesOrdXBonifDesc_ALU("Clientes.dat");
    //listarClientesOrdXBonifDesc("Clientes.dat");

    return 0;
}
int tVectorCrear_ALU(tVector* vec, size_t tamElem, int cant)
{
    void* direccion = malloc(cant * tamElem);
    if (!direccion)
    {
        printf("No se pudo reservar memoria\n");
        return SIN_MEM;
    }
    vec->dirI = direccion;
    vec->ce = 0;
    vec->tam = cant;
    vec->tamTD = tamElem;
    return TODO_OK;
}
int tVectorInsertarAlFinal_ALU(tVector* vec, void* elem)
{
    void* dirAInsertar = vec->dirI + vec->ce * vec->tamTD; ///inserto al final
    if(vec->ce == vec->tam)
    {
        size_t nuevoCap = vec->tam * 2;
        void* aux = realloc(vec->dirI, nuevoCap * vec->tamTD);
        if(!aux)
            return SIN_MEM;
        vec->dirI = aux;
        vec->tam = nuevoCap;
    }
    memcpy(dirAInsertar, elem, vec->tamTD);
    vec->ce++;
    return TODO_OK;
}
void tVectorDestruir_ALU(tVector* vec)
{
    free(vec->dirI);
}
void mostrarIdx_ALU(void* a)
{
    Indice ind = *(Indice*)a;
    printf("%d | %s\n", ind.nroReg, ind.codCliente);
}
void tVectorMostrar_ALU(tVector* vec, accion_ALU mostrar)
{

}

int compararVentas_ALU(void* a, void* b)
{
    Venta *aux1 = (Venta*)a;
    Venta *aux2 = (Venta*)b;
    return strcmpi(aux1->codCliente, aux2->codCliente);
}

void actualizarVentas_ALU(void* i, void* elem)
{

    return;

}

int tVectorInsertarOrdenadoyActualizar_ALU(tVector * vec, void* elem, cpm_ALU comp, Actualizar_ALU fusionar)
{

    return TODO_OK;
}
int compararBusquedaBin_ALU(void* a, void* b)
{
    char *cod = (char*)a;

    Indice aux = *(Indice*)b;
    return strcmpi(cod, aux.codCliente);
}

void* busquedaBinaria_ALU(tVector* vecVentas, void* elem, cpm_ALU comp)
{

    return NULL;
}

void mostrarVentas_ALU(void* i)
{

}

int bonificarClientes_ALU(const char* clientes, const char* clientesInd, const char* ventas)
{

    return TODO_OK;
}

void* buscarMm_ALU(void* inicio, void* fin, size_t tamTD, cpm_ALU comparacion)
{

}

void intercambiar_ALU(void* a, void*b, size_t tamTD)
{

}
void ordenarSeleccionGen_ALU(tVector* vec, cpm_ALU comparacion)
{

}


int compararOrdenamiento_ALU(void* a, void* b)
{
}
void mostrarClientes_ALU(void* a)
{
}
void listarClientesOrdXBonifDesc_ALU(const char* clientes)
{
/// Inserte el codigo aca ...

}
