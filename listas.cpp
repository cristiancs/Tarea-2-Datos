#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>

using namespace std;

int tamano;

typedef struct NodoLista {
  	int        *dato;
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


int append(Lista * lista, int *dato){
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

void moverAdelante(Lista *lista){
	if (lista != NULL && lista->nodo_actual != lista->fin){
		lista->posicion_actual +=1;
	}
	

}

void moverAtras(Lista *lista){
	if (lista != NULL && lista->nodo_actual != lista->inicio){
		lista->posicion_actual -=1;
	}
	

}

//void insertarpos(Lista *lista, int *dato){

//}

int main(){
	//Leer el archivo
	unsigned int cantidad = 0;
	string lectura;
	ifstream polinomiosFile; 
	polinomiosFile.open("entradaPolinomio.txt"); 
	cout << "El archivo se abrio bien\n";

   	// Verificar si se abrio bien el archivo
	if (!polinomiosFile.is_open()) {
		cout << "Error al abrir el archivo";
		return 0;
	}
	//obtener la cantidad y la lectura en que esta
	getline(polinomiosFile,lectura);
	cantidad = atoi(lectura.c_str());
	Lista Poli[cantidad];
	cout << "cantidad="<<cantidad <<"\n";
	//Lista Polinomios[cantidad];	
	cout << "lectura="<<lectura<<"\n";

	// Asigno variables 
	//int grados[cantidad+2];
	//cout <<grados <<"\n";
	unsigned int leidos = 0;
	unsigned int i = 0;
	int exponente=0;
	stringstream iss;
	while(leidos < cantidad){
		//cout<< cantidad <<"cantidad\n";
		getline(polinomiosFile,lectura);
		unsigned int monomios = atoi(lectura.c_str());
		int exponentemayor= 0;
		cout <<"cantidad de Monomio : " << monomios;
		cout <<"\n";

		int coeficiente;
		i = 0;
		//while para encontrar el exponente mayor
		while(i < monomios){
			string read;
			string monomio[2];
			getline(polinomiosFile,lectura);
			iss << lectura;
			int pos  = 0;
			while ( getline(iss, read, ' ') )
			{	
				monomio[pos] = read;
				++pos;
			}
			iss.clear();
			exponente = atoi((monomio[0]).c_str());
			i++;
			if (exponentemayor < exponente){
				exponentemayor = exponente;
				}
		}	
		cout <<exponentemayor<<" Exponente mayor del polinomio  "<<leidos<<"\n";
		cout <<"\n";
		//crear listas vacias sin este while a las 17:16 min compila el codigo
		k=0
		while(k<=exponentemayor){
			append(Poli[leidos],0); 
			k++
		}
		//termino del while
		leidos++;
	}
	polinomiosFile.close();

	string lectura1;
	ifstream polinomiosFile1; 
	int cantidad1=0;
	polinomiosFile1.open("entradaPolinomio.txt"); 
	cout << "El archivo se abrio bien\n";

	//obtener la cantidad y la lectura en que esta
	getline(polinomiosFile1,lectura1);
	cantidad1 = atoi(lectura1.c_str());
	cout << "cantidad1="<<cantidad1 <<"\n";
	//Lista Polinomios[cantidad1];	
	cout << "lectura1="<<lectura1<<"\n";
	leidos=0;
	while(leidos < cantidad1){
		//cout<< cantidad <<"cantidad\n";
		getline(polinomiosFile1,lectura1);
		unsigned int monomios = atoi(lectura1.c_str());
		cout <<"Polinomio"<<leidos<<"\n";
		cout <<"cantidad de Monomio : " << monomios<<"\n";
		int exponente;
		float coeficiente;
		i = 0;
		//While para obtener exponente y coeficientes del polinomio
			while(i < monomios){
				string read;
				string monomio[2];
				getline(polinomiosFile1,lectura1);
				iss << lectura1;
				int pos  = 0;

				while ( getline(iss, read, ' ') )
				{	
					monomio[pos] = read;
					++pos;
				}
				iss.clear();
				exponente = atoi((monomio[0]).c_str());
				coeficiente = atof((monomio[1]).c_str());
				//funcionaba a las 17:17, ants del while a continuacion
				//SOLO REEMPLAZAR 
				//int largo;
				//largo= Poli[leidos]->tamano;
				//------>>> actualizar(Poli[leidos],exponente, coeficiente);
				cout <<"exponente1:"<<exponente<<"\n";
				cout <<"coeficiente1:"<<coeficiente<<"\n";
				cout <<"\n";

				i++;
			}
			leidos++;

	while (getline(polinomiosFile,lectura)){
		string operaciones[3];
		int pos = 0;
		iss << lectura;
		while ( getline(iss, read, ' ') )
		{
			operaciones[pos] = read;
			++pos;
		}
		iss.clear();
		if(operaciones[0] == "COEFICIENTE"){


		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner

		}
	}		
	polinomiosFile.close();		
	return 0;
		}		

//laeiu maeiour aeioustaeioubaeiou saieouraeiounaeiou



}


//Lista *L1 = inicializar();
				//unsigned int k=0;
				//while(k<exponentemayor+1){
				//	append(L1, 0);

				//	k++;
//int append(Lista * lista, char *dato);
				//cout <<L1->inicio<<"imprimo lista\n";
				//borrar(L1);