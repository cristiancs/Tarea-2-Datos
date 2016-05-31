#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>

using namespace std;
// Implementación ABB Polinomios
struct nodo{
	int coeficiente;
	unsigned int exponente;
	struct nodo *izq, *der;
};

typedef struct nodo *ABB;

ABB crearNodo(int coeficiente, unsigned int exponente){
	ABB nuevoNodo = new(struct nodo);
	nuevoNodo->coeficiente = coeficiente;
	nuevoNodo->exponente = exponente;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}
void insertar(ABB &arbol, int coeficiente, unsigned int exponente){
	if(arbol==NULL)
	{
		arbol = crearNodo(coeficiente,exponente);
	}
	else if(exponente < arbol->exponente)
		insertar(arbol->izq, coeficiente,exponente);
	else if(exponente > arbol->exponente)
		insertar(arbol->der, coeficiente,exponente);
}

void preOrden(ABB arbol){
	if(arbol!=NULL)
	{
		cout << arbol->coeficiente <<"x^" << arbol->exponente << " ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

void enOrden(ABB arbol, unsigned int *lista){
	if(arbol!=NULL){
		enOrden(arbol->izq, lista);
		lista[arbol->exponente] = arbol->coeficiente;
		//cout << arbol->coeficiente <<"x^" << arbol->exponente << " ";
		enOrden(arbol->der, lista);
	}
}

void postOrden(ABB arbol){
	if(arbol!=NULL)
	{
		postOrden(arbol->izq);
		postOrden(arbol->der);
		cout << arbol->coeficiente <<"x^" << arbol->exponente << " ";
	}
}

void verArbol(ABB arbol, int n){
	if(arbol==NULL)
		return;
	verArbol(arbol->der, n+1);

	for(int i=0; i<n; i++)
		cout<<"   ";

	cout << arbol->coeficiente <<"x^" << arbol->exponente << " +";

	verArbol(arbol->izq, n+1);
}

// Horner
unsigned int horner(unsigned int *coeffs, int s, int x)
{
	int i;
	unsigned int res = 0.0;

	for(i=s-1; i >= 0; i--)
	{
		res = res * x + coeffs[i];
	}
	return res;
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
	ABB polinomios[cantidad+2];
	int grados[cantidad+2];
	// Pasar los Polinomios a ABB
	unsigned int leidos = 0;
	unsigned int i = 0;
	stringstream iss;
	//cout << "[debug]" << cantidad << endl;
	while(leidos < cantidad){
	//cout << "[debug]" << leidos << "," << cantidad << endl;
		getline(polinomiosFile,lectura);
		int monomios = atoi(lectura.c_str());
		int exponente;
		int coeficiente;
		i = 0;
		while(i < monomios){
			string read;
			string monomio[2];
			getline(polinomiosFile,lectura);
			iss << lectura;
			int pos  = 0;
			//cout << lectura << endl;
			while ( getline(iss, read, ' ') )
			{
				monomio[pos] = read;
				++pos;
			}
			iss.clear();
			exponente = atoi((monomio[0]).c_str());
			coeficiente = atoi((monomio[1]).c_str());
			grados[leidos] = monomios;
			insertar(polinomios[leidos], coeficiente, exponente);
			i++;
		}
		leidos++;
	}

	// Operaciones
	string read;
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
			// Buscar Coeficiente
		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner
			int polinomio = atoi(operaciones[1].c_str());

			int grado = grados[polinomio];
			float valor = atof(operaciones[2].c_str());

			// // unsigned int *coeffs[grado];
			// unsigned int **coeffs;
			// coeffs = malloc( sizeof(unsigned int) * grado);
			// int i = 0;
			// enOrden(polinomios[polinomio],coeffs);
			// for (i = 0; i < grado; ++i)
			// {
			// 	cout << coeffs[grado] << endl;
			// }
			//cout << grado << "," << valor << endl;
		}
	}

	// Horner
	

	//double coeffs[] = {-3, 3 };

	// cout <<  horner(coeffs, 2,3.5) << endl;


	//enOrden(polinomios[0]);
	cout << "\n";
	// cout << "\n";

	return 0;
}