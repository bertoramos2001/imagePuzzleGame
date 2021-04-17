//Código realizado por Alberto Ramos y Gonzalo Alfredo Segovia

#include "Matriz.h"

//funciones auxiliares de las funciones principales; pasamos la matriz por referencia constante, ya que no queremos modificar la matriz pero necesitamos utilizar sus datos y no queremos hacer una copia de ella
bool comprobarPosicionValidaMatriz(const tMatrizChar& mat, tCoor pos);
bool comprobarFilaValidaMatriz(const tMatrizChar& mat, int fila);
bool comprobarColumnaValidaMatriz(const tMatrizChar& mat, int columna);
bool comprobarDiagonalValidaMatriz(const tMatrizChar& mat, int diagonal);
bool comprobarMatrizCuadrada(const tMatrizChar& mat);

//carga en la matriz los datos dados mediante el flujo de entrada. Devuelve false si se produce un error en la lectura de los datos
bool cargar(tMatrizChar& mat, istream& ent) {
    bool cargaCorrecta = true;
    ent >> mat.dimFilas >> mat.dimColumnas; //insertamos el numero de filas y columnas de la matriz
    cargaCorrecta = !ent.fail(); //recogemos si los datos son validos (si fail es falso, la cargaCorrectasera correcta)
    //si no hay fallo en la carga de las dimensiones de la matriz, rellenamos las celdas de la matriz
    if (cargaCorrecta) {
        for (int i = 0; i < mat.dimFilas; i++) {
            for (int j = 0; j < mat.dimColumnas; j++) {
                ent >> mat.matrizChar[i][j];
            }
        }
        cargaCorrecta = !ent.fail(); //comprobamos que las entradas de la matriz tambien son correctas
    }
    if (!cargaCorrecta) {
        mat.dimFilas = mat.dimColumnas = 0;
    }
    return cargaCorrecta;
}

//compara si dos matrices son iguales
bool operator == (tMatrizChar const& mat1, tMatrizChar const& mat2) {
    bool sonIguales = true;
    //si las matrices no tienen la misma dimension, no son iguales, por lo que ya no las compararé
    if ((mat1.dimColumnas != mat2.dimColumnas) || (mat1.dimFilas != mat2.dimFilas)) {
        sonIguales = false;
    } else {
        //recorro las filas y columnas hasta llegar a la dimension de la matriz1 (que es la misma que la de la matriz 2 despues de compararlas)
        for (int i = 0; i < mat1.dimFilas; i++) { 
            for (int j = 0; j < mat1.dimColumnas; j++) { 
                if (mat1.matrizChar[i][j] != mat2.matrizChar[i][j]) { //si alguna posicion son diferentes, ponemos nuestro booleano a false
                    sonIguales = false;
                }
            }
        }
    }

    return sonIguales;
}

//intercambia las coordenadas pos1 y pos2 de la matriz. Devuelve falso si las posiciones no pertenecen al rango de la matriz
bool swap(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    bool intercambioHecho;
    tCoor temp;

    if ((comprobarPosicionValidaMatriz(mat, pos1)) && (comprobarPosicionValidaMatriz(mat, pos2))) { //nos ayudamos de una funcion auxiliar para ver que ambas posiciones son válidas
        //si ambas posiciones son válidas, realizamos el intercambio de posiciones
        temp = pos1;
        pos1 = pos2;
        pos2 = temp;
        intercambioHecho = true;
    }
    else {
        intercambioHecho = false;
    }
    return intercambioHecho; //devolvemos si hemos realizado el intercambio o no
}
//funcion auxiliar a swap que comprueba si una posicion de la matriz es válida
bool comprobarPosicionValidaMatriz(const tMatrizChar& mat, tCoor pos) {
    return (((pos.fila >= 0) && (pos.fila < mat.dimFilas)) && ((pos.columna >= 0) && (pos.columna < mat.dimColumnas))); //comprobamos si la posicion pertenece al rango de la matriz (es decir, que tanto fila como columna son mayores o iguales que 0 y menores que la dimension maxima y devolvemos si es cierto o falso
}

