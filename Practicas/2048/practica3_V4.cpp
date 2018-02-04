/* Realizado por David Antuña */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include <iomanip>
#include <time.h>
#include <Windows.h>
#include <conio.h>

/***********************
*  Tipos y Constantes  *
***********************/

const int CELDA_B = 6, CELDA_H = 3;

const int OBJETIVO = 2048;

const int DIM_DEF = 4, DIM_MAX = 12;
typedef int tArrayTablero[DIM_MAX][DIM_MAX];

typedef struct {
	tArrayTablero matriz;
	int dim;
} tTablero;

typedef struct {
	tTablero tablero;
	int puntos;
	int puntTotal;
	int objetivo;
} tJuego;

typedef enum { Arriba, Abajo, Derecha, Izquierda, Salir, Nada } tAccion;

// Estructura usada para poder emplear una unica funcion para desplazar hacia cualquier lugar
typedef struct {
	int fila;
	int columna;
} tVectorDesplazamiento;

// Tipos necesarios para implementar la V4
const int MAX_RECORDS = 10;
const string  ARCHIVO_RECORDS = "records.txt";

typedef struct {
	string nombre;
	int puntuacion;
} tRecord;

typedef tRecord tArrayRecords[MAX_RECORDS];

typedef struct {
	tArrayRecords records;
	int cont;
} tListaRecords;


/******************************
*  Funciones V1 Obligatorias  *
******************************/

/*
  * Inicializa el tablero: todas las baldosas libres menos dos que se eligen de manera aleatoria
  * Baldosas libres -> valor 1 / Baldosas elegidas aleatoriamente -> 2(95%) o 4(5%) (no pueden ser ambas 4)
  * @param tablero a inicializar
*/
void nuevaPartida(tJuego & juego);

/*
  * Cambia el color de la pantalla usando la biblioteca Windows.h
  * @param numero que identifica el color a pintar
*/
void colorFondo(int color);

/*
  * Devuelve la potencia de 2 que da como resultado num
  * @param num del que calcular la potencia de 2
  * @return resultado
*/
int log2(int num);

/*
  * Muestra el tablero, los puntos de la ultima jugada y la puntuacion acumulada
  * @param datos del juego actual
*/
void visualiza(const tJuego & juego);

/*
  * Pide un archivo y trata de cargar un tablero y la puntuacion de dicho archivo
  * Si no se puede cargar inicializa el tablero y pone los puntos a 0
  * @param datos de juego (tablero, puntos, ...)
*/
void carga(tJuego & juego);

/***********************
*  Funciones V1 Extra  *
***********************/

/*
  * Genera un aleatorio entre 0 y max-1
  * @param numero de valores que se pueden generar empezando en 0
  * @return aleatorio de entre los max valores posibles
*/
int aleatorio(int max);

/*
  * Genera una ficha "aleatoria" (2 o 4) para la inicializacion del tablero
  * Tiene un 95% de ser 2
  * @return 2 o 4
*/
int fichaAleatoria();

/*
  * Muestra un borde cualquiera (superior, intermedio o inferior) del tablero dependiendo de los char que le mandemos
  * @param1 dimension del tablero
  * @param2 char inicial del borde
  * @param3 char de separacion de columnas
  * @param4 char de fin de borde
*/
void mostrarBorde(int dim, char izq, char centro, char der);

/*
  * Muestra el contenido de una fila del tablero
  * @param1 tablero y dimension del mismo
  * @param2 fila que estamos mostrando
*/
void mostrarFila(const tTablero & tablero, int fila);

/*
  * Muestra las filas intermedias del tablero y las fichas que hay en el
  * @param tablero que contiene las fichas
*/
void mostrarFilasIntermedias(const tTablero & tablero);

/*
  * Muestra un mensaje de error si el nombre de archivo es invalido
*/
void errorExtensionToString();

/*
  * Comprueba si el nombre de archivo es valido
  * @param nombre a comprobar
  * @return [true -> nombre valido / false -> cualquier otro caso]
*/
bool validarNombre(string file);

/*
  * Pide al usuario un nombre de fichero y comprueba su validez
  * @return nombre de fichero
*/
string pedirFichero();

/*
  * Pregunta al usuario si desea realizar la carga del tablero
  * @return [true -> SI (cargar archivo) / false -> NO (nueva partida)]
*/
bool iniciarCarga();


/******************************
*  Funciones V2 Obligatorias  *
******************************/

/*
  * Lee que tecla se esta pulsando y devuelve el codigo de accion que corresponda
  * No puede devolver NADA, solo lee teclas especiales
  * @return accion elegida por el usuario [esc -> SALIR / flechas -> Direccion elegida]
*/
tAccion leeAccion();

/*
  * Desplaza las fichas del tablero en al direccion que indique accion
  * @param1 tablero que contiene las fichas
  * @param2 direccion en la que mover las fichas
*/
void inclinaTablero(tJuego & juego, tAccion accion);

