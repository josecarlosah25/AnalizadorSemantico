#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *archSal;

typedef struct NodoSimb{
	int clave;
	char* nombre;
	int tipo;
	char atomo;
	struct NodoSimb* siguiente;
}NodoSimb;

typedef struct {
	NodoSimb* head;

}TablaSimbolos;

TablaSimbolos crearTablaSimbolos(){
	TablaSimbolos tablaSimbolos;
	tablaSimbolos.head = NULL;
	return tablaSimbolos;
}

int insertarTablaSimbolos(TablaSimbolos* tabSimbActual, char* valor){
	NodoSimb* temp = tabSimbActual->head;
	NodoSimb* actual = (NodoSimb *)malloc(sizeof(NodoSimb));

	if(temp == NULL){
		actual->clave = 0;
		actual->nombre = valor;
		actual->atomo = 'a';
		actual->siguiente = NULL;
		actual->tipo = -1;
		tabSimbActual->head = actual;
		//printf("La posicion que ocupa la cadena en la tabla es: %d\n", actual->clave);
		return actual->clave;
	}
	else{
		while(temp->siguiente != NULL)
			temp = temp->siguiente;

		actual->clave = temp->clave + 1;
		actual->nombre = valor;
		actual->atomo = 'a';
		actual->siguiente = NULL;
		actual->tipo = -1;
		temp->siguiente = actual;
		//printf("La posicion que ocupa la cadena en la tabla es: %d\n", actual->clave);
		return actual->clave;
	}

}

void imprimirTablaSimbolos(TablaSimbolos tabSimbActual, FILE *archSal){
	
	if (tabSimbActual.head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoSimb* actual = tabSimbActual.head;
		printf("\n------TABLA DE SIMBOLOS-----");
		printf("\nPosicion \t_ \tNombre \t\t\t\t_ \tTipo\n");
		fprintf(archSal, "\n------TABLA DE SIMBOLOS-----");
		fprintf(archSal, "\nPosicion \t_ \tNombre \t\t\t\t_ \tTipo\n");
		while(actual!= NULL){
			if (strlen(actual->nombre) <= 14){
				printf(" %d \t\t| \t %s \t\t| \t %d\n", actual->clave, actual->nombre, actual->tipo);
				fprintf(archSal, " %d \t\t| \t %s \t\t| \t %d\n", actual->clave, actual->nombre, actual->tipo);
			}
			else{
				printf(" %d \t\t| \t %s \t| \t %d\n", actual->clave, actual->nombre, actual->tipo);
				fprintf(archSal, " %d \t\t| \t %s \t| \t %d\n", actual->clave, actual->nombre, actual->tipo);
			}
			actual = actual->siguiente;
		}
	}
}

int buscarTablaSimbolos(TablaSimbolos* tabSimbActual, char* cadena){
    NodoSimb *temp = tabSimbActual->head;
    while (temp != NULL) {

        if (strcmp(temp->nombre,cadena)==0){
            //printf("\nSe encuentra la palabra %s en el Tabla de Simbolos y su clave es %d \n", cadena, temp->clave);
            return temp->clave;
            //break;
        }
        else
            temp = temp->siguiente;
    }
    return -1;
}

char devolverAtomoSimb(TablaSimbolos* tabSimbActual, int clave){
    NodoSimb *temp = tabSimbActual->head;
    while (temp != NULL) {

        if (temp->clave == clave){
            //printf("\nSe encuentra la palabra %s en el Tabla de Simbolos y su clave es %d \n", cadena, temp->clave);
            return temp->atomo;
            //break;
        }
        else
            temp = temp->siguiente;
    }
    return -1;
}

//Obtener el tipo a partir de la posición de la tabla
int buscarPosTablaSimbolos(TablaSimbolos* tabSimbActual, int posicion){
    NodoSimb *temp = tabSimbActual->head;
    while (temp != NULL) {

        if (temp->clave == posicion){
            //printf("\nSe encuentra la posicion %d en el Tabla de Simbolos y su tipo es %d \n", cadena, temp->clave);
            return temp->tipo;
            //break;
        }
        else
            temp = temp->siguiente;
    }
    return -1;
}

void asignarTipo(TablaSimbolos* tabSimbActual, int posicion, int valorToken){
    NodoSimb *temp = tabSimbActual->head;
    while (temp != NULL) {
    	if(temp->valor == posicion)
    		temp->tipo = valorToken;
    	else
     		temp = temp->siguiente;
    }
    //return -1;
}
