/* Realizado por David Antuña */

#include <iostream>
#include <string>
using namespace std;
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

/* Tipos y Constantes */
const int CARTAS_POR_PALO = 13, CENTINELA = 52, MAX_CARTAS = 53, PALOS = 4, OPCIONES = 11, SALIR = 0;
const char CENTINELA_ARCHIVO = 'x';
typedef enum { picas, treboles, diamantes, corazones } tPalo;
typedef enum { A, Dos, Tres, Cuatro, Cinco, Seis, Siete, Ocho, Nueve, Diez, J, Q, K } tNumero;
typedef int tCarta;
typedef tCarta tMazo[MAX_CARTAS];

/* Prototipos */
/* Funciones Obligatorias V1 */
/*
  * Dado un mazo coloca en su primera posicion [0] el CENTINELA y pone el resto a 0
  * @param mazo a modificar
*/
void crearMazoVacio(tMazo mazo);

/*
  * Calcula el numero de cartas que hay en el mazo
  * @param mazo del que queremos conocer el tamaño
  * @return numero de cartas que contine dicho mazo
*/
int cuantasEnMazo(const tMazo mazo);

/*
  * Nos permite saber el palo de una carta
  * @param carta de la que queremos saber el palo
  * @return palo de la carta
*/
tPalo darPalo(tCarta carta);

/*
  * Nos permite saber el valor de una carta
  * @param carta de la que queremos saber el valor
  * @return valor de la carta
*/
tNumero darNumero(tCarta carta);

/*
  * Muestra por pantalla una carta
  * @param carta que queremos mostrar
*/
void escribirCarta(tCarta carta);

/*
  * Muestra por pantalla el contenido del mazo
  * @param mazo a mostrar
*/
void escribirMazo(const tMazo mazo);

/*
  * Carga el mazo de un fichero elegido por el usuario
  * @param mazo sobre el que realizar la carga
  * @return [false -> no se ha podido leer el fichero / true -> se ha podido realizar la lectura]
*/
bool cargarMazo(tMazo mazo);

/*
  * Baraja el mazo, realiza intercambios aleatorios entre las cartas
  * Se haran 3*numCartas intercambios
  * @param mazo a barajar
*/
void barajarMazo(tMazo mazo);

/*
  * Añade al final de mazoOriginal las cartas de nuevoMazo
  * @param1 mazoOriginal sobre el que concatenar
  * @param2 cartas a concatenar
  * @return [false -> mazoOriginal tiene mas cartas de las permitidas tras concatenar / true -> concatenacion exitosa]
*/
bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo);

/*
  * Quita a mazoOrigen las cartas de 0 a cuantasCoger y las coloca en mazoDestino
  * @param1 mazo con cartas que queremos cortar lo modificaremos al quitarle las cartas cortadas
  * @param2 lugar de corte
  * @param3 mazo auxiliar para guardar las cartas cortadas
  * @return [false -> mazoOrigen no tiene suficientes cartas / true -> mazoOrigen se ha podido cortar]
  * En caso de que el corte sea invalido mazoOrigen se devolvera sin modificar y mazo destino vacio
*/
bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino);

/*
  * Corta mazo por cuantas
  * En caso de que el lugar de corte indicado sea invalido se asumira que no se quiere cortar
  * Emplea la funcion [ partirMazo(); ]
  * @param1 mazo a cortar
  * @param2 lugar de corte
*/
void cortarMazo(tMazo mazo, int cuantas);

/*
  * Guarda el mazo en el fichero que especifique el usuario
  * @param1 mazo que se desea guardar
*/
void guardarMazo(const tMazo mazo);

/*
  * Muestra el usuario las opciones disponibles y solicita que seleccione una
  * @return opcion elegida
*/
int menu();

/* Funciones Extra V1 */
/*
  * Conviersion entre el enumerado tPalo y string
  * @param enumerado que queremos convertir
  * @return enumerado convertido a string
*/
string paloToString(tPalo palo);

/*
  * Conviersion entre el enumerado tNumero y string
  * @param enumerado que queremos convertir
  * @return enumerado convertido a string
*/
string numeroToString(tNumero numero);

/*
  * Solicita el usuario un nombre de fichero para cargar un mazo
  * @return nombre del fichero
*/
string pedirFichero();

/*
  * Comprueba que el nombre de fichero proporcionado por el usuario acaba con la extension .txt
  * @param nombre del fichero para validar
  * @return [true -> el fichero acaba con .txt / false -> cualquier otro caso]
*/
bool validarNombreFichero(string fichero);

/*
  * Muestra por pantalla un error en la extension del fichero
*/
void errorExtensionToString();

/*
  * Muestra por pantalla un error al leer un fichero
*/
void errorLecturaToString();

/*
  * Convierte el palo y valor leidos en un entero que se corresponda a dicha carta
  * @param1 palo de la carta
  * @param2 valor que representa la carta
  * @return valor asignado a la carta en nuestro mazo [0 - 51]
*/
int leidoToCarta(char palo, int numero);

/*
  * Convierten enteros/char a tPalo/tNumero respectivamente
  * @param entero/char a convertir
  * @return resultado de la conversion
*/
tPalo charToPalo(char palo);
tNumero intToNumero(int numero);

/*
  * Convierten tPalo/tNumero a enteros/char respectivamente
  * @param tPalo/tNumero a convertir
  * @return resultado de la conversion
*/
char paloToChar(tPalo palo);
int numeroToInt(tNumero numero);

/*
  * Genera una posicion aleatoria para cambiar
  * @param numero total de cartas en nuestro mazo para que la posicion a cambiar generada sea coherente
  * @return posicion aleatoria
*/
int cambioAleatorio(int numCartas);

