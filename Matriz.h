#ifndef MATRIZ
#define MATRIZ

#include <fstream>
#include <iomanip>
#include <iostream>
#include <bits/stdc++.h> //Libreria para usar el system
using namespace std;

#include "NodoMatriz.h"

class Matriz
{
public:
    string nodo;
    ofstream archivo;
	NodoMatriz* root;

	Matriz()
	{
		root = new NodoMatriz("root","","","");
	};

	bool estaVacia(); //---
    void insertar(string nombre, string contrasenia, string departamento, string empresa);
	void insertarColumna(string nombre, string contrasenia, string departamento, string empresa); //---
    void insertarFila(NodoMatriz* nuevo);

	NodoMatriz* buscar(string nombre, string departamento, string empresa); //---
    NodoMatriz* buscarNodo(NodoMatriz* temporal, string nombre, string departamento, string empresa);
	void eliminarNodo(string nombre); //---
	void visualizarMatriz(); //---
	
	//~ListaSimple();
	
};

bool Matriz::estaVacia(){
    return (root->getPosterior()==NULL) && (root->getInferior()==NULL);
}

NodoMatriz* Matriz::buscar(string nombre, string departamento, string empresa){
    return buscarNodo(root, nombre, departamento, empresa);
}

NodoMatriz* Matriz::buscarNodo(NodoMatriz* temporal, string nombre, string departamento, string empresa){
    if(Matriz::estaVacia()){
        cout << "Matriz vacia" << endl;
        return NULL;
    }
    else{
        NodoMatriz *tempDepartamento = root->getPosterior();
        NodoMatriz *tempEmpresa; //= root->getInferior();
        NodoMatriz *NodoEncontrado = NULL;
        while (tempDepartamento!=NULL){   
            if(tempDepartamento->getDepartamento() == departamento){
                //Se encontro la cabecera con el departamento buscado
                tempEmpresa=tempDepartamento->getInferior();
                while (tempEmpresa!=NULL)
                {
                    if(tempEmpresa->getEmpresa() == empresa){
                        NodoEncontrado = tempEmpresa;
                        break;
                    }
                    tempEmpresa = tempEmpresa->getInferior();
                }
                break;
            }
            tempDepartamento = tempDepartamento->getPosterior();
        }
        return NodoEncontrado;
    }
}

void Matriz::insertar(string nombre, string contrasenia, string departamento, string empresa){
    Matriz::insertarColumna(nombre,contrasenia,departamento,empresa);
}

