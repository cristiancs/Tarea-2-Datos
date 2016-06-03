#include <iostream>
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
  bool buscar(int a);
  bool push(int a);
  bool borrar(int a);
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

bool Lista_ord::push(int a){
  caja *p;
  p = new caja;
  p -> valor = a;

  p -> siguiente = principio;
  principio = p;

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

int main()
{
  
  Lista_ord lista;
  int valor_elemento;
  int op;
  cout << "Lista\n";
  cout << "0: Agregar elemento\t";
  cout << "1: Sacar elemento\n";
  cout << "2: Cuantos?\t\t";
  cout << "3: Pintar\n";
  cout << "-1: Salir\n\n";

  while(op != -1){
      cout << "Op: ";
        cin >> op;
        switch (op){
            case 0:
                cout << "Elemento a agregar: ";
                cin >> valor_elemento;
                if( ! lista.push(valor_elemento) ){
                    cout<<"El elemento ya se encontraba en la lista!\n";
                }
                break;
            case 1:
                if(lista.get_cuantos() != 0){
                    cout << "Se saco el elemento " << lista.pop() <<"\n";
                }else{
                    cout << "La lista esta vacia.\n";
                }
                break;
            case 2:
                cout << "La lista tiene "<< lista.get_cuantos() << " elementos\n";
                break;
        }
  }
  
  return 0;
}