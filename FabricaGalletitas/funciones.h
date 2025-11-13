#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
typedef struct {
    int depositoOrigen;
    int depositoDestino;
    char codigoProducto[16];
    double cantidad;
} Transferencia;

typedef struct {
    int numeroDeposito;
    char codigoProducto[16];
    int stock;
} Deposito;

#endif // FUNCIONES_H_INCLUDED
