/* Realizado por David Antuña y Rafael Garces */

#include "ListaCorreos.h"
#include "ListaRegistros.h"

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

/*
	* Dada una lista de correos aumenta su capacidad de almacenamiento
	* @param1 lista de registros
*/
void resize(tListaCorreos & correos);


void inicializar(tListaCorreos & correos, int capacidad) {
	correos.correos = new tCorreo*[capacidad];
	correos.capacidad = capacidad;
}

bool cargar(tListaCorreos & correos, string dominio) {
	bool abierto;
	ifstream fIn;
	string arch;

	arch = dominio + SUF_ARCH_C;
	fIn.open(arch.c_str());

	abierto = fIn.is_open();
	if (abierto) {
		fIn >> correos.cont;
		inicializar(correos, ((correos.cont / 10) + 1) * 10);
		for (int i = 0; i < correos.cont; i++) {
			correos.correos[i] = new tCorreo;
			cargar(*correos.correos[i], fIn);
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

	fOut << correos.cont << endl;
	for (int i = 0; i < correos.cont; i++) {
		guardar(*correos.correos[i], fOut);
	}

	fOut.close();
}

bool insertar(tListaCorreos & correos, const tCorreo & correo) {
	bool inser;
	int pos;
	// Comprobamos que no exista el identificador en la lista
	inser =(!buscar(correos, correo.id, pos));
	// Si queda espacio realizamos la insercion
	if (inser) {
		// Comprobamos que quede espacio -> si no queda aumentamos el tamaño
		if (correos.cont >= correos.capacidad) resize(correos);
		// Abrimos hueco
		correos.correos[correos.cont] = new tCorreo; // Creamos un nuevo espacio para correo al final de la lista
		desplazarDcha(correos, pos); // Movemos todos los correos a partir de pos un espacio a su derecha
		// Insertamos
		*correos.correos[pos] = correo;
		correos.cont++;
	}

	return inser;
}

bool buscar(const tListaCorreos & correos, string id, int & pos) {
	bool enc = false;
	int ini = 0, fin = correos.cont - 1, mitad;

	while (fin >= ini && !enc) {
		mitad = (ini + fin) / 2;
		if (id == correos.correos[mitad]->id) enc = true;
		else if (id < correos.correos[mitad]->id) fin = mitad - 1;
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

void borrar(tListaCorreos & correos, string id) {
	int pos;
	// Localizamos el correo en el array
	buscar(correos, id, pos);
	// Eliminamos el correo
	desplazarIzq(correos, pos);
	// Restamos la posicion eliminada
	correos.cont--;
}

void desplazarIzq(tListaCorreos & correos, int pos) {
	for (int i = pos; i < correos.cont - 1; i++) {
		correos.correos[i] = correos.correos[i + 1];
	}
}

void destruir(tListaCorreos & correos) {
	delete[] correos.correos;
	
	correos.cont = 0;
	correos.capacidad = 0;
}

void resize(tListaCorreos & correos) {
	tCorreo** nCorreos;
	// Aumentamos el tamaño de la lista
	correos.capacidad = aumentaCap(correos.capacidad);
	// Creamos el nuevo array
	nCorreos = new tCorreo*[correos.capacidad];
	// Copiamos los datos al nuevo array
	for(int i = 0; i < correos.cont; i++)
		nCorreos[i] = correos.correos[i];
	// Eliminamos el espacio que ocupaba el array antiguo
	delete[] correos.correos;
	// Asignamos el nuevo array
	correos.correos = nCorreos;
}