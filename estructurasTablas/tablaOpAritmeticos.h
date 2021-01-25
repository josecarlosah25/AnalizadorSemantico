#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoOp{
	int clave;
	char* caracteres;
	char atomo;
	struct NodoOp* siguiente;
}NodoOp;

typedef struct {
	NodoOp* head;

}TablaOperadores;

TablaOperadores crearTablaOperadores(){
	TablaOperadores tabOperadores;
	tabOperadores.head = NULL;
	return tabOperadores;
}

void insertarTablaOperadores(TablaOperadores* tabOpActual, char* valor, char atomo){
	NodoOp* temp = tabOpActual->head;
	NodoOp* actual = (NodoOp *)malloc(sizeof(NodoOp));
	actual->caracteres=(char *)malloc(strlen(valor)*sizeof(char));

	if(temp == NULL){
		actual->clave = 0;
		actual->atomo = atomo;
		strcpy(actual->caracteres, valor);
		actual->siguiente = NULL;
		tabOpActual->head = actual;
	}
	else{
		while(temp->siguiente != NULL)
			temp = temp->siguiente;

		actual->clave = temp->clave + 1;

		strcpy(actual->caracteres, valor);
		actual->atomo = atomo;
		actual->siguiente = NULL;
		temp->siguiente = actual;
	}

}

void imprimirTablaOperadores(TablaOperadores tabOpActual){
	
	if (tabOpActual.head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoOp* actual = tabOpActual.head;
		printf("\nPosicion \t_ \tCaracter\n");
		while(actual!= NULL){
			printf(" %d \t\t| \t %s\n", actual->clave, actual->caracteres);
			actual = actual->siguiente;
		}
	}
}

//Falta definir cómo buscar el átomo
char buscarTablaOperadores(TablaOperadores* tabOpActual, char* operador){
    NodoOp *temp = tabOpActual->head;
    while (temp != NULL) {

        if (strcmp(temp->caracteres, operador) == 0){
        	if(strcmp(operador, "**") == 0){
        		int clavePotencia = 48; //Código ASCII del 0 
        		//printf("\nSe encuentra el simbolo %s en la Tabla de Operadores y su clave es %d \n", operador, clavePotencia);
        		return clavePotencia;
        		//break;
        	}
        	else{
            	//printf("\nSe encuentra el simbolo %c en la Tabla de Operadores y devuelve %s \n", operador[0], temp->caracteres);
            	//printf("\naaaaa%d", atoi(temp->caracteres));
            	return temp->caracteres[0];
            	//break;
        	}
        }
        else
            temp = temp->siguiente;
    }

    return 'F';
}

char devolverAtomoArit(TablaOperadores* tabOpActual, char* operador){
    NodoOp *temp = tabOpActual->head;
    while (temp != NULL) {

        if (strcmp(temp->caracteres, operador) == 0)
        	return temp->atomo;
        else
            temp = temp->siguiente;
    }

    return 'F';
}
