/* Realizado por David Antuña y Rafael Garces */

#include <iostream>
using namespace std;
#include "ListaUsuarios.h"

const string ARCH_US = "_usuarios.txt";

/*
	* Dada una lista de usuarios desplaza todos los correos desde el final hasta pos (incluido) hacia la derecha
	* @param1 lista de usuarios a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarDcha(tListaUsuarios & usuarios, int pos);

/*
	* Muestra un mensaje por pantalla si ocurre un fallo al crear un usuario
*/
void listaLlenaToString();
void usuarioExistenteToString();

void inicializar(tListaUsuarios & usuarios) {
	usuarios.cont = 0;
}

bool cargar(tListaUsuarios & usuarios, string dominio, const tListaCorreos & correos) {
	bool abierto;
	ifstream fIn;
	string arch;
	arch = dominio + ARCH_US;

	fIn.open(arch.c_str());
	abierto = fIn.is_open();

	if (abierto) {
		while (cargar(usuarios.usuario[usuarios.cont], fIn, correos) && usuarios.cont < MAX_USER) {
			usuarios.cont++;
		}

		fIn.close();
	}

	return abierto;
}

void guardar(const tListaUsuarios & usuarios, string dominio) {
	ofstream fOut;
	string arch;
	arch = dominio + ARCH_US;

	fOut.open(arch.c_str());
	for (int i = 0; i < usuarios.cont; i++) {
		guardar(*usuarios.usuario[i], fOut);
	}
	fOut << CENT_ID;
	fOut.close();
}

bool aniadir(tListaUsuarios & usuarios, const tUsuario & usuario) {
	bool inser = false;
	int pos;

	if (usuarios.cont >= MAX_USER)
		listaLlenaToString();
	else if (buscarUsuario(usuarios, usuario.id, pos))
		usuarioExistenteToString();
	else inser = true;

	if (inser) {
		// Abrimos hueco para la insercion
		desplazarDcha(usuarios, pos);
		// Insertamos
		usuarios.usuario[pos] = new tUsuario(usuario);
		usuarios.cont++;
	}

	return inser;
}

bool buscarUsuario(const tListaUsuarios & usuarios, string id, int & pos) {
	bool enc = false;
	int ini = 0, fin = usuarios.cont - 1, mitad;

	while (ini <= fin && !enc) {
		mitad = (ini + fin) / 2;
		if (id == usuarios.usuario[mitad]->id) enc = true;
		else if (id < usuarios.usuario[mitad]->id) fin = mitad - 1;
		else ini = mitad + 1;
	}

	if (enc) pos = mitad;
	else pos = ini;

	return enc;
}

void desplazarDcha(tListaUsuarios & usuarios, int pos) {
	for (int i = usuarios.cont; i > pos; i--) {
		usuarios.usuario[i] = usuarios.usuario[i - 1];
	}
}

void destruir(tListaUsuarios & usuarios) {
	for(int i = 0; i < usuarios.cont; i++) {
		destruir(usuarios.usuario[i]->listaEnviados);
		destruir(usuarios.usuario[i]->listaRecibidos);
		delete usuarios.usuario[i];
	}
	usuarios.cont = 0;
}

void listaLlenaToString() {
	cout << endl << "La lista de usuarios esta llena" << endl;
}

void usuarioExistenteToString() {
	cout << endl << "El usuario introducido ya existe" << endl;
}