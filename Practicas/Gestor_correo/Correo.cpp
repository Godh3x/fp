/* Realizado por David Antuña y Rafael Garces */

#include "Correo.h"
#include <iostream>
#include <sstream>
#include <iomanip>

const string CENT_CUERPO_CG = "X";
const string CENT_CIN = "XXX";

bool operator<(const tCorreo & cIzq, const tCorreo & cDcha);

/*
	* Comprueba que el asunto del correo no comience por RE:
	* @param asunto a comprobar
	* @return [true -> no hay Re: / false -> hay Re: ó no existia el correo]
*/
bool comprobarRE(string asunto);

/*
	* En caso de que el string comience con la cadena "Re: " la elimina
	* @param string a procesar
	* @return string procesado
*/
string limpiarAsunto(string asunto);

/*
	* Solicita al usuario que introduzca el destinatario
	* @param lista de destinatarios
*/
void solicitarDestinatario(tListaDes & listaD);

/*
	* Solicita al usuario que introduzca el asunto
	* @return cadena con la informacion introducida
*/
string solicitarAsunto();

/*
	* Solicita al usuario que introduzca el cuerpo
	* @return cadena con la informacion introducida
*/
string solicitarCuerpo();

/*
	* Dados un emisor y una fecha genera el identificador unico de un correo
	* @param1 emisor
	* @param2 fecha
	* @return identificador
*/
string generaId(string emisor, tFecha fecha);

/*
	* Dada una fecha la da formato (incluye hora)
	* @param1 fecha
	* @return cadena con la fecha una vez dado el formato
*/
string mostrarFecha(tFecha fecha);

/*
	* Dada una fecha la da formato (no incluye hora)
	* @param1 fecha
	* @return cadena con la fecha una vez dado el formato
*/
string mostrarSoloDia(tFecha fecha);

/*
	* Dado un stream de entrada de datos carga la informacion referente al cuerpo de un correo
	* @param stream de entrada
	* @return string que contiene el cuerpo del correo que se ha leido
*/
string cargarCuerpo(ifstream & fIn);

bool operator<(const tCorreo & cIzq, const tCorreo & cDcha) {
	bool menor;

	if (limpiarAsunto(cIzq.asunto) < limpiarAsunto(cDcha.asunto)) menor = true;
	else if (limpiarAsunto(cIzq.asunto) > limpiarAsunto(cDcha.asunto)) menor = false;
	else if (cIzq.fecha < cDcha.fecha) menor = true;
	else menor = false;

	return menor;
}

bool comprobarRE(string asunto) {
	return (asunto.substr(0, 4) == "Re: ");
}

string limpiarAsunto(string asunto) {
	string procesado;

	procesado = asunto;
	if(comprobarRE(asunto)) {
		procesado.erase(0, 4);
	}

	return procesado;
}

void correoNuevo(tCorreo & correo, string emisor) {
	correo.emisor = emisor;
	solicitarDestinatario(correo.destinatarios);
	correo.asunto = solicitarAsunto();
	correo.cuerpo = solicitarCuerpo();
	correo.fecha = time(0);
	correo.id = generaId(emisor, correo.fecha);
}

void correoContestacion(const tCorreo & correoOriginal, tCorreo & correo, string emisor) {
	correo.emisor = emisor;
	correo.destinatarios.cont = 0;
	correo.destinatarios.destinatario[correo.destinatarios.cont] = correoOriginal.emisor;
	correo.destinatarios.cont++;
	correo.asunto = "Re: " + correoOriginal.asunto;
	stringstream cuerpoAux;
	cuerpoAux << solicitarCuerpo() << endl;
	cuerpoAux << "------------------------------------------------" << endl << endl;
	cuerpoAux << aCadena(correoOriginal);
	correo.cuerpo = cuerpoAux.str();
	correo.fecha = time(0);
	correo.id = generaId(emisor, correo.fecha);
}