void Matriz::insertarColumna(string nombre, string contrasenia, string departamento, string empresa){
    NodoMatriz* nuevo = new NodoMatriz(nombre,contrasenia,departamento,empresa);
    if (Matriz::estaVacia()){
        //Creando cabecera columna
        NodoMatriz* cabeceraC = new NodoMatriz("departamento","", departamento, "");
        //Creando cabecera fila
        NodoMatriz* cabeceraF = new NodoMatriz("empresa","","",empresa);
        //Enlazar root con las cabeceras
        root->setPosterior(cabeceraC);
        root->setInferior(cabeceraF);
        cabeceraC->setAnterior(root);
        cabeceraF->setSuperior(root);
        //Enlazar el nuevo nodo con las cabeceras
        cabeceraC->setInferior(nuevo);
        nuevo->setSuperior(cabeceraC);
        cabeceraF->setPosterior(nuevo);
        nuevo->setAnterior(cabeceraF);
    }
    else{
        //NODO TEMPORAL PARA RECORRER TODAS LAS CABECERAS COLUMNAS
        NodoMatriz* temporalC = root->getPosterior();
        //RECORRIDO COLUMNA
        while(true)
        {
            //SE ENCONTRO UNA CABECERA CON LA MISMA POSICION "X"
            //Se inserta en esa columna
            if (nuevo->getDepartamento() == temporalC->getDepartamento()){
                NodoMatriz* temporalF = temporalC;
                //Recorrer filas para insertar el nodo
                bool recorrido = true;
                while (recorrido)
                {
                    //YA EXISTE LA COLUMNA Y LA FILA
                    if(nuevo->getEmpresa() == temporalF->getEmpresa()){
                        cout << "Nodo ocupado" << endl;
                        recorrido=false;
                        break;
                    }
                    //Se inserta al final de las filas
                    else if(temporalF->getInferior()==NULL){
                        temporalF->setInferior(nuevo);
                        nuevo->setSuperior(temporalF);
                        //ENLAZAR NODO CON LA FILA CORRESPONDIENTE
                        Matriz::insertarFila(nuevo);
                        break;
                    }
                    //Se encontro un nodo mayor
                    //Se inserta antes del nodo encontrado
                    else if(temporalF->getEmpresa() > nuevo->getEmpresa()){
                        //Enlazar los nodos con el nuevo nodo
                        temporalF->getSuperior()->setInferior(nuevo);
                        nuevo->setSuperior(temporalF);
                        nuevo->setInferior(temporalF->getInferior());
                        temporalF->getInferior()->setSuperior(nuevo);
                        //ENLAZAR NODO CON LA FILA CORRESPONDIENTE
                        Matriz::insertarFila(nuevo);
                        break;
                    }
                    temporalF = temporalF->getInferior();
                }
                break;
            }
            //Se encontro una cabecera mayor
            //Se inserta antes de la cabecera encontrada
            if(temporalC->getDepartamento() > nuevo->getDepartamento() ){
                //Creando cabecera columna
                NodoMatriz* cabeceraC = new NodoMatriz("departamento","",departamento,"");
                //Enlazar cabeceras existentes con la nueva cabecera
                temporalC->getAnterior()->setPosterior(cabeceraC);
                cabeceraC->setAnterior(temporalC->getAnterior());
                cabeceraC->setPosterior(temporalC);
                temporalC->setAnterior(cabeceraC);
                //Enlazar cabecera columna con el nuevo nodo
                cabeceraC->setInferior(nuevo);
                nuevo->setSuperior(cabeceraC);
                //ENLAZAR NODO CON LA FILA CORRESPONDIENTE
                Matriz::insertarFila(nuevo);
                break;
            }
            //No se encontro una cabecera mayor
            //Inserta la cabecera al final
            if(temporalC->getPosterior() == NULL){
                //Creando cabecera columna
                NodoMatriz* cabeceraC = new NodoMatriz("departamento","",departamento,"");
                //Enlazar cabecera existente con la nueva cabecera
                temporalC->setPosterior(cabeceraC);
                cabeceraC->setAnterior(temporalC);
                //Enlazar cabecera columna con nuevo nodo
                cabeceraC->setInferior(nuevo);
                nuevo->setSuperior(cabeceraC);
                //ENLAZAR NODO CON LA FILA CORRESPONDIENTE
                Matriz::insertarFila(nuevo);
                break;
            }
            temporalC = temporalC->getPosterior();
        }
    }
}

void Matriz::insertarFila(NodoMatriz* nuevo){
    //NODO TEMPORAL PARA RECORRER TODAS LAS CABECERAS FILAS
    NodoMatriz* temporalF = root->getInferior();
    //RECORRIDO FILA
    while (true)
    {
        //SE ENCONTRO UNA CABECERA CON LA MISMA POSICION "Y"
        //Ya existe la cabecera fila, se inserta en esa fila
        if(temporalF->getEmpresa()==nuevo->getEmpresa()){
            NodoMatriz* temporalC = temporalF;
            bool recorrido = true;
            while (recorrido)
            {
                //SE inserta al final de la fila
                //Se enlaza con el ultimo nodo encontrado
                if(temporalC->getPosterior()==NULL){
                    temporalC->setPosterior(nuevo);
                    nuevo->setAnterior(temporalC);
                    recorrido = false;
                    break;
                }
                //Se encontro un nodo mayor
                //Se inserta antes del nodo encontrado
                else if(temporalC->getDepartamento() > nuevo->getDepartamento()){
                    temporalC->getAnterior()->setPosterior(nuevo);
                    nuevo->setAnterior(temporalC->getAnterior());
                    nuevo->setPosterior(temporalC);
                    temporalC->getPosterior()->setAnterior(nuevo);
                    recorrido = false;
                    break;
                }
                temporalC = temporalC->getPosterior();
            }
            break;
        }
        //SE ENCONTRO UNA CABECERA MAYOR 
        //Se crea la cabecera y se inserta antes de la cabecera encontrada
        else if(temporalF->getEmpresa() > nuevo->getEmpresa()){
            //Crear la nueva cabecera fila
            NodoMatriz* cabeceraF = new NodoMatriz("empresa","","",nuevo->getEmpresa());
            //Enlazar la cabecera nueva con la cabecera anterior encontrada
            temporalF->getSuperior()->setInferior(cabeceraF);
            cabeceraF->setSuperior(temporalF->getSuperior());
            cabeceraF->setInferior(temporalF);
            temporalF->setSuperior(cabeceraF);
            //Enlazar el nuevo nodo con la cabecera creada
            cabeceraF->setPosterior(nuevo);
            nuevo->setAnterior(cabeceraF);
            break;
        }
        //NO SE ENCONTRO UNA CABECERA MAYOR
        //Inserta la cabecera al final
        else if(temporalF->getInferior()==NULL){
            //Creando cabecera fila
            NodoMatriz* cabeceraF = new NodoMatriz("empresa","","",nuevo->getEmpresa());
            //Enlazar cabecera existente con la nueva cabecera
            temporalF->setInferior(cabeceraF);
            cabeceraF->setSuperior(temporalF);
            //Enlazar cabecera fila con nuevo nodo
            cabeceraF->setPosterior(nuevo);
            nuevo->setAnterior(cabeceraF);
            break;
        }
        temporalF=temporalF->getInferior();
    }   
}

