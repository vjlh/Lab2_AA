#include "definiciones.h"
int main(){

	recibirNombreArchivo();
	leerArchivosYGuardarDatos();
	BENEFICIO_MAX = 0;
	CAPITAL_UTILIZADO = 0;
	CAMINO_FINAL = (char*)calloc(50,sizeof(char));
	

	Nodo *raiz = crearNodo(0,0,"");

	//Aquí se realiza la inserción de los nodos
	for (int i = 0; i < NUMERO_INVERSIONES; ++i)
		backTracking(raiz,listaDatos[i].inversion,listaDatos[i].beneficio,i);

	escribirArchivo();
	liberar(raiz);
	return 0;
}