//intercambia las filas f1 y f2 de la matriz.Devuelve falso si las filas no pertenecen al rango de la matriz
bool swapF(tMatrizChar& mat, int f1, int f2) {
    bool intercambioHecho;
    unsigned char temp;

    if ((comprobarFilaValidaMatriz(mat, f1)) && (comprobarFilaValidaMatriz(mat, f2))) { //nos ayudamos de una funcion auxiliar para ver que ambas posiciones son válidas
        //si ambas filas son válidas, realizamos el intercambio de filas
        for (int i = 0; i < mat.dimColumnas; i++) {
            temp = mat.matrizChar[f1][i];
            mat.matrizChar[f1][i] = mat.matrizChar[f2][i];
            mat.matrizChar[f2][i] = temp;
        }
        intercambioHecho = true;
    }
    else {
        intercambioHecho = false;
    }
    return intercambioHecho; //devolvemos si hemos hecho el intercambio
}
//funcion auxiliar a swapF que comprueba si una fila de la matriz es válida
bool comprobarFilaValidaMatriz(const tMatrizChar& mat, int fila) {
    return ((fila >= 0) && (fila < mat.dimFilas)); //comprobamos si la fila pertenece al rango de la matriz (es decir, que ls fila es mayor o igual que 0 y menor que la dimension maxima de filas) y devolvemos si esto es cierto o falso
}

//intercambia las columnas c1 y c2 de la matriz.Devuelve falso si las columnas no pertenecen al rango de la matriz
bool swapC(tMatrizChar& mat, int c1, int c2) {
    bool intercambioHecho;
    unsigned char temp;

    if ((comprobarColumnaValidaMatriz(mat, c1)) && (comprobarColumnaValidaMatriz(mat, c2))) { //nos ayudamos de una funcion auxiliar para ver que ambas posiciones son válidas
        //si ambas filas son válidas, realizamos el intercambio de filas
        for (int i = 0; i < mat.dimFilas; i++) {
            temp = mat.matrizChar[i][c1];
            mat.matrizChar[i][c1] = mat.matrizChar[i][c2];
            mat.matrizChar[i][c2] = temp;
        }
        intercambioHecho = true;
    }
    else {
        intercambioHecho = false;
    }
    return intercambioHecho; //devolvemos si hemos hecho el intercambio
}
//funcion auxiliar a swapC que comprueba si una posicion de la matriz es válida
bool comprobarColumnaValidaMatriz(const tMatrizChar& mat, int columna) {
    return ((columna >= 0) && (columna < mat.dimColumnas)); //comprobamos si la columna pertenece al rango de la matriz (es decir, que la columna es mayor o igual que 0 y menor que la dimension maxima de columnas) y devolvemos si esto es cierto o falso
}

// intercambia las diagonales d y - d. Devuelve falso si las diagonales no pertenecen al rango de la matriz, o si la matriz no es cuadrada.
bool swapD(tMatrizChar& mat, int d) {
    bool intercambioRealizado;
    unsigned char temp;

    if ((comprobarDiagonalValidaMatriz(mat, d)) && (comprobarMatrizCuadrada(mat))) { //comprobamos que la matriz es cuadrada y que la diagonal introducida pertenece a la misma
        intercambioRealizado = true;
        for (int i = 0; i < mat.dimColumnas - d; i++) {  //podriamos poner dimColumnas o dimFilas, ya que la matriz ha de ser cuadrada y estas deberán ser iguales. Le restamos d porque cuanto mas nos acerquemos al borde, menos repeticiones tendremos que hacer
            temp = mat.matrizChar[i][d + i]; //durante el recorrido, la primera posicion sera la que marque el recorrido, y la segunda será la posición base de la diagonal mas la que marque el recorrido
            mat.matrizChar[i][d + i] = mat.matrizChar[d + i][i]; //asignaremos cada posicion de la matriz -d a la matriz d. Sabemos que serán las simétricas, ya que cuando una esla posicion [1][0], la otra sera [0][1] y asi sucesivamente
            mat.matrizChar[d + i][i] = temp;
        }
    }
    else {
        intercambioRealizado = false;
    }
    return intercambioRealizado;
}
//función auxiliar a swapD que comprueba si una posicion de la matriz es valida
bool comprobarDiagonalValidaMatriz(const tMatrizChar& mat, int diagonal) {
    if (diagonal < 0) { //las matrices negativas tambien estan en la matriz
        diagonal = -diagonal;
    }
    return ((diagonal >= 0) && (diagonal < mat.dimColumnas)); //podriamos poner dimColumnas o dimFilas, ya que la matriz ha de ser cuadrada y estas deberán ser iguales
}
//Función auxiliar que comprueba si una matriz es cuadrada
bool comprobarMatrizCuadrada(const tMatrizChar& mat) {
    return (mat.dimColumnas == mat.dimFilas);
}