/*
  * Desplaza a la izquierda las cartas de mazo tantas posiciones a la izquierda como indique posiciones
  * Las cartas de 0 a posiciones quedaran eliminadas
  * A la vez que desplazamos una carta escribiremos 0 en su posicion anterior asi al mover el centinela el lugar del anterio centinela se borrara
  * @param1 mazo a desplazar
  * @param2 desplazamientos
*/
void desplazarIzquierda(tMazo mazo, int posiciones);

/*
  * Muestra por pantalla un error si ocurre un error al unir dos mazos
*/
void errorAlUnirToString();

/*
  * Pide al usuario el lugar de corte del mazo
  * @return lugar para realizar el corte
*/
int solicitarCorteToString();

/*
  * Muestra por pantalla un error si no se puede realizar el corte solicitado
*/
void errorCortarToString();

/* Funciones Obligatorias V2 */
/*
  * Separa las cartas de mazo en dos mazos nuevos, uno contendra las cartas rojas (diamates y corazones) y otro las negras (picas y treboles)
  * @param1 mazo que contiene las cartas a repartir
  * @param2 mazo para guardar las cartas negras
  * @param3 mazo apra guardar las cartas rojas
*/
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);

/*
  * Separa las cartas de mazo en otros dos, uno con las cartas bajas (A a 7) y otro con las altas (8 a k)
  * @param1 mazo con cartas
  * @param2 mazo para las cartas bajas
  * @param3 mazo para las cartas altas
*/
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);

/*
  * Reparte mazo en tantos mazos como enCuantosMazos diga y guarda el queMazoPido en mazoNuevo
  * @param1 mazo con cartas
  * @param2 numero de mazos entre los que hacer el reparto
  * @param3 mazo que quiero quedarme
  * @param4 mazo en el que guardar el mazo que indique @param3
*/
void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo);

/* Funciones Extra V2 */
/*
  * Guarda en mazo[posicion] la carta y aumenta posicion
  * @param1 carta a guardar
  * @param2 mazo en el que guardarla
  * @param3 posicion del mazo en la que escribiremos
*/
void guardarCartaRepartida(tCarta carta, tMazo mazo, int &posicion);

/*
  * Se encargan de llamar a las funciones para repartir cartas y de manejar la salida por pantalla
  * @param1 mazo de cartas a repartir
*/
void repartoPorColor(const tMazo mazo);
void repartoPorValor(const tMazo mazo);
void repartoIntercalado(const tMazo mazo);

/* Funciones Obligatorias V3 */
/*
  * Se encarga de realizar el truco de los tres montones
*/
void trucoTresMontones();

/* Funciones Extra V3 */
/*
  * Se encarga de repartir el mazo ya barajado en montones, mostrarselos al usuario y unir los montones
  * Tambien mostrara al usuario un recordatorio de que no debe cambiar de carta si no estamos en la primera iteracion
  * @param1 mazo
*/
void reparteYReordena(tMazo mazo);

/*
  * Muestra por pantalla un error si el mazo elegido no tiene 21 cartas exactas y si alguna esta repetida
*/
void errorMazoTresMontones();

/*
  * Recorre mazo y busca si alguna de las cartas se repite
  * @param mazo en el que buscar
  * @return [true -> hay cartas repetidas / false -> no se repiten]
*/
bool buscarRepetidas(const tMazo mazo);

/*
  * Comprueba que el mazo cumpla los requisitos para realizar el truco de los tres montones
  * Requisitos: tamaño = 21 cartas && no hay cartas repetidas
  * @param mazo que queremos comprobar
  * @return [false -> el mazo no cumple los requisitos / true -> se puede usar este mazo]
*/
bool comprobarMazoTresMontones(const tMazo mazo);

/*
  * Dependiendo del valor elegido unira los mazos dejando en mazoNuevo la union de todos, siendo el mazo central de dicha union el elegido
  * @param1 mazo para realizar la union
  * @param2,3,4 montones
  * @param5 monton elegido
*/
void unirMazosTresMontones(tMazo mazoNuevo, tMazo mazo1, tMazo mazo2, tMazo mazo3, int elegido);

/*
  * Muestra un mensaje por pantalla recordando al usuario que no ha de cambiar su carta
*/
void recordatorioUsuario();

/*
  * Muestra al usuario la carta que habia elegido
*/
void averiguarCarta(const tCarta carta);

/* Funciones Obligatorias V4 */
/*
  * Se encarga de desarrollar el truco de la posada
*/
void trucoPosada();

/* Funciones Extra V4 */
/*
  * Muestra un error por pantalla si el mazo escogido no es valido para realizar el truco
*/
void errorMazoPosada();

/*
  * Comprueba que el mazo proporcionado este ordenado correctamente para la realizacion de truco
  * @param mazo a comprobar
  * @return [true -> el mazo esta ordenado correctamente / false -> mazo invalido]
*/
bool ordenadas(const tMazo mazo);

/*
  * Comprueba que el mazo proporcionado sea valido para el trco de la posada
  * @param mazo que se quiere comprobar
  * @return [true -> mazo ordenado y sin cartas repetidas / false -> cualquier otro caso]
*/
bool comprobarMazoPosada(const tMazo mazo);

/*
  * Reparte mazo en 4 montones
  * @param1 mazo a repartir
  * @param2,3,4,5 montones
*/
void repartirEn4Montones(const tMazo mazo, tMazo mazoAux1, tMazo mazoAux2, tMazo mazoAux3, tMazo mazoAux4);

/*
  * Muestra el contenido de los 4 montones
  * @param1,2,3,4 montones a mostrar
*/
void mostrar4Montones(tMazo mazoAux1, tMazo mazoAux2, tMazo mazoAux3, tMazo mazoAux4);

/* Funciones Obligatorias V5(OPCIONAL) */
/*
  * Hace que izq contenga las cartas pares del mazo (incluida Q) y der las impares (incluidas J y K)
  * @param1 mazo que contiene las cartas
  * @param2,3 mazos para guardar las cartas repartidas
*/
void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der);

