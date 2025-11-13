#include <stdio.h>
#include <stdlib.h>
#include <funciones.h>

int main()
{
    generarArchivoStockComponentes(argv[ARG_PATH_COMP]);

    generarArchivoArmadosYReparaciones(argv[ARG_PATH_ARM_REP]);

    puts("Componentes antes de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
    puts("");

    puts("Armados/Reparaciones:");
    mostrarArchivoArmadoYRep(argv[ARG_PATH_ARM_REP]);
    puts("");

    ///*********************************************************************************************************
    int resp = actualizarComponentes(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///******** Descomente la l�nea de abajo y comente la de arriba para probar su c�digo **********************
//    int resp = actualizarComponentes_ALU(argv[ARG_PATH_COMP], argv[ARG_PATH_ARM_REP]);
    ///*********************************************************************************************************

    if(resp != TODO_OK)
    {
        puts("Error actualizando los componentes.");
        return resp;
    }

    puts("\nComponentes despues de actualizar:\n");
    mostrarArchivoComponentes(argv[ARG_PATH_COMP]);
    return 0;
}
