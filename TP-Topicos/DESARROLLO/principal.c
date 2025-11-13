#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *vector;

    printf("Ingrese cantidad de elementos: ");
    scanf("%d", &n);

    vector = (int*) malloc(n * sizeof(int));

    if (vector == NULL) {
        printf("No hay memoria disponible\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &vector[i]);
    }

    printf("\nElementos ingresados:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", vector[i]);
    }

    free(vector); // liberar la memoria
    return 0;
}
    