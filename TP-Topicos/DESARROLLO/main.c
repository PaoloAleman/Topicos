#include "funciones.h"
int main() {
    int err=TODO_OK;
    
    /*EJ 1,2,3,4*/
    err = actualizarArchivoDivisiones("serie_ipc_divisiones.csv","arch_temporal.csv");
    if(err == TODO_OK)
    {
        printf("\nARCHIVO DE DIVISIONES ACTUALIZADO CORRECTAMENTE\n");
        /*EJ5*/
        printf("\nCALCULAR AJUSTE POR INFLACION\n");
        calcularMontoAjustadoPorIPC("serie_ipc_divisiones.csv");
    }
    /*EJ 6*/
    Vector vector;
    err = vectorCrear(&vector, sizeof(Clasificacion));
    if(err == TODO_OK)
    {
        printf("\nINDICE IPC POR GRUPOS (BIENES | SERVICIOS)\n");
        calcularIPCPorGrupos("serie_ipc_divisiones.csv", &vector);
        vectorDestruir(&vector);
    }
    /*EJ 7,8*/
    err = actualizarArchivoAperturas("serie_ipc_aperturas.csv","arch_temporal.csv");

    /*EJ 9*/
    if(err == TODO_OK)
    {
        printf("\nCALCULAR AJUSTE ALQUILER\n");
        calcularAjusteAlquiler("serie_ipc_aperturas.csv");
    }
    return 0;
}
int obtenerNumeroMes(const char *mesTexto) {
    const char *meses[] = {
        "enero", "febrero", "marzo", "abril", "mayo", "junio",
        "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"
    };

    const char **ptr = meses;
    int numero = 1;

    while (numero <= 12) {
        if (strcmpi(mesTexto, *ptr) == 0)
            return numero;
        ptr++;
        numero++;
    }
    return 0;
}


void solicitarMonto(float *monto) {
    printf("Ingrese el monto a evaluar:");
    scanf("%f", monto);
    fflush(stdin);
}

void solicitarRegion(char *region) {
    int idRegion;
    do {
        printf("Ingrese la region:\n"
           "1. Nacional\n"
           "2. GBA\n"
           "3. Pampeana\n"
           "4. Cuyo\n"
           "5. Noroeste\n"
           "6. Noreste\n"
           "7. Patagonia");
        scanf("%d", &idRegion);
        fflush(stdin);
        if (idRegion < 1 || idRegion > 7)
            printf("Valor invalido\n");
    }while (idRegion < 1 || idRegion > 7);

    switch (idRegion) {
        case 1: strcpy(region, "Nacional"); break;
        case 2: strcpy(region, "GBA"); break;
        case 3: strcpy(region, "Pampeana"); break;
        case 4: strcpy(region, "Cuyo"); break;
        case 5: strcpy(region, "Noroeste"); break;
        case 6: strcpy(region, "Noreste"); break;
        case 7: strcpy(region, "Patagonia"); break;
        default: strcpy(region, "Invalido"); break;
    }
}

void solicitarFecha(int *fecha) {
    printf("Ingrese la fecha con formato aaaamm: ");
    scanf("%d", fecha);
}

