/* Realizado por David Antuña y Rafael Garces */

#include "ListaRegistros.h"

/*
	* Dada una lista de registros desplaza todos los registros desde pos hasta el final hacia la izquierda
	* @param1 lista de registros a desplazar
	* @param2 pos: limite inferior del desplazamiento
*/
void desplazarIzq(tListaRegCorreo & listaReg, int pos);

/*
	* Dado una capacidad de array la reduce
	* @param1 entero a modifica
	* @return entero aumentado
*/
int reduceCap(int capacidad);

/*
	* Dada una lista de registros aumenta su capacidad de almacenamiento
	* @param1 lista de registros
	* @param2 nueva capacidad de la lista
*/
void resize(tListaRegCorreo & listaReg, int nCap);

/*
	* Comprueba si mas de la mitad de la capacidad total del array esta desocupada
	* @param1 espacio ocupado del array
	* @param2 capacidad total del array
	* @return [true -> se debe reducir la capacidad (mas de la mitad del array vacia) / false -> caso contrario]
*/
bool compruebaRedCap(int ocupado, int capacidad);


void inicializar(tListaRegCorreo & listaReg, int cap) {
	listaReg.registros = new tRegCorreo[cap];
	listaReg.capacidad = cap;
}

void cargar(tListaRegCorreo & listaReg, ifstream & fIn, const tListaCorreos & correos) {
	string id;
	int pos;

	fIn >> listaReg.cont;
	inicializar(listaReg, (((listaReg.cont / 10) + 1) * 10)); // Aproximamos la capacidad a la siguiente decena

	for (int i = 0; i < listaReg.cont; i++) {
		fIn >> id >> listaReg.registros[i].leido;
		if(buscar(correos, id, pos))
			listaReg.registros[i].correo = correos.correos[pos];
		else 
			listaReg.registros[i].correo = nullptr;
	}
}

void guardar(const tListaRegCorreo & listaReg, ofstream & fOut) {
	fOut << listaReg.cont << endl;

	for (int i = 0; i < listaReg.cont; i++) {
		fOut << listaReg.registros[i].correo->id << " " << listaReg.registros[i].leido << endl;
	}
}

void insertar(tListaRegCorreo & listaReg, tRegCorreo registro) {
	// Si no entra el registro -> Aumentamos el espacio disponible
	if (listaReg.cont >= listaReg.capacidad)	resize(listaReg, aumentaCap(listaReg.capacidad));
	// Insertamos
	listaReg.registros[listaReg.cont] = registro;
	listaReg.cont++;
}

bool borrar(tListaRegCorreo & listaReg, string id) {
	bool borrado;
	int pos;

	pos = buscar(listaReg, id);
	borrado = (pos != -1);

	if (borrado) {
		// Eliminamos el dato
		desplazarIzq(listaReg, pos);
		// Restamos la posicion eliminada
		listaReg.cont--;
	}

	// Comprobamos si podemos hacer la lista mas pequeña
	if(compruebaRedCap(listaReg.cont, listaReg.capacidad))
		resize(listaReg, reduceCap(listaReg.capacidad));

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
		encontrado = (listaReg.registros[pos].correo->id == id);
		if (!encontrado) pos++;
	}

	if (!encontrado) pos = -1;
	return pos;
}

void desplazarIzq(tListaRegCorreo & listaReg, int pos) {
	for (int i = pos; i < listaReg.cont - 1; i++) {
		listaReg.registros[i] = listaReg.registros[i + 1];
	}
}

void destruir(tListaRegCorreo & listaReg) {
	delete[] listaReg.registros;
	listaReg.registros = nullptr;
	listaReg.cont = 0;
	listaReg.capacidad = 0;
}

void resize(tListaRegCorreo & listaReg, int nCap) {
	tRegPtr nRegistros;
	// Aumentamos el tamaño de la lista
	listaReg.capacidad = nCap;
	// Creamos el espacio en memoria
	nRegistros = new tRegCorreo[nCap];
	// Copiamos los datos originales
	for (int i = 0; i < listaReg.cont; i++)
		nRegistros[i] = listaReg.registros[i];
	// Destruimos el espacio que usaba la lista
	delete[] listaReg.registros;
	// Le damos a la lista la ubicacion de su nuevo espacio
	listaReg.registros = nRegistros;
}

int aumentaCap(int capacidad) {
	return (capacidad * 3) / 2 + 1;
}

int reduceCap(int capacidad) {
	return capacidad * 2 / 3;
}

bool compruebaRedCap(int ocupado, int capacidad) {
	return ((capacidad / 2) > ocupado);
}