/*
  * Hace que izq contenga las figuras/As del mazo (A, J, Q, K) y der las demas (2 - 10)
  * @param1 mazo que contiene las cartas
  * @param2,3 mazos para guardar las cartas repartidas
*/
void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der);

/*
  * Gestiona el truco del jugador desconfiado
*/
void trucoJugadorDesconfiado();

/* Funciones Extra V5(OPCIONAL) */
/*
  * Comprueba que el numero dado sea par
  * @param numero a comprobar
  * @return [true -> numero es par / false -> cualquier otro caso]
*/
bool esPar(int numero);

/*
  * Comprueba que el tNumero dado sea una figura
  * Entendemos como figura: A, J, Q, K
  * @param tNumero a comprobar
  * @return [true -> es figura / false -> cualquiero otro caso]
*/
bool esFigura(tNumero valor);

/*
  * Comprueba que el mazo cumpla los requisitos para el truco del desconfiado
  * @param1 mazo a comprobar
  * Cartas requeridas: A, Q, K de picas; 2, 4, 5, 6, 9, Q, K de treboles; 2, 3, 4, 5, 6, 10, K de diamantes; 10, Q, K de corazones.
  * @return [true -> el mazo tiene las cartas requeridas / false -> cualquier otro caso]
*/
bool comprobarMazoDesconfiado(const tMazo mazo);

/*
  * Comprueba que mazo contenga las cartas requeridas
  * Para ello crea un mazo auxiliar con las cartas y comprueba para cada posicion del mazo si se encuentra en mazo auxiliar
  * @param mazo a comprobar
  * @return [true -> el mazo contiene todas las cartas / false -> cualquier otro caso]
*/
bool cartasRequeridas(const tMazo mazo);

/*
  * Muestra un mensaje de error si el mazo proporcionado no es valido
*/
void errorMazoDesconfiado();

/*
  * Separa los mazos de cada jugador en dos: izquierdo y derecho y los une de 2 metodos distitos uno para iteracion < 2 y otro para iteracion = 2
  * @param1,2,3,4 mazos de los 4 jugadores
  * @param5 lleva la cuenta de las iteraciones que se han realizado
*/
void reorganizaMazos(tMazo jugador1, tMazo jugador2, tMazo jugador3, tMazo jugador4, int iteracion);

/* Funciones y tipos esteticos */
const int MAX_COLOR = 15;
typedef enum {
	black, dark_blue, dark_green, dark_cyan, dark_red, dark_magenta, dark_yellow, light_gray, dark_gray, light_blue, light_green,
	light_cyan, light_red, light_magenta, light_yellow, white
} tColor;
/*
  * Hace que windows muestre por pantalla el color solicitado
*/
void setColor(tColor color);

/*
  * Muestra un rotulo con el nombre del programa
*/
void rotulo();

/*
  * Genera un color aleatorio entre 1 y MAX_COLOR dejamos el 0 fuera porque es el negro y no se veria
*/
int colorAleatorio();

/* Hilo Principal */ // Problema al mostrar la ñ
int main() {
	srand(time(NULL));
	system("chcp 1252"); //Para que se muestren de forma correcta las tildes.
	system("CLS");
	int opcion = menu();
	tMazo mazo; crearMazoVacio(mazo);

	while (opcion != SALIR){
		system("CLS");
		switch (opcion)	{
			case 1: {
						if (cargarMazo(mazo)) escribirMazo(mazo);
			} break;
			case 2: {
						barajarMazo(mazo);
						escribirMazo(mazo);
			} break;
			case 3: {
						tMazo nuevo_mazo; crearMazoVacio(nuevo_mazo);
						if (cargarMazo(nuevo_mazo)) {
							if (unirMazos(mazo, nuevo_mazo)) escribirMazo(mazo);
							else errorAlUnirToString();
						}
						else errorLecturaToString();
			} break;
			case 4: {
						escribirMazo(mazo);
						cortarMazo(mazo, solicitarCorteToString());
						escribirMazo(mazo);
			} break;
			case 5: { guardarMazo(mazo); } break;
			case 6: { repartoPorColor(mazo); } break;
			case 7: { repartoPorValor(mazo); } break;
			case 8: { repartoIntercalado(mazo); } break;
			case 9: { trucoTresMontones(); } break;
			case 10: { trucoPosada(); } break;
			case 11: { trucoJugadorDesconfiado(); } break;
		default: break;
		}
		system("Pause");
		system("CLS");
		opcion = menu();
	}

	return 0;
}

/* Funciones V1 */
void crearMazoVacio(tMazo mazo) {
	for (int i = 0; i < CENTINELA; i++) {
		mazo[i] = 0;
	}
	mazo[52] = CENTINELA;
}

int cuantasEnMazo(const tMazo mazo) {
	int cuantas = 0;

	while (mazo[cuantas] != CENTINELA) {
		cuantas++;
	}

	return cuantas;
}

tPalo darPalo(tCarta carta) {
	tPalo palo;

	if ((carta >= 0) && (carta <= 12)) palo = picas;
	if ((carta >= 13) && (carta <= 25)) palo = treboles;
	if ((carta >= 26) && (carta <= 38)) palo = diamantes;
	if ((carta >= 39) && (carta <= 51)) palo = corazones;

	return palo;
}

