/* Realizado por David Antuña y Rafael Garces */

#ifndef ListaUsuarios_h
#define ListaUsuarios_h

#include "Usuario.h"

const int MAX_USER = 50;
typedef tUsPtr tArrayUsuario[MAX_USER];
typedef struct {
	tArrayUsuario usuario;
	int cont;
} tListaUsuarios;

const string SUF_ARCH_U = "_usuarios.txt";

/*
	* Inicializa la lista
	* @param lista a inicializar
*/
void inicializar(tListaUsuarios & usuarios);

/*
	* Carga la lista con los usuarios correspondientes al dominio solicitado
	* @param1 contenedor para los datos de los usuarios
	* @param2 dominio del cual queremos cargar los usuarios
	* @param3 correos para que los registros creen los punteros
	* @return [true -> carga exitosa / false -> carga fallida]
*/
bool cargar(tListaUsuarios & usuarios, string dominio, const tListaCorreos & correos);

/*
	* Almacena en un archivo correspondiente al dominio la lista de usuarios
	* @param1 lista de usuarios a almacenar
	* @param2 dominio de los usuarios que se van a almacenar
*/
void guardar(const tListaUsuarios & usuarios, string dominio);

/*
	* Añade un usuario al lugar correspondiente de la lista siempre que quede espacio
	* @param1 lista sobre la que insertar al nuevo usuario
	* @param2 usuario que se desea añadir
	* @return [true -> exito / false -> fracaso]
*/
bool aniadir(tListaUsuarios & usuarios, const tUsuario & usuario);

/*
	* Busca un usuario por su identificador en la lista
	* @param1 lista de usuarios sobre la que realizar la busqueda
	* @param2 id del usuario que se busca
	* @param3 posicion en la que esta (encontrado) o deberia estar (no encontrado) el usuario
	* @return [true -> encontrado / false -> no encontrado]
*/
bool buscarUsuario(const tListaUsuarios & usuarios, string id, int & pos);

/*
	* Elimina de memoria los datos dinamicos de los usuarios
	* @param1 lista de correos
*/
void destruir(tListaUsuarios & usuarios);

#endif