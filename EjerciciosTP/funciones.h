#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

void insertarNumero(int numeros[], int numero, int tamanio);
void recorrerArrayDeEnteros(int numeros[], int tamanio);
void insertarEnDeterminadaPosicion(int numeros[], int numero, int posicion);
void solicitarNumero(int *numero);
void insertarNumeroOrdenado(int numeros[], int numero, int tamanio);
int contarApariciones(char *texto, char *palabra);
char* copiaCadena(const char* origen);
void* copiaCosas(void* origen, unsigned tam);

int cargarFloats(float numeros[], int maximo);
int mostrarMenu();
void recorrerArrayDeFloats(float numeros[], int tamanio);

#endif // FUNCIONES_H_INCLUDED