// 6 Evolución del IPC por grupos 
void calcularIPCPorGrupos(const char* nomArchivo_ipc, Vector* grupos) {
    FILE* fPArchIpc = fopen(nomArchivo_ipc,"r");
    if(!fPArchIpc)
    {
        puts("ERROR PARA ABRIR ARCHIVO DE DIVISIONES");
        return;
    }
    char buffer[500];
    fgets(buffer, sizeof(buffer), fPArchIpc);
    RegistroIPC reg;
    Clasificacion clasificacion;
    while (fgets(buffer, sizeof(buffer), fPArchIpc)) {
        if (trozarLineaDivisiones(buffer, &reg)) {
            if (strcmpi(reg.region, "nacional") == 0) {
                clasificacion.periodo = convertirFechaStringAInt(reg.periodo);
                strcpy(clasificacion.descripcion, reg.descripcion);
                clasificacion.indice_ipc = atof(reg.indice_ipc);
                strcpy(clasificacion.region, reg.region);
                clasificarGrupo(reg.descripcion, clasificacion.grupo);
                vectorInsertar(grupos, &clasificacion);
            }
        }
    }
    mostrarPromedios(grupos);

    fclose(fPArchIpc);
}
void clasificarGrupo(const char* descripcion, char *grupo) {
    if (strcmpi(descripcion, "alimentos y bebidas no alcohólicas") == 0 ||
        strcmpi(descripcion, "bebidas alcohólicas y tabaco") == 0 ||
        strcmpi(descripcion, "prendas de vestir y calzado") == 0 ||
        strcmpi(descripcion, "bienes y servicios varios") == 0 ||
        strcmpi(descripcion, "equipamiento y mantenimiento del hogar") == 0) {
        strcpy(grupo, "Bienes");
    } else if (strcmpi(descripcion, "recreación y cultura") == 0 ||
        strcmpi(descripcion, "restaurantes y hoteles") == 0 ||
        strcmpi(descripcion, "salud") == 0 ||
        strcmpi(descripcion, "transporte") == 0 ||
        strcmpi(descripcion, "educación") == 0 ||
        strcmpi(descripcion, "comunicación") == 0 ||
        strcmpi(descripcion, "vivienda, agua, electricidad, gas y otros combustibles") == 0) {
        strcpy(grupo, "Servicios");
    } else {
        strcpy(grupo, "Otro");
    }
}
void mostrarPromedios(Vector* grupos) {
    int periodoActual = 0;
    double sumaBienes = 0, sumaServicios = 0;
    int cantBienes = 0, cantServicios = 0;

    Clasificacion* clasificacion = grupos->vector;

    for (size_t i = 0; i < grupos->cantidadElementos; i++) {
        if (periodoActual != clasificacion[i].periodo && periodoActual != 0) {
            printf("\nPeriodo %d -> Bienes: %.2f | Servicios: %.2f",
                   periodoActual,
                   cantBienes ? sumaBienes / cantBienes : 0,
                   cantServicios ? sumaServicios / cantServicios : 0);

            sumaBienes = sumaServicios = 0;
            cantBienes = cantServicios = 0;
        }

        periodoActual = clasificacion[i].periodo;

        if (strcmpi(clasificacion[i].grupo, "Bienes") == 0) {
            sumaBienes += clasificacion[i].indice_ipc;
            cantBienes++;
        } else if (strcmpi(clasificacion[i].grupo, "Servicios") == 0) {
            sumaServicios += clasificacion[i].indice_ipc;
            cantServicios++;
        }
    }

    if (cantBienes + cantServicios > 0) {
        printf("\nPeriodo %d -> Bienes: %.2f | Servicios: %.2f\n",
               periodoActual,
               cantBienes ? sumaBienes / cantBienes : 0,
               cantServicios ? sumaServicios / cantServicios : 0);
    }
}

int actualizarArchivoAperturas(const char* nomArchAper,const char* nomArchAperTemp)
{
    FILE* archivo_ipc_aperturas = fopen(nomArchAper, "r");
    if (!archivo_ipc_aperturas) {
        puts("Error al abrir el archivo de aperturas");
        return 1;
    }
    FILE* archivo_ipc_aperturas_actualizado = fopen(nomArchAperTemp, "w");
    if (!archivo_ipc_aperturas_actualizado) {
        fclose(archivo_ipc_aperturas);
        puts("Error al crear el archivo actualizado");
        return 1;
    }
    char linea[256];
    RegistroIPC reg;
    fgets(linea, sizeof(linea), archivo_ipc_aperturas);
    fprintf(archivo_ipc_aperturas_actualizado, "%s", linea);

    while (fgets(linea, sizeof(linea), archivo_ipc_aperturas))
    {
        trozarLineaAperturas(linea,&reg);

        //Ejercicio 7
        convertirFormatoFecha(reg.periodo);
        //Ejercicio 8
            //Se reutiliza la funcion del punto 4
        convertirComaAPunto(reg.indice_ipc);
        
        fprintf(archivo_ipc_aperturas_actualizado,"%s;%s;%s;%s;%s;%.2f;%.2f;%s\n",reg.codigo,reg.descripcion,reg.clasificador,reg.periodo,reg.indice_ipc,reg.variacion_mensual,reg.variacion_interanual,reg.region);
    }

    fclose(archivo_ipc_aperturas);
    fclose(archivo_ipc_aperturas_actualizado);
    remove(nomArchAper);
    rename(nomArchAperTemp,nomArchAper);
    return TODO_OK;
}
// 7
    // Función para convertir AAAAMM → AAAA-MM-DD
void convertirFormatoFecha(char *periodo)
{
    char anio[5];
    char mes[3];

    strncpy(anio, periodo, 4);
    anio[4] = '\0';
    strncpy(mes, periodo + 4, 2);
    mes[2] = '\0';

    sprintf(periodo, "%s-%s-01", anio, mes);
}

// 8 // Se reutiliza la función del punto 4

