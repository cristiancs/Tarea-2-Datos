#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>
#include <iomanip>

using namespace std;

struct caja{
	double valor;
	caja* siguiente;
};
// Clase definiendo Lista enlazada
class Listapoli{
	caja *principio, *anterior;
	unsigned int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
/*

*/
//Se definen las funciones del TDA .
public:
	Listapoli();
	~Listapoli(); 
	bool buscarValor(unsigned int a, double* coeficiente);
	bool buscar(double a);
	bool actualizar(unsigned int a, double valor);
	bool push(double a);
	bool borrar();
	int get_cuantos();
};
/*****
* Listapoli::Listapoli
******
* Defino las casillas NULL , para crear una lista vacia.
* Returns:
* no retorna nada
*****/
Listapoli::Listapoli(){
	principio = NULL;
	anterior = NULL;
	cuantos = 0;
	encontrado = false;
	donde = VACIO;
}
/*****
* Listapoli::~Listapoli
******
* Libera memoria utilizada en la lista.
******
* Returns:
* no retorna nada
*****/
Listapoli::~Listapoli(){
	caja *p, *q;
	p = principio;
	while(p){
		q = p;
		p = p -> siguiente;
		delete q;
	}
	cuantos = 0;
}
/*****
* bool Listapoli::actualizar
******
* Modifica elemento de la lista en la posición entregada.
* Reemplaza el valor que ya esta en la lista por el entregado.
******
* Input:
Recibe unsigned int posicion, que indica en que posición se quiere modificar el valor, y también recibe
double valor , que es el valor que se quiere poner en la posición indicada.
******
* Returns:
* Valor booleano si se realizo bien la actualización.
*****/

bool Listapoli::actualizar(unsigned int posicion, double valor){
	caja *p;
	unsigned int i = 0;
	p = principio;
	if (!p){
		donde = VACIO;
		return false;
	}
	while (p){
		if (i == posicion){
			p->valor = valor;

			return true;
		}else{
			anterior = p;
			p = p -> siguiente;
		}
		i++;
	}
	return false;
}
/*****
* bool Listapoli::buscar
******
* Busca la posición entregada dentro de la lista.
******
* Input:
double a, posición que se busca.
******
* Returns:
* Booleano , para saber si se llega a la posición.
*****/

bool Listapoli::buscar(double a){
	caja *p;
	p = principio;
	if (!p){
		donde = VACIO;
		return false;
	}

	while (p){
		if (p -> valor == a){
			if(p == principio){
				donde = PRINCIPIO;
			}else{
				donde = ENMEDIO;
			}
			return true;
		}else if (p -> valor > a){
			if(p == principio){
				donde = PRINCIPIO;
			}else{
				donde = ENMEDIO;
			}
			return false;
		}else{
			anterior = p;
			p = p -> siguiente;
		}
	}
	donde = FINAL;
	return false;
}

/*****
* bool Listapoli::buscarValor
******
* Obtiene el valor de la posición que se pide , y este se modifica en un puntero,
asignado para este codigo como "coeficiente".
******
* Input:
unsigned int posicion, la posición de donde se quiere obtener el valor , en este programa la posición corresponde
al exponente del polinomio.
double *coeficiente , puntero el cual se modifica para obtener el valor contenido en la posición.
******
* Returns:
* Booleano si se encontro el valor (coeficiente) en la posición(exponente).
*****/

bool Listapoli::buscarValor(unsigned int posicion, double *coeficiente){
	caja *p;
	unsigned int i = 0;
	p = principio;
	if (!p){
		donde = VACIO;
		return false;
	}

	while (p){
		if (i == posicion){
			*coeficiente = p->valor;
			return true;
		}else{
			anterior = p;
			p = p -> siguiente;

		}
		i++;
	}
	return false;
}

/*****
* bool Listapoli::push
******
* Agrega valores a la lista.
* Principalmente lo utilizamos para iniciar una lista del tamaño del polinomio en cuestión llena de 0.
******
* Input:
*double a ,posición por la cual se irá avanzando para agregar "n" elementos.
******
* Returns:
* True al momento de agregar los valores.
*****/

bool Listapoli::push(double a){
	caja *p;
	buscar(a);
	p = new caja;
	p -> valor = a;
	if (donde == VACIO){
		p -> siguiente = NULL;
		principio = p;
	}else if (donde == PRINCIPIO){
		p -> siguiente = principio;
		principio = p;
	}else{
		p -> siguiente = anterior -> siguiente;
		anterior -> siguiente = p;
	}

	cuantos++;
	return true;
}
/*****
* bool Listapoli::borrar
******
* Elimina elemento de la lista
******
* Input:
No recibe nada , solo se le aplica al elemento esta función para eliminarlo de la lista.
******
* Returns:
* Booleano True para confirmar que se realizó correctamente la eliminación.
*****/
bool Listapoli::borrar(){
	caja *p;
	donde = FINAL;
	p = anterior -> siguiente;
	anterior -> siguiente = NULL;
	delete p;
	cuantos --;
	return true;
}

