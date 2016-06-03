#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* atoi */
#include <sstream>
#include <iomanip>

using namespace std;

struct caja{
  int valor;
  caja* siguiente;
};

class Lista_ord{
  caja *principio, *anterior;
  int cuantos;
  bool encontrado;
  enum donde_enum{VACIO, PRINCIPIO, ENMEDIO, FINAL};
  donde_enum donde;
public:
  Lista_ord();
  ~Lista_ord(); 
  bool buscarValor(int a, float* coeficiente);
  bool buscar(int a);
  bool actualizar(int a, int valor);
  bool push(int a);
  bool borrar(int a);
  void pintar();
  int pop();
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


bool Lista_ord::actualizar(int posicion, int valor){
    caja *p;
    int i = 0;
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
bool Lista_ord::buscar(int a){
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
bool Lista_ord::buscarValor(int posicion, float *coeficiente){
    caja *p;
    int i = 0;
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
bool Lista_ord::push(int a){
  caja *p;
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


bool Lista_ord::borrar(int a){
  caja *p;

  if (buscar(a))
        return false;

  if (donde == PRINCIPIO){
    p = principio;
    principio = p -> siguiente;
  }else if (donde == ENMEDIO){

    p = anterior -> siguiente;
    anterior -> siguiente = p -> siguiente;
  }else{
    p = anterior -> siguiente;
    anterior -> siguiente = NULL;
  }

  delete p;
  cuantos --;
  return true;
}

int Lista_ord::pop(){
  int valor;
  valor = principio -> valor;

  principio = principio -> siguiente;
  cuantos --;
  return valor;
}

int Lista_ord::get_cuantos(){
  return cuantos;
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
		//crear listas vacias sin este while a las 17:16 min compila el codigo
		int k=1;
		while(k<=exponentemayor){
			Poli[leidos].push(0);
			k++;
		}
		cout<< Poli[leidos].get_cuantos() <<"= largo de la lista\n";
		cout<<"\n";

		//termino del while
		leidos++;
	}
	polinomiosFile.close();

	string lectura1;
	ifstream polinomiosFile1; 
	unsigned int cantidad1=0;
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
				//SOLO REEMPLAZAR ;
				Poli[leidos].actualizar(exponente,coeficiente);
				cout <<"exponente1:"<<exponente<<"\n";
				cout <<"coeficiente1:"<<coeficiente<<"\n";
				cout <<"\n";

				i++;
			}
			leidos++;
	}
	string read;
	ofstream salidaFile;
	salidaFile.open("salidaPolinomio.txt");
	cout<< getline(polinomiosFile1,lectura1)<<"\n";
	while (getline(polinomiosFile1,lectura1)){
		cout<< "entre al while\n";
		string operaciones[3];
		cout <<operaciones;
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
			cout <<polinomio<<"\n";
			unsigned int exponente = atoi(operaciones[2].c_str());
			float* coeficiente = (float*) malloc(sizeof(float));
			*coeficiente = 0;
			Poli[polinomio].buscarValor(exponente, coeficiente);
			float valor = *coeficiente;
			cout<< valor<<"el valor encontrado\n";
			free((void *) coeficiente);
			salidaFile << std::fixed << std::setprecision(6) << valor << "\n";

		}
		else if(operaciones[0] == "EVALUAR"){
			// Horner

		}
	}		
	return 0;	
		}			