//dar la vuelta a la fila f con respecto al eje vertical central de la imagen.Devuelve falso si la fila no pertenece al rango de la matriz.
bool voltearF(tMatrizChar& mat, int f) {
    bool filaVolteada;
    unsigned char temp;
    int j = mat.dimColumnas - 1; //utilizaremos este indice para recorrer la matriz la mitad de su longitud, independientemente de su paridad

    if (comprobarFilaValidaMatriz(mat, f)) { //nos ayudamos de una funcion auxiliar para comprobar si la fila es valida
        for (int i = 0; i < j; i++, j--) { //recorreremos la fila hasta la mitad (haciéndolo así, valdrá tanto para cuando el numero de columnas sea impar o par) e intercambiamos las posiciones de la matriz
            temp = mat.matrizChar[f][i]; //tenemos en cuenta que la primera variable de la matriz será constante, porque queremos voltear los elementos de una sola fila de la matriz
            mat.matrizChar[f][i] = mat.matrizChar[f][j];
            mat.matrizChar[f][j] = temp;
        }
        filaVolteada = true;
    }
    else {
        filaVolteada = false;
    }
    return filaVolteada;
}

//dar la vuelta a la columna c con respecto al eje horizontal central de la imagen.Devuelve falso si la columna no pertenece al rango de la matriz.
bool voltearC(tMatrizChar& mat, int c) {
    bool columnaVolteada;
    unsigned char temp;
    int j = mat.dimFilas - 1; //utilizaremos este indice para recorrer la matriz la mitad de su longitud, independientemente de su paridad

    if (comprobarColumnaValidaMatriz(mat, c)) { //nos ayudamos de una funcion auxiliar para comprobar si la columna es valida
        for (int i = 0; i < j; i++, j--) { //recorreremos la fila hasta la mitad (haciéndolo así, valdrá tanto para cuando el numero de filas sea impar o par) e intercambiamos las posiciones de la matriz
            temp = mat.matrizChar[i][c]; //tenemos en cuenta que la segunda variable de la matriz será constante, porque queremos voltear los elementos de una sola columna de la matriz
            mat.matrizChar[i][c] = mat.matrizChar[j][c];
            mat.matrizChar[j][c] = temp;
        }
        columnaVolteada = true;
    }
    else {
        columnaVolteada = false;
    }
    return columnaVolteada;
}

