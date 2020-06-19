#ifndef ARBOL
#define ARBOL

#include <fstream>
#include <iomanip>
#include <iostream>
#include <bits/stdc++.h> 
using namespace std;
#include "NodoArbol.h"

template <class T> class Arbol
{
private:

public:
	ofstream archivo;
    string nodo;

	NodoArbol<T> *raiz;
	int recorridoNodos;

    Arbol(){
        recorridoNodos = 0;
        raiz = NULL;
    }

    void insertar(T nombre, T id, T descripcion){
        raiz = insertarNodo(raiz, nombre, id, descripcion); //25, 15
    };

    NodoArbol<T> *insertarNodo(NodoArbol<T> *subArbol, T nombre, T id, T descripcion){
        if (subArbol == NULL) //El arbol esta vacio
        {
            NodoArbol<T> *nuevo = new NodoArbol<T>(nombre, id, descripcion);
            subArbol = nuevo; //10
        }
        else if(id < subArbol->getId()){ //Se inserta del lado izquierdo
            NodoArbol<T> *nodoIzq;
            nodoIzq = insertarNodo(subArbol->getIzq(),nombre,id,descripcion); //10, 15
            subArbol -> setIzq(nodoIzq); //
        }
        else if(id > subArbol->getId()){ //Se inserta del lado derecho
            NodoArbol<T> *nodoDer;
            nodoDer = insertarNodo(subArbol->getDer(),nombre,id,descripcion);
            subArbol -> setDer(nodoDer); 
        }
        else{
            cout << "Nodo duplicado\n";
        }
        return subArbol; //10
    };
    
    NodoArbol<T> *buscar(T id){
        return buscarNodo(raiz,id);
    };
    
    NodoArbol<T> *buscarNodo(NodoArbol<T> *temporal, T id){
        if(temporal == NULL){
            cout << "Null \n";
            return NULL;
        }
        else if(id == temporal->getId())
            return temporal;
        else if(id < temporal->getId())
            return buscarNodo(temporal->getIzq(), id);
        else if(id > temporal->getId())
            return buscarNodo(temporal->getDer(), id);
    };

    void eliminar(T id){
        raiz = eliminarNodo(raiz,id);
    }

    NodoArbol<T> *eliminarNodo(NodoArbol<T> *temporal, T id){
        
        NodoArbol<T> *tempIzq;
        NodoArbol<T> *tempDer;
        //tempIzq = temporal->getIzq();
        //tempDer = temporal->getDer();
        if(temporal == NULL){
            cout << "Null " << endl;
            return NULL;
        }
        else if(id == temporal->getIzq()->getId()){ //Nodo->izquierda = dato a eliminar
            tempIzq = temporal->getIzq();
            if(tempIzq->getIzq()==NULL && tempIzq->getDer()!=NULL){ //Nodo a eliminar tiene solo hijo derecho
                temporal->setIzq(tempIzq->getDer());
                return temporal;
            }
            else if(tempIzq->getIzq()!=NULL && tempIzq->getDer()==NULL){ //Nodo a eliminar tiene solo hijo izquierdo
                temporal->setIzq(tempIzq->getIzq());
                return temporal;
            }
            else if(tempIzq->getIzq()!=NULL && tempIzq->getDer()!=NULL){ //El nodo a eliminar tiene hijo derecho e izquierdo
                tempIzq=tempIzq->getIzq();
                if(tempIzq->getIzq()==NULL){ //El nodo a eliminar solamente tiene un nodo del lado izquierdo
                    temporal->setIzq(tempIzq);
                }
                else{ //El nodo a eliminar tiene mas hijos del lado izquierdo
                tempDer=tempIzq->getDer();
                    while (true)
                    {
                        if(tempDer->getDer()==NULL){
                            temporal->getIzq()->id=tempDer->getId();
                            //buscar(tempDer->dato) = NULL;
                            tempDer==NULL;
                            break;
                        }
                        tempDer=tempDer->getDer();
                    }

                }
            }
            ///return temporal;
        }
        else if(id == temporal->getDer()->getId()){ //Nodo->derecha = dato a eliminar
            tempDer = temporal->getDer();
        }
        else if(id < temporal->getId()){
            eliminarNodo(temporal->getIzq(), id);
        }
        else if(id > temporal->getId()){
            eliminarNodo(temporal->getDer(), id);
        }
        else{
            cout << tempIzq->getId() << endl;
            cout << tempDer->getId() << endl;
        }
        return temporal;
        
    }
    
    void visualizarArbol(){
        archivo.open("graficaA.dot",ios::out);
        archivo << "digraph G {" << endl;

        visualizarArbol(raiz);

        archivo << "}";
        archivo.close();
        system("dot -Tpng graficaA.dot -o graficaA.png");
        system("display graficaA.png &");
    };
    
    void visualizarArbol(NodoArbol<T>* temporal){
        if(temporal == NULL){
            //cout << "Arbol vacio\n";
            return;
        }
        if(temporal->getIzq() != NULL){
            nodo = temporal->getNombre();
            archivo << nodo; archivo << " -> ";
            nodo = temporal->getIzq()->getNombre();
            archivo << nodo; archivo << ";";
        }
        visualizarArbol(temporal->getIzq());
        if(temporal->getDer() != NULL){
            nodo = temporal->getNombre();
            archivo << nodo; archivo << " -> ";
            nodo = temporal->getDer()->getNombre();
            archivo << nodo; archivo << ";";
        }
        visualizarArbol(temporal->getDer());
    };

    void mostrar(){
        mostrarConsola(raiz);
    };

    void mostrarConsola(NodoArbol<T> *temporal){
        if (temporal != NULL)
        {
            cout << "ID: " << temporal-> getId() << " | Nombre: " << temporal->getNombre() << " | Descr: " << temporal->getDescripcion()  << endl;
            //return raizSub;
            mostrarConsola(temporal->getIzq());
            mostrarConsola(temporal->getDer());
        }
    };

};

#endif