#ifndef LISTACD_H
#define LISTACD_H

#include <fstream>
#include <iostream>
#include <bits/stdc++.h> //Libreria para usar el system

#include "Nodo.h"
using namespace std;

class ListaCircularDoble
{
    public:
        Nodo* primero;
        Nodo* ultimo;

        ListaCircularDoble()
        {
            primero = ultimo = NULL;
        };

        bool estaVacia();
        void insertarInicio(string dato);
        void insertarFinal(string dato);
        Nodo* buscarNodo(string dato);
        void eliminarInicio();
        void eliminarFinal();
        void visualizarLista();
        
};

bool ListaCircularDoble::estaVacia(){
    return (primero == NULL) && (ultimo == NULL);
}

void ListaCircularDoble::insertarInicio(string dato){
    Nodo* nuevo = new Nodo(dato);
    if(ListaCircularDoble::estaVacia()){
        nuevo -> setSiguiente(nuevo);
        nuevo -> setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else{
        nuevo -> setSiguiente(primero);
        ultimo -> setSiguiente(nuevo);
        nuevo -> setAnterior(ultimo);
        primero -> setAnterior(nuevo);

        primero = nuevo;
    }
}

void ListaCircularDoble::insertarFinal(string dato){
    Nodo* nuevo = new Nodo(dato);
    if(ListaCircularDoble::estaVacia()){
        nuevo -> setSiguiente(nuevo);
        nuevo -> setAnterior(nuevo);
        primero = ultimo = nuevo;
    }
    else{
        nuevo -> setAnterior(ultimo);
        ultimo -> setSiguiente(nuevo);
        nuevo -> setSiguiente(primero);
        primero -> setAnterior(nuevo);

        ultimo = nuevo;
    }
}

void ListaCircularDoble::eliminarInicio(){
    if(ListaCircularDoble::estaVacia()){
        cout << "La lista esta vacia" << endl;
    }
    else{
        Nodo* segundo = primero -> getSiguiente();
        ultimo -> setSiguiente(segundo);
        segundo -> setAnterior(ultimo);
        primero = segundo;
    }
}

void ListaCircularDoble::eliminarFinal(){
    if (ListaCircularDoble::estaVacia()){
        cout << "La lista esta vacia" << endl;
    }
    else{
        Nodo* antepenultimo = ultimo -> getAnterior();
        antepenultimo -> setSiguiente(primero);
        primero -> setAnterior(antepenultimo);
        ultimo = antepenultimo;
    }
}

void ListaCircularDoble::visualizarLista(){
    if (ListaCircularDoble::estaVacia()){
        cout << "La lista esta vacia" << endl;
    }
    else{
        string nodo;
        ofstream archivo;
        archivo.open("graficaLCD.dot", ios::out);
        archivo << "digraph g { rankdir = LR; " << endl;
        
        Nodo* temporal = primero;

        do{
            nodo = temporal -> getDato();
            archivo << nodo;
            archivo << " -> ";
            //cout << nodo << endl;
            temporal = temporal -> getSiguiente();
            archivo << temporal -> getDato();
            archivo << ";";
            archivo << temporal -> getDato();
            archivo << " -> ";
            archivo << nodo;
            archivo << ";";
            
        }while(temporal != primero);

        archivo << " } ";
        archivo.close();
        system("dot -Tpng graficaLCD.dot -o graficaLCD.png");
        system("display graficaLCD.png &");
    }
}



#endif
