/**********************************************************************************************************************
******************************* Complete sus datos ********************************************************************
***********************************************************************************************************************
* Apellido, Nombres: Panasiuk, Fabio
*
* DNI: 
*
***********************************************************************************************************************
 * Correcci�n
***************

***********************************************************************************************************************
 * Nota:
**********************************************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Matriz/Matriz.h"
#include "../Vector/Vector.h"
#include "../SolucionMatrizDepositos/SolucionMatrizDepositos.h"

#define ARG_STOCKS 1
#define ARG_MOVIMIENTOS 2

#define TAM_CRITICO 0.7
#define CRECIMIENTO 1.3

// Prototipos de réplicas de SolucionMatrizDepositos.h
int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos);
int cargarMatrizMovimientosDepositos_ALU(const char* nombreMovimientos, int** matMovDeps, Vector* codigosDepositos);
int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks);
void inicializarMatrizEnCero_ALU(int** matMovDeps, int filas, int columnas);
int crearVectorCodigosDepositos_ALU(const char* nombreStocks, Vector* codigosDepositos);
int cmpCodDep_ALU(const void* e1, const void* e2);

// Prototipos de réplicas de Vector.h
int vectorCantidadElementos_ALU(const Vector* v);
int vectorCargarDeArchivo_ALU(const char* nombreArch, Vector* vector, size_t tamElem);
int vectorOrdBuscar_ALU(const Vector* v, void* elem, Cmp cmp);
int vectorCrear_ALU(Vector* vec, size_t tamElem);
int vectorInsertarAlFinal_ALU(Vector* vector, const void* elem);
void vectorDestruir_ALU(Vector* vec);
int vectorOrdInsertarCDup_ALU(Vector* vector, const void* elem, Cmp cmp);

// Prototipos de réplicas de Matriz.h
void matrizMostrar_ALU(int fil, int col, int** mat);
void** matrizCrear_ALU(int fil, int col, size_t tamElem);
void matrizDestruir_ALU(void** mat, int fil);

// Prototipos de funciones extra (no presentes en los .h dados)
void* vectorObtenerElem_ALU(const Vector* v, int indice);

// Entrada del programa

int main(int argc, char* argv[])
{
	generarStocks(argv[ARG_STOCKS]);
	generarMovimientos(argv[ARG_MOVIMIENTOS]);

	puts("Stocks antes de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

/*********************************************************************************************************************/
	actualizarDepositos_ALU(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/************* Descomente la funci�n de arriba y comente la de abajo para ejecutar su c�digo. ************************/
	// actualizarDepositos(argv[ARG_STOCKS], argv[ARG_MOVIMIENTOS]);
/*********************************************************************************************************************/

	puts("\nStocks despues de actualizar:");
	mostrarStocks(argv[ARG_STOCKS]);

	return 0;
}

// Réplicas de SolucionMatrizDepositos.h

int actualizarDepositos_ALU(const char* nombreStocks, const char* nombreMovimientos){
	/// Resolver. Todas las funciones que desarrolle deber�n tener el sufijo _ALU.
	Vector depos;
	int matTam;
	int** matMovs;

	printf("\n*** EJECUTANDO VERSION _ALU ***\n");

	crearVectorCodigosDepositos_ALU(nombreStocks, &depos);
	matTam = vectorCantidadElementos_ALU(&depos);
	matMovs = (int**)matrizCrear_ALU(matTam, matTam, sizeof(int));

	inicializarMatrizEnCero_ALU(matMovs, matTam, matTam);

	cargarMatrizMovimientosDepositos_ALU(nombreMovimientos, matMovs, &depos);

	printf("\nMatriz de movimientos:\n");
	matrizMostrar_ALU(matTam, matTam, matMovs);

	procesarMatrizMovimientosDepositosActualizandoStocks_ALU(matMovs, &depos, nombreStocks);

	matrizDestruir_ALU((void**)matMovs, matTam);
	vectorDestruir_ALU(&depos);

	return TODO_OK;
}

void inicializarMatrizEnCero_ALU(int** matMovDeps, int filas, int columnas){
	for(int i = 0; i < filas; i++){
		for(int j = 0; j < columnas; j++) {
			matMovDeps[i][j] = 0;
		}
	}
}

