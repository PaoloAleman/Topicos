#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int depOrigen;
    int depDestino;
    char codProd[16];
    int cantidad;
} Transferencia;

typedef struct {
    int nro_dep;
    char cod_prod[16];
    int stock;
} Deposito;

/* ==========================
   SIMULACIÓN DE VECTOR.H
   ========================== */
typedef struct {
    void* vec;
    int ce;
    int cap;
    size_t tamElem;
} Vector;

int vectorCrear(Vector* v, size_t tamElem) {
    v->cap = 10;
    v->ce = 0;
    v->tamElem = tamElem;
    v->vec = malloc(v->cap * tamElem);
    return v->vec ? 1 : 0;
}

void vectorDestruir(Vector* v) {
    free(v->vec);
    v->vec = NULL;
    v->ce = v->cap = 0;
}

int vectorInsertarAlFinal(Vector* v, const void* elem) {
    if (v->ce == v->cap) {
        v->cap *= 2;
        void* aux = realloc(v->vec, v->cap * v->tamElem);
        if (!aux) return 0;
        v->vec = aux;
    }
    memcpy((char*)v->vec + v->ce * v->tamElem, elem, v->tamElem);
    v->ce++;
    return 1;
}

void* vectorElemPos(const Vector* v, unsigned pos) {
    return (char*)v->vec + pos * v->tamElem;
}

/* ==========================
   FUNCIONES DEL PARCIAL
   ========================== */
void desencriptarTransferencias_ALU(const char* archTransferenciasEncr, const char* archTransferenciasDesencr) {
    FILE* archivoEncr = fopen(archTransferenciasEncr, "r");
    if (!archivoEncr) {
        printf("Error al abrir el archivo encriptado\n");
        return;
    }

    FILE* archivoDesencr = fopen(archTransferenciasDesencr, "w");
    if (!archivoDesencr) {
        printf("Error al abrir el archivo desencriptado\n");
        fclose(archivoEncr);
        return;
    }

    char buffer[256];


    while (fgets(buffer, sizeof(buffer), archivoEncr)) {

        buffer[strcspn(buffer, "\n")] = '\0';

        // Invertir la línea
        int len = strlen(buffer);
        for (int i = 0; i < len / 2; i++) {
            char aux = buffer[i];
            buffer[i] = buffer[len - i - 1];
            buffer[len - i - 1] = aux;
        }

        // Desplazar letras 5 lugares hacia atrás
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] > 101 && buffer[i] <= 122)
                buffer[i] -= 5;
            else if (buffer[i] >= 97 && buffer[i] <= 101)
                buffer[i] = 123 - (5 - (buffer[i] - 97));
        }


        fprintf(archivoDesencr, "%s\n", buffer);
    }

    fclose(archivoEncr);
    fclose(archivoDesencr);
}

void actualizarDepositos_ALU(const char* archTransferencias, const char* archDepositos) {

    FILE* archivo = fopen(archDepositos, "r+b");
    if (!archivo) {
        printf("Error al abrir depósitos\n");
        return;
    }

    FILE* archivoTransferencias = fopen(archTransferencias, "r");
    if (!archivoTransferencias) {
        printf("Error al abrir transferencias\n");
        fclose(archivo);
        return;
    }

    Vector vector;
    vectorCrear(&vector, sizeof(Transferencia));
    Transferencia transferencia;


    while (fscanf(archivoTransferencias, "%d|%d|%15[^|]|%d",
                  &transferencia.depOrigen,
                  &transferencia.depDestino,
                  transferencia.codProd,
                  &transferencia.cantidad) == 4) {
        vectorInsertarAlFinal(&vector, &transferencia);
    }
    Deposito deposito;

    while (fread(&deposito, sizeof(Deposito), 1, archivo) == 1) {
        for (int i = 0; i < vector.ce; i++) {
            Transferencia* t = (Transferencia*)vectorElemPos(&vector, i);

            if (strcmp(t->codProd, deposito.cod_prod) == 0) {
                if (t->depOrigen == deposito.nro_dep)
                    deposito.stock -= t->cantidad;
                if (t->depDestino == deposito.nro_dep)
                    deposito.stock += t->cantidad;
            }
        }
        fseek(archivo, -1 * sizeof(Deposito), SEEK_CUR);
        fwrite(&deposito, sizeof(Deposito), 1, archivo);
        fflush(archivo);

    }
    vectorDestruir(&vector);
    fclose(archivo);
    fclose(archivoTransferencias);
}
void mostrarArchivoDepositos_ALU(const char* archDepositos)
{
    FILE* arch = fopen(archDepositos, "rb");
    if (!arch)
    {
        printf("Error al abrir el archivo de depósitos.\n");
        return;
    }

    Deposito dep;
    printf("NroDep | CodProd         | Stock\n");
    printf("-------+-----------------+-------\n");

    while (fread(&dep, sizeof(Deposito), 1, arch) == 1)
    {
        printf("%6d | %-15s | %5d\n", dep.nro_dep, dep.cod_prod, dep.stock);
    }

    fclose(arch);
}
/* ==========================
   MAIN DE PRUEBA
   ========================== */
int main() {
    // Crear un archivo encriptado de prueba
    FILE* f = fopen("Transferencias.txt", "w");
    fprintf(f, "02|itwu|2|1\n");
    fclose(f);

    // Crear archivo binario de depósitos
    FILE* fd = fopen("Depositos.dat", "wb");
    Deposito d1 = {1, "prod", 100};
    Deposito d2 = {2, "prod", 50};
    fwrite(&d1, sizeof(Deposito), 1, fd);
    fwrite(&d2, sizeof(Deposito), 1, fd);
    fclose(fd);

    // Desencriptar
    desencriptarTransferencias_ALU("Transferencias.txt", "TransferenciasDesencriptadas.txt");

    printf("Contenido desencriptado:\n");

    // Actualizar depósitos
    actualizarDepositos_ALU("TransferenciasDesencriptadas.txt", "Depositos.dat");

    mostrarArchivoDepositos_ALU("Depositos.dat");


    return 0;
}
