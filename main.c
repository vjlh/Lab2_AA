#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Variables globales
int NUMERO_INVERSIONES;
int** MATRIZ_ADYACENCIA;
int NUMERO_PERMUTACIONES;
char *NOMBRE_ARCHIVO;
int CAPITAL_INVERTIDO;

struct Datos
{
	int inversion;
	int beneficio;
};
/*struct Arbol
{				
	NodoArbol* raiz;
};*/

struct Nodo
{
	struct Nodo *izq;
	struct Nodo *der;
	int beneficioAcumulado;
	int capitalAcumulado;
};


typedef struct Arbol Arbol;
typedef struct Nodo Nodo;
typedef struct Datos Datos;

Nodo *raiz = NULL;
Datos *listaDatos;
Datos DATO_NULO;

Nodo* crear_nodo(Datos dato){
	Nodo *nuevo_nodo;
	nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));

	nuevo_nodo->capitalAcumulado = dato.inversion;
	nuevo_nodo->beneficioAcumulado = dato.beneficio;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->der = NULL;
	return nuevo_nodo;
}
Nodo insertar(Dato dato){
	if (raiz == NULL)
		raiz = crear_nodo(DATO_NULO);

	Nodo *nuevo_nodo;
	nuevo_nodo = crear_nodo(dato);

	Nodo *anterior, *reco;
	anterior = NULL;
	reco = raiz;

}

/*Arbol* crearArbol()
{													//Funcion encargada de inicializar el arbol
	Arbol* t;										//Crea las raices que "sostendran" el árbol
	t = (Arbol*)malloc(sizeof(Arbol));				//o comenzarán el arbol
	if (t == NULL)
	{
		printf("Error asignando memoria al nodo\n");
		exit(1);
	}
	t->raiz = NULL;
	return t;										//Retorna el arbol inicializado
}*/

void recibirNombreArchivo() 
{
	FILE* archivo; //
	NOMBRE_ARCHIVO = (char*)malloc(sizeof(char)*25);//Estas variables globales definidas en las definiciones
	printf("Para comenzar primero se necesita el nombre de sus dos archivos de entrada junto a su formato\n");
	printf("Por ejemplo 'entrada1.txt' o prueba1.txt\n\nRecuerde que el primero es el que contiene las instrucciones y el segundo las lineas de control\n");
	do
	{
		printf("\nIngrese el nombre del archivo solicitado: ");
		scanf("%s",NOMBRE_ARCHIVO);
		while(getchar()!='\n');
		archivo = fopen(NOMBRE_ARCHIVO,"r");
		
		if (archivo == NULL) 
			printf("No se encuentra archivo con ese nombre, intente nuevamente\n");
		
	} while (archivo == NULL);
	fclose(archivo);
}

void leerArchivosYGuardarDatos()		
{										//primero cuenta cuantas lineas tiene el archivo	
	FILE* archivo_nodos;		//hecho esto, pasa todas las instrucciones que están en el archivo
	int inversion, beneficio, costo, aux2, i, largo,posicion;	//y los registros o direcciones de memoria involucrados en ella
	char buffer[100],buffer2[100],*valor1,*valor2, *valor3;
										//La función no retorna nada ya que todo lo que va modificando son punteros
	archivo_nodos = fopen(NOMBRE_ARCHIVO,"r");
	fscanf(archivo_nodos," %119[^\n]",buffer);
	
	CAPITAL_INVERTIDO = atoi(buffer);

	fgetc(archivo_nodos);
	
	printf("%i\n",CAPITAL_INVERTIDO);

	fscanf(archivo_nodos," %119[^\n]",buffer);
	NUMERO_INVERSIONES = atoi(buffer);

	fgetc(archivo_nodos);


	listaDatos = (Datos*)malloc(sizeof(Datos*)*NUMERO_INVERSIONES);
	posicion = 0;
	while (!feof(archivo_nodos))
	{
		memset(buffer,0, 100);
		memset(buffer2,0, 100);
		aux2 = 1;
		fscanf(archivo_nodos," %119[^\n]",buffer);
		largo = strlen(buffer);

		for (i = 0; i < largo; ++i)
			if (buffer[i] == ' ')
				aux2++;

		if (buffer[0] != '\0' && aux2 != largo && buffer[0] != '\n')
		{	
			for (i = 0; i < largo; ++i)
				if (buffer[i] != ' ')
					break;

			strncpy(buffer2,buffer+i,largo-i);
	
			valor1 = strtok(buffer2," ");
			inversion = atoi(valor1);

			valor2 = strtok(NULL," ");
			beneficio = atoi(valor2);

			listaDatos[posicion].inversion = inversion;
			listaDatos[posicion].beneficio = beneficio;
			posicion++;
		}	
		fgetc(archivo_nodos);
		if (feof(archivo_nodos))
			break;	
	}
	fclose(archivo_nodos);
}



int main(int argc, char const *argv[])
{
	recibirNombreArchivo();
	leerArchivosYGuardarDatos();
	DATO_NULO.inversion = 0;
	DATO_NULO.beneficio = 0;
	for (int i = 0; i < NUMERO_INVERSIONES; ++i)
	{
		printf("Inversion: %i con beneficio %i\n",listaDatos[i].inversion,listaDatos[i].beneficio);
		
	}
	return 0;
}