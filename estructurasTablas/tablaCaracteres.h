#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoCar{
	int clave;
	char caracter;
	int ascii;
	struct NodoCar* siguiente;
}NodoCar;

typedef struct {
	NodoCar* head;

}TablaCaracteres;

TablaCaracteres crearTablaCaracteres(){
	TablaCaracteres tabCaracteres;
	tabCaracteres.head = NULL;
	return tabCaracteres;
}

void insertarTablaCaracteres(TablaCaracteres* tabCarActual, char valor){
	//RECORDAR QUE EL VALOR INSERTADO TAMBIÉN ES EL ÁTOMO
	NodoCar* temp = tabCarActual->head;
	NodoCar* actual = (NodoCar *)malloc(sizeof(NodoCar));

	if(temp == NULL){
		actual->clave = 0;
		actual->caracter = valor;
		actual->siguiente = NULL;
		actual->ascii = valor;
		tabCarActual->head = actual;
		
	}
	else{
		while(temp->siguiente != NULL)
			temp = temp->siguiente;

		actual->clave += temp->clave + 1;
		actual->caracter = valor;
		actual->siguiente = NULL;
		actual->ascii = valor;
		temp->siguiente = actual;

			
	}
	

}

void imprimirTablaCaracteres(TablaCaracteres tabCarActual){
	
	if (tabCarActual.head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoCar* actual = tabCarActual.head;
		printf("\nPosicion \t_ \tCaracter \t_ \tASCII\n");
		while(actual!= NULL){
			printf(" %d \t\t| \t %c \t\t| \t %d\n", actual->clave, actual->caracter, actual->ascii);
			actual = actual->siguiente;
		}
	}
}

//Falta definir cómo buscar al átomo
int buscarTablaCaracteres(TablaCaracteres* tabCarActual, char caracter){
    NodoCar *temp = tabCarActual->head;
    while (temp != NULL) {
        if (temp->caracter == caracter){
        	//printf("\nSe encuentra el simbolo %c en la Tabla y su codigo ASCII es %d \n", caracter, temp->ascii);
        	return temp->ascii;
        	//break;
        	
        }
        else
            temp = temp->siguiente;
    }
    return -1;
}

