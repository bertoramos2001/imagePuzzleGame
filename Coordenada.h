//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#ifndef COORDENADA_H
#define COORDENADA_H

//estructura que recoge el tipo de datos de las coordenadas, que contiene tanto la coordenada x como la y
struct tCoor {
    unsigned short int fila, columna;
};

//compara si dos coordenadas son iguales
bool operator == (tCoor c1, tCoor c2);

//compara si dos coordenadas son distintas
bool operator != (tCoor c1, tCoor c2);

//devuelve la coordenada resultante de sumar las dos coordenadas
tCoor operator + (tCoor c1, tCoor c2);
#endif