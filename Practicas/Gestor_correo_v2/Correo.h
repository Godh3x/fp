/* Realizado por David Antuña y Rafael Garces */

#ifndef Correo_h
#define Correo_h

#include <string>
#include <fstream>
using namespace std;
#include <ctime>

const string CENT_ID = "XXX";

typedef time_t tFecha;

const int MAX_DES = 20;
typedef string tArrayDes[MAX_DES];
typedef struct {
	tArrayDes destinatario;
	int cont;
} tListaDes;

typedef struct {
	string emisor;
	tListaDes destinatarios;
	string asunto;
	string cuerpo;
	tFecha fecha;
	string id;
	int almacenado;
} tCorreo;

bool operator<(const tCorreo & cIzq, const tCorreo & cDcha);

/*
  * Dado un emisor y un contenedor de titpo tCorreo: rellena los campos del contenedor
	* @param1 Contenedor de tipo tCorreo
	* @param2 emisor
*/
void correoNuevo(tCorreo & correo, string emisor);

/*
	* Dado un correo y un emisor devuelve los datos correspondientes a la contestacion del mismo en un contenedor
	*	@param1 correo a contestar
	* @param2 contenedor para almacenar lo contestado
	* @param3 emisor
*/
void correoContestacion(const tCorreo & correoOriginal, tCorreo & correo, string emisor);

/*
	* Devuelve un string con el contenido completo del correo
	* @param correo
	* @return string con el contenido del parametro
*/
string aCadena(const tCorreo & correo);

/*
	* Devuelve un string que se usara para mostrar en la bandeja de entrada/salida
	* @param correo del que queremos conocer la cabecera
	* @return string con los datos referentes a: emisor, asunto y fecha sin hora
*/
string obetenerCabecera(const tCorreo & correo);

/*
	* Dado un stream de entrada (ya abierto) lee y devuelve los datos correspondientes a un correo
	* @param1 contenedor para los datos leidos
	* @param2 stream de entrada
*/
void cargar(tCorreo & correo, ifstream& fIn);

/*
	* Dado un stream de salida (ya abierto) escribe en el stream los  datos correspondientes a un correo
	* @param1 datos del correo a guardar
	* @param2 stream de salida
*/
void guardar(const tCorreo & correo, ofstream & fOut);

#endif