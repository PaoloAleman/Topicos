/***************************************************************************************
******************************* Complete sus datos *************************************
****************************************************************************************
* Apellido, Nombres:
*
* DNI:
*
*
****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <Cadena.h>
#include <Comun.h>
#include <Palabra.h>
#include <SecPal.h>
#include <Vector.h>
#include <Libro.h>
#include <SolucionBiblioteca.h>

#define NOMBRE_ARCH_LIBROS "Libros.dat"
#define NOMBRE_ARCH_LIBROS_INDICE "Libros.idx"
#define NOMBRE_ARCH_MOVIMIENTOS "Movimientos.txt"


bool vectorCrear_ALU(Vector* v, size_t tamElem);
void vectorDestruir_ALU(Vector* v);

int cargarVectorMovimientosLibro_ALU(Vector* vecMovs, const char* nombreArchMov);
int actualizarArchivoLibros_ALU(const char* nombreArchLibros, const char* nombreArchLibrosIndice, Vector* vecMovs);
int normalizarNombresLibros_ALU(const char* nombreArchLibros);
void normalizarPalabra_ALU(char* lectura);

int main()
{
    generarArchMovimientosLibro(NOMBRE_ARCH_MOVIMIENTOS);
	generarArchLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE);

	mostrarLibros(NOMBRE_ARCH_LIBROS);

	Vector vecMovs;
    vectorCrear_ALU(&vecMovs, sizeof(MovLibro));
	///vectorCrear(&vecMovs, sizeof(MovLibro));

	///Debe generar el vector de movimientos, consolidando los movimientos de los libros, a fin de que quede 1 sólo elemento en el vector por cada libro.
	///Aumentando o disminuyendo la cantidad según se trate de una devolución o un préstamo respectivamente.
	///La primitiva vectorOrdInsertar recibe un parámetro adicional, puntero a función Actualizar, para realizar la actualización en caso de que ya exista el elemento.
	///Puede utilizar las funciones resueltas, pero luego deberá reemplazarlas por su propia versión de las mismas.
    cargarVectorMovimientosLibro_ALU(&vecMovs, NOMBRE_ARCH_MOVIMIENTOS);
	///cargarVectorMovimientosLibro(&vecMovs, NOMBRE_ARCH_MOVIMIENTOS);

	///Para test
	puts("Vector movimientos");
	puts("Cod. Libro | Cant.");
	vectorRecorrer(&vecMovs, mostrarMovimientoLibro, NULL);

	puts("");

	///Debe actualizar el archivo binario de Libros, sumando o restando la cantidad.
	///La cantidad en el archivo no puede quedar negativa. Si eso sucede, se deberá descartar el movimiento y continuar con el siguiente.
	///Para acceder a cada registro, debe hacer uso del archivo índice, que tiene cada registro, el código del libro y su ubicación en el archivo(Nro de registro empezando por el 0).
	///Debe cargar el índice en memoria, para trabajar con él.
    actualizarArchivoLibros_ALU(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &vecMovs);
	///actualizarArchivoLibros(NOMBRE_ARCH_LIBROS, NOMBRE_ARCH_LIBROS_INDICE, &vecMovs);

	puts("");

	///Debe normalizar los nombres de los libros en el archivo.
	///Dejando sólo 1 espacio entre palabras, sin espacios ni caracteres antes de la primer palábra y después de la última.
	///Quedando la primer letra de cada palabra en mayúscula y el resto en minúscula.
    normalizarNombresLibros_ALU(NOMBRE_ARCH_LIBROS);
	///normalizarNombresLibros(NOMBRE_ARCH_LIBROS);

	mostrarLibros(NOMBRE_ARCH_LIBROS);

    vectorDestruir_ALU(&vecMovs);
	///vectorDestruir(&vecMovs);
    return 0;
}


bool vectorCrear_ALU(Vector* v, size_t tamElem)
{
    v->vec = malloc(tamElem * 10);

	if(!(v->vec)){
        printf("Error al asignar memoria dinamica\n");
        return 0;
	}

	v->tamElem=tamElem;
	v->ce=0;
	v->cap=10;

	return TODO_OK;
}

int cargarVectorMovimientosLibro_ALU(Vector* vecMovs, const char* nombreArchMov)
{
    FILE* archivo = fopen(nombreArchMov, "r");
    if(archivo == NULL){
        printf("Error al abrir el archivo de movimientos\n");
        return;
    }

    MovLibro movLibro;
    while(fscanf(archivo, "%s[^|]|%s[^|]|%d",&movLibro.codigoLibro, &movLibro.codigoSocio, &movLibro.cantidad)){
        vectorOrdInsertar(&vecMovsm, movLibro, cmpMovLibro_ALU, actualizarMovLibro_ALU);
    }

	fclose(archivo);
	return TODO_OK;
}

///Debe actualizar el archivo binario de Libros, sumando o restando la cantidad.
///La cantidad en el archivo no puede quedar negativa. Si eso sucede, se deberá descartar el movimiento y continuar con el siguiente.
///Para acceder a cada registro, debe hacer uso del archivo índice, que tiene cada registro, el código del libro y su ubicación en el archivo(Nro de registro empezando por el 0).
///Debe cargar el índice en memoria, para trabajar con él.
int actualizarArchivoLibros_ALU(const char* nombreArchLibros, const char* nombreArchLibrosIndice, Vector* vecMovs)
{
	FILE* archivoLibro = fopen(nombreArchLibros, "r+b");
	if(archivoLibro == NULL){
        printf("Error al abrir el archivo de libros\n");
        return;
	}

	FILE* archivoIndice = fopen(nombreArchLibrosIndice, "rb");
	if(archivoIndice == NULL){
        printf("Error al abrir el archivo de libros indice\n");
        return;
	}

	Vector vector;
	vectorCrear_ALU(&vector, sizeof(IndLibro));

	IndLibro indLibro;
	while(fread(&indLibro, sizeof(IndLibro), 1, archivoIndice) == 1){
        vectorInsertarAlFinal(&vector, &indLibro);
	}

	Libro libro;
	int encontrado;
	int cantidad;

	for(size_t i = 0; i < vector.ce; i++){
        IndLibro* indLibro = (IndLibro*) vectorElemPos(&vector, i);
        encontrado = 0;
        cantidad = 0;

        for(size_t j = 0; j < vecMovs->ce && !encontrado; j++){
            MovLibro* movLibro = (MovLibro*) vectorElemPos(vecMovs, j);

            if(strcmp(movLibro->codigoLibro, indLibro->codigo) == 0){
                cantidad = movLibro->cantidad;
                encontrado = 1;
            }
        }

        if(encontrado){
            fseek(archivoLibro, indLibro->nroReg * sizeof(Libro), SEEK_SET);
            fread(&libro, sizeof(Libro), 1, archivoLibro);
            fseek(archivoLibro, -1 * sizeof(Libro), SEEK_CUR);

            libro.cantidad = (libro.cantidad + cantidad < 0) ? libro.cantidad : libro.cantidad+cantidad;

            fwrite(&libro, sizeof(Libro), 1, archivoLibro);
            fflush(archivoLibro);
        }
	}

	fclose(archivoIndice);
	fclose(archivoLibro);
	vectorDestruir_ALU(&vector);

	return TODO_OK;
}


int normalizarNombresLibros_ALU(const char* nombreArchLibros)
{
    FILE* archivo = fopen(nombreArchLibros, "r+b");
    if(archivo == NULL){
        printf("Error al abrir el archivo Libros.dat");
        return;
    }

    Libro libro;

    while(fread(&libro, sizeof(Libro), 1, archivo) == 1){
        normalizarPalabra_ALU(libro.nombre);

        fseek(archivo, -1 * sizeof(Libro), SEEK_CUR);
        fwrite(&libro, sizeof(Libro), 1, archivo);
        fflush(archivo);
    }

    fclose(archivo);

	return TODO_OK;
}


void normalizarPalabra_ALU(char* lectura){
    char* escritura = lectura;
    int nuevaPalabra = 1;

    while(*lectura == ' ' || !isalpha(*lectura)){
        lectura++;
    }

    while(*lectura){
        if(*lectura == ' '){
            if(!nuevaPalabra){
                *escritura++ = ' ';
                nuevaPalabra = 1;
            }
        }else{
            if(nuevaPalabra){
                *escritura++ = toupper(*lectura);
                nuevaPalabra = 0;
            }else{
                *escritura++ = tolower(*lectura);
            }
        }
        lectura++;
    }

    if(escritura > lectura && *(escritura - 1) == ' '){
        escritura--;
    }

    *escritura = '\0';
}

int cmpMovLibro_ALU(const void* a, const void* b){
    const MovLibro* m1 = (const MovLibro*) a;
    const MovLibro* m2 = (const MovLibro*) b;
    return strcmp(m1->codigoLibro, m2->codigoLibro);
}

void actualizarMovLibro_ALU(void* existente, const void* nuevo){
    MovLibro* m1 = (MovLibro*) existente;
    const MovLibro* m2 = (const MovLibro*) nuevo;
    m1->cantidad += m2->cantidad;
}

void vectorDestruir_ALU(Vector* v)
{
    free(v->vec);
    v->vec = NULL;
    v->cap=0;
    v->tamElem=0;
    v->ce=0;
}
