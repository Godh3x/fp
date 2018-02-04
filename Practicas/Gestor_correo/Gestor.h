/* Realizado por David Antuña y Rafael Garces */

#ifndef Gestor_h
#define Gestor_h

#include <string>
using namespace std;
#include "ListaCorreos.h"
#include "ListaUsuarios.h"

typedef struct {
	string dominio;
	tListaCorreos correos;
	tListaUsuarios usuarios;
	int idUsuario;
} tGestor;

/*
	* Inicializa el gestor y trata de cargar la informacion referente al dominio solicitado
	* @param1 contenedor para los datos del gestor
	* @param2 dominio solicitado
	* @return [true -> todo cargado con exito / false -> alguna operacion de carga fallo]
*/
bool arrancar(tGestor & gestor, string dominio);

/*
	* Guarda la informacion actual del gestor en los archivos del dominio activo
	* @param informacion actual del gestor
*/
void apagar(const tGestor & gestor);

/*
	* Lee los datos necesarios para crear el usuario (id y contraseña) y crea el usuario
	* @param datos del gestor
	* @return [true -> usuario creado con exito / false -> la id ya existia o no habia hueco para su creacion]
*/
bool crearCuenta(tGestor & gestor);

/*
	* Lee los datos necesarios para validar un usuario (id y contraseña) y lo registra como usuario activo
	* @param1 datos del gestor
	* @return [true -> id existe && contraseña introducida coincide con la almacenada / false -> caso opuesto]
*/
bool iniciarSesion(tGestor & gestor);

/*
	* Solicita el correo que el usuario quiere leer
	* Si el correo existe lo marca como leido y lo busca en la lista de correos para mostrarlo
	* @param1 datos del gestor
	* @param2 lista de correos
*/
void leerCorreo(tGestor & gestor, tListaRegCorreo & listaReg);

/*
	* Inserta el correo en al lista de correos
	* Si se ha podido insertar añade el registro correspondiente tanto en la lista del emisor como del destinatario
	* Si el destinatario no existe o su bandeja de entrada esta llena mostrara un error
	* @param1 datos del gestor
	* @param2 correo que se desea enviar
*/
void enviarCorreo(tGestor & gestor, const tCorreo & correo);

/*
	* Borra el correo de la bandeja de un usuario (NO de la lista de correos)
	* @param1 datos del gestor
	* @param2 registros de los correos
*/
void borrarCorreo(tGestor & gestor, tListaRegCorreo & listaReg);

/*
	* Muestra una lista de correos sin leer ordenados por asunto (ignorado los "RE: ") y fecha
	* Todos los correos sin leer se marcaran como leidos
	* @param1 datos del gestor
	* @param2 registros de los correos
*/
void lecturaRapida(const tGestor & gestor, tListaRegCorreo & listaReg);

/*
	* Una vez se ha iniciado sesion en el gestor se encarga de manejar las peticiones del usuario
	* @param datos del gestor
*/
void gestionarSesion(tGestor & gestor);

#endif