/* Realizado por David Antuña y Rafael Garces */

#ifndef ListaCorreos_h
#define ListaCorreos_h

#include "Correo.h"

const int MAX_CORREOS = 100;

const string SUF_ARCH_C = "_correos.txt";

typedef tCorreo tArrayCorreos[MAX_CORREOS];

typedef struct {
	tArrayCorreos correos;
	int cont;
} tListaCorreos;

/*
	* Inicializa la lista de correos
	* @param lista de correos
*/
void inicializar(tListaCorreos & correos);

/*
	*	Carga la lista de correos desde <dominio>_correos.txt
	* @param1 lista de correos a cargar
	* @param2 dominio de los correos que estamos cargando
	* @return [true -> carga exitosa / false -> caso contrario]
*/
bool cargar(tListaCorreos & correos, string dominio);

/*
	* Guarda la lista de correos en <dominio>_correos.txt
	* @param1 lista de correos a guardar
	* @param2 dominio de los correos que estamos guardando
*/
void guardar(const tListaCorreos & correos, string dominio);

/*
	*	Inserta un correo en la lista de correos
	* @param1 lista de correos sobra la que realizar la insercion
	* @param2 correo que se va a insertar
	* @return [true -> insercion realizada / false -> caso contrario]
*/
bool insertar(tListaCorreos & correos, const tCorreo & correo);

/*
	*	Dada un identificador lo busca en la lista de correos
	* @param1 lista sobra la que realizar la busqueda
	* @param2 identificador del correo buscado
	* @param3 devolvera la posicion en la que esta o deberia estar el correo
	* @return [true -> existe un correo con el identificador buscado / false -> caso contrario]
*/
bool buscar(const tListaCorreos & correos, string id, int & pos);

/*
	* Ordena la lista de correos por asunto y fecha
	* @param lista de correos a ordenar
*/
void ordenar_AF(tListaCorreos & correos);

/*
	* Elimina un correo de una lista de correos dada la posicion del mismo
	* @param1 lista de correos que se desea procesar
	* @param2 posicion en la que se encuentra el correo que queremos eliminar
*/
void borrar(tListaCorreos & correos, int pos);

#endif