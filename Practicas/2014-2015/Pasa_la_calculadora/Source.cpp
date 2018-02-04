/** REALIZADO POR DAVID ANTUÑA Y RAFAEL GARCES **/

/* BIBLIOTECAS */
#include <iostream>
#include <string>
using namespace std;
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <Windows.h>

/* CONSTANTES */
const int MAX_PUNTUACION = 31, MAX_NUM = 9, PERSONA = 2, MAQUINA = 1, SALIR = 0, MAX_OPCIONES = 3;
const int IA_DEFECTO = 1, IA_MEDIA = 2, IA_DIFICIL = 3, MAX_COLOR = 15, LONG_CALC = 3;
const string ARCHIVO_INFO = "versionPC.txt", INFORME = "informePC.txt", CENTINELA = "XXX";

/* PROTOTIPOS DE LAS FUNCIONES */

/*
  * Se encarga del desarrollo del juego
  * Devuelve el ganador (0 - N/A // 1 - Autómata // 2 - Jugador)
*/
int pasaCalculadora(int dificultad);

/*
  * Decide aleatoriamente quien empieza
  * Devuelve un entero (1 - Autómata // 2 - Jugador)
*/
int quienEmpieza();

/*
  * Comprueba si el numero introducido se ajusta a los parametros de juego
  * Hara uso de 3 subprogramas: [ mismaFila() ], [ mismaColumna() ], [ rango() ]
  * Recibe 2 enteros como parametros (no se pueden modificar): el ultimo numero valido y el numero a comprobar
  * Devuelve un booleano indicando si el numero es válido
*/
bool digitoValido(int ultimo, int nuevo);

/*
  * Comprueba si el nuevo numero esta en la misma fila que el ultimo numero valido
  * Recibe 2 enteros como parametros (no se pueden modificar): el ultimo numero valido y el numero a comprobar
  * Devuelve un booleano indicando si el numero a comprobar se encuentra en la misma fila
*/
bool mismaFila(int ultimo, int nuevo);

/*
  * Comprueba si el nuevo numero esta en la misma columna que el ultimo numero valido
  * Recibe 2 enteros como parametros (no se pueden modificar): el ultimo numero valido y el numero a comprobar
  * Devuelve un booleano indicando si el numero a comprobar se encuentra en la misma columna
*/
bool mismaColumna(int ultimo, int nuevo);

/*
   * Comprueba que el numero introducido se encuentre entre 0 y 9
   * Recibe el numero introducido
   * Devuelve un booleano indicando si es valido o no
*/
bool rango(int nuevo);

/*
  * Genera un digito aleatorio entre 0 y la constante MAX_NUM
  * No conoce las reglas de juego y por tanto el numero generado no tiene porque ajustarse a ellas seran 
	otros subprogramas los que determinen la validez del mismo
*/
int digitoAleatorio();

/*
  * Hace uso del subprograma [ digitoAleatorio() ]
  * Solicita un numero aleatorio y verifica que se ajuste a las reglas del juego para la IA_FACIl
  * Si el numero es valido lo devuelve si no lo es solicita otro
*/
int digitoAutomata(int ultimo);

/*
  * Solicita al jugador un digito entre 0 y MAX_NUM
  * Hace uso de otros subprogramas para verificar la validez del numero introducido si no es valido solicita otro
  * Devuelve el numero elegido por el usuario
  * Este subprograma no tiene en cuenta el ultimo numero valido por lo que solo lo empleamos si el usuario empieza
	la partida
*/
int digitoUsuario();

/*
  * Solicita al jugador un digito entre 0 y MAX_NUM
  * Hace uso de otros subprogramas para verificar la validez del numero introducido si no es valido solicita otro
  * Devuelve el numero elegido por el usuario
*/
int digitoPersona(int ultimo);

/*
  * Se encarga de la entrada-salida por pantalla para saludar al jugador
  * Devuelve un string que contenga el nombre del jugador
*/
string saludarJugador();

/*
  * Se encarga de mostrar en pantalla el tablero con las opciones del usuario
  * Solo se la llama si empieza el usuario
*/
void mostrarCalculadoraInicial();

/*
  * Se encarga de mostrar por pantalla el tablero de juego
  * Recibe el ultimo numero valido para mostrarle al usuario en color verde los numeros que puede
	usar y en rojo los que no
*/
void mostrarCalculadora(int ultimo);

/*
  * Muestra al usuario una serie de opciones relacionadas con las funcionalidades del programa
	y le pide que escoga una
  * Devuelve un entero con la opcion escogida
*/
int menu();

