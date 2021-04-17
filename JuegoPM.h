//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#ifndef JUEGOPM_H
#define JUEGOPM_H
#include "Matriz.h"
#include <iomanip>
//#include <iostream> //en teoria ya esta introducido en matriz.h

//estructura que recoge el tipo de datos del juego, que contiene tanto la matriz actual, la objetivo, el numero de acciones maximo y el modo de juego
struct tJuegoPM {
    unsigned short int maxAcciones = 0;
    string modo;
    tMatrizChar matrizActual, matrizResultado;
};

//funcion principal del juego 
void mainJuegoPM();

//menu para seleccionar el tipo de juego (1 o 2) o salir (0)
int menu();

// inicia los parámetros del juego que correspondan y llama a la función cargar definida a continuación.
bool iniciar(tJuegoPM& jpm, string modo);

//abre el fichero que corresponda y llama a la función cargar del módulo Matriz.
bool cargar(tJuegoPM& jpm);

//muestra el estado del reto utilizando las facilidades del módulo utilidadesSYS.Debe mostrar primero la imagen que se está modificando y a continuación la imagen objetivo.Debe mostrar también el número de intentos que quedan
void mostrar(tJuegoPM const& jpm);

//permite realizar las acciones necesarias para jugar y controla si se ha llegado al límite de acciones permitidas;
bool jugar(tJuegoPM& jpm);

//según el comando de acción tecleado por el usuario, llama a la acción correspondiente definida en el módulo Matriz;
void accion(tJuegoPM& jpm);

#endif