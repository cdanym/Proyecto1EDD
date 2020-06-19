#ifndef NODOARBOL
#define NODOARBOL

#include <iostream>
using namespace std;

template <class T> class NodoArbol
{
private:

public:
    T nombre, id, descripcion;
    NodoArbol* izq;
	NodoArbol* der;

    NodoArbol(){
        izq = der = NULL;
    };

    NodoArbol(T nombre, T id, T descripcion){
        this->nombre = nombre;
		this->id = id;
		this->descripcion = descripcion;
        izq = der = NULL;
    };

	T getNombre(){
		return nombre;
	}
	
	T getId(){
		return id;
	}

	T getDescripcion(){
		return descripcion;
	}

	NodoArbol* getIzq(){
		return izq;
	}

	NodoArbol* getDer(){
		return der;
	}

	void setIzq(NodoArbol* izq){
		this->izq = izq;
	}

	void setDer(NodoArbol* der){
		this->der = der;
	}
};

#endif