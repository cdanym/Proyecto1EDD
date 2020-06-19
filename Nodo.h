#ifndef NODOLISTA_H
#define NODOLISTA_H
#include <string>
#include <iostream>
using namespace std;

class Nodo
{
protected:
	
public:
	string dato;
	int numero;

	Nodo *anterior;
	Nodo *siguiente;

	Nodo(string dato){
		this->dato = dato;
		//dato = d;
		anterior = NULL;
		siguiente = NULL;
	}

	Nodo(int numero){
		this->numero = numero;
		anterior = NULL;
		siguiente = NULL;
	}

	string getDato(){
		return dato;
	}

	int getNumero(){
		return numero;
	}

	Nodo *getAnterior(){
		return anterior;
	}

	Nodo *getSiguiente(){
		return siguiente;
	}

	void setAnterior(Nodo *anterior){
		this->anterior = anterior;
	}
	void setSiguiente(Nodo *siguiente){
		this->siguiente = siguiente;
	}

	~Nodo();

};

#endif