//dar la vuelta a la diagonal d con respecto al centro de eje perpendicular de dicha diagonal.Devuelve falso si la diagonal no pertenece al rango de la matriz o si la matriz no es cuadrada.
bool voltearD(tMatrizChar& mat, int d) {
    bool matrizVolteada;
    unsigned char temp;

    if ((comprobarDiagonalValidaMatriz(mat, d)) && (comprobarMatrizCuadrada(mat)) && (d >= 0)) { //comprobamos que la matriz es cuadrada y que la diagonal introducida pertenece a la misma
        matrizVolteada = true;
        int j = mat.dimColumnas - 1; //podriamos poner dimColumnas o dimFilas, ya que la matriz ha de ser cuadrada y estas deberán ser iguales
        for (int i = 0; d + i < j; i++, j--) { //recorremos mientras d+i sea menor que j, y no simplemente i, ya que el verdadero contador dentro de la fila es d+i, que contiene la informacion de la componente x, la cual irá aumentando con las iteraciones
            temp = mat.matrizChar[i][d+ i]; //asignamos la posicion actual por arriba de la diagonal a la variable temp
            mat.matrizChar[i][d + i] = mat.matrizChar[j - d][j]; //intercambiamos la posicion actual por arriba con la posicion actual por abajo de la diagonal de la matriz
            mat.matrizChar[j - d][j] = temp; //asignamos el valor de temp (posicion actual por arriba) a la posicion actual por abajo de la diagonal
        }
    }
    else if ((comprobarDiagonalValidaMatriz(mat, d)) && (comprobarMatrizCuadrada(mat)) && (d < 0)) {
        //ahora aplicamos la misma logica que arriba pero para las diagonales negativas, es decir, con las filas y columnas al reves
        matrizVolteada = true;
        d = -d;
        int j = mat.dimColumnas - 1; 
        for (int i = 0; d + i < j; i++, j--) {
            temp = mat.matrizChar[d + i][i]; 
            mat.matrizChar[d + i][i] = mat.matrizChar[j][j - d];
            mat.matrizChar[j][j - d] = temp;
        }
    }
    else {
        matrizVolteada = false;

    }
    return matrizVolteada;
}

//dar la vuelta a la imagen completa con respecto a su eje vertical central.
void voltearV(tMatrizChar& mat) {
    for (int i = 0; i < mat.dimFilas; i++) {
        voltearF(mat, i); //para cada fila en la matriz, volteamos los valores de la fila, lo que resultará en voltear la matriz completa con respecto a su eje vertical
    }
}

//dar la vuelta a la imagen completa con respecto a su eje horizontal central.
void voltearH(tMatrizChar& mat) {
    for (int i = 0; i < mat.dimColumnas; i++) {
        voltearC(mat, i); //para cada columna en la matriz, volteamos los valores de la columna, lo que resultará en voltear la matriz completa con respecto a su eje horizontal
    }
}
//rotar una imagen 90 grados en el sentido de las agujas del reloj.
void rotarD(tMatrizChar& mat) {
    tMatriz matrizAux; //creamos una matriz auxiliar, que tendrá las dimensiones de filas y columnas al reves que nuestra matriz original (ya que las matrices no serán siempre cuadradas)
    for (int i = 0; i < mat.dimFilas; i++) {
        for (int j = 0; j < mat.dimColumnas; j++) {
            matrizAux[j][i] = mat.matrizChar[mat.dimFilas - 1 - i][j]; //rellenaremos nuestra matriz auxiliar por las columnas, empezando por la ultima fila de nuestra matriz original (que pasaremos a la primera columna de la matriz auxiliar) y acabando por la primera fila de la matriz original (que irá a la última columna de la matriz auxiliar)
        }
    }
    int temp;
    //ahora intercambiamos el numero de filas por el de columnas (si la matriz fuera cuadrada, se quedaría igual)
    temp = mat.dimColumnas;
    mat.dimColumnas = mat.dimFilas;
    mat.dimFilas = temp;
    //finalmente, asignamos el valor de la matriz ya rotada a nuestra matriz original
    for (int i = 0; i < mat.dimFilas; i++) {
        for (int j = 0; j < mat.dimColumnas; j++) {
            mat.matrizChar[i][j] = matrizAux[i][j];
        } //realizamos la asignacion de esta manera ya que no nos dejaba hacer mat.matrizChar = matrizAux, por no ser matrizChar un valor modificable
    }
}