/*
  * Mostrara por pantalla el archivo de informacion "versionPC.txt"
  * Devuelve un booleano indicando si el archivo se ha podido abrir en caso contrario muestra un mensaje por pantalla
*/
bool mostrarInformacion();

/*
  * Muestra un rotulo con el nombre del juego
*/
void rotulo();

/*
  * Se encarga de actualizar el informe al final de cada ejecucion completa
  * Recibe el numero de parditas jugadas durante la ejecucion y cuantas de ellas terminaron con abandono y
	en cuantas gano la maquina
  * El subprograma abrira para lectura el archivo cuyo nombre este guardado en la constante [ INFORME ] 
	en caso de que la apertura falle llamara a inicializar informe que pondra todo a 0's para poder actualizar
  * Tras cerrar el archivo para lectura actualizara los datos y abrira el mismo archivo para escritura con lo
	que escribira las variables actualizadas y cerrara el archivo
*/
void actualizarInforme(int jugadas, int ganadas, int abandonosN);

/*
  * Le da al usuario la oportunidad de elegir entre las distintas dificultades de nuestra IA
  * Devuelve un entero que indica el nivel escogido (1 - Defecto // 2 - Normal (MEJORADA) // 3- DIFICIL (MEJORADA2))
*/
int selectorDificultad(int actualD);

/*
  * Se encarga de generar el numero elegido por la maquina para la IA_MEDIA
  * Ahora la maquina trata de escoger un numero que no la haga perder y que deje al usuario lo mas cercano a 31
	posible
  * Comprueba todos los numeros del 1 al 9 y solo para los que sean validos hace su posible suma,
	guarda la mayor suma posible hasta el momento
  * Si detecta que no tiene ningun numero valido que no pase de 31 al sumar decide rendirse poniendo pierdo a true
*/
int digitoAutomataMejorado(int ultimo, int suma, bool &pierdo);

/*
  * Hace que windows muestre por pantalla el color solicitado
*/
void setColor(int color);

/*
  * Genera un numero aleatorio entre 1 y MAX_COLOR(15), no incluimos el 0 porque es black y no se veria
  * Devolveremos el entero generado y le pediremos a windows que muestre las letras del color elegido aleatoriamente
*/
int colorAleatorio();

/*
  * Genera el numero elegido por la IA_DIFICIL
  * Ahora la maquina ademas de sopesar sus opciones sopesa las posibles opciones del usuario y elige el
	digito que lo deje con menos posibilidades de ganar
  * Comprueba los numeros del 1 al 9 validos, de todos ellos descarta los que la hagan pasarse de 31 y de
	los que quedan escoge aquel que deje menos numeros posibles al usuario 
  * Si detecta que no tiene ningun numero valido que no pase de 31 al sumar decide rendirse poniendo pierdo a true
*/
int digitoAutomataMejorado2(int ultimo, int suma, bool &pierdo);

/*
  * Se encarga de realizar la jugada de apertura del juego
  * Devuelve el numero introducido por el jugador o la maquina
  * Ademas modifica la variable ultimaJugada para asi saber quien ha empezado
*/
int jugadaInicial(int &ultimaJugada);

/*
  * Gestiona una jugada por parte de la maquina
  * Devuelve el numero elegido
  * Recibe la dificultad para saber que IA usar al elegir el numero
  * Actualiza el valor de suma
*/
int jugadaMaquina(int dificultad, bool &pierdo, int &suma, int ultimoNum);

/*
  * Gestiona una jugada por parte del usuario
  * Devuelve el numero elegido
  * Actualiza el valor de suma
*/
int jugadaPersona(int &suma, int ultimoNum);

/*
  * Inicializa a 0 todos los elementos del informe si la apertura para leerlo ha fallado
*/
void inicializarInforme(int &usos, int &partidasJug, int &partidasGM, int &abandonos);

/*
  * Recibe la suma actual y el numero valido de la ultima jugada
  * Devuelve la suma de ambos
*/
int actualizaSuma(int suma, int ultimoNum);

/*
  * Se encargan de la salida por pantalla
*/
void rendicionToString();
void victoriaToString(int ganador);
void sumaToString(int suma);
void despedidaToString(string nombre, int ultimoNum);
void errorLecturaToString();
void errorEscrituraToString();