/***********************
*  Funciones V2 Extra  *
***********************/

/*
  * Desplaza y combina las fichas del tablero hacia cualquier direccion actualizando la puntuacion cuando corresponda
  * @param1 datos de juego actuaññes
  * @param2 vector que indica el desplazamiento que vamos a realizar
  * @param3 vector que usamos para inicializar las variables fila y columna
*/
void desplazaYCombina(tJuego & juego, tVectorDesplazamiento desplazamiento, tVectorDesplazamiento inicio);


/******************************
*  Funciones V3 Obligatorias  *
******************************/

/*
  * Dado un tablero comprueba que el usuario no haya ganado
  * @param1 tablero a comprobar
  * @param2 objetivo del juego
*/
bool tableroMeta(const tTablero & tablero, int meta);

/*
  * Comprueba si quedan baldosas libres
  * @param datos de tablero actuales
  * @return [true -> esta lleno / false -> queda espacio]
*/
bool tableroLleno(const tTablero & tablero);

/*
  * Combina las fichas del tablero tras realizar el movimiento indicado por accion y devuelve los puntos conseguidos
  * @param1 datos de juego
  * @param2 direccion en la que se tratan de combinar las fichas
*/
//void combinaFichas(tJuego & juego, tAccion accion);

/*
  * Crea en una posicion aleatoria (vacia) una nueva ficha
  * @param tablero en el que generar la ficha y dimensiones del mismo
*/
void nuevaFicha(tTablero & tablero);

/***********************
*  Funciones V3 Extra  *
***********************/

/*
  * En el caso de que el usuario presione ESC le pregunta si desea salir
  * @return [true -> desea salir / false -> no desea salir]
*/
bool comprobarSalir();

/*
  * Espera hasta que el usuario pulsa intro
*/
void pausa();

/*
  * Muestra un mensaje cuando el usuario decide salir
*/
void abandonoToString();

/*
  * Muestra un mensaje cuando el usuario gana
*/
void victoriaToString();

/*
  * Muestra un mensaje cuando el usuario pierde
*/
void derrotaToString();

/*
  * Recorre el tablero comprobando si existe algun posible movimiento
  * @param tablero a comprobar
  * @return [true -> aun hay movimientos posibles en el tablero / false -> caso contrario]
*/
bool movimientosPosibles(const tTablero & tablero);

/*
  * Busca combinaciones de fichas en el sentido que indique recorrido
  * @param1 datos de juego
  * @param2 vector de recorrido que indica el sentido de busqueda
  * @param3 vector que nos indica donde iniciamos el recorrido del array
*/
//void combina(tJuego & juego, tVectorDesplazamiento recorrido, tVectorDesplazamiento inicio);


/******************************
*  Funciones V4 Obligatorias  *
******************************/

/*
  * Añade la puntuacion del usuario a la lista de records actuales
  * Solo se guardan 10 puntuaciones en caso de ser mayor que alguna de las guardadas se descartara la menor
  * @param puntuacion conseguida
*/
void nuevoRecord(int puntos);

/*
  * Muestra el contenido del archivo en el que se almacenan los records
*/
void muestraRecords();

/*
  * Pide un nombre de archivo para almacenar la partida actual
  * @param datos de la partida a almacenar
*/
void guarda(const tJuego & juego);

/***********************
*  Funciones V4 Extra  *
***********************/

/*
  * Carga de archivo las mejores puntuaciones
  * @param contenedor para los records que cargamos del archivo
*/
void cargaPuntuaciones(tListaRecords & listaRecords);

/*
  * Se solicita un nombre de usuario para almacenar su puntuacion
  * @return nombre de usuario introducido
*/
string solicitaUsuario();

/*
  * Muestra un los valores de un record
  * @param1 datos del record a mostrar
  * @param2 posicion del record
*/
void mostrarRecord(const tRecord & record, int num);

/*
  * Busca la posicion en la que debe ir el nuevo record
  * @param1 records guardados
  * @param2 record a buscar
  * @return [-1 -> no se debe insertar / [0 - 9] -> posicion que debe ocupar el record]
*/
int buscarPosicion(const tListaRecords & listaRecords, const tRecord & record);

/*
  * Inserta el nuevo record en pos de arrayRecords
  * @param1 records actuales
  * @param2 nuevo record
  * @param3 lugar del nuevo record en los records guardados
*/
void insertaRecord(tListaRecords & listaRecords, const tRecord & record, int pos);

/*
  * Pregunta al usuario si desea guardar la partida
  * @return [true -> se guarda la partida en curso / false -> caso contrario]
*/
bool guardarPartida();

/*
  * Guarda los records una vez actualizados en el archivo
  * @param records a guardar
*/
void guardaRecords(const tListaRecords & listaRecords);

