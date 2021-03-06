/* Realizado por David Antu�a y Rafael Garces */

#include <iostream>
using namespace std;
#include <iomanip>
#include "Gestor.h"
#include <sstream>

const int MAX_OP_L = 1;

/*
	* Muestra un mensaje por pantalla que hace referencia al dominio cargado
*/
void bienvenidaToString(string dominio);

/*
	* Solicita al usuario que introduzca su identificador
	* @param dominio del gestor
	* @return cadena con la informacion introducida
*/
string solicitarId(string dominio);

/*
	* Solicita al usuario que introduzca su contrase�a
	* @return cadena con la informacion introducida
*/
string solicitarContrasenia();

/*
	* Solicita al usuario que introduzca el correo que desea leer
	* @return int con la posicion del correo
*/
int solicitarCorreoL();

/*
	* Solicita al usuario que introduzca el correo que desea borrar
	* @return int con la posicion del correo
*/
int solicitarCorreoB();

/*
	* Muestra un mensaje por pantalla que informa de que el correo solicitado no existe
*/
void correoNEToString();

/*
	* Muestra un menu de opciones ejecutables durante la lectura de un correo
*/
int opcionLectura();

/*
	* Muestra un mensaje por pantalla que informa de que hubo un error al insertar el registro en el destinatario
	* @param destinatario al que hace referencia el mensaje
*/
void errorDestinatarioNEToString(string des);

/*
	* Muestra un mensaje por pantalla que informa de que hubo un error al borrar el correo
*/
void correoNoBToString();

/*
	* Dado un contenedor y una lista de registros de correo selecciona y almacena correos no leidos y que no sean contestaciones
	* Ademas al almacenar el correo en el contenedor auxiliar marca el registro como leido
	* @param1 contenedor
	* @param2 lista de registros de correo
*/
void crearListaLR(tListaCorreos & listaAux, tListaRegCorreo & listaReg);

/*
	* Dado un listado de correos genera un string con todo el contenido del listado para mostrar por pantalla
	* @param listado de correos a mostrar
	* @return string con todo el contenido del listado
*/
string generarLR(const tListaCorreos & listaAux);

/*
	* Muestra la informacion de la pantalla principal referente al usuario activo
	* @param1 datos del gestor
	* @param2 indica que bandeja mostrar [true -> entrada / false -> salida]
*/
void mostrarPantPrinc(const tGestor & gestor, bool bandEnt);

/*
	* Muestra el menu de opciones disponibles para el usuario activo
	* @param1 booleano que indica que bandeja se esta mostrando
	* @return opcion elegida
*/
int menuSesion(bool bandEnt);

/*
	* Muestra la informacion de la bandeja que se le envia
	* @param informacion de la bandeja
*/
void mostrarBandeja(const tListaRegCorreo & bandeja);

/*
	* Muestra un separador compuesto por una fila de "-"
*/
void separador();

/*
	* Muestra um mensaje cuando falla al enviar un correo porque no queda espacio
*/
void gestorLlenoToString();


bool arrancar(tGestor & gestor, string dominio) {
	bool arrancado;

	inicializar(gestor.usuarios);
	// Cargamos los correos
	arrancado = cargar(gestor.correos, dominio); 
	// Los usuarios se cargan mas tarda para poder mandar los correos y asi crear los punteros de los registros
	arrancado = (arrancado && cargar(gestor.usuarios, dominio, gestor.correos));
	if (arrancado) gestor.dominio = dominio;
	else {
		gestor.correos.cont = 0;
		inicializar(gestor.correos);
	}

	return arrancado;
}

void apagar(tGestor & gestor) {
	guardar(gestor.usuarios, gestor.dominio);
	destruir(gestor.usuarios);
	guardar(gestor.correos, gestor.dominio);
	destruir(gestor.correos);
}

bool crearCuenta(tGestor & gestor) {
	bool creado;
	tUsuario usuario;

	bienvenidaToString(gestor.dominio);

	usuario.id = solicitarId(gestor.dominio);
	usuario.pwd = solicitarContrasenia();

	usuario.listaEnviados.cont = 0;
	inicializar(usuario.listaEnviados);

	usuario.listaRecibidos.cont = 0;
	inicializar(usuario.listaRecibidos);

	creado = (aniadir(gestor.usuarios, usuario));

	if (creado) buscarUsuario(gestor.usuarios, usuario.id, gestor.idUsuario);

	return creado;
}

bool iniciarSesion(tGestor & gestor) {
	bool iniciada = false;
	string id, contrasenia;
	int pos;

	bienvenidaToString(gestor.dominio);

	id = solicitarId(gestor.dominio);
	contrasenia = solicitarContrasenia();

	if (buscarUsuario(gestor.usuarios, id, pos)) {
		iniciada = (contrasenia == gestor.usuarios.usuario[pos]->pwd);
		if (iniciada) gestor.idUsuario = pos;
	}

	return iniciada;
}

