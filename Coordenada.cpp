//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#include "Coordenada.h"

//compara si dos coordenadas son iguales
bool operator == (tCoor c1, tCoor c2) {
    return ((c1.fila == c2.fila) && (c1.columna == c2.columna));
}

//compara si dos coordenadas son distintas
bool operator != (tCoor c1, tCoor c2) {
    return ((c1.fila != c2.fila) || (c1.columna != c2.columna));
}

//devuelve la coordenada resultante de sumar las dos coordenadas
tCoor operator + (tCoor c1, tCoor c2) {
    tCoor coorResultado; //definimos un tipo tCoor, que será el que devolvamos
    //sumamos cada coordenada x e y y las guardamos en sus respectivas posiciones en nuestra nueva variable tipo tCoor
    coorResultado.fila = c1.fila + c2.fila;
    coorResultado.columna = c1.columna + c2.columna;

    return coorResultado; //devolvermos la variable tCoor
}