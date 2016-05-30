#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
using namespace std;
// Implementación ABB Polinomios
struct nodo{
	unsigned int nro;
	unsigned int exponente;
	struct nodo *izq, *der;
};

typedef struct nodo *ABB;

ABB crearNodo(unsigned int x, unsigned int y)
{
	ABB nuevoNodo = new(struct nodo);
	nuevoNodo->nro = x;
	nuevoNodo->exponente = y;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}
void insertar(ABB &arbol, unsigned int x, unsigned int y)
{
	if(arbol==NULL)
	{
		arbol = crearNodo(x,y);
	}
	else if(x < arbol->exponente)
		insertar(arbol->izq, x,y);
	else if(x > arbol->exponente)
		insertar(arbol->der, x,y);
}

void preOrden(ABB arbol)
{
	if(arbol!=NULL)
	{
		cout << arbol->nro <<"x^" << arbol->exponente << " ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

void enOrden(ABB arbol)
{
	if(arbol!=NULL)
	{
		enOrden(arbol->izq);
		cout << arbol->nro <<"x^" << arbol->exponente << " ";
		enOrden(arbol->der);
	}
}

void postOrden(ABB arbol)
{
	if(arbol!=NULL)
	{
		postOrden(arbol->izq);
		postOrden(arbol->der);
		cout << arbol->nro <<"x^" << arbol->exponente << " ";
	}
}

void verArbol(ABB arbol, int n)
{
	if(arbol==NULL)
		return;
	verArbol(arbol->der, n+1);

	for(int i=0; i<n; i++)
		cout<<"   ";

	cout<< arbol->nro << ", "<< arbol->exponente  <<endl;

	verArbol(arbol->izq, n+1);
}



int main(){

	// Read File
	int cantidad = 0;
	string lectura;
	ifstream polinomiosFile; 
	polinomiosFile.open("entradaPolinomio.txt"); 

   	// Verificar si se abrio bien el archivo
	if (!polinomiosFile.is_open()) {
		cout << "Error al abrir el archivo";
		return 0;
	}
   	// Obtener Cantidad de Polinomios
   	getline(polinomiosFile,lectura);
   	cantidad = atoi(lectura.c_str());
	// Crear un array de ABB
	ABB polinomios[cantidad]; 

	// Pasar los Polinomios a ABB
	unsigned int leidos = 0;
	unsigned int i = 0;
	while(leidos < cantidad){
		getline(polinomiosFile,lectura);
		int monomios = atoi(lectura.c_str());
		cout << monomios << "\n";
		while(i < monomios){
			getline(polinomiosFile,lectura);
			int exponente;
			int coeficientes;
			exponente = lectura[0];
			coeficientes = lectura[3];
			insertar(polinomios[leidos], exponente, coeficientes);
			i++;
		}
		leidos++;
	}

	verArbol(polinomios[0], 2);

	return 0;
}