void leerCorreo(tGestor & gestor, tListaRegCorreo & listaReg) {
	int pos;

	pos = listaReg.cont - solicitarCorreoL();
	// Si no se comprueba esto podriamos acceder a registros[-1] por ejemplo
	if (pos < listaReg.cont && pos >= 0) {
		// Si el correo existe en la lista de correos lo marcamos como leido
		correoLeido(listaReg, listaReg.registros[pos].correo->id);

		// Mostrar correo + opciones
		system("CLS");
		cout << aCadena(*listaReg.registros[pos].correo) << endl;
		switch (opcionLectura()) {
		case 1: {
			tCorreo contestacion;
			correoContestacion(*listaReg.registros[pos].correo, contestacion, gestor.usuarios.usuario[gestor.idUsuario]->id);
			enviarCorreo(gestor, contestacion);
			}
		break;
		default: break;
		}
	}
	else correoNEToString();
}

void enviarCorreo(tGestor & gestor, const tCorreo & correo) {
	// Insertamos el correo en la lista de correos de la aplicacion
	if (insertar(gestor.correos, correo)) {
		int pos, posC;
		tRegCorreo reg;
		buscar(gestor.correos, correo.id, posC);
		reg.correo = gestor.correos.correos[posC];
		reg.leido = true;
		// Buscamos al emisor y insertamos el registro del correo en la bandeja de salida
		// No se contempla el caso en el que el emisor no se encuentre dado que ya se ha verificado su existencia al iniciar sesion
		// Como podemos aumentar el tama�o no contemplamos que no entre
		insertar(gestor.usuarios.usuario[gestor.idUsuario]->listaEnviados, reg);
		gestor.correos.correos[posC]->almacenado += 1; // Le sumamos 1 porque lo hemos insertado en el emisor
		// Buscamos al destinatario y insertamos el registro del correo en la bandeja de entrada
		reg.leido = false;
		for(int i = 0; i < correo.destinatarios.cont; i++) {
			if (!buscarUsuario(gestor.usuarios, correo.destinatarios.destinatario[i], pos)) errorDestinatarioNEToString(correo.destinatarios.destinatario[i]);
			else {
				insertar(gestor.usuarios.usuario[pos]->listaRecibidos, reg);
				gestor.correos.correos[posC]->almacenado += 1; // Si lo hemos insertado en un destinatario sumamos 1
			}
		}
	}
	else gestorLlenoToString();
}

void errorDestinatarioNEToString(string des) {
	cout << "El destinatario " << des << " no existe" << endl;
}

void borrarCorreo(tGestor & gestor, tListaRegCorreo & listaReg) {
	int pos;

	pos = listaReg.cont - solicitarCorreoB();
	// Almacenamos la id del correo que estamos borrando para asi poder implementar la eliminacion de correos del gestor
	if (pos >= 0 && pos < listaReg.cont) {
		if (listaReg.registros[pos].correo->almacenado <= 1) borrar(gestor.correos, listaReg.registros[pos].correo->id);
		else listaReg.registros[pos].correo->almacenado--;
		if (!borrar(listaReg, listaReg.registros[pos].correo->id)) correoNoBToString();	
	}
	else correoNEToString();
}

void correoNoBToString() {
	cout << "No se pudo eliminar el correo solicitado" << endl;
}

void lecturaRapida(tListaRegCorreo & listaReg) {
	tListaCorreos listaAux;

	crearListaLR(listaAux, listaReg);
	ordenar_AF(listaAux);

	cout << generarLR(listaAux);
}

void crearListaLR(tListaCorreos & listaAux, tListaRegCorreo & listaReg) {
	inicializar(listaAux);

	for (int i = 0; i < listaReg.cont; i++) {
		if (!listaReg.registros[i].leido) {
			listaAux.correos[listaAux.cont] = listaReg.registros[i].correo;
			listaAux.cont++;
			listaReg.registros[i].leido = true;
		}
	}
}

string generarLR(const tListaCorreos & listaAux) {
	stringstream lr;

	for(int i = 0; i < listaAux.cont; i++) {
		lr << aCadena(*listaAux.correos[i]) << endl;
		lr << endl << "------------------------------------------------" << endl;
	}

	return lr.str();
}

