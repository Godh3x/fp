/* Realizado por David Antuña y Rafael Garces */

#include <iostream>
using namespace std;
#include "Gestor.h"

const string DOMINIO = "fdimail.com";
const int MAX_MENU = 2;

/*
	* Muestra un menu al usuario y solicita una opcion
	* @return opcion elegida
*/
int menu();

/*
	* Muestran un mensaje por pantalla
*/
void sesionNIniToString();
void despedidaToString();

int main() {
	tGestor gestor;
	int op;

	if(!arrancar(gestor,DOMINIO)){
		cout << "No se ha podido arrancar la aplicacion en el dominio" << endl;
		cout << "Se arrancara con las listas vacias" << endl;
		gestor.dominio = DOMINIO;
		system("pause");
		system("cls");
	}
		do{
			system("cls");
			op = menu();
			switch(op){
			case 1:	{
				if(iniciarSesion(gestor)) gestionarSesion(gestor);
				else sesionNIniToString();
					}
			break;
			case 2:	
				if(crearCuenta(gestor)) gestionarSesion(gestor);
			break;
			case 0: despedidaToString(); break;
			default: break;
			}
			system("Pause");
		}while(op != 0);

	apagar(gestor);
	return 0;
}

int menu() {
	int op;

	cout << "Elija la opcion deseada:" << endl;
	cout << "\t1- Acceder a mi cuenta de correo" << endl;
	cout << "\t2- Crear cuenta de correo" << endl << endl;
	cout << "\t0- Salir" << endl;
	
	do {
		cout << "Opcion: ";
		cin.sync(); cin.clear();
		cin >> op;
	} while (op < 0 && op > MAX_MENU);

	return op;
}

void sesionNIniToString() {
	cout << endl << "No se ha podido iniciar la sesion el usuario/contrasenia no son correctos" << endl;
}

void despedidaToString() {
	cout << "Hasta pronto!" << endl;
}