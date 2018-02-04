/* Realizado por David Antuña y Rafael Garces */

#ifndef ListaRegistros_h
#define ListaRegistros_h

#include <string>
#include <fstream>
using namespace std;

const int MAX_REGISTROS = 100;

typedef struct {
	string id;
	bool leido;
} tRegCorreo;

typedef tRegCorreo tArrayRegCorreo[MAX_REGISTROS];

typedef struct {
	tArrayRegCorreo registros;
	int cont;
} tListaRegCorreo;

/*
	* Inicializa la lista
	* @param lista de registros a inicializar
*/
void inicializar(tListaRegCorreo & listaReg);

/*
	* Dado un stream de entrada (ya abierto) lee los datos correspondientes a la lista de registros
	* @param1 lista de registros para almacenar los datos leidos
	* @param2 stream de entrada
*/
void cargar(tListaRegCorreo & listaReg, ifstream & fIn);

/*
	* Dado un stream de salida (ya abierto) almacena los datos de una lista de registros
	* @param1 lista de registros a almacenar
	* @param2 stream de salida
*/
void guardar(const tListaRegCorreo & listaReg, ofstream & fOut);

/*
	* Dado un registro lo inserta al final de la lista
	* @param1 lista de correos sobre la que realizar la insercion
	* @param2 registro a insertar en la lista
	* @return [true -> insercion realizada / false -> lista llena (insercion no realizada)]
*/
bool insertar(tListaRegCorreo & listaReg, tRegCorreo registro);

/*
	* Dado un id busca el registros asociado y lo elemina de la lista(sin dejar huecos)
	* @param1 lista de registros de la que se va a borrar
	* @param2 id del registro que se quiere eliminar
	* @return [false -> id no encontrada / true -> cualquier otro caso]
*/
bool borrar(tListaRegCorreo & listaReg, string id);

/*
	* Dado un identificador de correo: lo busca y pone el flag leido a true
	* @param1 lista de registros
	* @param2 id del correo que se ha leido
	* @return [true -> registro encontrado / false -> caso contrario]
*/
bool correoLeido(tListaRegCorreo & listaReg, string id);

/*
	* Busca en la lista de correos la posicion de un registro conociendo su identificador
	* @param1 lista de registros
	* @param2 id del correo que queremos buscar
	* @return [-1 -> id no encontrada / pos -> id encontrada]
*/
int buscar(const tListaRegCorreo & listaReg, string id);

#endif