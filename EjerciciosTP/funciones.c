#include "funciones.h"

void insertarNumero(int numeros[], int numero, int tamanio){
    int insertado=0, i = 0;
    while(insertado == 0 && i < tamanio){
        if(numeros[i] == 0){
            numeros[i] = numero;
            insertado = 1;
        }
        i++;
    }
}

void recorrerArrayDeEnteros(int numeros[], int tamanio){
    printf("Lista de numeros:\n");
    for(int i = 0; i < tamanio; i++){
        printf("Numero %d -> %d\n", i+1 , numeros[i]);
    }
}

void insertarEnDeterminadaPosicion(int numeros[], int numero, int posicion){
    do{
        printf("Ingrese la posicion en el array de enteros (1-5):");
        scanf("%d", &posicion);
        if(posicion < 1 || posicion > 5){
            printf("Posición inválida\n");
        }
    }while(posicion < 1 || posicion > 5);
    numeros[posicion - 1] = numero;
}

void solicitarNumero(int *numero){
    printf("Ingrese un numero para insertar en el array de enteros:");
    scanf("%d", numero);
}

void insertarNumeroOrdenado(int numeros[], int numero, int tamanio){
    int insertado = 0, i = 0;
    while(insertado == 0 && i < tamanio){
        if(numero < numeros[i] || i == tamanio - 1){
            numeros[i] = numero;
            insertado = 1;
        }
        i++;
    }
}

int contarApariciones(char *texto, char *palabra){
    if (!texto || !palabra) return 0;

    int apariciones = 0;
    size_t len = strlen(palabra);
    if (len == 0) return 0;

    char *p = texto;              // puntero que recorre el texto
    char *inicio = texto;         // guarda el inicio para comprobar límites

    while (*p) {
        if (strncmp(p, palabra, len) == 0) {
            // comprobar límite izquierdo: p es inicio del texto o el anterior NO es alfanumérico
            int left_ok = (p == inicio) || !isalnum((unsigned char)*(p - 1));
            // comprobar límite derecho: el carácter después de la palabra NO es alfanumérico
            int right_ok = !isalnum((unsigned char)*(p + len));
            if (left_ok && right_ok) {
                apariciones++;
            }
        }
        p++; // avanzamos un carácter (permite solapamiento)
    }

    return apariciones;
}

char* copiaCadena(const char* origen) {
    int longitud = strlen(origen); // ✔ strlen recibe un const char*, no *origen
    char *nuevaCadena = (char*) malloc((longitud + 1) * sizeof(char)); // ✔ +1 para '\0'
    if (nuevaCadena == NULL) {
        return NULL; // ✔ buena práctica: controlar error de memoria
    }

    strcpy(nuevaCadena, origen); // ✔ copia el contenido de origen en la nueva cadena
    return nuevaCadena; // ✔ devolvés el puntero, no el contenido
}

void* copiaCosas(void* origen, unsigned tam) {
    void* copia = malloc(tam); // ✔ reserva la cantidad de bytes indicada
    if (copia == NULL) {
        return NULL; // ✔ controlar error de memoria
    }

    memcpy(copia, origen, tam); // ✔ copia byte a byte los datos
    return copia; // ✔ devuelve la dirección del nuevo bloque
}

int mostrarMenu(){
    int opcion = 0;
    do{
        printf("Seleccione una opción\n1. Buscar el mínimo elemento\n2.Calcular el promedio de los valores de las posiciones pares\n3.Mostrarlo en orden inverso\n4.Salir\n");
        scanf("%d", &opcion);
        if(opcion < 0 || opcion > 5){
            printf("Opcion invalida\n");
        }
    }while(opcion != 4);
    return opcion;
}

int cargarFloats(float numeros[], int maximo){
    float valor;
    int contador = 0;
    printf("Ingrese hasta %d numeros (-1 para terminar):\n", maximo);

    float *p = numeros;

    while(p < numeros + maximo && valor != -1){
        printf("Valor %d:", contador + 1);
        scanf("%f", valor);
        if(valor != -1){
            contador++;
        }
        p++;
    }
    return contador;
}

void recorrerArrayDeFloats(float numeros[], int tamanio){
    for(float *p = numeros; p < numeros + tamanio; p++){
        printf("Número -> %f\n", p);
    }
}