tNumero darNumero(tCarta carta) {
	tNumero valor;

	if ((carta == 0) || (carta == 13) || (carta == 26) || (carta == 39)) valor = A;
	if ((carta == 1) || (carta == 14) || (carta == 27) || (carta == 40)) valor = Dos;
	if ((carta == 2) || (carta == 15) || (carta == 28) || (carta == 41)) valor = Tres;
	if ((carta == 3) || (carta == 16) || (carta == 29) || (carta == 42)) valor = Cuatro;
	if ((carta == 4) || (carta == 17) || (carta == 30) || (carta == 43)) valor = Cinco;
	if ((carta == 5) || (carta == 18) || (carta == 31) || (carta == 44)) valor = Seis;
	if ((carta == 6) || (carta == 19) || (carta == 32) || (carta == 45)) valor = Siete;
	if ((carta == 7) || (carta == 20) || (carta == 33) || (carta == 46)) valor = Ocho;
	if ((carta == 8) || (carta == 21) || (carta == 34) || (carta == 47)) valor = Nueve;
	if ((carta == 9) || (carta == 22) || (carta == 35) || (carta == 48)) valor = Diez;
	if ((carta == 10) || (carta == 23) || (carta == 36) || (carta == 49)) valor = J;
	if ((carta == 11) || (carta == 24) || (carta == 37) || (carta == 50)) valor = Q;
	if ((carta == 12) || (carta == 25) || (carta == 38) || (carta == 51)) valor = K;

	return valor;
}

void escribirCarta(tCarta carta) {
	cout << numeroToString(darNumero(carta)) << " de " << paloToString(darPalo(carta)) << endl;
}

string paloToString(tPalo palo) {
	string aux;

	switch (palo)
	{
		case picas: aux = "picas"; break;
		case treboles: aux = "treboles"; break;
		case diamantes: aux = "diamantes"; break;
		case corazones: aux = "corazones"; break;
		default: break;
	}

	return aux;
}

string numeroToString(tNumero numero) {
	string aux;

	switch (numero)
	{
		case A: aux = "A"; break;
		case Dos: aux = "2"; break;
		case Tres: aux = "3"; break;
		case Cuatro: aux = "4"; break;
		case Cinco: aux = "5"; break;
		case Seis: aux = "6"; break;
		case Siete: aux = "7"; break;
		case Ocho: aux = "8"; break;
		case Nueve: aux = "9"; break;
		case Diez: aux = "10"; break;
		case J: aux = "J"; break;
		case Q: aux = "Q"; break;
		case K: aux = "K"; break;
		default: break;
	}

	return aux;
}

void escribirMazo(const tMazo mazo) {
	for (int i = 0; mazo[i] != CENTINELA; i++) {
		escribirCarta(mazo[i]);
	}
}

bool cargarMazo(tMazo mazo) {
	bool cargado = false;
	string fichero;
	int aux = 0, cartas = 0; // lleva la cuenta de cuantas veces se ha intentado abrir el fichero si es superior a 3 vuelve al menu
	ifstream fIn;

	do {
		fichero = pedirFichero();
		fIn.open(fichero.c_str());
		if (!fIn.is_open())	errorLecturaToString();
		else {
			cargado = true;
			char palo;	int numero;
			fIn >> palo >> numero;
			while ((palo != CENTINELA_ARCHIVO) && (cartas < CENTINELA)) {
				mazo[cartas] = leidoToCarta(palo, numero);
				cartas++;
				fIn >> palo >> numero;
			}
			mazo[cartas] = CENTINELA;
		}
		++aux;
	} while ((aux < 3) && (!fIn.is_open()));
	fIn.close();

	return cargado;
}

string pedirFichero() {
	string fichero;

	do {
		cout << "Nombre del fichero: ";
		cin >> fichero;	cin.sync(); cin.clear();
	} while (!validarNombreFichero(fichero));

	return fichero;
}

bool validarNombreFichero(string fichero) {
	bool valido = true;

	if (fichero.length() >= 4) {
		string aux;
		for (int i = 4; i > 0; i--) {
			aux += fichero[fichero.length() - i];
		}
		if (aux != ".txt") {
			valido = false;
			errorExtensionToString();
		}
	}
	else valido = false;

	return valido;
}

void errorExtensionToString() {
	setColor(light_red);
	cout << "El fichero proporcionado no tiene un nombre valido" << endl;
	cout << "Asegurese de que el nombre termina con la extension .txt" << endl;
	setColor(white);
}

void errorLecturaToString() {
	setColor(light_red);
	cout << "Error: no se pudo leer el fichero" << endl;
	setColor(white);
}

int leidoToCarta(char palo, int numero) {
	int carta;

	switch (intToNumero(numero))
	{
		case A: carta = A + CARTAS_POR_PALO * charToPalo(palo); break;
		case Dos: carta = Dos + CARTAS_POR_PALO * charToPalo(palo); break;
		case Tres: carta = Tres + CARTAS_POR_PALO * charToPalo(palo); break;
		case Cuatro: carta = Cuatro + CARTAS_POR_PALO * charToPalo(palo); break;
		case Cinco: carta = Cinco + CARTAS_POR_PALO * charToPalo(palo); break;
		case Seis: carta = Seis + CARTAS_POR_PALO * charToPalo(palo); break;
		case Siete: carta = Siete + CARTAS_POR_PALO * charToPalo(palo); break;
		case Ocho: carta = Ocho + CARTAS_POR_PALO * charToPalo(palo); break;
		case Nueve: carta = Nueve + CARTAS_POR_PALO * charToPalo(palo); break;
		case Diez: carta = Diez + CARTAS_POR_PALO * charToPalo(palo); break;
		case J: carta = J + CARTAS_POR_PALO * charToPalo(palo); break;
		case Q: carta = Q + CARTAS_POR_PALO * charToPalo(palo); break;
		case K: carta = K + CARTAS_POR_PALO * charToPalo(palo); break;
		default: break;
	}

	return carta;
}

tPalo charToPalo(char palo) {
	tPalo resultado;

	switch (palo)
	{
		case 'p': resultado = picas; break;
		case 't': resultado = treboles; break;
		case 'd': resultado = diamantes; break;
		case 'c': resultado = corazones; break;
		default:break;
	}

	return resultado;
}

