//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#include "JuegoPM.h"
#include "UtilidadesSYS.h"


//función principal del juego
void mainJuegoPM() {
	tJuegoPM juegoPM;
	int numModo;
	string stringModo;
	bool ganadoPartida;

	numModo = menu(); //la funcion menu nos dará el numero de modo (1 representando 1D y 2 representando 2D)
	if (numModo == 1) {
		stringModo = "1D";
	}
	else if (numModo == 2) {
		stringModo = "2D";
	}

	while (numModo != 0) { //se ejecutará el bucle principal siempre que el usuario no introduzca un 0 (que saldría del programa)
		ganadoPartida = false; //al inicio de cada turno, la variable ganadoPartida sera falso
		bool iniciarCorrecto;
		do {
			iniciarCorrecto = iniciar(juegoPM, stringModo); //llamamos a la funcion iniciar, que llama a la función cargar a su vez
		} while (!iniciarCorrecto); //mientras haya problemas con la función iniciar, la llamaremos hasta que el usuario introduzca bien el fichero

		cout << "\tTienes " << juegoPM.maxAcciones << " intentos!!!" << endl;
		mostrar(juegoPM);
		if (juegoPM.matrizActual == juegoPM.matrizResultado) { //antes de nada comprobamos si las matrices que nos dan ya son iguales
			ganadoPartida = true;
		}
		while (!ganadoPartida && (juegoPM.maxAcciones > 0)) { //en caso de que las matrices que nos dan no sean iguales, y aun tengamos movimientos, realizaremos la accion indicada y mostraremos el resultado
			accion(juegoPM);
			mostrar(juegoPM);
			if (juegoPM.matrizActual == juegoPM.matrizResultado) { //antes de nada comprobamos si las matrices que nos dan ya son iguales
				ganadoPartida = true;
			}
		}
		if (ganadoPartida) {
			cout << "\t";
			cout << "Lo has conseguido!!" << endl;
		}
		else {
			cout << "\t";
			cout << "No lo has conseguido :(. Intentalo de nuevo" << endl;
		}
		numModo = menu(); //volvemos a llamar a menu, ya que necesitamos el numModo para ver si seguimos iterando o no
		if (numModo == 1) {
			stringModo = "1D";
		}
		else if (numModo == 2) {
			stringModo = "2D";
		}
	}
}

//menu para seleccionar el tipo de juego (1 o 2) o salir (0)
int menu() {
	int opcion;

	do {
		cout << endl;
		cout << "\t";
		cout << "Elige una opcion:" << endl << endl;
		cout << "\t";
		cout << "1 Version de juego - 1D" << endl;
		cout << "\t";
		cout << "2 Version de juego - 2D" << endl;
		cout << "\t";
		cout << "0 salir" << endl;
		cin >> opcion;
	} while ((opcion < 0) || (opcion > 2)); //mientras no se introduzcan 0, 1 o 2, se seguirá pidiendo un número
	return opcion;
}

//inicia los parámetros del juego que correspondan y llama a la función cargar definida a continuación
bool iniciar(tJuegoPM& jpm, string modo) {
	jpm.modo = modo; //añadimos el string del modo a la estructura de juego
	bool inicioValido = cargar(jpm); //cargamos la estructura de juego y vemos si es valido

	return inicioValido;
}

