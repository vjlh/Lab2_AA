#pragma once
//Librerías a utilizar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Declaración de estructuras a utilizar

//Nodo representa cada nodo del árbol, con la informacion necesaria para la resolución del problema
struct Nodo{
	int valorAcumulado;
	int beneficioAcumulado;
	char *camino;
	struct Nodo *izquierdo;
	struct Nodo *derecho;
};

//Datos almacena una inversión y el beneficio asociado a esta, sirve para guardar los datos del archivo de entrada
struct Datos
{
	int inversion;
	int beneficio;
};

typedef struct Datos Datos;
typedef struct Nodo Nodo;

//Definición de las variables globales
int BENEFICIO_MAX;
int CAPITAL_UTILIZADO;
int NUMERO_INVERSIONES;
int CAPITAL_LIMITE;
char *NOMBRE_ARCHIVO;
char *CAMINO_FINAL;
Datos *listaDatos;

//Encabezados de las funciones implementadas
void recibirNombreArchivo();
void leerArchivosYGuardarDatos();
Nodo *crearNodo(int, int, char*);
void backTracking(Nodo*, int, int, int);
void escribirArchivo();
void printCurrent(char*,int,int);
void liberar(Nodo* t);