//intercambiar las celdas vecinas o adyacentes de las posiciones pos1 y pos2.
bool swapAdy(tMatrizChar& mat, tCoor pos1, tCoor pos2) {
    bool dentroDelLimite = false, seSolapan = false;
    unsigned char temp;
    //primero comprobamos si las filas adyacentes de las posiciones coinciden (si estan en diagonal no pasaria nada)
    if ((pos1.fila + 1 == pos2.fila + 1) || (pos1.fila + 1 == pos2.fila - 1) || (pos1.fila - 1 == pos2.fila + 1) || (pos1.fila == pos2.fila+ 1) || (pos1.fila == pos2.fila - 1)) {
        //si las filas adyacentes coinciden, veremos que si hay más de tres celdas de distancia entre los centros, las celdas de alrededor se podrán cambiar
        if (abs(pos1.columna - pos2.columna) < 3) {
            seSolapan = true;
        }
    } 
    //ahora comprobamos que las columnas adyacentes a las posiciones coinciden (si estan en diagonal de nuevo no pasa nada)
    if ((pos1.columna + 1 == pos2.columna + 1) || (pos1.columna + 1 == pos2.columna - 1) || (pos1.columna - 1 == pos2.columna + 1) || (pos1.columna == pos2.columna + 1) || (pos1.columna == pos2.columna - 1)) {
        //si las columnas adyacentes coinciden, veremos que si hay más de tres celdas de distancia, de nuevo, entrelos centros, las celdas de alrededor se podrán cambiar
        if (abs(pos1.fila - pos2.fila) < 3) {
            seSolapan = true;
        }
    }

    //luego comprobamos que las filas adyacentes a cada posicion son correctas con las funciones auxiliares previamente definidas
    if (comprobarFilaValidaMatriz(mat, pos1.fila - 1) && comprobarFilaValidaMatriz(mat, pos1.fila + 1) && comprobarColumnaValidaMatriz(mat, pos1.columna - 1) && comprobarColumnaValidaMatriz(mat, pos1.columna + 1)) {
        if (comprobarFilaValidaMatriz(mat, pos2.fila - 1) && comprobarFilaValidaMatriz(mat, pos2.fila + 1) && comprobarColumnaValidaMatriz(mat, pos2.columna - 1) && comprobarColumnaValidaMatriz(mat, pos2.columna + 1)) {
            dentroDelLimite = true;
            if (!seSolapan) { //si ademas de estar dentro del limite, las posiciones no se solapan
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if ((i != 1) || (j != 1)) { //en el caso de estar en la posicion i=1 y j =1 (centro) no intercambiaremos la posicion
                            temp = mat.matrizChar[pos1.fila - 1 + i][pos1.columna - 1 + j];
                            mat.matrizChar[pos1.fila - 1 + i][pos1.columna - 1 + j] = mat.matrizChar[pos2.fila - 1 + i][pos2.columna - 1 + j];
                            mat.matrizChar[pos2.fila - 1 + i][pos2.columna - 1 + j] = temp;
                        }
                    }
                }
            }
        }
    }
    if (seSolapan) {
        cout << "Las filas adyacentes de las coordenadas introducidas se solapan" << endl;
    }
    if (!dentroDelLimite) {
        cout << "Las filas adyacentes a alguna de las coordenadas no esta en la matriz" << endl;
    }
    return (dentroDelLimite && !seSolapan);
}

//Voltear la imagen completa respecto a la diagonal principal.Devuelve falso si la matriz no es cuadrada
bool VoltearID(tMatrizChar& mat) {
    bool matrizVolteada;
    unsigned char temp;
    if (mat.dimColumnas != mat.dimFilas) {
        matrizVolteada = false;
    }
    else {
        matrizVolteada = true;
        for (int i = 0; i < mat.dimFilas - 1; i++) {
            for (int j = i + 1; j < mat.dimColumnas; j++) {
                temp = mat.matrizChar[i][j];
                mat.matrizChar[i][j] = mat.matrizChar[j][i];
                mat.matrizChar[j][i] = temp;
            }
        }
    }
    return matrizVolteada;
}
