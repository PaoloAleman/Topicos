#include <funciones.h>

int actualizarComponentes_ALU(const char* pathComponentes)
{
///	Resolver.
/// Nota: Resuelva esta, y todas las funciones que necesite, en este archivo. Que ser� el que debe entregar. No modifique ni entregue otro/s archivos del proyecto.
/// Agregue el sufijo "_ALU" a todas las funciones que genere.
    FILE* archivo = fopen(pathComponentes, "r+b");
    if(archivo == NULL){
        printf("Error al abrir el archivo de componentes");
        return;
    }

    Vector armaReps;
    vectorCrear_ALU(&armaReps, sizeof(ArmaRep));
    cargarArmaRepEnVector_ALU(&armaReps);

    Vector indices;
    vectorCrear_ALU(&indices, sizeof(IndComponente));
    cargarVectorComponentesIdx_alu("Componentes.idx", &indices);

    Componente componente;
    int encontrado;
    int cantidad;

    for(size_t i = 0; i < indices.ce; i++){
        IndComponente* indComponente = (IndComponente*) vectorElemPos(&indices, i);
        encontrado = 0;
        cantidad = 0;

        for(size_t j = 0; j < armaReps.ce && !encontrado; j++){
            ArmaRep* armaRep = (ArmaRep*) vectorElemPos(&armaReps, j);

            if(strcmp(armaRep->codigo, indComponente->codigo) == 0){
                encontrado = 1;
                cantidad = armaRep->cantidad;
            }
        }

        if(encontrado){
            fseek(archivo, indComponente->nroReg * sizeof(Componente), SEEK_SET);
            fread(&componente, sizeof(Componente), 1, archivo);
            componente.stock -= cantidad;
            fseek(archivo, -1 * sizeof(Componente), SEEK_CUR);
            fwrite(&componente, sizeof(Componente), 1, archivo);
            fflush(archivo);
        }
    }

    fclose(archivo);
    vectorDestruir_alu(&armaReps);
    vectorDestruir_alu(&indices);
    return TODO_OK;


}

void cargarVectorComponentesIdx_alu(char* pathComponentesIdx, Vector* vector){
    FILE* archivo=fopen(pathComponentesIdx,"rb");

    if(!archivo)
    {
        puts("ERROR ARCHIVO COMPONENTES IDX");
    }

    IndComponente indComponente;

    while(fread(&indComponente,sizeof(IndComponente),1,archivo) == 1){
        vectorInsertarAlFinal_ALU(vector, &indComponente);
    }

    fclose(archivo);
}

void cargarArmaRepEnVector_ALU(const char* pathArmYRepTxt, Vector* vec){
    FILE* archivo = fopen(pathArmYRepTxt, "r");

    if(archivo == NULL){
        printf("Error al abrir el archivo de Armado y Reparaciones");
        return;
    }

    char cadena[100];
    ArmaRep buffer;

    while(fgets(cadena, 100, archivo)){
        if(trozado_alu(cadena, &buffer)){
            vectorOrdInsertar(&vec, buffer, cmpMovArmaRep_ALU, actualizarMovArmaRep_ALU);
        }
    }
    fclose(archivo);
}

int cmpMovArmaRep_ALU(const void* a, const void* b){
    ArmaRep* ar1 = (ArmaRep*) a;
    ArmaRep* ar2 = (ArmaRep*) b;
    return strcmp(ar1->codigo, ar2->codigo);
}

void actualizarMovArmaRep_ALU(void* existente, const void* nuevo){
    ArmaRep* ar1 = (ArmaRep*) existente;
    const ArmaRep* ar2 = (const ArmaRep*) nuevo;
    ar1->cantidad += ar2->cantidad;
    ar1->precio = ar2->precio;
}

bool trozado_alu(char* cad, ArmaRep* buffer){
    char* aux;
    aux = strchr(cad, '\n');
    *aux = '\0';

    aux = strrchr(cad, '|');
    sscanf(aux+1, "%d", &(buffer->precio));
    *aux='\0';

    aux = strrchr(cad, '|');
    sscanf(aux+1, "%d", &(buffer->cantidad));
    *aux='\0';

    aux = strrchr(cad, '|');
    strcpy(buffer->codigo, aux+1);
    *aux = '\0';

    sscanf(cad, "%d", &(buffer->numeroOperacion));

    return true;
}

int vectorCrear_ALU(Vector* vec, size_t tamElem){
    vec->tamElem = tamElem;
    vec->vec = malloc(100 * tamElem);
    vec->ce = 0;
    vec->cap = 100;
    return 0;
}

void vectorDestruir_alu(Vector* vec){
    vec->cap = 0;
    vec->ce = 0;
    vec->tamElem = 0;
    free(vec->vec);
}

int vectorInsertarAlFinal_ALU(Vector* vec, const void* elemento){
    if(vec->ce == vec->cap){
        vec->cap *= 2;
        void* aux = realloc(vec->vec, vec->cap * vec->tamElem);
        if(!aux) return 0;
        vec->vec = aux;
    }

    memcpy((char*)vec->vec + vec->ce * vec->tamElem, elem, vec->tamElem);
    vec->ce++;
    return 1;
}

void* vectorElemPos(const Vector* v, unsigned pos) {
    return (char*)v->vec + pos * v->tamElem;
}

int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp, Actualizar actualizar)
{
    char* inicio = (char*)vector->vec;
    char* fin = inicio + vector->ce * vector->tamElem;
    char* actual = inicio;

    // Buscar posición ordenada o elemento existente
    while (actual < fin) {
        int comparacion = cmp(elem, actual);

        if (comparacion == 0) {
            // Ya existe → actualizo
            if (actualizar)
                actualizar(actual, elem);
            return TODO_OK;
        }

        if (comparacion < 0)
            break; // Encontramos dónde insertar

        actual += vector->tamElem;
    }

    // Verificar si hay easpacio
    if (vector->ce == vector->cap)
        return SIN_MEMORIA;

    // Mover elementos a la derecha para hacer lugar
    memmove(actual + vector->tamElem, actual, fin - actual);

    // Copiar nuevo elemento en su lugar
    memcpy(actual, elem, vector->tamElem);

    vector->ce++;
    return TODO_OK;
}