tNumero intToNumero(int numero) {
	tNumero resultado;

	switch (numero)
	{
		case 1: resultado = A; break;
		case 2: resultado = Dos; break;
		case 3: resultado = Tres; break;
		case 4: resultado = Cuatro; break;
		case 5: resultado = Cinco; break;
		case 6: resultado = Seis; break;
		case 7: resultado = Siete; break;
		case 8: resultado = Ocho; break;
		case 9: resultado = Nueve; break;
		case 10: resultado = Diez; break;
		case 11: resultado = J; break;
		case 12: resultado = Q; break;
		case 13: resultado = K; break;
		default:break;
	}

	return resultado;
}

void barajarMazo(tMazo mazo) {
	int posicion1, posicion2, cambios = 0, numCartas = cuantasEnMazo(mazo);
	// guardamos el numero de cartas para no tener que calcularlo en cada iteracion
	while (cambios < 3 * numCartas) {
		posicion1 = cambioAleatorio(numCartas);
		// asi evitamos que se intente hacer un cambio entre la misma posicion
		do { posicion2 = cambioAleatorio(numCartas); } while (posicion1 == posicion2);
		/* Metodo 1 */
		swap(mazo[posicion1], mazo[posicion2]);
		/* Metodo 2 */
		/*tCarta aux = mazo[posicion1];
		mazo[posicion1] = mazo[posicion2];
		mazo[posicion2] = aux;*/
		cambios++;
	}

} // se puede usar swap??

int cambioAleatorio(int numCartas) {
	return (rand() % numCartas);
}

bool unirMazos(tMazo mazoOriginal, const tMazo nuevoMazo) {
	bool unidos = true;

	// Comprobamos que se puedan unir
	if (cuantasEnMazo(mazoOriginal) + cuantasEnMazo(nuevoMazo) >= MAX_CARTAS) unidos = false;
	else { // Unimos los mazos
		int aux = cuantasEnMazo(mazoOriginal);
		for (int i = 0; i < cuantasEnMazo(nuevoMazo); i++) {
			mazoOriginal[aux + i] = nuevoMazo[i];
		}
		mazoOriginal[aux + cuantasEnMazo(nuevoMazo)] = CENTINELA;
	}

	return unidos;
}

bool partirMazo(tMazo mazoOrigen, int cuantasCoger, tMazo mazoDestino) {
	bool partido = true;
	int cuantas = cuantasEnMazo(mazoOrigen);
	if (cuantasCoger >= cuantas) partido = false;
	else {
		for (int i = 0; i < cuantasCoger; i++) {
			mazoDestino[i] = mazoOrigen[i];
		}
		mazoDestino[cuantasCoger] = CENTINELA;
		desplazarIzquierda(mazoOrigen, cuantasCoger);
	}

	return partido;
}

void desplazarIzquierda(tMazo mazo, int posiciones) {
	int numCartas = cuantasEnMazo(mazo);
	for (int i = posiciones; i <= numCartas; i++) {
		mazo[i - posiciones] = mazo[i];
		mazo[i] = 0;
	}
}

void cortarMazo(tMazo mazo, int cuantas) {
	tMazo mazo_aux; crearMazoVacio(mazo_aux);
	system("cls");
	if (cuantas > 0) {
		if (partirMazo(mazo, cuantas, mazo_aux)) unirMazos(mazo, mazo_aux);
		else errorCortarToString();
	}

}

void guardarMazo(const tMazo mazo) {
	string fichero = pedirFichero();
	ofstream fOut;
	int aux = 0;

	fOut.open(fichero.c_str());

	while ((aux < CENTINELA) && mazo[aux] != CENTINELA) {
		fOut << paloToChar(darPalo(mazo[aux])) << " " << numeroToInt(darNumero(mazo[aux])) << endl;
		aux++;
	}
	fOut << CENTINELA_ARCHIVO;

	fOut.close();
}

char paloToChar(tPalo palo) {
	char aux;

	switch (palo)
	{
		case picas: aux = 'p'; break;
		case treboles: aux = 't'; break;
		case diamantes: aux = 'd'; break;
		case corazones: aux = 'c'; break;
		default: break;
	}

	return aux;
}

int numeroToInt(tNumero numero) {
	int aux;

	switch (numero)
	{
		case A: aux = 1; break;
		case Dos: aux = 2; break;
		case Tres: aux = 3; break;
		case Cuatro: aux = 4; break;
		case Cinco: aux = 5; break;
		case Seis: aux = 6; break;
		case Siete: aux = 7; break;
		case Ocho: aux = 8; break;
		case Nueve: aux = 9; break;
		case Diez: aux = 10; break;
		case J: aux = 11; break;
		case Q: aux = 12; break;
		case K: aux = 13; break;
		default: break;
	}

	return aux;
}

int menu() {
	int opcion; rotulo();

	cout << "1 - Cargar mazo de cartas de fichero" << endl;
	cout << "2 - Barajar mazo de cartas" << endl;
	cout << "3 - Añadir mazo" << endl;
	cout << "4 - Cortar mazo" << endl;
	cout << "5 - Guardar mazo de cartas en fichero" << endl;
	cout << "6 - Separar en negras y rojas" << endl;
	cout << "7 - Separar en bajas y altas" << endl;
	cout << "8 - Repartir un mazo de manera alterna en montones" << endl;
	cout << "9 - Truco de los 3 montones" << endl;
	cout << "10 - Truco de la posada" << endl;
	cout << "11 - Truco del jugador desconfiado" << endl;
	cout << "0 - Salir" << endl;
	do {
		cout << "Opcion: ";
		cin >> opcion; cin.sync(); cin.clear();
	} while ((opcion < SALIR) || (opcion > OPCIONES));

	return opcion;
}