void Matriz::visualizarMatriz(){
    if(Matriz::estaVacia()){
        cout << "La matriz esta vacia" << endl;
    }
    else{
        /*
        1) ASIGNAR ROOT A UN TEMPORAL PARA EL RECORRIDO

        2) RECORRER LAS CABECERAS COLUMNAS
        3) IMPRIMIR LAS CABECERAS Y ENLAZARLAS ENTRE SI 
        4) RECORRER LAS CABECERAS FILAS
        5) IMPRIMIR LAS CABECERAS Y ENLAZARLAS ENTRE SI

        6) EMPEZAR A RECORRER LAS CABECERAS FILAS
        7) POR CADA CABECERA FILA, RECORRER LOS NODOS HORIZONTALMENTE
        8) GUARDAR CADA NODO ENCONTRADO
        9)
        */

        int contCabColumna = 0, contCabFila = 0;
        //--- 1 ---
        NodoMatriz* cabeceraC = root->getPosterior();
        NodoMatriz* cabeceraF = root->getInferior();
        
        archivo.open("graficaM.dot",ios::out);
        archivo << "digraph G {" << endl;
        archivo << "node[shape=box]" << endl;
        archivo << "root[label = \"Root\", width = 1.5, style = filled, group = 1];" << endl;

        //--- 2) RECORRER LAS CABECERAS COLUMNAS ---
        while (cabeceraC != NULL)
        {
            archivo << cabeceraC->getDepartamento() << "[label= \"" << cabeceraC->getDepartamento() << "\", width=1.5, style=filled, group=1];" << endl;
            contCabColumna = contCabColumna + 1;
            cabeceraC = cabeceraC->getPosterior();
        }
        archivo << "root -> " << root->getPosterior()->getDepartamento() << ";" << endl;

        cabeceraC = root->getPosterior();
        //--- 3) IMPRIMIR LAS CABECERAS COLUMNAS Y ENLAZARLAS ENTRE SI ---
        if(contCabColumna > 1){
            for (int i = 0; i < (contCabColumna-1); i++)
            {
                archivo << cabeceraC->getDepartamento() << " -> " << cabeceraC->getPosterior()->getDepartamento() << ";" << endl;
                archivo << cabeceraC->getPosterior()->getDepartamento() << " -> " << cabeceraC->getDepartamento() << ";" << endl;

                cabeceraC = cabeceraC->getPosterior();
            }
        }

        //RANK SAME PARA LAS CABECERAS COLUMNAS
        cabeceraC = root->getPosterior();
        archivo << "{rank = same; root; ";
        for (int i = 0; i < contCabColumna; i++)
        {
            archivo << cabeceraC->getDepartamento() << "; ";
            cabeceraC = cabeceraC->getPosterior();
        }
        archivo << "}" << endl;
        
        //--- 4) RECORRER LAS CABECERAS FILAS ---
        while (cabeceraF != NULL)
        {
            archivo << cabeceraF->getEmpresa() << "[label= \"" << cabeceraF->getEmpresa() << "\", width=1.5, style=filled, group=2];" << endl;
            contCabFila = contCabFila + 1;
            cabeceraF = cabeceraF->getInferior();
        }

        archivo << "root -> " << root->getInferior()->getEmpresa() << ";" << endl;
        cabeceraF = root->getInferior();
        //--- 5) IMPRIMIR LAS CABECERAS FILAS Y ENLAZARLAS ENTRE SI ---
        if(contCabFila > 1){
            for (int i = 0; i < (contCabFila-1); i++)
            {
                archivo << cabeceraF->getEmpresa() << " -> " << cabeceraF->getInferior()->getEmpresa() << ";" << endl;

                archivo << cabeceraF->getInferior()->getEmpresa() << " -> " << cabeceraF->getEmpresa() << ";" << endl;

                cabeceraF = cabeceraF->getInferior();
            }
        }

        //--- 6) EMPEZAR A RECORRER LAS CABECERAS FILAS ---
        cabeceraF = root->getInferior();
        while (cabeceraF != NULL)
        {
            NodoMatriz* temporalNodo = cabeceraF->getPosterior();
            //--- 7) POR CADA CABECERA FILA, RECORRER LOS NODOS HORIZONTALMENTE ---
            while (temporalNodo != NULL)
            {
                //--- 8) GUARDAR CADA NODO ENCONTRADO ---
                archivo << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << "[label= \"" << temporalNodo->getNombre() << "\", width=1.5];" << endl;

                temporalNodo = temporalNodo->getPosterior();
            }
            cabeceraF = cabeceraF->getInferior();   
        }

        //--- 9) EMPEZAR A RECORRER LAS CABECERAS FILAS ---
        cabeceraF = root->getInferior();
        while (cabeceraF != NULL)
        {
            NodoMatriz* temporalNodo = cabeceraF->getPosterior();
            //--- 10) POR CADA CABECERA FILA, RECORRER LOS NODOS HORIZONTALMENTE ---
            while (temporalNodo != NULL)
            {
                //--- 11) POR CADA NODO ENCONTRADO, ENLAZARLO CON EL NODO ANTERIOR Y SUPERIOR ---
                
                //Nodo actual -> Nodo anterior;
                //Nodo anterior -> Nodo actual;
                if(temporalNodo->getAnterior()->getDepartamento() == ""){
                    //Enlazando la cabecera
                    archivo << temporalNodo->getAnterior()->getEmpresa() << " -> " << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << ";" << endl; 
                }
                else{
                    archivo << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << " -> " <<
                    temporalNodo->getAnterior()->getDepartamento() << temporalNodo->getAnterior()->getEmpresa() << "; " << endl;

                    archivo << temporalNodo->getAnterior()->getDepartamento() << temporalNodo->getAnterior()->getEmpresa() << " -> " << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << ";" << endl;
                }
                
                //Nodo actual -> Nodo superior;
                //Nodo superior -> Nodo actual;
                if(temporalNodo->getSuperior()->getEmpresa() == ""){
                    //Enlazando la cabecera
                    archivo  << temporalNodo->getSuperior()->getDepartamento() << " -> " << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << ";" << endl;
                }
                else{
                    archivo << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << " -> " << temporalNodo->getSuperior()->getDepartamento() << temporalNodo->getSuperior()->getEmpresa() << ";" << endl;

                    archivo << temporalNodo->getSuperior()->getDepartamento() << temporalNodo->getSuperior()->getEmpresa() << " -> " << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << ";" << endl;
                }
                
                temporalNodo = temporalNodo->getPosterior();
            }

            temporalNodo = cabeceraF;
            //Rank same de la fila actual
            archivo << "{rank = same; ";
            while (temporalNodo != NULL)
            {
                if(temporalNodo->getDepartamento()==""){
                    archivo << temporalNodo->getEmpresa() << "; ";
                }
                else{
                    archivo << temporalNodo->getDepartamento() << temporalNodo->getEmpresa() << "; ";
                }
                temporalNodo = temporalNodo->getPosterior();
            }
            archivo << "}" << endl;
            cabeceraF = cabeceraF->getInferior();
        }

        archivo << "}";
        archivo.close();
        system("dot -Tpng graficaM.dot -o graficaM.png");
        system("display graficaM.png &");
	
    }
}

#endif
