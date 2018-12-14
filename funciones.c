#include "definiciones.h"

//FUNCIONES DE LECTURA Y ALMACENAMIENTO DE LOS DATOS DEL ARCHIVO DE ENTRADA

/*
*Funcion que recibe el nombre del archivo de entrada pidiendoselo por pantalla al usuario
*@return: No tiene porque se tiene una variable global que almacenará el nombre
*/
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

/*
*Esta funcion se encarga del proceso de lectura y obtencion de los datos del archivo de entrada y su posterior traspaso
 a la matriz de adyacencia
*@return: No genera salidas, porque el almacenamiento que hace, lo hace en la matriz declarada de manera global, estas
*/
void leerArchivosYGuardarDatos()		
{											
	FILE* archivo_entrada;		
	int costo, lineaVacia, i, largoLinea,posicion;
	char buffer[100],buffer2[100],*inversion,*beneficio, *valor3;

	archivo_entrada = fopen(NOMBRE_ARCHIVO,"r");

	fscanf(archivo_entrada," %119[^\n]",buffer);
	CAPITAL_LIMITE = atoi(buffer);
	fgetc(archivo_entrada);

	fscanf(archivo_entrada," %119[^\n]",buffer);
	NUMERO_INVERSIONES = atoi(buffer);
	fgetc(archivo_entrada);

	listaDatos = (Datos*)calloc(NUMERO_INVERSIONES,sizeof(Datos*));
	posicion = 0;

	while (!feof(archivo_entrada))
	{
		memset(buffer,0, 100);
		memset(buffer2,0, 100);
		lineaVacia = 1;
		fscanf(archivo_entrada," %119[^\n]",buffer);
		largoLinea = strlen(buffer);

		for (i = 0; i < largoLinea; ++i)
			if (buffer[i] == ' ')
				lineaVacia++;

		if (buffer[0] != '\0' && lineaVacia != largoLinea && buffer[0] != '\n' && buffer[0] != '\t')
		{	
			for (i = 0; i < largoLinea; ++i)
				if (buffer[i] != ' ')
					break;

			strncpy(buffer2,buffer+i,largoLinea-i);

			inversion = strtok(buffer2," ");
			beneficio = strtok(NULL," ");

			listaDatos[posicion].inversion = atoi(inversion);
			listaDatos[posicion].beneficio = atoi(beneficio);
			posicion++;
		}	
		fgetc(archivo_entrada);
		if (feof(archivo_entrada))
			break;	
	}
	fclose(archivo_entrada);
	free(NOMBRE_ARCHIVO);
}

/*
*Esta funcion se encarga de la creación de un nodo, con sus datos respectivos
*@param valor: Se refiere al costo acumulado hasta el momento de llegar a ese nodo
*@param beneficio: Se refiere al beneficio acumulado hasta el momento de llegar a ese nodo
*@param camino: Muestra el camino que se recorrió para llegar a ese nodo
*@return: Retorna el nodo creado, con los valores especificados
*/
Nodo *crearNodo(int valor,int beneficio,char *camino){
	Nodo *nuevo = (Nodo *)calloc(1,sizeof(Nodo));
	nuevo->camino = (char*)calloc(50,sizeof(char));
	strcpy(nuevo->camino,camino);
	strcat(nuevo->camino,"-");
	nuevo->valorAcumulado = valor;
	nuevo->beneficioAcumulado = beneficio;
	return nuevo;
}

/*
*Esta funcion se encarga de la inserción de los nodos en el arbol y la creación de las posibles
 soluciones, es decir va generando el backtracking, recorre crea y retrocede, cuando terminan
 todas las inserciones de nodos, la solución ya ha sido encontrada y se almacena en variables
 globales
*@param nodoActual: Se refiere al nodo que se encuentra recorriendo actualmente
*@param valor: Se refiere al valor o inversion que se quiere insertar o añadir
*@param beneficio: Se refiere al beneficio que posee la inversión que se desea agregar
*@param indice: Indice que representa a la inversión que se quiere añadir, para generar el camino 
*@return: No retorna nada
*/
void backTracking(Nodo *nodoActual, int valor,int beneficio,int indice){
	if(nodoActual->izquierdo != NULL){
		backTracking(nodoActual->izquierdo,valor,beneficio,indice);
	}
	if(nodoActual->derecho != NULL){
		backTracking(nodoActual->derecho,valor,beneficio,indice);
	}
	if(nodoActual->izquierdo == NULL && nodoActual->derecho == NULL){
		int valorAcumulado = nodoActual->valorAcumulado + valor;
		printCurrent(nodoActual->camino,nodoActual->valorAcumulado,nodoActual->beneficioAcumulado);
		if (valorAcumulado <= CAPITAL_LIMITE)
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
				CAPITAL_UTILIZADO = valorAcumulado;
				strcpy(CAMINO_FINAL,caminoAcumulado);
			}
			nodoActual->izquierdo = crearNodo(nodoActual->valorAcumulado,nodoActual->beneficioAcumulado,nodoActual->camino);
			nodoActual->derecho = crearNodo(valorAcumulado,beneficioAcumulado,caminoAcumulado);		
		}
	}
}

/*
*Esta funcion se encarga de escribir el archivo solución, es decir en un archivo de texto
 escribe el beneficio maximo que se encontró, el capital que se gastó y la lista de las 
 inversiones utilizadas
*/
void escribirArchivo(){
	FILE *archivo_salida;
   	char *indice;

	archivo_salida = fopen("salida.out","w");
	indice = strtok(CAMINO_FINAL, "-");
	
	if (indice != NULL)
	{
		fprintf(archivo_salida,"%i %i\n",CAPITAL_UTILIZADO,BENEFICIO_MAX);
		fprintf(archivo_salida,"%d\n",listaDatos[atoi(indice)].inversion);
	 	while((indice = strtok(NULL,"-")) != NULL)
			fprintf(archivo_salida,"%d\n",listaDatos[atoi(indice)].inversion);

		fclose(archivo_salida);
	}
	else
		fprintf(archivo_salida,"Todas las combinaciones de las inversiones superan su presupuesto");

	printf("\nEl programa ha terminado...\n");
	free(CAMINO_FINAL);
}

/*
*Esta funcion se encarga de mostrar el estado del nodo que se encuentra uno visitando al momento
 de insertar, es decir cuando se llega a un nodo que no tiene hijos.
*@param camino: El camino por el que se llega a ese nodo
*@param camino: El costo acumulado hasta ese nodo
*@param camino: El beneficio acumulado hasta ese nodo
*/
void printCurrent(char* camino,int costo,int beneficio){
	#ifdef DEBUG

	printf("enter para continuar...\n");
	while(getchar() != '\n')
	;
	
   	char *indice, *caminoCopy;
   	caminoCopy = (char*)calloc(30,sizeof(char));
   	strcpy(caminoCopy,camino);
	indice = strtok(caminoCopy, "-");

	if (indice != NULL)
	{
		printf("%d\n",listaDatos[atoi(indice)].inversion);
	 	while((indice = strtok(NULL,"-")) != NULL)
			printf("%d\n",listaDatos[atoi(indice)].inversion);

		printf("\nCosto acumulado: %i\nBeneficio acumulado: %i\n",costo,beneficio);
		
	}
	else
		printf("\nNinguna Inversion se ha utilizado aqui\n");
	
	#endif
}
/* 
*Esta funcion libera toda la memoria que utilizó el árbol
*@param t: Raiz del arbol que se va a liberar de la memoria
*/
void liberar(Nodo* t)
{
	if(t != NULL)						
	{									
		liberar(t->izquierdo);
		liberar(t->derecho);
		free(t);
	}
}