//abre el fichero que corresponda y llama a la función cargar del módulo Matriz.
bool cargar(tJuegoPM& jpm) {
	string nombreArchivo;
	bool archivoCargado, falloArchivo = false;
	cout << "Nombre del archivo (sin indicador de tipo ni extension)" << endl;
	cin >> nombreArchivo;
	nombreArchivo = nombreArchivo + "_" + jpm.modo + ".txt";
	//nombreArchivo = nombreArchivo + ".txt"; //esto es valido para los algunos de los ficheros de pruebas adicionales
	nombreArchivo = "C:/Users/salgu/Downloads/ficherosPrimeraEntrega/" + nombreArchivo; //tuvimos que hacer esto porque no nos abría el archivo poniendo solamente el nombre del mismo

	ifstream archivo;
	archivo.open(nombreArchivo);
		if (archivo.is_open()) {
			archivoCargado = true;
			//llamamos a la función cargar, definida en el módulo matriz, donde se carga la matriz con los valores de entrada, para cargar la matriz rezultado
			if (!cargar(jpm.matrizActual, archivo)) { 
				falloArchivo = true;
				cout << "Ha habido un fallo con la carga de la matriz resultado" << endl;
			}
			//llamamos a la función cargar, definida en el módulo matriz, donde se carga la matriz con los valores de entrada, para cargar la matriz actual
			if (!cargar(jpm.matrizResultado, archivo)) { 
				falloArchivo = true;
				cout << "Ha habido un fallo con la carga de la matriz actual" << endl;
			}
			//insertamos el numero maximo de movimientos tambien del fichero
			archivo >> jpm.maxAcciones;
		}
		else {
			archivoCargado = false;
			cout << "No se ha encontrado el archivo con el nombre indicado, por favor intentelo de nuevo" << endl;
		}
	return (archivoCargado && !falloArchivo);
}

//muestra el estado del reto utilizando las facilidades del módulo utilidadesSYS.Debe mostrar primero la imagen que se está modificando y a continuación la imagen objetivo.Debe mostrar también el número de intentos que quedan
void mostrar(tJuegoPM const& jpm) {
	cout << "\t  ";
	for (int col = 0; col < jpm.matrizActual.dimColumnas; ++col) { //mostramos los numeros de las columnas, ocupando 2 espacios cada numero
		cout << setw(2) << col;
	}
	cout << endl;

	//mostramos primero la imagen de la matriz que se está modificando
	for (int i = 0; i < jpm.matrizActual.dimFilas; i++) { //iteramos sobre las filas
		cout << "\t" << setw(2) << i << ' '; //mostramos el numero de cada fila antes de pintarla por pantalla
		for (int j = 0; j < jpm.matrizActual.dimColumnas; j++) { //iteramos sobre las columnas
			colorCTA(15, int(jpm.matrizActual.matrizChar[i][j]) - int('0')); //llamamos a la funcion auxiliar de utilidadesSYS para pintar los colores de cada celda
			cout << ' ' << ' ';
		}
		colorCTA(15, 0);
		cout << "\n";
	}
	cout << endl;

	cout << "\t  ";
	for (int col = 0; col < jpm.matrizResultado.dimColumnas; ++col) { //volvemos a hacer lo mismo que antes para mostrar los numeros de cada columna
		cout << setw(2) << col;
	}
	cout << endl;

	//ahora mostramos la imagen de la matriz objetivo, aplicando los mismos procedimientos que antes
	for (int i = 0; i < jpm.matrizResultado.dimFilas; i++) {
		cout << "\t" << setw(2) << i << ' ';
		for (int j = 0; j < jpm.matrizResultado.dimColumnas; j++) {
			colorCTA(15, int(jpm.matrizResultado.matrizChar[i][j]) - int('0'));
			cout << ' ' << ' ';
			//cout << jpm.matrizResultado.matrizChar[i][j];
		}
		colorCTA(15, 0);
		cout << "\n";
	}
	cout << endl;
	cout << "\t";
	cout << "Te quedan " << jpm.maxAcciones << " intentos" << endl; //en la funcion dice que debemos mostrar el numero de intentos en esta funcion, aunque para que nos quede igual que en la practica habria que poner esto en el main, para que no se ejecute antes del primer movimiento
	cout << endl;
}

//permite realizar las acciones necesarias para jugar y controla si se ha llegado al límite de acciones permitidas;
bool jugar(tJuegoPM& jpm) {
	bool quedanIntentos = true;
	if (jpm.maxAcciones == 0) {
		quedanIntentos = false;
	}
	return quedanIntentos;
}

