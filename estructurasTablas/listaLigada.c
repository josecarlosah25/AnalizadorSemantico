#include <stdio.h>
#include <stdlib.h>

int numClave = 0;

typedef struct NodoCat{
	int clave;
	char* contenido;
	struct NodoCat* siguiente;
}NodoCat;

typedef struct {
	NodoCat* head;

}Catalogo;

Catalogo crearCatalogo(){
	Catalogo catalogo;
	catalogo.head = NULL;
	return catalogo;
}

void insertarCatalogo(Catalogo* catActual, char* valor){
	NodoCat* temp = catActual->head;
	NodoCat* actual = (NodoCat *)malloc(sizeof(NodoCat));

	if(temp == NULL){
		actual->clave = numClave;
		actual->contenido = valor;
		actual->siguiente = NULL;
		catActual->head = actual;
	}
	else{
		while(temp->siguiente != NULL)
			temp = temp->siguiente;

		numClave++;
		actual->clave = numClave;
		actual->contenido = valor;
		actual->siguiente = NULL;
		temp->siguiente = actual;
			
	}
	

}

void imprimirCatalogo(Catalogo catActual){
	
	if (catActual.head == NULL)
		printf("La tabla esta vacia\n");
	else{
		NodoCat* actual = catActual.head;
		printf("Posicion \t_ \tContenido\n");
		while(actual!= NULL){
			printf(" %d \t\t| \t %s\n", actual->clave, actual->contenido);
			actual = actual->siguiente;
		}
	}
}

void buscarCatalogo(Catalogo* catActual, char* cadena){
    NodoCat *temp = catActual->head;
    while (temp != NULL) {
        if (temp->contenido == cadena){
            printf("\nSe encuentra la palabra %s en el catalogo y su clave es %d \n", cadena, temp->clave);
            //return clave;
            break;
        }
        else
            temp = temp->siguiente;
    }
}

int main(){
	Catalogo catalogo = crearCatalogo();
	insertarCatalogo(&catalogo, "hola");
	insertarCatalogo(&catalogo, "buenos");
	insertarCatalogo(&catalogo, "dias");
	insertarCatalogo(&catalogo, "a");
	insertarCatalogo(&catalogo, "todos");
	buscarCatalogo(&catalogo, "buenos");
	imprimirCatalogo(catalogo);
}