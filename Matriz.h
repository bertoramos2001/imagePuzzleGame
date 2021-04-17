//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#ifndef MATRIZ_H
#define MATRIZ_H
#include <fstream>
#include <iostream>
#include <math.h> //incluimos esta libreria para el valor absoluto en un pequeño calculo para las matrices que se solapan en SwapAdy
#include "Coordenada.h"
using namespace std;

const int DIM_MAX = 64; //dimension maxima de las imagenes

//definimos la matriz con la dimension maxima
typedef unsigned char tMatriz[DIM_MAX][DIM_MAX];
//estructura que recoge el tipo de datos de las matrices de caracteres, que contiene tanto la propia matriz como su dimension de filas y columnas
struct tMatrizChar{
    tMatriz matrizChar;
    unsigned short int dimFilas, dimColumnas;
};

//carga en la matriz los datos dados mediante el flujo de entrada. Devuelve false si se produce un error en la lectura de los datos
bool cargar(tMatrizChar& mat, istream& ent);

//compara si dos matrices son iguales
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2);

//intercambia las coordenadas pos1 y pos2 de la matriz. Devuelve falso si las posiciones no pertenecen al rango de la matriz
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2);

//intercambia las filas f1 y f2 de la matriz.Devuelve falso si las filas no pertenecen al rango de la matriz
bool swapF(tMatrizChar& mat, int f1, int f2);

//intercambia las columnas c1 y c2 de la matriz.Devuelve falso si las columnas no pertenecen al rango de la matriz
bool swapC(tMatrizChar& mat, int c1, int c2);

// intercambia las diagonales d y - d. Devuelve falso si las diagonales no pertenecen al rango de la matriz, o si la matriz no es cuadrada.
bool swapD(tMatrizChar& mat, int d);

//dar la vuelta a la fila f con respecto al eje vertical central de la imagen.Devuelve falso si la fila no pertenece al rango de la matriz.
bool voltearF(tMatrizChar& mat, int f);

//dar la vuelta a la columna c con respecto al eje horizontal central de la imagen.Devuelve falso si la columna no pertenece al rango de la matriz.
bool voltearC(tMatrizChar& mat, int c);

//dar la vuelta a la diagonal d con respecto al centro de eje perpendicular de dicha diagonal.Devuelve falso si la diagonal no pertenece al rango de la matriz o si la matriz no es cuadrada.
bool voltearD(tMatrizChar& mat, int d);

//dar la vuelta a la imagen completa con respecto a su eje vertical central.
void voltearV(tMatrizChar& mat);

//dar la vuelta a la imagen completa con respecto a su eje horizontal central.
void voltearH(tMatrizChar& mat);

//rotar una imagen 90 grados en el sentido de las agujas del reloj.
void rotarD(tMatrizChar& mat);

//intercambiar las celdas vecinas o adyacentes de las posiciones pos1 y pos2.
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2);

//Voltear la imagen completa respecto a la diagonal principal.Devuelve falso si la matriz no es cuadrada
bool VoltearID(tMatrizChar& mat);
#endif