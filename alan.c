#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	int valorAcumulado;
	int beneficioAcumulado;
	char *camino;
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
int CAPITAL_MAX;
int NUMERO_INVERSIONES;
int CAPITAL_INVERTIDO;
char *NOMBRE_ARCHIVO;
char *CAMINO_FINAL;
Datos *listaDatos;

void recibirNombreArchivo() 
{
	FILE* archivo;
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
{											
	FILE* archivo_nodos;		
	int inversion, beneficio, costo, aux2, i, largo,posicion;
	char buffer[100],buffer2[100],*valor1,*valor2, *valor3;

	archivo_nodos = fopen(NOMBRE_ARCHIVO,"r");
	fscanf(archivo_nodos," %119[^\n]",buffer);
	
	CAPITAL_INVERTIDO = atoi(buffer);

	fgetc(archivo_nodos);
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

struct nodo *crearNodo(int valor,int beneficio,char *camino){
	struct nodo *nuevo = (struct nodo *)calloc(1,sizeof(struct nodo));
	nuevo->camino = (char*)calloc(100,sizeof(char));
	strcpy(nuevo->camino,camino);
	strcat(nuevo->camino,"-");
	nuevo->valorAcumulado = valor;
	nuevo->beneficioAcumulado = beneficio;
	return nuevo;
}

int agregarNodo(struct nodo *nodoActual, int valor,int beneficio,int indice){
	int x = 0, y = 0;
	if(nodoActual->izquierdo != NULL){
		x = agregarNodo(nodoActual->izquierdo,valor,beneficio,indice);
	}
	if(nodoActual->derecho != NULL){
		y = agregarNodo(nodoActual->derecho,valor,beneficio,indice);
	}
	if(nodoActual->izquierdo == NULL && nodoActual->derecho == NULL){
		int valorAcumulado = nodoActual->valorAcumulado + valor;
		if (valorAcumulado <= CAPITAL_INVERTIDO)
		{
			char *inversion,*caminoAcumulado;
			int beneficioAcumulado;

			beneficioAcumulado = nodoActual->beneficioAcumulado + beneficio;
			inversion = (char*)calloc(5,sizeof(char));
			caminoAcumulado = (char*)calloc(50,sizeof(char));
			
			sprintf(inversion,"%i", indice);			
			strcpy(caminoAcumulado,nodoActual->camino);
			strcat(caminoAcumulado,inversion);

			if(beneficioAcumulado>BENEFICIO_MAX)
			{
				BENEFICIO_MAX = beneficioAcumulado;
				CAPITAL_MAX = valorAcumulado;
				strcpy(CAMINO_FINAL,caminoAcumulado);
			}
			nodoActual->izquierdo = crearNodo(0,0,"");
			nodoActual->derecho = crearNodo(valorAcumulado,beneficioAcumulado,caminoAcumulado);		
		}
		return 2;
	}
	return x + y;
}

void escribirArchivo(){
	FILE *archivo_salida;
	archivo_salida = fopen("salida.out","w");
	fprintf(archivo_salida,"%i %i\n",CAPITAL_MAX,BENEFICIO_MAX);

   	char *ptr;

   	ptr = strtok(CAMINO_FINAL, "-");    // Primera llamada => Primer token
		fprintf(archivo_salida,"%d\n",listaDatos[atoi(ptr)].inversion);
 	
 	while((ptr = strtok(NULL,"-")) != NULL)    // Posteriores llamadas
		fprintf(archivo_salida,"%d\n",listaDatos[atoi(ptr)].inversion);

	fclose(archivo_salida);
	printf("\nEl programa ha terminado...\n");
}

int main(){
	recibirNombreArchivo();
	leerArchivosYGuardarDatos();
	BENEFICIO_MAX = 0;
	CAPITAL_MAX = 0;
	CAMINO_FINAL = (char*)calloc(50,sizeof(char));
	struct nodo *raiz = crearNodo(0,0,"");

	for (int i = 0; i < NUMERO_INVERSIONES; ++i)
		agregarNodo(raiz,listaDatos[i].inversion,listaDatos[i].beneficio,i);

	escribirArchivo();
	
	printf("El beneficio maximo es: %d\nEl capital utilizado es: %d\nCamino de: %s\n",BENEFICIO_MAX,CAPITAL_MAX,CAMINO_FINAL);

	return 0;
}