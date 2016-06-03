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

class Lista_ord{
	caja *principio, *anterior;
	unsigned int cuantos;
	bool encontrado;
	enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
	donde_enum donde;
public:
	Lista_ord();
	~Lista_ord(); 
	bool buscarValor(unsigned int a, double* coeficiente);
	bool buscar(double a);
	bool actualizar(unsigned int a, double valor);
	bool push(double a);
	bool borrar();
	int get_cuantos();
};

Lista_ord::Lista_ord(){
	principio = NULL;
	anterior = NULL;
	cuantos = 0;
	encontrado = false;
	donde = VACIO;
}

Lista_ord::~Lista_ord(){
	caja *p, *q;
	p = principio;
	while(p){
		q = p;
		p = p -> siguiente;
		delete q;
	}
	cuantos = 0;
}


bool Lista_ord::actualizar(unsigned int posicion, double valor){
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
bool Lista_ord::buscar(double a){
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
bool Lista_ord::buscarValor(unsigned int posicion, double *coeficiente){
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
bool Lista_ord::push(double a){
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


bool Lista_ord::borrar(){
	caja *p;
	donde = FINAL;
	p = anterior -> siguiente;
	anterior -> siguiente = NULL;
	delete p;
	cuantos --;
	return true;
}

int Lista_ord::get_cuantos(){
	return cuantos;
}
// Horner
double horner(Lista_ord *coeffs, int s, double x)
{
	int i;
	double res = 0.0;
	double k;

	for(i=s-1; i >= 0; i--)
	{	
		coeffs->buscarValor(i,&k);
		res = res * x + k; 
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
	Lista_ord Poli[cantidad]; 

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

		unsigned int k=0;
		while(k<=exponentemayor){
			Poli[leidos].push(0);
			k++;
		}

		leidos++;
	}
	polinomiosFile.close();

	string lectura1;
	ifstream polinomiosFile1; 
	unsigned int cantidad1=0;
	polinomiosFile1.open("entradaPolinomio.txt"); 

	//obtener la cantidad y la lectura en que esta
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
	string read;
	ofstream salidaFile;
	salidaFile.open("salidaPolinomio.txt");
	
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
			// lista de coefientes
			salidaFile <<  horner(&Poli[polinomio], grado,valor) << "\n";

			
		}
	}
	polinomiosFile1.close();
	salidaFile.close();
	i=0;
	while(i<cantidad){
		while (Poli[i].get_cuantos()!=0){
			Poli[i].borrar();
		}
		i++;
	}		
	return 0;	
}			