/* Programa principal */
int main() {
	SetConsoleTitle("Pasa La Calculadora V4"); // Cambiamos el nombre mostrado en la consola
	srand(time(NULL)); // establce la semilla para los numeros aleatorios
	rotulo(); // En cada ejecucion se mostrara el rotulo de diferentes colores (son aleatorios)
	int opcion, ganador = -1, dificultad = IA_DEFECTO, jugadas = 0, ganadas = 0, abandonos = 0;
	opcion = menu();
	
	while (opcion != 0){
		switch (opcion)	{
			case 1: {
					jugadas++;
					ganador = pasaCalculadora(dificultad);
			} break;
			case 2: {
					if (!mostrarInformacion()) errorLecturaToString();
			} break;
			case 3: {
					dificultad = selectorDificultad(dificultad);
			} break;
			default: break;
		}
		if (ganador == 0) { abandonos++; }
		if (ganador == MAQUINA) { ganadas++; }
		opcion = menu();
	}

	actualizarInforme(jugadas, ganadas, abandonos);
	
	system("Pause");	
	return 0;
}

int pasaCalculadora(int dificultad) {
	string nombre;
	int ganador, ultimoNum, ultimaJugada, suma = 0;
	bool pierdo = false;

	nombre = saludarJugador();

	ganador = 0;

	ultimoNum = jugadaInicial(ultimaJugada);

	if (ultimoNum != SALIR)	suma = actualizaSuma(suma, ultimoNum); sumaToString(suma);

	while ((ultimoNum != SALIR) && (ganador != PERSONA) && (ganador != MAQUINA) && (!pierdo))  {
		if (ultimaJugada == PERSONA) {
			ultimoNum = jugadaMaquina(dificultad, pierdo, suma, ultimoNum);
			if (suma >= MAX_PUNTUACION) ganador = PERSONA;
			else  ultimaJugada = MAQUINA; 
		}
		else {
			ultimoNum = jugadaPersona(suma, ultimoNum);
			if (suma >= MAX_PUNTUACION) ganador = MAQUINA;
			else ultimaJugada = PERSONA;
		}
		if ((ultimoNum != SALIR) && (!pierdo)) sumaToString(suma);
	}

	if (ultimoNum != SALIR) {
		if (pierdo) { rendicionToString(); ganador = PERSONA; }
		else victoriaToString(ganador);
	}

	despedidaToString(nombre, ultimoNum);

	return ganador;
}

int quienEmpieza(){

	return ((rand() % PERSONA) + 1);

}

bool digitoValido(int ultimo, int nuevo){

	return ((mismaFila(ultimo, nuevo) || mismaColumna(ultimo, nuevo)) && (ultimo != nuevo) && rango(nuevo));

}

bool mismaFila(int ultimo, int nuevo){

	return (((ultimo - 1) / LONG_CALC) == ((nuevo - 1) / LONG_CALC));

}

bool mismaColumna(int ultimo, int nuevo){

	return (((ultimo - 1) % LONG_CALC) == ((nuevo - 1) % LONG_CALC));

}

bool rango(int nuevo) {

	return ((nuevo >= 0) && (nuevo <= MAX_NUM));

}

int digitoAleatorio(){

	return ((rand() % MAX_NUM) + 1);

}

int digitoAutomata(int ultimo){
	int numero;

	do {
		numero = digitoAleatorio();
	} while (!digitoValido(ultimo, numero));

	return numero;
}

int digitoUsuario(){
	int numero;

	mostrarCalculadoraInicial();
	do{
		cout << "Introducde un digito (0 para abandonar): ";
		cin >> numero; cin.sync(); cin.clear();
	} while (!rango(numero));

	return numero;
}

int digitoPersona(int ultimo) {
	int numero;

	mostrarCalculadora(ultimo);
	do{
		cout << "Introducde un digito (0 para abandonar): ";
		cin >> numero; cin.sync(); cin.clear();
	} while (!digitoValido(ultimo, numero) && numero != SALIR);

	return numero;
}

string saludarJugador() {
	string nombre;

	cout << "Bienvenido a pasalacalculadora!" << endl << "Como te llamas? ";
	cin >> nombre; cin.sync(); cin.clear();
	cout << "Hola " << nombre << endl;
	cout << endl << "-----------------------------------------" << endl << endl;

	return nombre;
}

void mostrarCalculadoraInicial() {

	for(int i = (MAX_NUM/LONG_CALC); i >= 1; i--) {
		for(int k = LONG_CALC - 1; k >= 0; k--) {
			cout << LONG_CALC*i-k << "   ";
		}
		cout << endl;
	}
	cout << endl;

}

void mostrarCalculadora(int ultimo) {

	for (int i = (MAX_NUM / LONG_CALC); i >= 1; i--) {
		for (int k = LONG_CALC - 1; k >= 0; k--) {
			if (digitoValido((LONG_CALC*i - k), ultimo)) setColor(10); // mostrar en verde
			else setColor(12); // mostrar en rojo
			cout << LONG_CALC*i - k << "   ";
		}
		cout << endl;
	}
	cout << endl;
	setColor(15); // Pone el color de escritura a blanco de nuevo

}

