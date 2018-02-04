/* Realizado por David Antuña y Rafael Garces */

#include "Usuario.h"

const string CENT_US = "XXX";

bool cargar(tUsuario & usuario, ifstream & fIn) {
	bool cargado;
	string id;

	fIn >> id;
	cargado = (id != CENT_US.c_str());
	if (cargado) {
		usuario.id = id;
		fIn >> usuario.pwd;
		cargar(usuario.listaRecibidos, fIn);
		cargar(usuario.listaEnviados, fIn);
	}

	return cargado;
}

void guardar(const tUsuario & usuario, ofstream & fOut) {
	fOut << usuario.id << endl << usuario.pwd << endl;
	guardar(usuario.listaRecibidos, fOut);
	guardar(usuario.listaEnviados, fOut);
}

void inicializar(tUsuario & usuario, string id, string contrasenia) {
	usuario.id = id;
	usuario.pwd = contrasenia;
}

bool validarContrasenia(const tUsuario & usuario, string contrasenia) {
	return (usuario.pwd == contrasenia);
}