void gestionarSesion(tGestor & gestor) {
	tCorreo correo;
	int op;
	bool bandEnt = true;
	
	do {
		mostrarPantPrinc(gestor, bandEnt);
		op = menuSesion(bandEnt);
		switch (op)
		{
		case 1:
			if (bandEnt) leerCorreo(gestor, gestor.usuarios.usuario[gestor.idUsuario]->listaRecibidos);
			else leerCorreo(gestor, gestor.usuarios.usuario[gestor.idUsuario]->listaEnviados);
			break;
		case 2:
			correoNuevo(correo, gestor.usuarios.usuario[gestor.idUsuario]->id);
			enviarCorreo(gestor, correo);
			break;
		case 3:
			if (bandEnt) borrarCorreo(gestor, gestor.usuarios.usuario[gestor.idUsuario]->listaRecibidos);
			else borrarCorreo(gestor, gestor.usuarios.usuario[gestor.idUsuario]->listaEnviados);
			break;
		case 4:
			bandEnt = !bandEnt;
			break;
		case 5:
			system("CLS");
			if (bandEnt) lecturaRapida(gestor.usuarios.usuario[gestor.idUsuario]->listaRecibidos);
			else lecturaRapida(gestor.usuarios.usuario[gestor.idUsuario]->listaEnviados);
			
			break;
		default: break;
		}
		if (op != 0) system("Pause"); // Comprobacion para no hacer dos pausas seguidas al volver al menu de inicio
	} while (op != 0);
}

void mostrarPantPrinc(const tGestor & gestor, bool bandEnt) {
	system("CLS");

	cout << "Correo de " << gestor.usuarios.usuario[gestor.idUsuario]->id << endl;

	cout << setw(40) << setfill('-') << "Bandeja de ";
	if(bandEnt) cout << "entrada";
	else cout << "salida";
	cout << setw(30) << setfill('-') << "-" << endl;
	separador();
	cout << "L N" << setw(10) << "EMISOR" << setw(25) << "ASUNTO" << setw(36) << "FECHA" << endl;
	separador();

	if(bandEnt) mostrarBandeja(gestor.usuarios.usuario[gestor.idUsuario]->listaRecibidos);
	else mostrarBandeja(gestor.usuarios.usuario[gestor.idUsuario]->listaEnviados);
}

int menuSesion(bool bandEnt) {
	int op;

	separador();
	cout << "Elija una opcion:" << endl;
	cout << "\t1- Leer correo" << endl;
	cout << "\t2- Enviar correo" << endl;
	cout << "\t3- Borrar correo" << endl;
	cout << "\t4- Ver bandeja de ";
	if(bandEnt) cout << "salida" << endl;
	else cout << "entrada" << endl;
	cout << "\t5- Lectura rapida" << endl;
	cout << "\t0- Cerrar sesion" << endl;
	separador();

	cout << "Introduza una opcion: ";
	cin >> op;
	cin.sync(); cin.clear();

	return op;
}

void mostrarBandeja(const tListaRegCorreo & bandeja) {
	for(int i = bandeja.cont - 1; i >= 0; i--) {
		if (!bandeja.registros[i].leido) cout << "*";
		else cout << " ";
		cout << " " << bandeja.cont - i << " - " << obetenerCabecera(*bandeja.registros[i].correo) << endl;
	}
}

void separador() {
	cout << setw(79) << setfill('-') << "-" << endl;
	cout << setfill(' ');
}

int opcionLectura() {
	int op;

	cout << "----------------------------------------------------" << endl;
	cout << "Elija una opcion:" << endl;
	cout << "\t1 - Contestar correo" << endl;
	cout << "\t0 - Salir" << endl;
	cout << "----------------------------------------------------" << endl;
	do {
		cout << "Introduza una opcion: ";
		cin.sync(); cin.clear();
		cin >> op;
	} while (op < 0 && op > MAX_OP_L);

	return op;
}

void bienvenidaToString(string dominio) {
	system("CLS");
	cout << "Bienvenido al correo de " << dominio;
}

string solicitarId(string dominio) {
	string id;

	do {
		cout << endl << "Introduzca su identificador de correo: ";
		cin.sync(); cin.clear();
		cin >> id;
	} while (cin.fail());

	id += "@";
	id += dominio.c_str();

	return id;
}

string solicitarContrasenia() {
	string contrasenia;

	do {
		cout << "Introduzca su contrasenia: ";
		cin.sync(); cin.clear();
		cin >> contrasenia;
	} while (cin.fail());

	return contrasenia;
}

int solicitarCorreoL() {
	int pos;

	do {
		cout << endl << "Introduzca el numero del correo que quiere leer: ";
		cin.sync(); cin.clear();
		cin >> pos;
	} while (cin.fail());

	return pos;
}

int solicitarCorreoB() {
	int pos;

	do {
		cout << endl << "Introduzca el numero del correo que quiere borrar: ";
		cin.sync(); cin.clear();
		cin >> pos;
	} while (cin.fail());

	return pos;
}

void correoNEToString() {
	cout << "El numero de correo proporcionado no es valido" << endl;
}

void gestorLlenoToString() {
	cout << "El correo no se ha enviado porque el gestor esta lleno" << endl;
}