/*
  * Se encarga de informar a l usuario del resultado al finalizar la partida
  * @param1 estado final del juego
  * @param2 [true -> ha ganado / false -> no ha ganado]
  * @param3 [true -> ha perdido / false -> no ha perdido]
*/
void informarUsuario(const tJuego & juego, bool meta, bool derrota);


int main() {
	srand(time(NULL));
	tJuego juego;
	juego.puntos = 0;
	tAccion accion;

	bool meta = false, derrota = false, salir = false;;

	if (iniciarCarga()) carga(juego);
	else  nuevaPartida(juego);

	while (!salir && !meta && !derrota){
		visualiza(juego); // Mostramos el tablero
		accion = leeAccion();
		if (accion == Salir) {
			if (comprobarSalir()) salir = true;
			else accion = Nada;
		}
		if (!salir && accion != Nada) {
			inclinaTablero(juego, accion); // Realizamos el movimiento
			//combinaFichas(juego, accion); // Combinamos las fichas
			visualiza(juego); // Mostramos el tablero

			meta = tableroMeta(juego.tablero, juego.objetivo); // Comprobamos si el usuario ha ganado
			derrota = tableroLleno(juego.tablero); // Comprobamos si ha perdido
		}
		
	}

	informarUsuario(juego, meta, derrota);

	return 0;
}

/******************************
*  Funciones V1 Obligatorias  *
******************************/

