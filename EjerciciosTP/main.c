#include <stdio.h>
#include <stdlib.h>
#include "funciones.c"

int main(){
    //Ejercicio 1.1
    int numero, posicion, tamanio=5;
    int numeros[5] = {10, 20, 30, 40, 50};
    //solicitarNumero(&numero);

    //insertarEnDeterminadaPosicion(numeros, numero, posicion);

    //recorrerArrayDeEnteros(numeros, 5);

    //Ejercicio 1.2
    //solicitarNumero(&numero);
    //insertarNumeroOrdenado(numeros, numero, tamanio);
    //recorrerArrayDeEnteros(numeros, tamanio);

    //Ejercicio 1.8
    //printf("La palabra '%s' aparece %d veces.\n", "hola", contarApariciones("hola mundo hola gente hola", "hola"));

    //Ejercicio 2.1 y 2.2

    /*
    int cantidad;
    solicitarNumero(&cantidad);
    int *arr = (int*) malloc(cantidad * sizeof(int));
    if (arr == NULL) {
        printf("Error al reservar memoria\n");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        arr[i] = i + 1;
        printf("%d ", arr[i]);
    }
    free(arr);
    return 0;
    */

    //Ejercicio 2.3
    //printf("Cadena copiada -> %s\n", copiaCadena("Hello world!"));
    //printf("Copia -> %s\n", copiaCosas("Hello world!", sizeof(char)));
    float numbers[10];
    int cantidad = cargarFloats(numbers, 10);
    recorrerArrayDeFloats(numbers, 10);

    int opcion = mostrarMenu();

}
