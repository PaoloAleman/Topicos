/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres: Fernandez, Mario
*
* DNI: 39.912.991
*
****************************************************************************************/

#include <locale.h>
#include <windows.h>
#include <stdio.h>
#include <TiposArmadoPC.h>
#include <SolucionParcialArmadoPC.h>

#define ARG_PATH_COMP 1
#define ARG_PATH_ARM_REP 2
#define TAM_LINEA 50
#define TAM_VEC 100

int actualizarComponentes_alu(const char* nombreComponentes, const char* nombreArmadoYRep);
int convertirArmYRepTxtABin_alu(const char* pathArmYRepTxt, const char* pathArmYRepBin);
void obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx);
void cargarArmadosYRepEnVector_alu(const char* pathArmYRepTxt, Vector* vec);
int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep);
bool trozado_alu(char* cad,ArmadoYRep* buffer);
int vectorCrear_ALU(Vector* vec, size_t tamElem);
void vectorDestruir_alu(Vector* vec);

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "spanish");	// Cambiar locale - Suficiente para máquinas Linux
    SetConsoleCP(1252); 			// Cambiar STDIN -  Para máquinas Windows
    SetConsoleOutputCP(1252);		// Cambiar STDOUT - Para máquinas Windows

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
    ///******** Descomente la línea de abajo y comente la de arriba para probar su código **********************
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


int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que será el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_ALU" a todas las funciones que genere.

    convertirArmYRepTxtABin_alu(pathArmadoYRep,"ArmadosYReparaciones.dat");
    obtenerPathIdx_alu(pathComponentes,"Componentes.idx");

    Vector vecAyR;
    vectorCrear_ALU(&vecAyR,sizeof(ArmadoYRep));
    cargarArmadosYRepEnVector_alu(pathArmadoYRep,&vecAyR);

    Vector vecIdx;
    vectorCrear_ALU(&vecIdx,sizeof(IndComponente));
    cargarVectorIdx("Componentes.idx",&vecIdx);

    //no llego con el tiempo

    vectorDestruir_alu(&vecAyR);
    return TODO_OK;


}

void cargarVectorIdx(const char* pathArchIdx, Vector* vec)
{
    FILE* archIdx=fopen(pathComponentesIdx,"rb");

    if(!archCompIdx)
    {
        puts("ERROR ARCHIVO IDX");
    }

    IndComponente buffer;
     while(fread(&buffer,sizeof(IndComponente),1,archIdx))
    {
      memcpy(vec->vec,&buffer,sizeof(IndComponente));
      vec->vec+=vec->tamElem;
    }

}
void cargarArmadosYRepEnVector_alu(const char* pathArmYRepTxt, Vector* vec)
{
    FILE* archaArmyRep=fopen(pathArmYRepTxt,"rt");

    if(!archaArmyRep)
    {
        puts("ERROR ARCHIVO ARCHIVO ARMADO Y REPARACIONES");
    }

    char cadena[TAM_LINEA];
    ArmadoYRep buffer;
    vectorCrear(vec,sizeof(ArmadoYRep));

    while(fgets(cadena,TAM_LINEA,archaArmyRep))
    {
        if(trozado_alu(cadena,&buffer)==true)
        {
            memcpy(vec->vec,&buffer,sizeof(ArmadoYRep));
            vec->vec+=vec->tamElem;
            vec->ce++;
        }
    }

    fclose(archaArmyRep);
}

int convertirArmYRepTxtABin_alu(const char* pathArmYRepTxt, const char* pathArmYRepBin)
{
    FILE* archaArmyRep=fopen(pathArmYRepTxt,"rt");

    if(!archaArmyRep)
    {
        puts("ERROR ARCHIVO ARCHIVO ARMADO Y REPARACIONES");
        return ERROR;
    }


    FILE* archaArmyRepBin=fopen(pathArmYRepBin,"wb");

    if(!archaArmyRepBin)
    {
        puts("ERROR ARCHIVO ARCHIVO ARMADO Y REPARACIONES BINARIO");
        fclose(archaArmyRep);
        return ERROR;
    }

    char cadena[TAM_LINEA];
    ArmadoYRep buffer;

    while(fgets(cadena,TAM_LINEA,archaArmyRep))  //convertir el archivo de ArmYrep a BINARIO.
    {
        if(trozado_alu(cadena,&buffer)==true)
            fwrite(&buffer,sizeof(ArmadoYRep),1,archaArmyRepBin);
    }

    fclose(archaArmyRep);
    fclose(archaArmyRepBin);
    return TODO_OK;
}

void obtenerPathIdx_alu(const char* pathComponentes, char* pathComponentesIdx)
{
    FILE* archCompIdx=fopen(pathComponentesIdx,"wb");

    if(!archCompIdx)
    {
        puts("ERROR ARCHIVO COMPONENTES IDX");
    }

    FILE* archComp=fopen(pathComponentes,"rb");

    if(!archComp)
    {
        puts("ERROR ARCHIVO COMPONENTES");
        fclose(archCompIdx);
    }

    Componente varCom;
    IndComponente varIdx;
    int contReg=0;

    while(fread(&varCom,sizeof(Componente),1,archComp))
    {
        strcpy(varIdx.codigo,varCom.codigo);
        varIdx.nroReg=contReg;
        contReg++;
        fwrite(&varIdx,sizeof(IndComponente),1,archCompIdx);
    }

    fclose(archComp);
    fclose(archCompIdx);
}

int vectorCrear_ALU(Vector* vec, size_t tamElem)
{
    vec->vec=malloc(TAM_VEC*tamElem);
    vec->ce=0;
    vec->tamElem=tamElem;
    vec->cap=TAM_VEC;

    return TODO_OK;
}

void vectorDestruir_alu(Vector* vec)
{
    vec->cap=0;
    vec->ce=0;
    vec->tamElem=0;
    free(vec->vec);
}

bool trozado_alu(char* cad,ArmadoYRep* buffer) //   1|MEMCORSAIR8GB|2|39,00
{
    char* aux;
    aux=strchr(cad,'\n');
    *aux='\0';

    aux=strrchr(cad,'|');
    sscanf(aux+1,"%lf",&(buffer->precioUnitario));
    *aux='\0';

    aux=strrchr(cad,'|');
    sscanf(aux+1,"%d",&(buffer->cantidad));
    *aux='\0';

    aux=strrchr(cad,'|');
    strcpy(buffer->codigo,aux+1);
    *aux='\0';

    sscanf(cad,"%d",&(buffer->nroOp));

    return true;
}