int cargarMatrizMovimientosDepositos_ALU(const char* nombreMovimientos, int** matMovDeps, Vector* codigosDepositos){
	Movimiento mov;
	int orig, dest;
	FILE* f = fopen(nombreMovimientos, "r");
	if(!f){
		printf("\nERROR: No se pudo leer el archivo de movimientos.");
		return ERR_ARCHIVO;
	}
	fscanf(f, "%10s%10s%6d", mov.depOrigen, mov.depDestino, &mov.cantidad);
	while(!feof(f)){
		orig = vectorOrdBuscar_ALU(codigosDepositos, mov.depOrigen, cmpCodDep_ALU);
		dest = vectorOrdBuscar_ALU(codigosDepositos, mov.depDestino, cmpCodDep_ALU);
		matMovDeps[orig][dest] += mov.cantidad;
		fscanf(f, "%10s%10s%6d", mov.depOrigen, mov.depDestino, &mov.cantidad);
	}
	return TODO_OK;
}

int procesarMatrizMovimientosDepositosActualizandoStocks_ALU(int** matMovDeps, const Vector* codigosDepositos, const char* nombreStocks){
	Vector stocks;
	int sumaStock, error = 0, elementosActualizados;
	Stock auxStock;
	FILE* f = fopen(nombreStocks, "rb+");
	if(!f){
		printf("\nERROR: No se pudo leer el archivo de stock.");
		return ERR_ARCHIVO;
	}

	error = vectorCrear_ALU(&stocks, sizeof(int));
	if(error != TODO_OK){
		printf("\nERROR: No se ha podido crear el vector [procesarMatrizMovimientosDepositosActualizandoStocks_ALU].");
		fclose(f);
		return error;
	}

	for(int i = 0; i < vectorCantidadElementos_ALU(codigosDepositos); i++){
		sumaStock = 0;
		for(int j = 0; j < vectorCantidadElementos_ALU(codigosDepositos); j++){
			sumaStock += matMovDeps[j][i] - matMovDeps[i][j];
		}
		vectorInsertarAlFinal_ALU(&stocks, &sumaStock);
	}

	// Estoy convencido de que esta logica se puede mejorar, pero como funciona bien voy a seguir avanzando con el resto del examen. Si me da tiempo vuelvo para mejorarlo.
	elementosActualizados = 0;
	while(elementosActualizados < vectorCantidadElementos_ALU(codigosDepositos)){
		fread(&auxStock, sizeof(Stock), 1, f);
		auxStock.stock += *(int*)vectorObtenerElem_ALU(&stocks, vectorOrdBuscar_ALU(codigosDepositos, auxStock.codDeposito, cmpCodDep_ALU));
		fseek(f, -(long)sizeof(Stock), SEEK_CUR);
		fwrite(&auxStock, sizeof(Stock), 1, f);
		fflush(f);
		elementosActualizados++;
	}

	vectorDestruir_ALU(&stocks);
	fclose(f);
	return TODO_OK;
}

int crearVectorCodigosDepositos_ALU(const char* nombreStocks, Vector* codigosDepositos){
	int error = 0;
	FILE* f = fopen(nombreStocks, "rb");
	Stock stock;
	if(!f){
		printf("\nERROR: No se ha podido abrir el archivo \"%s\".", nombreStocks);
		return ERR_ARCHIVO;
	}

	error = vectorCrear_ALU(codigosDepositos, sizeof(stock.codDeposito));
	if(error != TODO_OK){
		printf("\nERROR: No se ha podido crear el vector [crearVectorCodigosDepositos_ALU].");
		return error;
	}

	fread(&stock, sizeof(stock), 1, f);
	while(!feof(f)){
		vectorOrdInsertarCDup_ALU(codigosDepositos, stock.codDeposito, cmpCodDep_ALU);
		fread(&stock, sizeof(stock), 1, f);
	}

	return TODO_OK;
}

int cmpCodDep_ALU(const void* e1, const void* e2){
	char* _e1 = (char*)e1;
	char* _e2 = (char*)e2;
	return strcmp(_e1, _e2);
}

// Réplicas de Vector.h

int vectorCantidadElementos_ALU(const Vector* v){
	if(v == NULL){
		printf("\nERROR: Se intento obtener las dimensiones de un vector inexistente.");
		return 0;
	}
	return v->ce;
}

