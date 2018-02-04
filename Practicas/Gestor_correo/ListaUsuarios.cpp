/* Realizado por David Antuña y Rafael Garces */

#include "ListaUsuarios.h"

const string ARCH_US = "_usuarios.txt";
const string CENT_ID = "XXX";

/*
	* Dada una lista de usuarios desplaza todos los correos desde el final hasta pos (incluido) hacia la derecha
	* @param1 lista de usuarios a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarDcha(tListaUsuarios & usuarios, int pos);

void inicializar(tListaUsuarios & usuarios) {
	usuarios.cont = 0;
}

bool cargar(tListaUsuarios & usuarios, string dominio) {
	bool abierto;
	ifstream fIn;
	string arch;
	arch = dominio + ARCH_US;

	fIn.open(arch.c_str());
	abierto = fIn.is_open();

	if (abierto) {
		while (cargar(usuarios.usuario[usuarios.cont], fIn)) {
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
		guardar(usuarios.usuario[i], fOut);
	}
	fOut << CENT_ID;
	fOut.close();
}

bool aniadir(tListaUsuarios & usuarios, const tUsuario & usuario) {
	bool inser;
	int pos;

	inser = ((usuarios.cont < MAX_USER) && !buscarUsuario(usuarios, usuario.id, pos));
	if (inser) {
		// Abrimos hueco para la insercion
		desplazarDcha(usuarios, pos);
		// Insertamos
		usuarios.usuario[pos] = usuario;
		usuarios.cont++;
	}

	return inser;
}

bool buscarUsuario(const tListaUsuarios & usuarios, string id, int & pos) {
	bool enc = false;
	int ini = 0, fin = usuarios.cont - 1, mitad;

	while (ini <= fin && !enc) {
		mitad = (ini + fin) / 2;
		if (id == usuarios.usuario[mitad].id) enc = true;
		else if (id < usuarios.usuario[mitad].id) fin = mitad - 1;
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