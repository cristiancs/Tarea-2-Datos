#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>

int tamano;

typedef struct NodoLista {
  	char                *dato;
  	struct NodoLista *siguiente;
  	int tamano;
}Nodo;

typedef struct ListaIdentificar {
  	Nodo *inicio;
  	Nodo *fin;
  	int tamano;
  	Nodo *nodo_actual;
  	int posicion_actual;
}Lista;

Lista *inicializar (){
	Lista *lista;
	lista = (Lista *) malloc(sizeof(Lista));
 	lista->inicio = (Nodo *) malloc(sizeof(Nodo));
 	lista->fin = (Nodo *) malloc(sizeof(Nodo));
 	lista->tamano = 0;
 	return lista;
}


int append(Lista * lista, char *dato){
  	Nodo *nuevoNodo;
  	if ((nuevoNodo = (Nodo *) malloc (sizeof (Nodo))) == NULL)
    	return -1;
  	nuevoNodo->dato = dato;
  	nuevoNodo->siguiente = NULL;
  	if(nuevoNodo->tamano == 0){
	  	lista->inicio = nuevoNodo;
	  	lista->fin = nuevoNodo;
	  	lista->tamano++;
	}else{
		lista->fin->siguiente = nuevoNodo;
	  	lista->fin = nuevoNodo;
	  	lista->tamano++;
	}
  	return 0;
}

void borrar(Lista * lista){
	if(lista != NULL){
		if (lista->inicio->siguiente == NULL){
			free( (void *) lista->inicio);
		
		}
		else{
			Nodo *temp = lista->inicio->siguiente;
			while(temp!=NULL){
				free( (void *) lista->inicio);
				lista->inicio = temp;
				temp = lista->inicio->siguiente;

			}
		}
	}
}

int main()
{

Lista *k = inicializar();

borrar(k);

	return 0;
}