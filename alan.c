#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	int num;
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
int NUMERO_INVERSIONES;
int CAPITAL_INVERTIDO;
char *NOMBRE_ARCHIVO;
char *CAMINO_FINAL;
Datos *listaDatos;

struct nodo *crearNodo(int valor, int num,int beneficio,char *camino){
	struct nodo *nuevo = (struct nodo *)calloc(1,sizeof(struct nodo));
	nuevo->camino = (char*)calloc(100,sizeof(char));
	strcpy(nuevo->camino,camino);
	strcat(nuevo->camino,"-");
	nuevo->num = num;
	nuevo->valorAcumulado = valor;
	nuevo->beneficioAcumulado = beneficio;
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
		int valorAcumulado = nodoActual->valorAcumulado + valor;
		if (valorAcumulado <= VALORLIMITE)
		{
			char *inversion,*caminoAcumulado;
			int beneficioAcumulado;

			beneficioAcumulado = nodoActual->beneficioAcumulado + beneficio;
			inversion = (char*)calloc(10,sizeof(char));
			caminoAcumulado = (char*)calloc(100,sizeof(char));
			
			sprintf(inversion, "%i", valor);			
			strcpy(caminoAcumulado,nodoActual->camino);
			strcat(caminoAcumulado,inversion);

			if(beneficioAcumulado>BENEFICIO_MAX)
			{
				BENEFICIO_MAX = beneficioAcumulado;
				strcpy(CAMINO_FINAL,caminoAcumulado);
			}
			nodoActual->izquierdo = crearNodo(0,0,0,"");
			nodoActual->derecho = crearNodo(valorAcumulado,valor,beneficioAcumulado,caminoAcumulado);
				
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
    printf ( "%d/%d\n", root->valorAcumulado, root->beneficioAcumulado);
    structure ( root->izquierdo, level + 1 );
  }
}

int main(){
	recibirNombreArchivo();
	leerArchivosYGuardarDatos();
	struct nodo *raiz = crearNodo(0,0,0,"");
	VALORLIMITE = 40;
	BENEFICIO_MAX = 0;
	CAMINO_FINAL = (char*)calloc(100,sizeof(char));
	printf("Nodos agregados %d\n",agregarNodo(raiz,40,7));
	printf("Nodos agregados %d\n",agregarNodo(raiz,25,6));
	printf("Nodos agregados %d\n",agregarNodo(raiz,15,8));
	structure(raiz,0);

	printf("El beneficio maximo es: %d con un camino de: %s\n",BENEFICIO_MAX,CAMINO_FINAL);

	return 0;
}