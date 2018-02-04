/* Realizado por David Antuña y Rafael Garces */

#include "ListaRegistros.h"

/*
	* Dada una lista de registros desplaza todos los registros desde pos hasta el final hacia la izquierda
	* @param1 lista de registros a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarIzq(tListaRegCorreo & listaReg, int pos);

void inicializar(tListaRegCorreo & listaReg) {
	listaReg.cont = 0;
}

void cargar(tListaRegCorreo & listaReg, ifstream & fIn) {
	fIn >> listaReg.cont;

	for (int i = 0; i < listaReg.cont; i++) {
		fIn >> listaReg.registros[i].id >> listaReg.registros[i].leido;
	}
}

void guardar(const tListaRegCorreo & listaReg, ofstream & fOut) {
	fOut << listaReg.cont << endl;

	for (int i = 0; i < listaReg.cont; i++) {
		fOut << listaReg.registros[i].id << " " << listaReg.registros[i].leido << endl;
	}
}

bool insertar(tListaRegCorreo & listaReg, tRegCorreo registro) {
	bool inser;

	inser = (listaReg.cont < MAX_REGISTROS);
	if (inser) {
		listaReg.registros[listaReg.cont] = registro;
		listaReg.cont++;
	}

	return inser;
}

bool borrar(tListaRegCorreo & listaReg, string id) {
	bool borrado;
	int pos;

	pos = buscar(listaReg, id);
	borrado = (pos != -1);

	if (borrado) {
		// Eliminamos el dato al escribir encima de el
		desplazarIzq(listaReg, pos);
		// Restamos la posicion eliminada
		listaReg.cont--;
	}

	return borrado;
}

bool correoLeido(tListaRegCorreo & listaReg, string id) {
	bool encontrado;
	int pos;

	pos = buscar(listaReg, id);
	encontrado = (pos != -1);

	if (encontrado) listaReg.registros[pos].leido = true;

	return encontrado;
}

int buscar(const tListaRegCorreo & listaReg, string id) {
	int pos = 0;
	bool encontrado = false;

	while ((pos < listaReg.cont) && !encontrado) {
		encontrado = (listaReg.registros[pos].id == id);
		if (!encontrado) pos++;
	}

	if (!encontrado) pos = -1;
	return pos;
}

void desplazarIzq(tListaRegCorreo & listaReg, int pos) {
	for (int i = pos; i < listaReg.cont; i++) {
		listaReg.registros[i] = listaReg.registros[i + 1];
	}
}