void errorAlUnirToString() {
	setColor(light_red);
	cout << "Error: no se pueden unir los mazos" << endl;
	setColor(white);
}

int solicitarCorteToString() {
	int corte;

	do {
		cin.sync(); cin.clear();
		cout << "Corte: ";
		cin >> corte;
	} while (cin.fail());

	return corte;
}

void errorCortarToString() {
	setColor(light_red);
	cout << "Error: no se pudo realizar el corte solicitado" << endl;
	setColor(white);
}

/* Funciones V2 */
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo) {
	int contRojo = 0, contNegro = 0;
	for (int i = 0; i < cuantasEnMazo(mazo); i++){
		if ((darPalo(mazo[i]) == treboles) || (darPalo(mazo[i]) == picas)) guardarCartaRepartida(mazo[i], mazoNegro, contNegro);
		else guardarCartaRepartida(mazo[i], mazoRojo, contRojo);
	}
	mazoNegro[contNegro] = CENTINELA;
	mazoRojo[contRojo] = CENTINELA;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas) {
	int contBajas = 0, contAltas = 0;
	for (int i = 0; i < cuantasEnMazo(mazo); i++) {
		int aux = darNumero(mazo[i]);
		if (darNumero(mazo[i]) <= Siete) guardarCartaRepartida(mazo[i], mazoBajas, contBajas);
		else guardarCartaRepartida(mazo[i], mazoAltas, contAltas);
	}
	mazoBajas[contBajas] = CENTINELA;
	mazoAltas[contAltas] = CENTINELA;
}

void repartirIntercalando(const tMazo mazo, int enCuantosMazos, int queMazoPido, tMazo mazoNuevo) {
	int contNuevo = 0, aux = 0;
	for (int i = 0; i < cuantasEnMazo(mazo); i++){
		if (aux == queMazoPido) guardarCartaRepartida(mazo[i], mazoNuevo, contNuevo);

		if (aux < enCuantosMazos - 1) aux++;
		else aux = 0;
	}
	mazoNuevo[contNuevo] = CENTINELA;
}

void guardarCartaRepartida(tCarta carta, tMazo mazo, int &posicion) {
	mazo[posicion] = carta;
	posicion++;
}

void repartoPorColor(const tMazo mazo) {
	tMazo mazoNegro, mazoRojo;
	crearMazoVacio(mazoNegro); crearMazoVacio(mazoRojo);

	repartirNegroRojo(mazo, mazoNegro, mazoRojo);

	cout << "Mazo negro:" << endl; escribirMazo(mazoNegro);
	cout << endl << "Mazo Rojo:" << endl; escribirMazo(mazoRojo);
}

void repartoPorValor(const tMazo mazo) {
	tMazo mazoBajas, mazoAltas;
	crearMazoVacio(mazoBajas); crearMazoVacio(mazoAltas);

	repartirBajaAlta(mazo, mazoBajas, mazoAltas);

	cout << "Mazo bajas:" << endl; escribirMazo(mazoBajas);
	cout << endl << "Mazo altas:" << endl; escribirMazo(mazoAltas);
}

void repartoIntercalado(const tMazo mazo) {
	int numMazos, queMazo;
	tMazo nuevoMazo; nuevoMazo[0] = CENTINELA;

	do {
		cout << "En cuantos mazos quiere repartir las cartas: ";
		cin.sync(); cin.clear(); cin >> numMazos;
	} while (cin.fail());

	if (numMazos > 0) {
		do {
			cout << "Que mazo desea quedarse: ";
			cin.sync(); cin.clear(); cin >> queMazo;
		} while (cin.fail() || queMazo <= 0 || queMazo > numMazos);

		repartirIntercalando(mazo, numMazos, queMazo - 1, nuevoMazo);
	}

	cout << "Nuevo mazo:" << endl; escribirMazo(nuevoMazo);
}

/* Funciones V3 */
void trucoTresMontones() {
	tMazo mazo;
	crearMazoVacio(mazo);
	do {
		cargarMazo(mazo);
		if (!comprobarMazoTresMontones(mazo)) errorMazoTresMontones();
	} while (!comprobarMazoTresMontones(mazo));

	// Desarrollo del truco
	barajarMazo(mazo);

	reparteYReordena(mazo);

	averiguarCarta(mazo[10]);
}

void reparteYReordena(tMazo mazo) {
	int aux;
	tMazo mazoAux1, mazoAux2, mazoAux3;
	for (int i = 0; i < 3; i++){
		// Repartimos los mazos
		repartirIntercalando(mazo, 3, 0, mazoAux1);
		repartirIntercalando(mazo, 3, 1, mazoAux2);
		repartirIntercalando(mazo, 3, 2, mazoAux3);
		// Mostramos los mazos
		cout << "Mazo 1:" << endl; escribirMazo(mazoAux1);
		cout << endl << "Mazo 2:" << endl; escribirMazo(mazoAux2);
		cout << endl << "Mazo 3:" << endl; escribirMazo(mazoAux3);
		cout << endl;
		do {
			if (i != 0) recordatorioUsuario();
			cout << "En que mazo esta tu carta: ";
			cin >> aux;
		} while (aux != 1 && aux != 2 && aux != 3);
		//Unimos los mazos
		tMazo mazoNuevo; mazoNuevo[0] = CENTINELA;
		unirMazosTresMontones(mazoNuevo, mazoAux1, mazoAux2, mazoAux3, aux);
		mazo[0] = CENTINELA; unirMazos(mazo, mazoNuevo);
		system("CLS");
	}
}