void nuevaPartida(tJuego & juego) {
	juego.tablero.dim = DIM_DEF;
	juego.puntTotal = 0;
	juego.objetivo = OBJETIVO;
	// Inicializamos todo el tablero vacio
	for (int f = 0; f < DIM_DEF; f++) {
		for (int c = 0; c < DIM_DEF; c++) {
			juego.tablero.matriz[f][c] = 1;
		}
	}
	// Elegimos dos baldosas aleatoriamente y colocamos una ficha en ellas
	int f = aleatorio(DIM_DEF), c = aleatorio(DIM_DEF);

	juego.tablero.matriz[f][c] = fichaAleatoria();
	nuevaFicha(juego.tablero);
	
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

int log2(int num) {
	int res = 0;
	int aux = num;

	while (aux / 2 > 0) {
		res++;
		aux = aux / 2;
	}

	return res;
}

void visualiza(const tJuego & juego) {
	system("CLS");
	// Mostramos las puntuaciones parcial y total
	cout << setw(6) << juego.puntos << setw(12) << "Puntos: " << juego.puntTotal << endl;
	// Mostramos la primera fila
	mostrarBorde(juego.tablero.dim, char(218), char(194), char(191));
	//Mostamos las filas intermedias y las fichas
	mostrarFilasIntermedias(juego.tablero);
	// Mostramos la ultima fila
	mostrarBorde(juego.tablero.dim, char(192), char(193), char(217));
	cout << "Usa las teclas de flecha (ESC para salir)...";
}

void carga(tJuego & juego) {
	string file = pedirFichero();
	ifstream fIn;

	fIn.open(file.c_str());

	if (!fIn.is_open()) {
		juego.puntos = 0;
		nuevaPartida(juego);
	}
	else {
		int dim;
		fIn >> dim;

		if (dim > DIM_MAX) {
			// No se puede cargar
			nuevaPartida(juego);
		}
		else {
			juego.tablero.dim = dim;
			for (int f = 0; f < juego.tablero.dim; f++) {
				for (int c = 0; c < juego.tablero.dim; c++) {
					fIn >> juego.tablero.matriz[f][c];
				}
			}
			fIn >> juego.puntTotal >> juego.objetivo;
			juego.puntos = 0;
		}
	}
	fIn.close();
}

/***********************
*  Funciones V1 Extra  *
***********************/

int aleatorio(int max) {
	return rand() % max;
}

int fichaAleatoria() {
	int ficha;

	if (aleatorio(101) <= 95) ficha = 2;
	else ficha = 4;

	return ficha;
}

void mostrarBorde(int dim, char izq, char centro, char der) {
	cout << izq;
	for (int j = 0; j < dim - 1; j++) {
		for (int i = 0; i < 6; i++) {
			cout << char(196);
		}
		cout << centro;
	}
	for (int i = 0; i < 6; i++) {
		cout << char(196);
	}
	cout << der << endl;
}

void mostrarFila(const tTablero & tablero, int fila) {
	for (int i = 0; i < CELDA_H; i++) { // Bucle que dibuja las DIM - 1 columnas CELDA_H veces
		for (int c = 0; c < tablero.dim; c++) { // Bucle para dibujar DIM - 1 columnas
			colorFondo(0); // Reseteamos el color entre columnas para que la linea de separacion tenga fondo negro
			cout << char(179);
			colorFondo(log2(tablero.matriz[fila][c]));
			cout << setw(CELDA_B);
			if (i == CELDA_H / 2 && tablero.matriz[fila][c] != 1) cout << tablero.matriz[fila][c];
			else cout << " ";
		}
		colorFondo(0); // Asi reseteamos el coloreado de fondo en caso de que la ultima posicion de la comlumna estuviera coloreada
		cout << char(179) << endl;
	}
}

void mostrarFilasIntermedias(const tTablero & tablero) {
	for (int f = 0; f < tablero.dim - 1; f++) { // Bucle que dibuja todas las filas menos la ultima
		mostrarFila(tablero, f);
		mostrarBorde(tablero.dim, char(195), char(197), char(180));
	}
	mostrarFila(tablero, tablero.dim - 1);
}

void errorExtensionToString() {
	cout << "Error: la extension del archivo ha de ser .txt" << endl;
}

bool validarNombre(string file) {
	bool ok = true;

	if (file.length() >= 4) {
		string aux;
		for (int i = 4; i > 0; i--) {
			aux += file[file.length() - i];
		}
		if (aux != ".txt") {
			ok = false;
			errorExtensionToString();
		}
	}
	else ok = false;

	return ok;
}

string pedirFichero() {
	string file;

	do {
		cout << "Nombre de archivo: ";
		cin >> file; cin.sync();  cin.clear();
	} while (!validarNombre(file));

	return file;
}

bool iniciarCarga() {
	char letra;

	do {
		cin.sync(); cin.clear();
		cout << "Quieres cargar una partida [S/N]? ";
		cin >> letra;
		letra = toupper(letra);
	} while (letra != 'S' && letra != 'N');

	return (letra == 'S');
}

/******************************
*  Funciones V2 Obligatorias  *
******************************/

tAccion leeAccion() {
	tAccion accion = Nada;
	int dir;

	while (accion == Nada) { // Tenemos que devolver alguna accion asi que esperamos hasta obtenerla
		cin.sync();
		dir = _getch(); // dir: tipo int
		if (dir == 0xe0) {
			dir = _getch();
			// Una vez comprobado que es una tecla especial comprobamos de cual se trata
			if (dir == 72) accion = Arriba;
			else if (dir == 80) accion = Abajo;
			else if (dir == 77) accion = Derecha;
			else if (dir == 75) accion = Izquierda;
		}
		// Si no, si dir es 27, es la tecla Esc
		else if (dir == 27) accion = Salir;
	}

	return accion;
}

/*void inclinaTablero(tTablero & tablero, tAccion accion) {
	// Colocamos el vector de desplazamiento a 0 (no desplaza por defecto)
	tVectorDesplazamiento desplazamiento;
	desplazamiento.fila = 0;
	desplazamiento.columna = 0;
	// Generamos las posiciones inicialies para la filas y columna
	tVectorDesplazamiento inicio;
	inicio.fila = 0;
	inicio.columna = 0;
	// Cambiamos el valor del vector hacia el sentido en que tenga que moverse
	if (accion == Derecha) {
		desplazamiento.columna = 1;
		inicio.columna = tablero.dim - 2;
	}
	else if (accion == Izquierda) {
		desplazamiento.columna = -1;
		inicio.columna = 1;
	}
	else if (accion == Arriba) {
		desplazamiento.fila = -1;
		inicio.fila = 1;
	}
	else if (accion == Abajo) {
		desplazamiento.fila = 1;
		inicio.fila = tablero.dim - 2;
	}

	desplaza(tablero, desplazamiento, inicio);
}*/

void inclinaTablero(tJuego & juego, tAccion accion) {
	// Colocamos el vector de desplazamiento a 0 (no desplaza por defecto)
	tVectorDesplazamiento desplazamiento;
	desplazamiento.fila = 0;
	desplazamiento.columna = 0;
	// Generamos las posiciones inicialies para la filas y columna
	tVectorDesplazamiento inicio;
	// Cambiamos el valor del vector hacia el sentido en que tenga que moverse
	if (accion == Derecha) {
		desplazamiento.columna = -1;
		inicio.fila = juego.tablero.dim - 1;
		inicio.columna = juego.tablero.dim - 1;
	}
	else if (accion == Izquierda)  {
		desplazamiento.columna = 1;
		inicio.fila = 0;
		inicio.columna = 0;
	}
	else if (accion == Arriba) {
		desplazamiento.fila = 1;
		inicio.fila = 0;
		inicio.columna = 0;
	}
	else if (accion == Abajo) {
		desplazamiento.fila = -1;
		inicio.fila = juego.tablero.dim - 1;
		inicio.columna = juego.tablero.dim - 1;
	}

	juego.puntos = 0;
	desplazaYCombina(juego, desplazamiento, inicio);
	juego.puntTotal += juego.puntos;
	nuevaFicha(juego.tablero);
}

/***********************
*  Funciones V2 Extra  *
***********************/

/*
void desplazaDerecha(tJuego & juego) {
	for (int f = 0; f < juego.dim; f++) { // Recorre las filas
		for (int i = 0; i < juego.dim; i++) {
			for (int c = juego.dim - 2; c >= 0; c--) { // Recorre las columnas
				// Comprobamos que la casilla de destino este vacia y que la casilla origen sea una ficha
				if (juego.tablero[f][c + 1] == 1 && juego.tablero [f][c] > 1)
				swap(juego.tablero[f][c + 1], juego.tablero[f][c]);
			}
		}
	}
}


void desplazaIzquierda(tJuego & juego) {
	for (int f = 0; f < juego.dim; f++) { // Recorre las filas
		for (int i = 0; i < juego.dim; i++) {
			for (int c = 1; c < juego.dim; c++) { // Recorre las columnas
				// Comprobamos que la casilla de destino este vacia y que la casilla origen sea una ficha
				if (juego.tablero[f][c - 1] == 1 && juego.tablero[f][c] > 1)
				swap(juego.tablero[f][c - 1], juego.tablero[f][c]);
			}
		}
	}
}

void desplazaArriba(tJuego & juego) {
	for (int c = 0; c < juego.dim; c++) { // Recorre las columnas
		for (int i = 0; i < juego.dim; i++) {
			for (int f = 1; f < juego.dim; f++) { // Recorre las filas
				// Comprobamos que la casilla de destino este vacia y que la casilla origen sea una ficha
				if (juego.tablero[f - 1][c] == 1 && juego.tablero[f][c] > 1)
				swap(juego.tablero[f - 1][c], juego.tablero[f][c]);
			}
		}
	}
}

void desplazaAbajo(tJuego & juego) {
	for (int c = 0; c < juego.dim; c++) { // Recorre las columnas
		for (int i = 0; i < juego.dim; i++) {
			for (int f = juego.dim - 2; f >= 0; f--) { // Recorre las filas
				// Comprobamos que la casilla de destino este vacia y que la casilla origen sea una ficha
				if (juego.tablero[f + 1][c] == 1 && juego.tablero[f][c] > 1)
				swap(juego.tablero[f + 1][c], juego.tablero[f][c]);
			}
		}
	}
}
*/

/*void desplaza(tTablero & tablero, tVectorDesplazamiento desplazamiento, tVectorDesplazamiento inicio)  {
	// Inicializamos las variables auxiliares que usaremos para recorrer el array
	int f, c;
	f = inicio.fila;
	c = inicio.columna;
	// Recorremos el array y desplazamos
	for (int i = 0; i < tablero.dim; i++) {
		while (f < tablero.dim && f >= 0) {
			while (c < tablero.dim && c >= 0) {
				if (tablero.matriz[f + desplazamiento.fila][c + desplazamiento.columna] == 1 && tablero.matriz[f][c] > 1)
					swap(tablero.matriz[f + desplazamiento.fila][c + desplazamiento.columna], tablero.matriz[f][c]);

				if (inicio.columna == 0 || inicio.columna == 1) c++;
				else c--;
			}
			c = inicio.columna;
			if (inicio.fila == 0 || inicio.fila == 1) f++;
			else f--;
		}
		f = inicio.fila;
	}
}*/

/*void desplazaYCombina(tJuego & juego, tVectorDesplazamiento desplazamiento, tVectorDesplazamiento inicio)  {
	// Inicializamos las variables auxiliares que usaremos para recorrer el array
	int f, c;
	f = inicio.fila;
	c = inicio.columna;
	// Recorremos el array y desplazamos
	int huecos;
	if (desplazamiento.fila == 0) {
		while (f < juego.tablero.dim && f >= 0) {
			huecos = 0;
			while (c < juego.tablero.dim && c >= 0) {
				if (juego.tablero.matriz[f][c] == 1)
					huecos++;
				else if (huecos > 0) {
					if (juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] == juego.tablero.matriz[f][c]) {
						// Combinamos las fichas
						juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] *= 2;
						// Borramos la ficha combinada
						juego.tablero.matriz[f][c] = 1;
						// Actualizamos los puntos
						juego.puntos += juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)];
					}
					else swap(juego.tablero.matriz[f - desplazamiento.fila*huecos][c - desplazamiento.columna*huecos], juego.tablero.matriz[f][c]);

					c = c - desplazamiento.columna*huecos;
					huecos = 0;
				}
				c = c + desplazamiento.columna;
			}
			c = inicio.columna;
			f = f + desplazamiento.columna;
		}
	}
	else {
		while (c < juego.tablero.dim && c >= 0) {
			huecos = 0;
			while (f < juego.tablero.dim && f >= 0) {
				if (juego.tablero.matriz[f][c] == 1)
					huecos++;	
				else if (huecos > 0) {
					if (juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] == juego.tablero.matriz[f][c]) {
						// Combinamos las fichas
						juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] *= 2;
						// Borramos la ficha combinada
						juego.tablero.matriz[f][c] = 1;
						// Actualizamos los puntos
						juego.puntos += juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)];
					}
					else swap(juego.tablero.matriz[f - desplazamiento.fila*huecos][c - desplazamiento.columna*huecos], juego.tablero.matriz[f][c]);

					f = f - desplazamiento.fila*huecos;
					huecos = 0;
				}
				f = f + desplazamiento.fila;
			}
			f = inicio.fila;
			c = c + desplazamiento.fila;
		}
	}
}*/

void desplazaYCombina(tJuego & juego, tVectorDesplazamiento desplazamiento, tVectorDesplazamiento inicio)  {
	// Inicializamos las variables auxiliares que usaremos para recorrer el array
	int f, c;
	f = inicio.fila;
	c = inicio.columna;
	// Recorremos el array y desplazamos
	int huecos;
	while ((f < juego.tablero.dim && f >= 0) && (c < juego.tablero.dim && c >= 0)) {
		huecos = 0;
		while ((f < juego.tablero.dim && f >= 0) && (c < juego.tablero.dim && c >= 0)) {
			if (juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] == juego.tablero.matriz[f][c]) {
				// Combinamos las fichas
				juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)] *= 2;
				// Borramos la ficha combinada
				juego.tablero.matriz[f][c] = 1;
				// Actualizamos los puntos
				juego.puntos += juego.tablero.matriz[f - desplazamiento.fila*(huecos + 1)][c - desplazamiento.columna*(huecos + 1)];
			}
			else{
				if (juego.tablero.matriz[f][c] == 1)
					huecos++;
				else if (huecos > 0) {
					swap(juego.tablero.matriz[f - desplazamiento.fila*huecos][c - desplazamiento.columna*huecos], juego.tablero.matriz[f][c]);

					f = f - desplazamiento.fila*huecos;
					c = c - desplazamiento.columna*huecos;
					huecos = 0;
				}
				f = f + desplazamiento.fila;
				c = c + desplazamiento.columna;
			}
		}
		if (desplazamiento.fila == 0) c = inicio.columna;
		else f =  inicio.fila;

		f = f + desplazamiento.columna;
		c = c + desplazamiento.fila;
	}
}