int menu(){
	int opcion;

	cout << "Selecciona una opcion: " << endl;
	cout << "1 - Jugar" << endl;
	cout << "2 - Acerca de" << endl;
	cout << "3 - Selector de dificultad" << endl;
	cout << "0 - Salir" << endl;

	do {
		cout << "Opcion: ";
		cin >> opcion; cin.clear(); cin.sync();
	} while ((opcion < SALIR) || (opcion > MAX_OPCIONES));

	cout << endl << "-----------------------------------------" << endl << endl;

	return opcion;
}

bool mostrarInformacion() {
	string aux;
	ifstream fIn;
	bool ok = true;

	cout << endl << endl << "-------------------------------------------------------------------------------" << endl << endl;

	fIn.open(ARCHIVO_INFO.c_str());
	if (!fIn.is_open()) ok = false;
	else {
		getline(fIn, aux);
		while (aux != CENTINELA.c_str()){
			cout << aux << endl;
			getline(fIn, aux);
		}

		cout << endl << "-------------------------------------------------------------------------------" << endl;
	}
	fIn.close();

	return ok;
}

void rotulo() {
	setColor(colorAleatorio());
	cout << " *****  ***   *****  ***        *      ***  " << endl;
	setColor(colorAleatorio());
	cout << " *   * *   *  *     *   *       *     *   * " << endl;
	setColor(colorAleatorio());
	cout << " ***** *****  ***** *****       *     ***** " << endl;
	setColor(colorAleatorio());
	cout << " *     *   *      * *   *       *     *   * " << endl;
	setColor(colorAleatorio());
	cout << " *     *   *  ***** *   *       ***** *   * " << endl;
	cout << endl << endl;
	setColor(colorAleatorio());
	cout << " *****  ***  *     ***** *   * *      ***  ***    ***  ****   *** " << endl;
	setColor(colorAleatorio());
	cout << " *     *   * *     *     *   * *     *   * *   * *   * *   * *   *" << endl;
	setColor(colorAleatorio());
	cout << " *     ***** *     *     *   * *     ***** *   * *   * ****  *****" << endl;
	setColor(colorAleatorio());
	cout << " *     *   * *     *     *   * *     *   * *   * *   * *  *  *   *" << endl;
	setColor(colorAleatorio());
	cout << " ***** *   * ***** ***** ***** ***** *   * ***    ***  *   * *   *" << endl;
	setColor(colorAleatorio());
	cout << " -------------------------------------------------------------------  " << endl << endl;
	setColor(15);
}

int selectorDificultad(int actualD) {
	int dificultad;

	cout << "Bienvenido al selector de dificultad!" << endl;
	cout << "Ten cuidado al elegir la dificultad, no querras que te derrote un ordenador" << endl << endl;

	cout << "La dificultad actual es: "; //Los setcolor hace que se muestre de un color u otro en base a la dificultad
	if (actualD == IA_DEFECTO) { setColor(10); cout << "FACIL" << endl << endl; }
	else if (actualD == IA_MEDIA) { setColor(14); cout << "NORMAL" << endl << endl; }
	else { setColor(12); cout << "DIFICIL" << endl << endl; }
	setColor(15);

	cout << "Seleccion una dificultad para la IA:" << endl;
	cout << "1 - Facil" << endl;
	cout << "2 - Normal" << endl;
	cout << "3 - Dificil" << endl;
	do{
		cout << "Dificultad: ";
		cin >> dificultad; cin.sync(); cin.clear();
	} while ((dificultad != IA_DEFECTO) && (dificultad != IA_MEDIA) && (dificultad != IA_DIFICIL));
	cout << endl << "-----------------------------------------" << endl << endl;

	return dificultad;
}

int digitoAutomataMejorado(int ultimo, int suma, bool &pierdo) {
	int numero = -1;

	pierdo = true;
	for (int i = 1; i <= MAX_NUM; i++){
		if (digitoValido(ultimo, i)){ // Comprueba que el numero esta dentro de los parametros del juego
			if (suma + i < MAX_PUNTUACION){ // Comprueba que no se pase de 31 al sumar ese numero
				if ((suma + i) >= (suma + (i-1))) { numero = i; } // Mira si es la suma maxima posible, si lo es guarda el numero
				pierdo = false;
			}
		}
	}

	return numero;
}

void setColor(int color) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);

}

int colorAleatorio(){

	return ((rand() % MAX_COLOR) + 1);

}