void unirMazosTresMontones(tMazo mazoNuevo, tMazo mazo1, tMazo mazo2, tMazo mazo3, int elegido) {
	if (elegido == 1) {
		unirMazos(mazoNuevo, mazo2);
		unirMazos(mazoNuevo, mazo1);
		unirMazos(mazoNuevo, mazo3);
	}
	else if (elegido == 2) {
		unirMazos(mazoNuevo, mazo3);
		unirMazos(mazoNuevo, mazo2);
		unirMazos(mazoNuevo, mazo1);
	}
	else {
		unirMazos(mazoNuevo, mazo2);
		unirMazos(mazoNuevo, mazo3);
		unirMazos(mazoNuevo, mazo1);
	}
}

bool comprobarMazoTresMontones(const tMazo mazo) {
	return ((cuantasEnMazo(mazo) == 21) && (!buscarRepetidas(mazo)));
}

bool buscarRepetidas(const tMazo mazo) {
	bool repetidas = false;

	for (int i = 0; i < cuantasEnMazo(mazo) - 2; i++) {
		for (int j = i + 1; j < cuantasEnMazo(mazo) - 1; j++) {
			if (mazo[i] == mazo[j]) repetidas = true;
		}
	}

	return repetidas;
}

void errorMazoTresMontones() {
	setColor(light_red);
	cout << "Error: mazo invalido" << endl;
	cout << "El mazo debe tener 21 cartas distintas exactas" << endl;
	setColor(white);
}

void recordatorioUsuario() {
	cout << "Recuerda que no debes cambiar la carta elegida anteriormente" << endl;
}

void averiguarCarta(const tCarta carta) {
	cout << endl << endl << "Tu carta es ";
	escribirCarta(carta);
	cout << endl;
}

/* Funciones V4 */
void trucoPosada() {
	tMazo mazo;
	crearMazoVacio(mazo);
	do {
		cargarMazo(mazo);
		if (!comprobarMazoPosada(mazo)) errorMazoPosada();
	} while (!comprobarMazoPosada(mazo));

	//Desarrollo del truco
	tMazo mazoAux1, mazoAux2, mazoAux3, mazoAux4;

	repartirEn4Montones(mazo, mazoAux1, mazoAux2, mazoAux3, mazoAux4);

	//Mostramos los mazos repartidos
	mostrar4Montones(mazoAux1, mazoAux2, mazoAux3, mazoAux4); system("pause"); system("cls");

	// Unimos los mazos y mostramos
	mazo[0] = CENTINELA;
	unirMazos(mazo, mazoAux1);
	unirMazos(mazo, mazoAux2);
	unirMazos(mazo, mazoAux3);
	unirMazos(mazo, mazoAux4);

	escribirMazo(mazo);
	cortarMazo(mazo, solicitarCorteToString());
	system("CLS");

	repartirEn4Montones(mazo, mazoAux1, mazoAux2, mazoAux3, mazoAux4);
	mostrar4Montones(mazoAux1, mazoAux2, mazoAux3, mazoAux4);
}

void mostrar4Montones(tMazo mazoAux1, tMazo mazoAux2, tMazo mazoAux3, tMazo mazoAux4) {
	cout << "Mazo 1:" << endl; escribirMazo(mazoAux1);
	cout << endl << "Mazo 2:" << endl; escribirMazo(mazoAux2);
	cout << endl << "Mazo 3:" << endl; escribirMazo(mazoAux3);
	cout << endl << "Mazo 4:" << endl; escribirMazo(mazoAux4);
}

void repartirEn4Montones(const tMazo mazo, tMazo mazoAux1, tMazo mazoAux2, tMazo mazoAux3, tMazo mazoAux4) {
	//Repartimos en 4 mazos
	repartirIntercalando(mazo, 4, 0, mazoAux1);
	repartirIntercalando(mazo, 4, 1, mazoAux2);
	repartirIntercalando(mazo, 4, 2, mazoAux3);
	repartirIntercalando(mazo, 4, 3, mazoAux4);
}

void errorMazoPosada() {
	setColor(light_red);
	cout << "Error: mazo invalido" << endl;
	cout << "El mazo debe contener: 4 J's, 4 Q's, 4 K's y 4 Ases (uno de cada palo) y en este mismo orden " << endl;
	setColor(white);
}

bool comprobarMazoPosada(const tMazo mazo) {
	return ((cuantasEnMazo(mazo) == 16) && (!buscarRepetidas(mazo)) && (ordenadas(mazo)));
}

bool ordenadas(const tMazo mazo) {
	bool ordenadas = true;

	for (int i = 0; i < cuantasEnMazo(mazo); i++) {
		if (((i >= 0 && i <= 3) && (darNumero(mazo[i]) != J)) || ((i >= 4 && i <= 7) && (darNumero(mazo[i]) != Q))
			|| ((i >= 8 && i <= 11) && (darNumero(mazo[i]) != K)) || ((i >= 12 && i <= 15) && (darNumero(mazo[i]) != A))) ordenadas = false;
	}

	return ordenadas;
}

/* Funciones V5(OPCIONAL) */
void repartirParImpar(const tMazo mazo, tMazo izq, tMazo der) {
	int contIzq = 0, contDer = 0;
	for (int i = 0; i < cuantasEnMazo(mazo); i++) {
		if (esPar(numeroToInt(darNumero(mazo[i])))) guardarCartaRepartida(mazo[i], izq, contIzq);
		else guardarCartaRepartida(mazo[i], der, contDer);
	}
	izq[contIzq] = CENTINELA;
	der[contDer] = CENTINELA;
}

void repartirFiguraNoFigura(const tMazo mazo, tMazo izq, tMazo der) {
	int contIzq = 0, contDer = 0;
	for (int i = 0; i < cuantasEnMazo(mazo); i++) {
		if (esFigura(darNumero(mazo[i]))) guardarCartaRepartida(mazo[i], izq, contIzq);
		else guardarCartaRepartida(mazo[i], der, contDer);
	}
	izq[contIzq] = CENTINELA;
	der[contDer] = CENTINELA;
}

