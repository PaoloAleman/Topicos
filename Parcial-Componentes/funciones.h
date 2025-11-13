#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {
    char codigo[21];
    char descripcion[51];
    int stock;
    float precio;
} Componente;

typedef struct {
    int numeroOperacion;
    char codigo[21];
    int cantidad;
    float precio;
} ArmaRep;

typedef struct {
    void* vec;
    size_t tamElem;
    size_t ce;
    size_t cap;
} Vector;

typedef struct
{
    char codigo[21];
    int nroReg;
}
IndComponente;

typedef void (*Actualizar)(void* actualizado, const void* actualizador);

void cargarVectorComponentesIdx_alu(char* pathComponentesIdx, Vector* vector);
void cargarArmaRepEnVector_ALU(const char* pathArmYRepTxt, Vector* vec);
int actualizarComponentes_ALU(const char* pathComponentes, const char* pathArmadoYRep);
bool trozado_alu(char* cad,ArmadoYRep* buffer);
int vectorCrear_ALU(Vector* vec, size_t tamElem);
void vectorDestruir_alu(Vector* vec);
int vectorInsertarAlFinal_ALU(Vector* vec, const void* elemento);
int vectorOrdInsertar(Vector* vector, const void* elem, Cmp cmp, Actualizar actualizar);
#endif // FUNCIONES_H_INCLUDED
