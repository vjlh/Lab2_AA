#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	int num;
	int valor;
	int beneficio;
	struct nodo *izquierdo;
	struct nodo *derecho;
};

struct Datos
{
	int inversion;
	int beneficio;
};

typedef struct Datos Datos;


int VALORLIMITE;
int BENEFICIO_MAX;
int NUMERO_INVERSIONES;
int CAPITAL_INVERTIDO;
char *NOMBRE_ARCHIVO;
Datos *listaDatos;


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

struct nodo *crearNodo(int valor, int num,int beneficio){
	struct nodo *nuevo = (struct nodo *) calloc(1,sizeof(struct nodo));
	nuevo->num = num;
	nuevo->valor = valor;
	nuevo->beneficio = beneficio;
	return nuevo;
}

int agregarNodo(struct nodo *nodoActual, int valor,int beneficio){
	int x = 0, y = 0;
	if(nodoActual->izquierdo != NULL){
		x = agregarNodo(nodoActual->izquierdo,valor,beneficio);
	}
	if(nodoActual->derecho != NULL){
		y = agregarNodo(nodoActual->derecho,valor,beneficio);
	}
	if(nodoActual->izquierdo == NULL && nodoActual->derecho == NULL){
		int valorAcumulado = nodoActual->valor + valor;
		if (valorAcumulado<= VALORLIMITE)
		{
			int beneficioAcumulado = nodoActual->beneficio + beneficio;
			nodoActual->izquierdo = crearNodo(0,0,0);
			nodoActual->derecho = crearNodo(valorAcumulado,valor,beneficio);
				
		}
		return 2;
	}
	return x + y;
}


void padding ( char ch, int n ){
  int i;
  
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}

void structure (struct nodo *root, int level ){
  int i;
  
  if ( root == NULL ) {
    padding ( '\t', level );
    puts ( "~" );
  } else {
    structure ( root->derecho, level + 1 );
    padding ( '\t', level );
    printf ( "%d/%d\n", root->valor, root->beneficio);
    structure ( root->izquierdo, level + 1 );
  }
}

int main(){
	struct nodo *raiz = crearNodo(0,0,0);
	VALORLIMITE = 40;
	printf("Nodos agregados %d\n",agregarNodo(raiz,40,7));
	printf("Nodos agregados %d\n",agregarNodo(raiz,25,6));
	printf("Nodos agregados %d\n",agregarNodo(raiz,15,8));
	structure(raiz,0);
	return 0;
}