/******************************
*  Funciones V3 Obligatorias  *
******************************/

bool tableroMeta(const tTablero & tablero, int meta) {
	int f = 0, c;
	bool encontrado = false;
	while (f < tablero.dim && !encontrado) {
		c = 0;
		while (c < tablero.dim && !encontrado) {
			encontrado = encontrado || (tablero.matriz[f][c] >= meta);
			c++;
		}
		f++;
	}

	return encontrado;
}

bool tableroLleno(const tTablero & tablero) {
	bool lleno = true;
	int f = 0, c;

	while ((f < tablero.dim) && lleno) {
		c = 0;
		while ((c < tablero.dim) && lleno) {
			lleno = lleno && (tablero.matriz[f][c] != 1);
			c++;
		}
		f++;
	}

	return lleno;
}

/*void combinaFichas(tJuego & juego, tAccion accion) {
	// Colocamos el vector de recorrido a 0
	tVectorDesplazamiento recorrido;
	recorrido.fila = 0;
	recorrido.columna = 0;
	// Generamos las posiciones inicialies para la filas y columna
	tVectorDesplazamiento inicio;
	inicio.fila = 0;
	inicio.columna = 0;
	// Cambiamos el valor del recorrido hacia el sentido en que tenga que moverse y el inicio
	if (accion == Derecha){
		inicio.columna = juego.tablero.dim - 1;
		recorrido.columna = -1;
	}
	else if (accion == Izquierda) {
		recorrido.columna = 1;
	}
	else if (accion == Arriba) {
		recorrido.fila = 1;
	}
	else if (accion == Abajo) {
		inicio.fila = juego.tablero.dim - 1;
		recorrido.fila = -1;
	}
	juego.puntos = 0; // Reseteamos la puntucion de la jugada anterior
	combina(juego, recorrido, inicio);

	juego.puntTotal += juego.puntos;
	inclinaTablero(juego.tablero, accion); // Volvemos a mover para llenar los huecos de las fichas combinadas
	nuevaFicha(juego.tablero);
}*/