void trucoJugadorDesconfiado() {
	tMazo mazo;
	crearMazoVacio(mazo);
	do {
		cargarMazo(mazo);
		if (!comprobarMazoDesconfiado(mazo)) errorMazoDesconfiado();
	} while (!comprobarMazoDesconfiado(mazo));
	
	// Desarrollo del truco
	// barajamos y mostramos el mazo
	barajarMazo(mazo); escribirMazo(mazo); system("Pause"); system("CLS");

	// Repartimos cartas a los 4 jugadores
	tMazo jugador1, jugador2, jugador3, jugador4;
	repartirEn4Montones(mazo, jugador1, jugador2, jugador3, jugador4);
	mostrar4Montones(jugador1, jugador2, jugador3, jugador4); system("Pause"); system("CLS");

	// Reorganizamos los mazos de los jugadores
	for (int i = 0; i < 3; i++){
		reorganizaMazos(jugador1, jugador2, jugador3, jugador4, i);
		cout << "VUELTA " << i + 1 << endl << endl;
		mostrar4Montones(jugador1, jugador2, jugador3, jugador4);
		cout << endl;
	}
}

bool esPar(int numero) {
	return (numero % 2 == 0);
}

bool esFigura(tNumero valor) {
	return ((valor == A) || (valor == J) || (valor == Q) || (valor == K));
}

bool comprobarMazoDesconfiado(const tMazo mazo) {
	return((cuantasEnMazo(mazo) == 20) && (!buscarRepetidas(mazo)) && (cartasRequeridas(mazo)));
}

bool cartasRequeridas(const tMazo mazo) {
	bool ok = true;
	tMazo mazoAux = { 0, 11, 12, 14, 16, 17, 18, 21, 24, 25, 27, 28, 29, 30, 31, 35, 38, 48, 50, 51, CENTINELA }; // mazo que contiene las cartas requeridas
	int cont = 0;

	while ((cont < cuantasEnMazo(mazoAux))&& ok) {
		bool esta = false;
		for (int j = 0; j < cuantasEnMazo(mazo); j++) {
			if (mazoAux[cont] == mazo[j])	esta = true;
		}
		if (!esta) ok = false;
		else cont++;
	}

	return ok;
}

void errorMazoDesconfiado() {
	setColor(light_red);
	cout << "Error: mazo invalido" << endl;
	cout << "El mazo debe contener las siguientes cartas (no importa el orden):" << endl;
	cout << "A, Q, K de picas; 2, 4, 5, 6, 9, Q, K de treboles;" << endl;
	cout << "2, 3, 4, 5, 6, 10, K de diamantes; 10, Q, K de corazones." << endl;
	setColor(white);
}

void reorganizaMazos(tMazo jugador1, tMazo jugador2, tMazo jugador3, tMazo jugador4, int iteracion) {
	tMazo izq1, der1, izq2, der2, izq3, der3, izq4, der4;
	
	repartirNegroRojo(jugador1, izq1, der1);		// Jugador1: Negras - izquierda / Rojas - derecha
	repartirBajaAlta(jugador2, izq2, der2);			// Jugador2: A hasta 7 - izquierda / 8 hasta K - derecha
	repartirParImpar(jugador3, izq3, der3);			// Jugador3: Pares - izquierda / Impares - derecha
	repartirFiguraNoFigura(jugador4, izq4, der4);	// Jugador4: Figuras - izquierda / No figuras - derecha
	// Reseteamos los mazos de los jugadores para realizar las uniones
	jugador1[0] = CENTINELA; jugador2[0] = CENTINELA; jugador3[0] = CENTINELA; jugador4[0] = CENTINELA;
	if (iteracion < 2) {
		unirMazos(jugador1, der4); unirMazos(jugador1, izq2); // Nuevo mazo jugador1
		unirMazos(jugador2, der1); unirMazos(jugador2, izq3); // Nuevo mazo jugador2
		unirMazos(jugador3, der2); unirMazos(jugador3, izq4); // Nuevo mazo jugador3
		unirMazos(jugador4, der3); unirMazos(jugador4, izq1); // Nuevo mazo jugador4
	}
	else {
		unirMazos(jugador1, der1); unirMazos(jugador1, izq2); // Nuevo mazo jugador1
		unirMazos(jugador2, der2); unirMazos(jugador2, izq3); // Nuevo mazo jugador2
		unirMazos(jugador3, der3); unirMazos(jugador3, izq4); // Nuevo mazo jugador3
		unirMazos(jugador4, der4); unirMazos(jugador4, izq1); // Nuevo mazo jugador4
	}
}

/* Funciones esteticas */
void setColor(tColor color) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);

}

int colorAleatorio() {
	return ((rand() % MAX_COLOR) + 1);
}

//Color aleatorio por filas
void rotulo() {
	SetConsoleTitle("Trucos de Magia V5(OPCIONAL)");

	setColor(tColor(colorAleatorio()));
	cout << " ***** ****   *   * *****  ***  *****     ***   ***** " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "   *   *   *  *   * *     *   * *         *   * *     " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "   *   ****   *   * *     *   * *****     *   * ****  " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "   *   *  *   *   * *     *   *     *     *   * *     " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "   *   *   *  ***** *****  ***  *****     ***   ***** " << endl;

	cout << endl << endl;
	setColor(tColor(colorAleatorio()));
	cout << "              *   *  ***  ***** *****  ***  " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "              ** ** *   * *       *   *   * " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "              * * * ***** *  **   *   ***** " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "              *   * *   * *   *   *   *   * " << endl;
	setColor(tColor(colorAleatorio()));
	cout << "              *   * *   * ***** ***** *   * " << endl;
	setColor(tColor(colorAleatorio()));
	cout << " -------------------------------------------------------" << endl << endl;
	setColor(white);
}