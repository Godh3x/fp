/* Realizado por David Antuña y Rafael Garces */

#include "ListaCorreos.h"

/*
	* Dada una lista de correos desplaza todos los correos desde el final hasta pos (incluido) hacia la derecha
	* @param1 lista de correos a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarDcha(tListaCorreos & correos, int pos);

/*
	* Dada una lista de correos desplaza todos los correos desde pos hasta el final (incluido) hacia la izquieda
	* @param1 lista de registros a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarIzq(tListaCorreos & correos, int pos);

void inicializar(tListaCorreos & correos) {
	correos.cont = 0;
}

bool cargar(tListaCorreos & correos, string dominio) {
	bool abierto;
	ifstream fIn;
	string arch;

	arch = dominio + SUF_ARCH_C;
	fIn.open(arch.c_str());

	abierto = fIn.is_open();
	if (abierto) {
		while (cargar(correos.correos[correos.cont], fIn)) {
			correos.cont++;
		}
		
		fIn.close();
	}

	return abierto;
}

void guardar(const tListaCorreos & correos, string dominio) {
	ofstream fOut;
	string arch;

	arch = dominio + SUF_ARCH_C;
	fOut.open(arch.c_str());

	for (int i = 0; i < correos.cont; i++) {
		guardar(correos.correos[i], fOut);
	}
	fOut << CENT_ID;

	fOut.close();
}

bool insertar(tListaCorreos & correos, const tCorreo & correo) {
	bool inser;
	int pos;
	// Comprobamos que quede espacio y que no exista el identificador en la lista
	inser = ((correos.cont < MAX_CORREOS) && !buscar(correos, correo.id, pos));
	// Si queda espacio realizamos la insercion
	if (inser) {
		// Abrimos hueco
		desplazarDcha(correos, pos);
		// Insertamos
		correos.correos[pos] = correo;
		correos.cont++;
	}

	return inser;
}

bool buscar(const tListaCorreos & correos, string id, int & pos) {
	bool enc = false;
	int ini = 0, fin = correos.cont - 1, mitad;

	while (fin >= ini && !enc) {
		mitad = (ini + fin) / 2;
		if (id == correos.correos[mitad].id) enc = true;
		else if (id < correos.correos[mitad].id) fin = mitad - 1;
		else ini = mitad + 1;
	}

	if (enc) pos = mitad;
	else pos = ini;

	return enc;
}

void ordenar_AF(tListaCorreos & correos) {
	bool inter = true;
	int i = 0;

	while (i < correos.cont - 1 && inter) {
		inter = false;
		for (int j = correos.cont - 1; j > i; j--) {
			if (correos.correos[j] < correos.correos[j - 1]) {
				swap(correos.correos[j], correos.correos[j - 1]);
				inter = true;
			}
		}
		if (inter) i++;
	}
}

void desplazarDcha(tListaCorreos & correos, int pos) {
	for (int i = correos.cont; i > pos; i--) {
		correos.correos[i] = correos.correos[i - 1];
	}
}

void borrar(tListaCorreos & correos, int pos) {
		// Eliminamos el correo al escribir encima de el
		desplazarIzq(correos, pos);
		// Restamos la posicion eliminada
		correos.cont--;
}

void desplazarIzq(tListaCorreos & correos, int pos) {
	for (int i = pos; i < correos.cont; i++) {
		correos.correos[i] = correos.correos[i + 1];
	}
}