void nuevaFicha(tTablero & tablero) {
	int f, c;
	// Generamos posiciones aleatorias hasta que una de las generadas este vacia
	do {
		f = aleatorio(tablero.dim);
		c = aleatorio(tablero.dim);
	} while (tablero.matriz[f][c] != 1);
	// Ponemos en la posicion vacia una ficha aleatoria
	tablero.matriz[f][c] = fichaAleatoria();
}

/***********************
*  Funciones V3 Extra  *
***********************/

bool comprobarSalir() {
	char aux;

	do {
		cin.sync(); cin.clear();
		cout << endl << "Seguro que quieres salir [S/N]? ";
		cin >> aux;
		aux = toupper(aux);
	} while (aux != 'S' && aux != 'N');

	return (aux == 'S');
}

void pausa() {
	cin.clear(); cin.sync();
	cout << "Pulsa Intro para salir...";
	while (cin.get() != '\n');
}

void abandonoToString() {
	cout << "Has abandonado la partida... Hasta otra!" << endl;
	pausa();
}

void victoriaToString() {
	cout << endl << "Enhorabuena, has ganado! Hasta otra!" << endl;
	pausa();
}

void derrotaToString() {
	cout << endl << "Lo siento! El tablero esta lleno..." << endl;
	pausa();
}

