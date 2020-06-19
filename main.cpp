#include "Matriz.h"
#include "NodoMatriz.h"
#include "Arbol.h"
#include "NodoArbol.h"
#include "ListaCircularDoble.h"
#include "ListaSimple.h"
#include "Nodo.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string.h>
#include <bits/stdc++.h>
using namespace std;


int main(){
    string admin = "admin";
    string password = "password";
    string usuario, contrasenia, departamento, empresa;
    int menuAdmin = 1;
    int menuUser = 1;
    string nomActivo, descActivo, idActivo;

    Matriz *miMatriz = new Matriz();
    NodoMatriz *tempUsuario;
    ListaCircularDoble *misTransacciones = new ListaCircularDoble();
    ListaSimple *misActivosRentados = new ListaSimple();

    string idActivoRentar, diasRentar;

    while (menuAdmin != 0)
    {
        cout << "1. Registrar usuario" << endl;
        cout << "2. Menu usuario" << endl;
        cout << "3. Reporte matriz dispersa" << endl;
        cout << "4. Reporte Activos disponibles de un departamento" << endl;
        cout << "5. Reporte activos disponibles de una empresa" << endl;
        cout << "6. Reporte transacciones" << endl;
        cout << "7. Reporte activos de un usuario" << endl;
        cout << "8. Activos rentados por un usuario" << endl;
        cout << "9. Ordenar transacciones" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> menuAdmin;
        cout << endl;

        switch (menuAdmin)
        {
        case 1:
            //SE AGREGA A LA MATRIZ
            cout << "Nombre usuario: "; cin >> usuario;
            cout << "Contraseña: "; cin >> contrasenia;
            cout << "Departamento: "; cin >> departamento;
            cout << "Empresa: "; cin >> empresa;
            cout << "Usuario registrado!" << endl; 
            //+Validar que no exista el nombre en el mismo departamento y empresa
            miMatriz->insertar(usuario,contrasenia,departamento,empresa);
            miMatriz->visualizarMatriz();
            break;
        case 2:
            //+Pidiendo datos para iniciar sesion
            cout << "Nombre usuario: "; cin >> usuario;
            cout << "Contraseña: "; cin >> contrasenia;
            cout << "Departamento: "; cin >> departamento;
            cout << "Empresa: "; cin >> empresa;
            //Validar que los datos existan en la matriz
            tempUsuario = miMatriz->buscar(usuario,departamento,empresa);
            cout << tempUsuario->getNombre() << endl;
            while (menuUser != 7)
            {
                cout << "1. Agregar activo" << endl;
                cout << "2. Eliminar activo" << endl;
                cout << "3. Modificar activo" << endl;
                cout << "4. Rentar activo" << endl;
                cout << "5. Activos rentados" << endl;
                cout << "6. Mis activos rentados" << endl;
                cout << "7. Cerrar sesion"<< endl;
                cin >> menuUser;
                cout << endl;
                switch (menuUser)
                {
                case 1:
                    //SE AGREGA AL ARBOL
                    cout << "Nombre: "; cin >> nomActivo;
                    cout << "Descripcion: "; cin >> descActivo;
                    cout << "ID: "; cin >> idActivo;
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->insertar(nomActivo,idActivo,descActivo);
                    break;
                case 2:
                    //ELIMINAR DEL ARBOL
                    //Se mostrara una lista en consola de los activos que posee el usuario
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->mostrar();
                    //Se selecciona el ID del activo a eliminar
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->eliminar(idActivo);
                    
                    break;
                case 3:
                    //MODIFICAR LA DESCRIPCION DE UN ACTIVO
                    //Se mostrara una lista en consola de los activos que posee el usuario
                    //Se selecciona el ID del activo a modificar
                    //Se añade la nueva descripcion

                    break;
                case 4:
                    //RENTAR ACTIVO - CATALOGO DE ACTIVOS
                    //Se mostrara una lista en consola de los activos que posee el usuario
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->mostrar();
                    //Se selecciona el ID del activo a rentar
                    cout << "Selecciona el ID del activo a rentar" << endl;
                    cin >> idActivoRentar;
                    //Se ingresa los dias que se rentara el activo
                    cout << "Ingresa los dias que se rentara" << endl;
                    cin >> diasRentar;
                    //Se elimina del catalogo de activos
                    misTransacciones->insertarFinal(idActivoRentar);
                    misActivosRentados->insertarFinal(nomActivo);
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->mostrar();
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->visualizarArbol();
                    break;
                case 5:
                    //ACTIVOS RENTADOS
                    //Se mostrara una lista con los activos que ha rentado el usuario
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->mostrar();
                    //Se mostrara un menu para registrar la devolucion
                    //Se Ingresa el ID del activo a devolver
                    cout << "Ingresar el ID del activo a devoler" << endl;
                    cin >> idActivoRentar;
                    //Se agrega de nuevo el activo al catalogo de activos
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->mostrar();
                    miMatriz->buscar(usuario,departamento,empresa)->misActivos->visualizarArbol();
                    break;
                case 6:
                    //MIS ACTIVOS RENTADOS
                    //Se mostrara una lista con los activos que ha rentado el usuario
                    //(Regresar al menu anterior)    

                    break;
                case 7:
                    //CERRAR SESION

                    break;
                default:
                    cout << "Opcion no valida" << endl;
                    break;
                }
                break;    
            }
            break;
        case 3:
            //VISUALIZAR MATRIZ DISPERSA
            miMatriz->visualizarMatriz();
            break;
        case 6:
            misTransacciones->visualizarLista();
            break;
        case 7:
            //Arboles
        case 8:
            misActivosRentados->visualizarLista();
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
        cout << endl;
    }
    

    cout << "Usuario Administrador: " << admin << endl;
    return 0;
}