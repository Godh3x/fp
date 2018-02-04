/* Realizado por David Antuña y Rafael Garces */

#include "Usuario.h"

const string CENT_US = "XXX";

bool cargar(tUsPtr & usuario, ifstream & fIn, const tListaCorreos & correos) {
	bool cargado;
	tUsuario usAux;

	fIn >> usAux.id;
	cargado = (usAux.id != CENT_US.c_str());
	if (cargado) {
		fIn >> usAux.pwd;
		cargar(usAux.listaRecibidos, fIn, correos);
		cargar(usAux.listaEnviados, fIn, correos);
		usuario = new tUsuario(usAux);
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