// 9
void calcularAjusteAlquiler(const char* nomArchAperturas) {
    float monto;
    char region[10];
    int fechaInicio;
    double ipcInicio = 0, ipcMax = 0;
    char fechaMaxStr[11]="";

    FILE* archivo_aperturas = fopen(nomArchAperturas, "r");
    if (archivo_aperturas == NULL) {
        printf("\nError al abrir el archivo serie_ipc_aperturas.csv");
        return;
    }

    solicitarMonto(&monto);
    solicitarRegion(region);
    printf("--- Ingrese el Periodo de Inicio de Contrato ---\n");
    solicitarFecha(&fechaInicio);
    char fechaIniStr[11];
    sprintf(fechaIniStr, "%d-%02d-01", fechaInicio / 100, fechaInicio % 100);

    char buffer[500];
    RegistroIPC ra;
    RegistroIPC registros_encontrados[MAX_MESES_REPORTE];
    int count = 0;
    int encontradoInicio = 0;

    fgets(buffer, sizeof(buffer), archivo_aperturas); // Saltar encabezado

    while (fgets(buffer, sizeof(buffer), archivo_aperturas)) {
        if (trozarLineaAperturas(buffer, &ra)) {
            if (strcmpi(ra.descripcion, FILTRO_DESCRIPCION_ALQUILER) == 0 && strcmpi(ra.region, region) == 0) {

                if (strcmp(ra.periodo, fechaIniStr) == 0) {
                    ipcInicio = atof(ra.indice_ipc);
                    encontradoInicio = 1;
                }

                if (encontradoInicio && count < MAX_MESES_REPORTE) {
                    registros_encontrados[count++] = ra;


                    if (strcmp(ra.periodo, fechaMaxStr) > 0) {
                        strcpy(fechaMaxStr, ra.periodo);
                        ipcMax = atof(ra.indice_ipc);
                    }
                }
            }
        }
    }
    fclose(archivo_aperturas);

    if (ipcInicio == 0 || count == 0) {
        printf("Error: No se pudo encontrar el indice de inicio para la region y fecha dadas.\n");
        return;
    }

    double montoAjustadoTotal = monto * (ipcMax / ipcInicio);
    double variacionTotal = ((ipcMax / ipcInicio)-1) * 100;

    printf("\n--- Calculadora de Alquileres ---\n");
    printf("Monto inicial:       $ %.2f\n", monto);
    printf("Monto ajustado:      $ %.2f\n", montoAjustadoTotal);
    printf("Variacion porcentual:  %.2f %%\n", variacionTotal);

    FILE* archivo_binario = fopen(ARCHIVO_BINARIO_SALIDA, "wb");
    if (archivo_binario == NULL) {
        perror("Error al crear archivo binario de salida");
        return;
    }

    
    //printf("\n--- Detalle Mes a Mes ---\n");
    //printf("-----------------------------------------------------------\n");
    //printf("%-10s %-12s %-12s %-15s\n", "Periodo", "Indice", "Variacion %", "Monto ajustado");
    //printf("-----------------------------------------------------------\n");
    
    FilaTablaAlquiler fila;

    //Iterar sobre los registros guardados para generar la tabla
    for (int i = 0; i < count; i++) {
        ra = registros_encontrados[i];

        // Llenar la struct 'fila' para la tabla
        strncpy(fila.periodo, ra.periodo, 7); //agarro los AAAA-MM
        fila.periodo[7] = '\0';
        fila.indice = atof(ra.indice_ipc);
        //variación y monto contra el índice INICIAL
        fila.variacionPct = ((atof(ra.indice_ipc) / ipcInicio )-1) * 100;
        fila.montoAjustado = monto * (atof(ra.indice_ipc) / ipcInicio);

        fwrite(&fila, sizeof(FilaTablaAlquiler), 1, archivo_binario);
    }

    fclose(archivo_binario);
    leerMostrarTablaBinario(ARCHIVO_BINARIO_SALIDA);
}
void leerMostrarTablaBinario(const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo binario '%s' para lectura.\n", nombreArchivo);
        return;
    }
    printf("-----------------------------------------------------------\n");
    printf("%-10s %-12s %-12s %-15s\n", "Periodo", "Indice", "Variacion %", "Monto ajustado");
    printf("-----------------------------------------------------------\n");

    FilaTablaAlquiler fila;
    // Lee registros del tamaño de la struct FilaTablaAlquiler, 1 a la vez
    while (fread(&fila, sizeof(FilaTablaAlquiler), 1, archivo) == 1) {
        printf("%-10s %-12.2f %-12.2f %-15.2f\n",
               fila.periodo,
               fila.indice,
               fila.variacionPct,
               fila.montoAjustado);
    }
    fclose(archivo);
}