string aCadena(const tCorreo & correo) {
	stringstream f;

	f << "De: " << correo.emisor << right << setw(35) << mostrarFecha(correo.fecha) << left << endl;
	f << "Para: " << correo.destinatarios.destinatario[0];
	for(int i = 1; i < correo.destinatarios.cont; i++) {
		f << "; " << correo.destinatarios.destinatario[i];
	}
	f << endl;
	f << "Asunto: " << correo.asunto << endl;
	f << correo.cuerpo << endl;

	return f.str();
}

string obetenerCabecera(const tCorreo & correo) {
	stringstream cab;

	cab << left << setw(25) << correo.emisor << setw(37) << correo.asunto << mostrarSoloDia(correo.fecha);

	return cab.str();
}

bool cargar(tCorreo & correo, ifstream & fIn) {
	bool valido;
	string  aux;

	fIn >> aux;
	valido = (aux != CENT_ID);
	if (valido) {
		correo.id = aux;
		fIn >> correo.fecha >> correo.emisor;
		fIn >> correo.destinatarios.cont;
		for (int i = 0; i < correo.destinatarios.cont; i++) {
			fIn >> correo.destinatarios.destinatario[i];
		}
		// Al hacer este getline evitamos que tenga un error al leer dado que leera hasta el primer salto, es decir, no leera la linea que debe
		getline(fIn, aux);
		getline(fIn, correo.asunto);
		correo.cuerpo = cargarCuerpo(fIn);
	}

	return valido;
}

void guardar(const tCorreo & correo, ofstream & fOut) {
	fOut << correo.id << endl;
	fOut << correo.fecha << endl;
	fOut << correo.emisor << endl;
	fOut << correo.destinatarios.cont << endl;
	for(int i = 0; i < correo.destinatarios.cont; i++) {
		fOut << correo.destinatarios.destinatario[i] << endl;
	}
	fOut << correo.asunto << endl;
	fOut << correo.cuerpo;
	fOut << CENT_CUERPO_CG << endl;
}

void solicitarDestinatario(tListaDes & listaD) {
	string aux;
	listaD.cont = 0;

	do {
		cout << "Destinatarios (al menos uno, XXX para terminar): ";
		cin.sync(); cin.clear();
		cin >> aux;
	} while (aux == CENT_CIN || cin.fail());

	while (aux != CENT_CIN.c_str()) {
		listaD.destinatario[listaD.cont] = aux;
		listaD.cont++;
		cout << "Destinatarios (XXX para terminar): ";
		cin.sync(); cin.clear();
		cin >> aux;
	}
}

string solicitarAsunto() {
	string asunto;
	
	do {
		cout << "Asunto (una linea): ";
		cin.sync(); cin.clear();
		cin >> asunto;
	} while (cin.fail());

	return asunto;
}

string solicitarCuerpo() {
	string cuerpo, aux;
	stringstream flujo;

	cout << "Cuerpo (XXX para terminar): " << endl;
	getline(cin, aux); // Coge la linea vacia

	getline(cin, aux);
	while (aux != CENT_CIN) {
		flujo << aux << endl;
		getline(cin, aux);
	}
	cuerpo = flujo.str();

	return cuerpo;
}

string generaId(string emisor, tFecha fecha) {
	stringstream id;
	
	id << emisor << "_" << fecha;
	
	return id.str();
}

string mostrarFecha(tFecha fecha) {
	stringstream resultado;
	tm ltm;

	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	resultado << " (" << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << ")";

	return resultado.str();
}

string mostrarSoloDia(tFecha fecha) {
	stringstream resultado;
	tm ltm;

	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;

	return resultado.str();
}

string cargarCuerpo(ifstream & fIn) {
	stringstream cuerpo;
	string aux;

	getline(fIn, aux);
	while (aux != CENT_CUERPO_CG) {
		cuerpo << aux << endl;
		getline(fIn, aux);
	}

	return cuerpo.str();
}