bool movimientosPosibles(const tTablero & tablero) {
	bool movimiento = false;

	for (int f = 0; f < tablero.dim; f++) {
		for (int c = 0; c < tablero.dim; c++) {
			//movimiento = movimiento && (tablero[f][c] == (tablero[f+1][c]))
			if (f == tablero.dim - 1) { // Si estamos en la ultima fila no podemos comprobar con la fila de abajo
				if (c != tablero.dim - 1) // En la ultima columna de la ultima fila no comprobamos nada
					movimiento = (movimiento || (tablero.matriz[f][c] == tablero.matriz[f][c + 1]));
			}
			else if (c == tablero.dim - 1) { // Si estamos en la ultima columna no podemos comprobar mas a la derecha
				movimiento = (movimiento || (tablero.matriz[f][c] == tablero.matriz[f + 1][c]));
			}
			else
				movimiento = (movimiento || (tablero.matriz[f][c] == tablero.matriz[f + 1][c])
				|| (tablero.matriz[f][c] == tablero.matriz[f][c + 1]));
		}
	}

	return movimiento;
}

/*void combina(tJuego & juego, tVectorDesplazamiento recorrido, tVectorDesplazamiento inicio) {
	// Inicializamos las variables auxiliares que usaremos para recorrer el array
	int f, c;
	f = inicio.fila;
	c = inicio.columna;
	// Combinamos las fichas
	while (f < juego.tablero.dim && f >= 0) {
		while (c < juego.tablero.dim && c >= 0) {
			if ((juego.tablero.matriz[f][c] > 1) && (juego.tablero.matriz[f][c] == juego.tablero.matriz[f + recorrido.fila][c + recorrido.columna])) {
				juego.tablero.matriz[f][c] *= 2; // Duplicamos el valor, como las fichas a sumar son las mismas es el mismo resultado
				juego.tablero.matriz[f + recorrido.fila][c + recorrido.columna] = 1; // Quitamos la ficha sumada de su anterior posicion
				juego.puntos += juego.tablero.matriz[f][c]; // Sumamos la puntuacion de esa combinacion
			}
			if (inicio.columna == 0) c++;
			else c--;
		}
		c = inicio.columna;
		if (inicio.fila == 0) f++;
		else f--;
	}
}*/

/*
void combinaDerecha(tJuego & juego) {
	for (int f = 0; f < juego.dim; f++) {
		for (int c = juego.dim - 1; c >= 0; c--) {
			if ((juego.tablero[f][c] > 1) && (juego.tablero[f][c] == juego.tablero[f][c - 1])){ // Al ser iguales con comprobar que 1 es mayor los dos lo seran
			juego.tablero[f][c] *= 2; // Duplicamos el valor, como las fichas a sumar son las mismas es el mismo resultado
			juego.tablero[f][c - 1] = 1; // Quitamos la ficha sumada de su anterior posicion
			juego.puntos += juego.tablero[f][c]; // Sumamos la puntuacion de esa combinacion
			}
		}
	}
}

void combinaIzquierda(tJuego & juego) {
	for (int f = 0; f < juego.dim; f++) {
		for (int c = 0; c < juego.dim; c++) {
			if ((juego.tablero[f][c] > 1) && (juego.tablero[f][c] == juego.tablero[f][c + 1])){ // Al ser iguales con comprobar que 1 es mayor los dos lo seran
			juego.tablero[f][c] *= 2; // Duplicamos el valor, como las fichas a sumar son las mismas es el mismo resultado
			juego.tablero[f][c + 1] = 1; // Quitamos la ficha sumada de su anterior posicion
			juego.puntos += juego.tablero[f][c]; // Sumamos la puntuacion de esa combinacion
			}
		}
	}
}

void combinaArriba(tJuego & juego) {
	for (int c = 0; c < juego.dim; c++) {
		for (int f = 0; f < juego.dim; f++) {
			if ((juego.tablero[f][c] > 1) && (juego.tablero[f][c] == juego.tablero[f + 1][c])){ // Al ser iguales con comprobar que 1 es mayor los dos lo seran
			juego.tablero[f][c] *= 2; // Duplicamos el valor, como las fichas a sumar son las mismas es el mismo resultado
			juego.tablero[f + 1][c] = 1; // Quitamos la ficha sumada de su anterior posicion
			juego.puntos += juego.tablero[f][c]; // Sumamos la puntuacion de esa combinacion
			}
		}
	}
}

void combinaAbajo(tJuego & juego) {
	for (int c = 0; c < juego.dim; c++) {
		for (int f = juego.dim - 1; f >= 0; f--) {
			if ((juego.tablero[f][c] > 1) && (juego.tablero[f][c] == juego.tablero[f - 1][c])){ // Al ser iguales con comprobar que 1 es mayor los dos lo seran
				juego.tablero[f][c] *= 2; // Duplicamos el valor, como las fichas a sumar son las mismas es el mismo resultado
				juego.tablero[f - 1][c] = 1; // Quitamos la ficha sumada de su anterior posicion
				juego.puntos += juego.tablero[f][c]; // Sumamos la puntuacion de esa combinacion
			}
		}
	}
}
*/