/*****
* int Listapoli::get_cuantos
******
* Cuenta cuantos elementos posee la lista.
* Importante para comprobar que la lista se haya creado correctamente de los n elementos que se le solicitó.
******
* Input:
no recibe nada.
******
* Returns:
* Retorna la cantidad que de elementos contenidos en la lista.
*****/
int Listapoli::get_cuantos(){
	return cuantos;
}
/*****
* double horner
******
* Aplica algoritmo de horner al polinomio. Evaluar "x" en el polinomio.
******
* Input:
Listapoli *coeffs, 
int s, tamaño del polinomio. (exponente mayor)
double x, valor donde se va a evaluar.
double *k, puntero a la variable donde se alamacenará el valor buscado
******
* Returns:
* Res, resultado de la aplicación del algoritmo
*****/
// Horner
double horner(Listapoli *coeffs, int s, double x, double *k)
{
	int i;
	double res = 0.0;

	for(i=s-1; i >= 0; i--)
	{	
		coeffs->buscarValor(i,k);
		res = res * x + *k; 
	}
	return res;
}


int main(){
	//Leer el archivo
	unsigned int cantidad = 0;
	string lectura;
	ifstream polinomiosFile; 
	polinomiosFile.open("entradaPolinomio.txt"); 

   	// Verificar si se abrio bien el archivo
	if (!polinomiosFile.is_open()) {
		cout << "Error al abrir el archivo";
		return 0;
	}
	//obtener la cantidad y la lectura en que esta
	getline(polinomiosFile,lectura);
	cantidad = atoi(lectura.c_str());
	//crear arreglo con la cantidad de listas que se necesita (cantidad de polinomios)
	Listapoli Poli[cantidad]; 

	// Asigno variables 
	unsigned int leidos = 0;
	unsigned int i = 0;
	unsigned int exponente=0;
	stringstream iss;
	while(leidos < cantidad){
		getline(polinomiosFile,lectura);
		unsigned int monomios = atoi(lectura.c_str());
		unsigned int exponentemayor= 0;

		i = 0;
		//while para encontrar el exponente mayor
		while(i < monomios){
			string read;
			string monomio[2];
			getline(polinomiosFile,lectura);
			iss << lectura;
			unsigned int pos  = 0;
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
		// Completar las listas creadas llenandolas de 0, hasta el largo del polinomio , definido por el exponente mayor.
		unsigned int k=0;
		while(k<=exponentemayor){
			Poli[leidos].push(0);
			k++;
		}

		leidos++;
	}
	//Cierro archivo para poder recorrerlo denuevo.
	polinomiosFile.close();

	//Defino variables similares a las anteriores para una lectura desde el comienzo
	string lectura1;
	ifstream polinomiosFile1; 
	unsigned int cantidad1=0;
	polinomiosFile1.open("entradaPolinomio.txt"); 

	//obtener la cantidad y la lectura en que esta
	//se obtiene los valores del exponente, coeficiente, cantidad de polinomios, y monomios que los componen.
	getline(polinomiosFile1,lectura1);
	cantidad1 = atoi(lectura1.c_str());
	leidos=0;
	while(leidos < cantidad1){
		getline(polinomiosFile1,lectura1);
		unsigned int monomios = atoi(lectura1.c_str());
		unsigned int exponente;
		double coeficiente;
		i = 0;
		//While para obtener exponente y coeficientes del polinomio
		while(i < monomios){
			string read;
			string monomio[2];
			getline(polinomiosFile1,lectura1);
			iss << lectura1;
			unsigned int pos  = 0;

			while ( getline(iss, read, ' ') )
			{	
				monomio[pos] = read;
				++pos;
			}
			iss.clear();
			exponente = atoi((monomio[0]).c_str());
			coeficiente = atof((monomio[1]).c_str());
			Poli[leidos].actualizar(exponente,coeficiente);


			i++;
		}
		leidos++;
	}
	//creo archivo de salida , con variables neesarias.
	string read;
	ofstream salidaFile;
	salidaFile.open("salidaPolinomio.txt");
	//recorro el archivo de entrada para encontrar valores donde evaluar, y aplicar algoritmo.
	while (getline(polinomiosFile1,lectura1)){
		string operaciones[3];
		unsigned int pos = 0;
		iss << lectura1;
		while ( getline(iss, read, ' ') )
		{
			operaciones[pos] = read;
			++pos;
		}
		iss.clear();

		if(operaciones[0] == "COEFICIENTE"){
			unsigned int polinomio = atoi(operaciones[1].c_str());
			unsigned int exponente = atoi(operaciones[2].c_str());
			double* coeficiente = (double*) malloc(sizeof(double));
			*coeficiente = 0;
			Poli[polinomio].buscarValor(exponente, coeficiente);
			double valor = *coeficiente;
			free((void *) coeficiente);
			salidaFile << std::fixed << std::setprecision(6) << valor << "\n";

		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner
			unsigned int polinomio = atoi(operaciones[1].c_str());
			unsigned int grado = Poli[polinomio].get_cuantos();
			double valor = atof(operaciones[2].c_str());
			double *k = (double *) malloc(sizeof(double));
			//aplico algoritmo de horner
			double retorno = horner(&Poli[polinomio], grado,valor, k);
			free((void *) k);
			salidaFile << retorno << "\n";

			
		}
	}
	//cierro archivos
	polinomiosFile1.close();
	salidaFile.close();
	i=0;
	//while para eliminar los bloques generados.
	while(i<cantidad){
		Poli[i].~Listapoli();
		i++;
	}
	return 0;	
}	