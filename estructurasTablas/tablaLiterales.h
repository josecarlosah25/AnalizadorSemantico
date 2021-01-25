#include <stdio.h>
#include <stdlib.h>

FILE *archSal;

typedef struct NodoLit{
	int clave;
	char* cadena;
	char atomo;
	struct NodoLit* siguiente;
}NodoLit;

typedef struct {
	NodoLit* head;

}TablaLiterales;

TablaLiterales crearTablaLiterales(){
	TablaLiterales tablaLit;
	tablaLit.head = NULL;
	return tablaLit;
}

int insertarTablaLiterales(TablaLiterales* tablaLit, char* valor, char atomo){
	NodoLit* temp = tablaLit->head;
	NodoLit* actual = (NodoLit *)malloc(sizeof(NodoLit));

	if(temp == NULL){
		actual->clave = 0;
		actual->cadena = valor;
		actual->atomo = atomo;
		actual->siguiente = NULL;
		tablaLit->head = actual;
		//printf("La posicion que ocupa la cadena en la tabla es: %d\n", actual->clave);
		return actual->clave;
	}
	else{
		while(temp->siguiente != NULL)
			temp = temp->siguiente;

		actual->clave += temp->clave + 1;
		actual->cadena = valor;
		actual->atomo = atomo;
		actual->siguiente = NULL;
		temp->siguiente = actual;
		//printf("La posicion que ocupa la cadena recien insertada en la tabla es: %d\n", actual->clave);
		return actual->clave;
			
	}
	

}

void imprimirTablaLiterales(TablaLiterales tablaLit, FILE *archSal){
	
	if (tablaLit.head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoLit* actual = tablaLit.head;
		printf("\n-----TABLA DE LITERALES-----");
		printf("\nPosicion \t_ \tCadena\n");
		//fprintf(archSal, "\n------TABLA DE LITERALES-----");
		fprintf(archSal, "\nPosicion \t_ \tCadena\n");
		while(actual!= NULL){
			
			printf(" %d \t\t| \t %s\n", actual->clave, actual->cadena);
			fprintf(archSal, " %d \t\t| \t %s\n", actual->clave, actual->cadena);
			actual = actual->siguiente;
		}
	}
}

char devolverAtomoLit(TablaLiterales* tablaLit, int clave){
    NodoLit *temp = tablaLit->head;
    while (temp != NULL) {
        if (temp->clave == clave){
            //printf("\nSe encuentra el valor %s en el catalogo y su clave es %d \n", cadena, temp->clave);
            return temp->atomo;
            
        }
        else
            temp = temp->siguiente;
    }
    
	return 'F';
}