int vectorCargarDeArchivo_ALU(const char* nombreArch, Vector* vector, size_t tamElem){
	int error = 0;
	FILE* f = fopen(nombreArch, "rb");
	void* elem;
	if(!f){
		printf("\nERROR: No se ha podido abrir el archivo \"%s\".", nombreArch);
		return ERR_ARCHIVO;
	}
	elem = malloc(tamElem);
	if(!elem){
		printf("\nERROR: No se ha podido reservar memoria para el elemento a leer [vectorCargarDeArchivo_ALU]");
		return SIN_MEM;
	}

	error = vectorCrear_ALU(vector, tamElem);
	if(error != TODO_OK){
		printf("\nERROR: No se ha podido crear el vector [vectorCargarDeArchivo_ALU].");
		return error;
	}

	fread(elem, tamElem, 1, f);
	while(!feof(f)){
		vectorInsertarAlFinal_ALU(vector, elem);
		fread(elem, tamElem, 1, f);
	}

	return TODO_OK;
}

int vectorOrdBuscar_ALU(const Vector* v, void* elem, Cmp cmp){
	int res = -1;
	int cmpRes = 0;
	int i = 0;
	while(i < v->ce && res == -1 && cmpRes <= 0){
		cmpRes = cmp(v->vec + (i * v->tamElem), elem);
		if(cmpRes == 0)
			res = i;
		i++;
	}
	return res;
}

int vectorCrear_ALU(Vector* vec, size_t tamElem){
	vec->vec = malloc(tamElem * 10);
	if(!vec->vec){
		printf("\nERROR: No se pudo reservar memoria para crear el vector.");
		return SIN_MEM;
	}
	vec->cap = 10;
	vec->ce = 0;
	vec->tamElem = tamElem;

	return TODO_OK;
}

int vectorInsertarAlFinal_ALU(Vector* vector, const void* elem){
	if(vector->ce > (float)vector->cap * TAM_CRITICO){
		vector->cap *= CRECIMIENTO;
		vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
		if(!vector->vec){
			printf("\nERROR: No se pudo reservar memoria para expandir el vector.");
			return SIN_MEM;
		}
	}
	memcpy(vector->vec + (vector->ce * vector->tamElem), elem, vector->tamElem);
	vector->ce++;

	return TODO_OK;
}

void vectorDestruir_ALU(Vector* vec){
	free(vec->vec);
	vec->ce = 0;
	vec->cap = 0;
	vec->tamElem = 0;
}

int vectorOrdInsertarCDup_ALU(Vector* vector, const void* elem, Cmp cmp){
	int posAInsertar = 0, i;

	if(vector->ce > (float)vector->cap * TAM_CRITICO){
		vector->cap *= CRECIMIENTO;
		vector->vec = realloc(vector->vec, vector->cap * vector->tamElem);
		if(!vector->vec){
			printf("\nERROR: No se pudo reservar memoria para expandir el vector.");
			return SIN_MEM;
		}
	}

	while(cmp(vector->vec + (posAInsertar * vector->tamElem), elem) < 0)
		posAInsertar++;

	vector->ce++;

	for(i = vector->ce; i > posAInsertar; i--)
		memcpy((void*)(vector->vec + (i * vector->tamElem)), (void*)(vector->vec + ((i - 1) * vector->tamElem)), vector->tamElem);

	memcpy((void*)(vector->vec + (posAInsertar * vector->tamElem)), elem, vector->tamElem);

	return TODO_OK;
}

// Réplicas de Matriz.h
void matrizMostrar_ALU(int fil, int col, int** mat){
	for(int i = 0; i < fil; i++){
		for(int j = 0; j < col; j++)
			printf("%02d ", mat[i][j]);
		printf("\n");
	}
}

void** matrizCrear_ALU(int fil, int col, size_t tamElem){
	void** mat = malloc(sizeof(void*) * fil);
	if(mat){
		for(int i = 0; i < col; i++){
			mat[i] = malloc(tamElem * col);
		}
	}

	return mat;
}

void matrizDestruir_ALU(void** mat, int fil){
	for(int i = 0; i < fil; i++){
		free(mat[i]);
	}
	free(mat);
}

// Funciones extra (no presentes en los .h dados)

void* vectorObtenerElem_ALU(const Vector* v, int indice){
	if(v == NULL || indice < 0 || indice > v->ce){
		printf("\nERROR: Se intento obtener un elemento inexistente del vector.");
		return NULL;
	}
	return v->vec + indice * v->tamElem;
}
