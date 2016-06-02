#include <iostream>
#include <fstream>
// #include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>
#include <iomanip>

using namespace std;
// Implementación ABB Polinomios
struct nodo{
	int coeficiente;
	unsigned int exponente;
	struct nodo *izq, *der;
};

typedef struct nodo *ABB;

/*****
* ABB CrearNodo
******
* Crea nuevos nodos en el arbol binario
******
* Input:
* int coeficiente : Coeficiente del monomio a almacenar
* unsigned int exponente : Exponente del monomio a almacenar
******
* Returns:
* ABB nuevoNodo, Nodo creado con los valores ingresados
*****/
ABB crearNodo(int coeficiente, unsigned int exponente){
	ABB nuevoNodo = new(struct nodo);
	nuevoNodo->coeficiente = coeficiente;
	nuevoNodo->exponente = exponente;
	nuevoNodo->izq = NULL;
	nuevoNodo->der = NULL;

	return nuevoNodo;
}
/*****
* void insertar
******
* Inserta un elemento en el arbol ABB
******
* Input:
ABB &arbol: Arbol donde se insertara el nodo
int coeficiente: Coeficiente del monomio
unsigned int exponente: Exponente del monomio
******
* Returns:
* no retorna nada
*****/
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

/*****
* void liberar
******
* Libera la memoria del ABB
******
* Input:
ABB arbol: Arbol a Liberar
******
* Returns:
* no retorna nada
*****/
void liberar(ABB arbol)
{
     if(arbol!=NULL)
     {
          liberar(arbol->izq);
          liberar(arbol->der);
          free((void *) arbol);
     }
}

/*****
* void buscar
******
* Busca el elemento con el mismo exponente en el arbol
******
* Input:
ABB arbol : Arbol donde se buscaa
float* coeficiente : Puntero al coeficiente que se guardara al encontrar el valor
unsigned int exponente : Exponente Buscado
******
* Returns:
* No retorna nada
*****/
void buscar(ABB arbol, float* coeficiente, unsigned int exponente){
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
/*****
* void enOrden
******
* Resumen Función
******
* Input:
ABB arbol : Arbol donde se realiza la busqueda
double *lista : Puntero de la lista donde se guardaran los exponentes de cada coeficiente
******
* Returns:
* No retorna anda
*****/
void enOrden(ABB arbol, double lista[]){
	if(arbol!=NULL){
		enOrden(arbol->izq, lista);
		lista[arbol->exponente] = arbol->coeficiente;
		enOrden(arbol->der, lista);
	}
}

/*****
* double horner
******
* Resumen Función
******
* Input:
double *coeffs : Puntero a la lista de coeficientes
int s : Grado del polinomio
double x : Valor a evaluar el polinomio
******
* Returns:
* double res, Resultado de evaluar el polinomio en x
*****/
double horner(double coeffs[], int s, double x){
  int i;
  double res = 0.000000;
 
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
		cout << "Error al abrir el archivo" << endl;
		return 0;
	}
   	// Obtener Cantidad de Polinomios
	getline(polinomiosFile,lectura);
	cantidad = atoi(lectura.c_str());
	// Crear un array de ABB
	ABB polinomios[cantidad];
	int i = 0;
	while (i < cantidad){
		polinomios[i] = NULL;
		++i;
	}

	// int grados[cantidad];
	unsigned int mayorGrado[cantidad];
	// Pasar los Polinomios a ABB
	int leidos = 0;
	
	stringstream iss;
	while(leidos < cantidad){
		getline(polinomiosFile,lectura);
		int monomios = atoi(lectura.c_str());
		unsigned int exponente;
		int coeficiente;
		i = 0;
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
			if(exponente > mayorGrado[i]){
				mayorGrado[i] = exponente;
			}
			coeficiente = atoi((monomio[1]).c_str());
			// grados[leidos] = monomios;
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
			float* coeficiente = (float*) malloc(sizeof(float));
			*coeficiente = 0;
			buscar(polinomios[polinomio], coeficiente, exponente);
			int valor = *coeficiente;
			free((void *) coeficiente);
			salidaFile << valor << "\n";
		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner
			int polinomio = atoi(operaciones[1].c_str());

			int elementos = mayorGrado[polinomio];
			double valor = atof(operaciones[2].c_str());

			// lista de coefientes
			double coeffs[elementos];
			i = 0;
			while(i <= elementos){
				coeffs[i] = 0;
				++i;
			}

			enOrden(polinomios[polinomio],coeffs);
			i = 0;
			while(i <= elementos){
				// coeffs[i] = 0;
				if(coeffs[i] != 0){
					cout << coeffs[i] << "," << i << ";";
				}
				
				++i;
			}
			salidaFile << std::fixed << std::setprecision(6) << horner(coeffs, elementos+1,valor) << "\n";
			//salidaFile <<  horner(coeffs, grado+1,valor)  << "\n";

		}
	}
	polinomiosFile.close();
	salidaFile.close();
	i = 0;
	while(i < cantidad){
		liberar(polinomios[i]);
		++i;
	}
	
	return 0;
}