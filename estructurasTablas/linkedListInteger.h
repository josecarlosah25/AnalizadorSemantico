#include <stdio.h>
#include <stdlib.h>

int numClave = 0;

typedef struct NodoInt{
	int valor;
	struct NodoInt* siguiente;
}NodoInt;

typedef struct {
	NodoInt* head;
}Temp;

Temp crearTemp(){
	Temp temporal;
	temporal.head = NULL;
	return temporal;
}

void insertarInt(Temp* listaInt, int valor){
	NodoInt* temp_nodo = listaInt->head;
	NodoInt* actual = (NodoInt *)malloc(sizeof(NodoInt));

	if(temp_nodo == NULL){
		actual->valor = valor;
		actual->siguiente = NULL;
		listaInt->head = actual;
	}
	else{
		while(temp_nodo->siguiente != NULL)
			temp_nodo = temp_nodo->siguiente;
		actual->valor = valor;
		actual->siguiente = NULL;
		temp_nodo->siguiente = actual;
			
	}
	

}

void imprimirLinkedList(Temp* listaInt){
	
	if (listaInt->head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoInt* actual = listaInt->head;
		printf("Posicion \t_ \tContenido\n");
		while(actual!= NULL){
			printf(" %d\n", actual->valor);
			actual = actual->siguiente;
		}
	}
}

int buscarValor(Temp* lista, int index){
    NodoInt* node = lista->head;

    int i=0;

    for(i=0;i<index;i++){
    	node= node->siguiente;
    }

    return node->valor;
}