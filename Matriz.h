#ifndef MATRIZ_H
#define MATRIZ_H

int** crearMatriz(int alto, int ancho);
/*void imprimirMatriz(int** matriz, int filas, int columnas);*/
void liberarMatriz(int** matriz, int alto);
int** insertarPieza(int** tablero, int altoTablero, int anchoTablero, int altoPieza, int anchoPieza, int valorFigura=1);
int** moverPieza(int** tablero, int altoTablero, int anchoTablero, int accion);
bool compararMatrices(int** tablero, int** tableroCopia, int alto, int ancho);
bool puedeBajar(int** tablero, int** copia, int altoTablero, int columnasTablero);
void eliminarFilasLlenas(int** tablero, int altoTablero, int columnasTablero);

#endif