//según el comando de acción tecleado por el usuario, llama a la acción correspondiente definida en el módulo Matriz;
void accion(tJuegoPM& jpm) {
	bool cambioCorrecto = true; //esta variable e dira si se ha realizado la accion correctamente
	string accion;
	cin >> accion;

	if (accion == "SF") { //intercambiar filas f1 y f2
		int f1, f2;
		cin >> f1 >> f2;
		cambioCorrecto = swapF(jpm.matrizActual, f1, f2); 

		if (!cambioCorrecto) {
			cout << "Las filas introducidas no se encuentran en el rango de la matriz" << endl;
		}
	}
	else if (accion == "SC") { //intercambiar las columnas c1 y c2
		int c1, c2;
		cin >> c1 >> c2;
		cambioCorrecto = swapC(jpm.matrizActual, c1, c2); 

		if (!cambioCorrecto) {
			cout << "Las columnas introducidas no se encuentran en el rango de la matriz" << endl;
		}
	}
	else if (accion == "SD") { //intercambiar diagonales d y -d
		int d;
		cin >> d; //obtenemos el valor de la diagonal d
		cambioCorrecto = swapD(jpm.matrizActual, d);

		if (!cambioCorrecto) {
			cout << "La diagonal introducida no pertenece al rango de la matriz o la matriz no es cuadrada" << endl;
		}
	}
	else if (accion == "VF") { //voltear cierta fila f
		int f;
		cin >> f; 
		cambioCorrecto = voltearF(jpm.matrizActual, f);

		if (!cambioCorrecto) {
			cout << "La fila introducida no pertenece al rango de la matriz" << endl;
		}
	}
	else if (accion == "VC") { //voltear cierta columna c
		int c;
		cin >> c;
		cambioCorrecto = voltearC(jpm.matrizActual, c);

		if (!cambioCorrecto) {
			cout << "La columna introducida no pertenece al rango de la matriz" << endl;
		}
	}
	else if ((accion == "VD") && (jpm.modo == "1D")) { //voltear cierta diagonal d. En este caso añadimos la especificacion de modo de juego porque hay otra funcion q la que se llama tambien como VD en el modo 2D
		int d;
		cin >> d;
		cambioCorrecto = voltearD(jpm.matrizActual, d);

		if (!cambioCorrecto) {
			cout << "La diagonal introducida no pertenece al rango de la matriz o la matriz no es cuadrada" << endl;
		}
	}
	else if (accion == "VV") { //voltear toda la imagen respecto a la vertical
		voltearV(jpm.matrizActual);
		cambioCorrecto = true; //el cambio no puede ser incorrecto, esto siempre se cumple
	}
	else if (accion == "VH") { //voltear toda la imagen respecto a la horizontal
		voltearH(jpm.matrizActual);
		cambioCorrecto = true; //el cambio no puede ser incorrecto, esto siempre se cumple
	}
	else if (accion == "RD") { //rotar toda la imagen hacia la derecha
		rotarD(jpm.matrizActual);
		cambioCorrecto = true; //el cambio no puede ser incorrecto, esto siempre se cumple
	}
	else if (accion == "SA") { //intercambiar las posiciones alrededor de las coordenadas introducidas
		tCoor coor1, coor2;
		cin >> coor1.fila >> coor1.columna >> coor2.fila >> coor2.columna;
		cambioCorrecto = swapAdy(jpm.matrizActual, coor1, coor2);
	}
	else if ((accion == "VD") && (jpm.modo == "2D")) { //voltear la matriz respecto a la diagonal principal.  En este caso añadimos la especificacion de modo de juego porque hay otra funcion q la que se llama tambien como VD en el modo 1D
		cambioCorrecto = VoltearID(jpm.matrizActual);

		if (!cambioCorrecto) {
			cout << "La matriz no es cuadrada" << endl;
		}
	}
	else {
		cout << "accion no valida, intentelo de nuevo" << endl;
		cambioCorrecto = false; //si no se escribe bien el movimiento, el cambio correcto será falso
	}
	if (cambioCorrecto) { //si el cambio ha sido correcto, se restará 1 al numero maximo de acciones
		jpm.maxAcciones--;
	}
	else {
		cout << "No se ha aplicado el cambio correctamente, no se te resta ningun movimiento" << endl;
	}
}