/******************************
*  Funciones V4 Obligatorias  *
******************************/

void nuevoRecord(int puntos) {
	tRecord record;
	tListaRecords listaRecords;
	record.puntuacion = puntos;
	// Cargamos los records existentes
	cargaPuntuaciones(listaRecords);
	
	// Buscamos el lugar para la insercion
	int pos = buscarPosicion(listaRecords, record);
	if (pos != -1) {
		record.nombre = solicitaUsuario();
		insertaRecord(listaRecords, record, pos);
		guardaRecords(listaRecords);
	}
}

void muestraRecords() {
	ifstream fIn;
	tRecord aux;
	int i = 1;
	fIn.open(ARCHIVO_RECORDS.c_str());
	if (fIn.is_open()) {
		cout << endl << "MEJORES PUNTUACIONES" << endl;
		cout << "---------------------" << endl;
		while (!fIn.eof() && i <= MAX_RECORDS) {
			fIn >> aux.nombre >> aux.puntuacion;
			mostrarRecord(aux, i);
			i++;
		}
	}
	fIn.close();
}

void guarda(const tJuego & juego) {
	string archivo;
	archivo = pedirFichero();

	ofstream fOut;
	fOut.open(archivo.c_str());
	
	fOut << juego.tablero.dim << endl;
	for (int f = 0; f < juego.tablero.dim; f++) {
		for (int c = 0; c < juego.tablero.dim; c++) {
			fOut << juego.tablero.matriz[f][c] << endl;
		}
	}
	fOut << juego.puntTotal << " " << juego.objetivo;

	fOut.close();
}

/***********************
*  Funciones V4 Extra  *
***********************/

void cargaPuntuaciones(tListaRecords & listaRecords) {
	ifstream fIn;
	tRecord aux;
	listaRecords.cont = 0;
	int i = 0;

	fIn.open(ARCHIVO_RECORDS.c_str());
	if (fIn.is_open()) {
		while (!fIn.eof() && i < MAX_RECORDS) {
			fIn >> aux.nombre >> aux.puntuacion;
			listaRecords.records[i] = aux;
			listaRecords.cont++;
			i++;
		}
	}
	fIn.close();
}

string solicitaUsuario() {
	string nombre;

	do {
		cin.sync(); cin.clear();
		cout << endl << "Introduzca un nombre de usuario: ";
		cin >> nombre;
	} while (cin.fail());

	return nombre;
}

void mostrarRecord(const tRecord & record, int num) {
	cout << num << " - " << record.nombre << " " << record.puntuacion << endl;
}

int buscarPosicion(const tListaRecords & listaRecords, const tRecord & record) {
	int pos = 0;

	while (listaRecords.records[pos].puntuacion > record.puntuacion) {
		pos++;
	}

	// No se encontraron elementos con puntuaciones menores y la lista esta llena
	if((pos == listaRecords.cont) && (listaRecords.cont >= MAX_RECORDS)) pos = -1;

	return pos;
}

void insertaRecord(tListaRecords & listaRecords, const tRecord & record, int pos) {
	// Abrimos espacio para la insercion
	for (int i = listaRecords.cont - 1; i > pos; i--) {
		listaRecords.records[i] = listaRecords.records[i - 1];
	}
	// Insertamos
	listaRecords.records[pos] = record;
	if (listaRecords.cont < MAX_RECORDS) listaRecords.cont++;
}

bool guardarPartida() {
	char aux;

	do {
		cin.sync(); cin.clear();
		cout << endl << "Quieres guardar la partida [S/N]? ";
		cin >> aux;
		aux = toupper(aux);
	} while (aux != 'S' && aux != 'N');

	return (aux == 'S');
}

void guardaRecords(const tListaRecords & listaRecords) {
	ofstream fOut;
	fOut.open(ARCHIVO_RECORDS.c_str());

	for (int i = 0; i < listaRecords.cont; i++) {
		fOut << listaRecords.records[i].nombre << " " << listaRecords.records[i].puntuacion << endl;
	}

	fOut.close();
}

void informarUsuario(const tJuego & juego, bool meta, bool derrota) {
	if (meta) {
		nuevoRecord(juego.puntTotal);
		muestraRecords();
		victoriaToString();
	}
	else if (derrota){
		derrotaToString();
	}
	else {
		if (guardarPartida()) guarda(juego);
		abandonoToString();
	}
}