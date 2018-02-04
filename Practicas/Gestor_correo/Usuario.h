/* Realizado por David Antuña y Rafael Garces */

#ifndef Usuario_h
#define Usuario_h

#include <string>
#include <fstream>
using namespace std;
#include "ListaRegistros.h"

typedef struct {
	string id;
	string pwd;
	tListaRegCorreo listaRecibidos;
	tListaRegCorreo listaEnviados;
} tUsuario;

/*
	* Dado un stream de entrada (ya abierto) carga un usuario de fichero
	* @param1 usuario a cargar
	* @param2 stream de entrada
	* @return [true -> carga exitosa / false -> no se ha cargado el usuario);
*/
bool cargar(tUsuario & usuario, ifstream & fIn);

/*
	* Dado un stream de salida (ya abierto) guarda el contenido de un usario en fichero
	* @param1 datos del usuario a guardar
	* @param2 stream de salida
*/
void guardar(const tUsuario & usuario, ofstream & fOut);

/*
	* Dados un identificador y una contraseña los asigna al usuario
	* @param1 usuario al que asignarle los datos
	* @param2 id a asignar
	* @param3 contraseña a asignar
*/
void inicializar(tUsuario & usuario, string id, string contrasenia);

/*
	* Dados un usuario y una contrasenia comprueba si coinciden
	* @param1 datos del usuario
	* @param2 contrasenia a validar
	* @return [true -> las contraseñas coinciden / false -> caso contrario]
*/
bool validarContrasenia(const tUsuario & usuario, string contrasenia);

#endif