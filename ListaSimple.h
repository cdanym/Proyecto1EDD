#ifndef LISTA_H
#define LISTA_H

#include <fstream>
#include <iostream>
using namespace std;
#include "Nodo.h"

class ListaSimple
{
public:
	Nodo *primero;
	Nodo *ultimo;
	ListaSimple()
	{
		primero = ultimo = NULL;
	};

	bool estaVacia(); //---
	void insertarInicio(string dato); //---
	void insertarFinal(string dato); //---
	//void insertarEntreNodos(int *anterior, string dato);
	Nodo* bucarNodo(string datoNodo); //---
	void eliminarInicio(); //---
	void eliminarFinal(); //---
	void eliminarNodo(string dato);
	void visualizarListaInt(); //---
	void visualizarLista(); //---
	void listaOrdenadaInt(int dato); //---
	void listaOrdenadaString(string dato); //---

	//~ListaSimple();
	
};


bool ListaSimple::estaVacia()
{
	return ((primero==NULL) && (ultimo==NULL));
}

void ListaSimple::insertarInicio(string dato)
{
	Nodo *nuevo = new Nodo(dato); //Se crea el nuevo nodo;
	if (ListaSimple::estaVacia())
	{
		primero = ultimo = nuevo;
	}
	else
	{
		nuevo -> setSiguiente(primero); //Se enlaza el nuevo nodo al primero
		primero = nuevo; //Se verifica que el nodo creado sea el primero
	}
}

void ListaSimple::insertarFinal(string dato)
{
	Nodo *nuevo = new Nodo(dato); //Creando el nuevo nodo
	if (ListaSimple::estaVacia())
	{
		primero = ultimo = nuevo;
	}
	else
	{
		ultimo -> setSiguiente(nuevo); //Se enlaza el ulitmo nodo al nuevo
		ultimo = nuevo; //Se verifica que el ndo creado sea el ultimo
	}
}


void ListaSimple::eliminarInicio()
{
	if (ListaSimple::estaVacia())
	{
		cout << "La lista esta vacia" << endl;
	}
	else
	{
		Nodo* segundo = primero -> getSiguiente();
		primero = segundo;
	}
}

void ListaSimple::eliminarFinal()
{
	if (ListaSimple::estaVacia())
	{
		cout << "La lista esta vacia" << endl;
	}
	else
	{
		Nodo* temporal = primero;
		if (primero == ultimo) //Si primero y ultimo son igulaes, solo hay un elemento en la lista
		{
			primero = ultimo = NULL; //Se eliminan las referencias
		}
		while (temporal != NULL)
		{
			if (temporal -> getSiguiente() == ultimo) //Si el siguiente de temporal es el ultimo, entonces temporal es el antepenultimo
			{
				//cout << "---Se encontro el ultimo nodo---" << endl;
				temporal -> setSiguiente(NULL); //Se cambia el enlace, quitando la referencia del ultimo nodo
				ultimo = temporal; //Se verifica que temporal sea el ultimo
				//cout << "Fin de la lista--- " << temporal -> siguiente <<endl;
				break;
			}
			temporal = temporal -> getSiguiente(); //Recorriendo la lista
		}
	}
}

void ListaSimple::visualizarLista()
{
	if (ListaSimple::estaVacia())
	{
		cout << "La lista esta vacia" << endl;
	}
	else
	{
		string nodo;
		ofstream archivo;
		archivo.open("graficaLS.dot",ios::out);
		archivo << "digraph G { rankdir = LR " << endl;

		Nodo* actual = primero;
		while(actual != NULL)
		{
			if(actual -> getSiguiente() != NULL){
				nodo = actual -> getDato();
				archivo << nodo;
				archivo << " -> ";
				//cout << nodo << endl;
				actual = actual -> getSiguiente();
			}
			else{
				nodo = actual -> getDato();
				archivo << nodo;
				//cout << nodo << endl;
				actual = actual -> getSiguiente();
			}
		}
		archivo << "; }";
		archivo.close();
		system("dot -Tpng graficaLS.dot -o graficaLS.png");
		system("display graficaLS.png &");
	}
}


#endif