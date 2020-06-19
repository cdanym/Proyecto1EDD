#ifndef NODOMATRIZ
#define NODOMATRIZ

#include "NodoArbol.h"
#include "Arbol.h"
#include <string>
#include <iostream>
using namespace std;

class NodoMatriz
{
public:
	string nombre, contrasenia, departamento, empresa;
	NodoMatriz* anterior;
	NodoMatriz* posterior;
    NodoMatriz* superior;
    NodoMatriz* inferior; 
	Arbol<string> *misActivos;

	NodoMatriz(string nombre, string contrasenia, string departamento, string empresa){
		this->nombre = nombre;
		this->contrasenia = contrasenia;
		this->departamento = departamento;
		this->empresa = empresa;
		anterior = posterior = superior = inferior = NULL;
		misActivos = new Arbol<string>();
	};

	Arbol<string> *getActivos(){ //RETORNA EL ARBOL CON LOS ACTIVOS QUE POSEE EL USUARIO
		return misActivos;
	}

	string getNombre(){
		return nombre;
	}

	string getContrasenia(){
		return contrasenia;
	}

	string getDepartamento(){
		return departamento;
	}

	string getEmpresa(){
		return empresa;
	}

	NodoMatriz* getAnterior(){
		return this->anterior;
	}

	NodoMatriz* getPosterior(){
		return this->posterior;
	}

	NodoMatriz* getSuperior(){
		return this->superior;
	}

	NodoMatriz* getInferior(){
		return this->inferior;
	}

	void setAnterior(NodoMatriz* anterior){
		this->anterior = anterior;
	}

	void setPosterior(NodoMatriz* posterior){
		this->posterior = posterior;
	}

	void setSuperior(NodoMatriz* superior){
		this->superior = superior;
	}

	void setInferior(NodoMatriz* inferior){
		this->inferior = inferior;
	}

	~NodoMatriz();
};


#endif