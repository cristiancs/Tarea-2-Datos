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

void buscar(ABB arbol, int* coeficiente, unsigned int exponente){
	if(arbol!=NULL){
		if(exponente == arbol->exponente){
			*coeficiente = arbol->coeficiente;
		}
		else if(exponente > arbol->exponente){
			buscar(arbol->der, coeficiente, exponente);
		}
		else{
			buscar(arbol->izq, coeficiente, exponente);
		}
	}
}

void enOrden(ABB arbol, double *lista){
	if(arbol!=NULL){
		enOrden(arbol->izq, lista);
		lista[arbol->exponente] = arbol->coeficiente;
		enOrden(arbol->der, lista);
	}
}

// Horner
double horner(double *coeffs, int s, double x)
{
  int i;
  double res = 0.0;
 
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
	int i = 0;
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
	ofstream salidaFile;
	salidaFile.open("salidaPolinomio.txt");
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
			int polinomio = atoi(operaciones[1].c_str());
			unsigned int exponente = atof(operaciones[2].c_str());
			int* coeficiente = (int*) malloc(sizeof(int));
			*coeficiente = 0;
			buscar(polinomios[polinomio], coeficiente, exponente);
			salidaFile << *coeficiente << "\n";
			free((void *) coeficiente);
		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner
			int polinomio = atoi(operaciones[1].c_str());

			int grado = grados[polinomio];
			double valor = atof(operaciones[2].c_str());

			// lista de coefientes
			double *coeffs;
			coeffs = (double *) calloc(grado, sizeof(double));
			enOrden(polinomios[polinomio],coeffs);
			salidaFile <<  horner(coeffs, grado+1,valor) << "\n";
			free((void *) coeffs);
		}
	}
	polinomiosFile.close();
	salidaFile.close();
	return 0;
}