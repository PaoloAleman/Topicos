#include <stdio.h>
#include <string.h>
#include "secuenciaPalabras.h"
#include "palabra.h"

#define CANT_ARG 4
#define TAM 201

char* normalizarCadena(char* cadOrig, char* cadDest);

int main(int argv, char* argc[])
{
	if(argv > CANT_ARG){
		return -1;
	}

	char normalizada[TAM] ;

	normalizarCadena(argc[1], normalizada);

	puts(normalizada);

	/*
	char cifra[] = "esTee..<ES... un8586TiTuLo'¿'¿";

	puts(normalizarCadena(cifra));

	*/
	
	return 0;
}

char* normalizarCadena(char* cadOrig, char* cadDest)
{
	SecuenciaPalabras secLectura, secEscritura;
	Palabra palTmp;

	secuenciaPalabrasCrear(&secLectura, cadOrig);
	secuenciaPalabrasCrear(&secEscritura, cadDest);

	secuenciaPalabrasLeer(&secLectura, &palTmp);

	while(!secuenciaPalabrasFin(&secLectura)){
		palabraATitulo(&palTmp);
		secuenciaPalabrasEscribir(&secEscritura, &palTmp);
		secuenciaPalabrasEscribirChar(&secEscritura, ' ');
		secuenciaPalabrasLeer(&secLectura, &palTmp);
	}

	secuenciaPalabrasCerrar(&secEscritura);

	return cadDest;
}