int digitoAutomataMejorado2(int ultimo, int suma, bool &pierdo) {
	int numero = -1, casosA = 0, casosN;

	pierdo = true;
	for (int i = 1; i <= MAX_NUM; i++){
		casosN = 0;
		if (digitoValido(ultimo, i)){ // Comprueba que el numero esta dentro de los parametros del juego
			if (suma + i < MAX_PUNTUACION){ // Comprueba que no se pase de 31 al sumar ese numero
				pierdo = false;
				for (int j = 1; j <= MAX_NUM; j++){
					if (digitoValido(i, j)){ // Comprueba que el posible numero del usuario fuera valido
						if ((suma + i + j) >= MAX_PUNTUACION) { casosN++; } 
					} // Comprueba si la suma del usuario seria superior a 31 y de ser asi lo contabiliza
				}
				if (casosN >= casosA) { numero = i; } 
			} // Si el numero i es el que mas casos tiene de hacer perder al usuario, coge ese
		}
	}

	return numero;
}

void actualizarInforme(int jugadas, int ganadas, int abandonosN) {
	int usos, partidasJug, partidasGM, abandonos;
	ifstream fIn;
	ofstream fOut;

	/* LEEMOS LA INFORMACION DEL ARCHIVO */
	fIn.open(INFORME.c_str());

	if (!fIn.is_open()) inicializarInforme(usos, partidasJug, partidasGM, abandonos);
	else fIn >> usos >> partidasJug >> partidasGM >> abandonos;

	fIn.close();

	/* ACTUALIZAMOS LA INFORMACION CON LOS NUEVOS DATOS */
	usos++;
	partidasJug += jugadas;
	partidasGM += ganadas;
	abandonos += abandonosN;

	/* ESCRIBIMOS LA NUEVA INFORMACION EN EL ARCHIVO */
	fOut.open(INFORME.c_str());

	if (!fOut.is_open()) errorEscrituraToString();
	else fOut << usos << endl << partidasJug << endl << partidasGM << endl << abandonos;

	fOut.close();
}

int jugadaInicial(int &ultimaJugada) {
	int numero;

	if (quienEmpieza() == PERSONA) {
		cout << "Empiezas tu" << endl << endl;
		numero = digitoUsuario();
		ultimaJugada = PERSONA;
	}
	else {
		cout << "Empiezo yo" << endl << endl;
		numero = digitoAleatorio();
		cout << "Yo pulso: " << numero << endl;;
		ultimaJugada = MAQUINA;
	}

	return numero;
}

int jugadaMaquina(int dificultad, bool &pierdo, int &suma, int ultimoNum) {
	int numero;

	if (dificultad == IA_DEFECTO){ numero = digitoAutomata(ultimoNum); }
	else if (dificultad == IA_MEDIA) { numero = digitoAutomataMejorado(ultimoNum, suma, pierdo); }
	else { numero = digitoAutomataMejorado2(ultimoNum, suma, pierdo); }
	if (!pierdo){ cout << "Yo pulso: " << numero << endl; }
	
	suma = actualizaSuma(suma, numero);

	return numero;
}

int jugadaPersona(int &suma, int ultimoNum) {
	int numero;

	numero = digitoPersona(ultimoNum);
	suma = actualizaSuma(suma, numero);

	return numero;
}

void rendicionToString(){

	cout << "Admito mi derrota, no tengo forma de ganar" << endl;
	cout << "¡Enhorabuena has ganado!" << endl;

}

void victoriaToString(int ganador) {

	if (ganador == MAQUINA) cout << "Lo siento has perdido!" << endl;
	else cout << "Enhorabuena has ganado!" << endl;

}

int actualizaSuma(int suma, int ultimoNum) {

	return (suma + ultimoNum);

}

void sumaToString(int suma) {

	cout << "Suma: " << suma << endl;
	cout << endl << "-----------------------------------------" << endl << endl;

}

void despedidaToString(string nombre, int ultimoNum) {
	
	if (ultimoNum == SALIR) cout << endl << "Lo dejaremos en tablas por esta vez..." << endl;

	cout << "Hasta la proxima " << nombre << endl;
	cout << endl << "-----------------------------------------" << endl << endl;

}

void errorLecturaToString() {

	cout << "Error: no se ha encontrado el archivo" << endl;
	cout << endl << "-------------------------------------------------------------------------------" << endl;

}

void errorEscrituraToString() {

	cout << "Error: no se han podido actualizar los datos del juego" << endl;

}

void inicializarInforme(int &usos, int &partidasJug, int &partidasGM, int &abandonos) {

	usos = 0;
	partidasJug = 0;
	partidasGM = 0;
	abandonos = 0;

}