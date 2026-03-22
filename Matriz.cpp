#include "Matriz.h"
#include <cstdlib>
#include "Piezas.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int** crearMatriz(int ancho, int alto) {
    // Reservar memoria para alto filas
    int** matriz = new int*[alto];
    for (int i = 0; i < alto; i++) {
        // Reservar memoria para ancho + 2 columnas (una izquierda y una derecha)
        matriz[i] = new int[ancho + 2];
    }

    // Llenar la matriz
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho + 2; j++) {
            if (j == 0 || j == ancho + 1) {
                matriz[i][j] = 3; // columnas extra izquierda y derecha
            } else {
                matriz[i][j] = 0; // resto de la matriz
            }
        }
    }

    return matriz;
}




int** insertarPieza(int** tablero, int altoTablero, int anchoTablero, int altoPieza, int anchoPieza, int valorFigura) {
    int columnasTablero = anchoTablero + 2;
    int espacio=0;

    // Generar la pieza automáticamente con Cuadrado (o cualquier otra función)
    int** pieza = generarPiezaAleatoria();

    // Vertical: siempre arriba
    int inicioFila = 0;
    // Horizontal: centrada
    int inicioColumna = (columnasTablero - anchoPieza) / 2;

    // Copiar únicamente las posiciones que coincidan con el valor de la figura
    for (int i = 0; i < altoPieza; i++) {
        for (int j = 0; j < anchoPieza; j++) {
            if(espacio==4){
                inicioFila--;

            }
            if (pieza[i][j] == valorFigura) {

                tablero[inicioFila + i][inicioColumna + j] = pieza[i][j];
                espacio=0;

            }else {
                espacio++;

            }

        }
    }

    // Liberar memoria de la pieza después de usarla
    for (int i = 0; i < altoPieza; i++) {
        delete[] pieza[i];
    }
    delete[] pieza;

    return tablero;
}

int** moverPieza(int** tablero, int** copia, int altoTablero, int anchoTablero, int accion) {
    int columnasTablero = anchoTablero + 2;

    int** nuevoTablero = new int*[altoTablero];
    for (int i = 0; i < altoTablero; i++) {
        nuevoTablero[i] = new int[columnasTablero];
        for (int j = 0; j < columnasTablero; j++)
            nuevoTablero[i][j] = tablero[i][j];
    }

    for (int i = 0; i < altoTablero; i++)
        for (int j = 0; j < columnasTablero; j++)
            if (tablero[i][j] == 1)
                nuevoTablero[i][j] = 0;

    // ── ACCION 3: BAJAR ─────────────────────────────────────────────
    if (accion == 3) {
        bool puedeBajar = true;
        for (int i = 0; i < altoTablero; i++)
            for (int j = 0; j < columnasTablero; j++)
                if (tablero[i][j] == 1) {
                    if (i >= altoTablero - 1) puedeBajar = false;
                    else if (copia[i + 1][j] == 1) puedeBajar = false;
                }

        for (int i = 0; i < altoTablero; i++)
            for (int j = 0; j < columnasTablero; j++)
                if (tablero[i][j] == 1)
                    nuevoTablero[puedeBajar ? i + 1 : i][j] = 1;

        for (int i = 0; i < altoTablero; i++) delete[] tablero[i];
        delete[] tablero;
        return nuevoTablero;
    }

    // ── ACCION 4: ROTAR ─────────────────────────────────────────────
    if (accion == 4) {
        int minI = altoTablero, maxI = -1, minJ = columnasTablero, maxJ = -1;
        for (int i = 0; i < altoTablero; i++)
            for (int j = 0; j < columnasTablero; j++)
                if (tablero[i][j] == 1) {
                    if (i < minI) minI = i;
                    if (i > maxI) maxI = i;
                    if (j < minJ) minJ = j;
                    if (j > maxJ) maxJ = j;
                }

        int altoPieza  = maxI - minI + 1;
        int anchoPieza = maxJ - minJ + 1;

        int** pieza = new int*[altoPieza];
        for (int i = 0; i < altoPieza; i++) {
            pieza[i] = new int[anchoPieza];
            for (int j = 0; j < anchoPieza; j++)
                pieza[i][j] = tablero[minI + i][minJ + j];
        }

        int** rotada = new int*[anchoPieza];
        for (int i = 0; i < anchoPieza; i++) {
            rotada[i] = new int[altoPieza];
            for (int j = 0; j < altoPieza; j++)
                rotada[i][j] = pieza[altoPieza - 1 - j][i];
        }

        int centroI = (minI + maxI) / 2;
        int centroJ = (minJ + maxJ) / 2;
        int offsetI = centroI - (anchoPieza - 1) / 2;
        int offsetJ = centroJ - (altoPieza - 1) / 2;

        bool puedeRotar = true;
        for (int i = 0; i < anchoPieza && puedeRotar; i++)
            for (int j = 0; j < altoPieza && puedeRotar; j++)
                if (rotada[i][j] == 1) {
                    int ti = offsetI + i, tj = offsetJ + j;
                    if (ti < 0 || ti >= altoTablero || tj < 0 || tj >= columnasTablero)
                        puedeRotar = false;
                    else if (tablero[ti][tj] == 3)
                        puedeRotar = false;
                    else if (copia[ti][tj] == 1)
                        puedeRotar = false;
                }

        if (puedeRotar) {
            for (int i = 0; i < anchoPieza; i++)
                for (int j = 0; j < altoPieza; j++)
                    if (rotada[i][j] == 1) {
                        int ti = offsetI + i, tj = offsetJ + j;
                        if (ti >= 0 && ti < altoTablero && tj >= 0 && tj < columnasTablero)
                            nuevoTablero[ti][tj] = 1;
                    }
        } else {
            for (int i = 0; i < altoTablero; i++)
                for (int j = 0; j < columnasTablero; j++)
                    if (tablero[i][j] == 1)
                        nuevoTablero[i][j] = 1;
        }
        for (int i = 0; i < altoPieza;  i++) delete[] pieza[i];
        delete[] pieza;
        for (int i = 0; i < anchoPieza; i++) delete[] rotada[i];
        delete[] rotada;

        for (int i = 0; i < altoTablero; i++) delete[] tablero[i];
        delete[] tablero;
        return nuevoTablero;
    }

    // ── ACCIONES 1 y 2: IZQUIERDA / DERECHA ────────────────────────
    bool puedeMover = true;

    if (accion == 1)
        for (int i = 0; i < altoTablero; i++)
            for (int j = 0; j < columnasTablero; j++)
                if (tablero[i][j] == 1) {
                    if (tablero[i][j-1] == 3) puedeMover = false;
                    else if (copia[i][j-1] == 1) puedeMover = false;
                }

    if (accion == 2)
        for (int i = 0; i < altoTablero; i++)
            for (int j = 0; j < columnasTablero; j++)
                if (tablero[i][j] == 1) {
                    if (tablero[i][j+1] == 3) puedeMover = false;
                    else if (copia[i][j+1] == 1) puedeMover = false;
                }

    for (int i = 0; i < altoTablero; i++)
        for (int j = 0; j < columnasTablero; j++)
            if (tablero[i][j] == 1) {
                if      (accion == 1 && puedeMover) nuevoTablero[i][j-1] = 1;
                else if (accion == 2 && puedeMover) nuevoTablero[i][j+1] = 1;
                else                                nuevoTablero[i][j]   = 1;
            }

    for (int i = 0; i < altoTablero; i++) delete[] tablero[i];
    delete[] tablero;
    return nuevoTablero;
}


bool compararMatrices(int** tablero, int** tableroCopia, int alto, int ancho) {
    for (int i = 0; i < alto; i++)
        for (int j = 0; j < ancho; j++)
            if (tablero[i][j] == 1 && tableroCopia[i][j] == 1)
                return false;
    return true;
}


bool puedeBajar(int** tablero, int** copia, int altoTablero, int columnasTablero) {
    for (int j = 0; j < columnasTablero; j++) {
        for (int i = altoTablero - 1; i >= 0; i--) {
            if (tablero[i][j] == 1) {
                if (i >= altoTablero - 1)
                    return false;
                // colisión con pieza estática en copiaMatriz
                if (copia[i + 1][j] == 1)
                    return false;
                break;
            }
        }
    }
    return true;
}

void eliminarFilasLlenas(int** tablero, int altoTablero, int columnasTablero) {
    for (int i = altoTablero - 1; i >= 0; i--) {
        bool filaLlena = true;
        for (int j = 0; j < columnasTablero; j++) {
            if (tablero[i][j] != 1 && tablero[i][j] != 3) {
                filaLlena = false;
                break;
            }
        }

        if (filaLlena) {
            // bajar todas las filas de arriba una posicion
            for (int k = i; k > 0; k--)
                for (int j = 0; j < columnasTablero; j++)
                    tablero[k][j] = tablero[k-1][j];

            // nueva fila vacia en la parte superior
            for (int j = 0; j < columnasTablero; j++) {
                if (j == 0 || j == columnasTablero - 1)
                    tablero[0][j] = 3;
                else
                    tablero[0][j] = 0;
            }

            // revisar la misma fila de nuevo
            i++;
        }
    }
}


void verificarGameOver(int** matriz, int** copia, int alto, int ancho) {
    for (int i = 0; i < alto; i++)
        for (int j = 0; j < ancho + 2; j++)
            if (matriz[i][j] == 1 && copia[i][j] == 1) {
                cout << "Game Over" << endl;
                exit(0);
            }
}


int** rotarPieza(int** pieza, int filas, int columnas) {
    int** rotada = new int*[columnas];
    for (int i = 0; i < columnas; i++) {
        rotada[i] = new int[filas];
        for (int j = 0; j < filas; j++)
            rotada[i][j] = pieza[filas - 1 - j][i];
    }
    for (int i = 0; i < filas; i++) delete[] pieza[i];
    delete[] pieza;
    return rotada;
}

int** generarPiezaAleatoria() {
    srand(time(0));
    int figura = rand() % 7 + 1; // del 1 al 5
    int rotaciones = rand() % 5;  // del 0 al 4

    int** pieza;
    switch (figura) {
    case 1: pieza = Figura1(4, 4); break;
    case 2: pieza = Figura2(4, 4); break;
    case 3: pieza = Figura3(4, 4); break;
    case 4: pieza = Figura4(4, 4); break;
    case 5: pieza = Figura5(4, 4); break;
    case 6: pieza = Cuadrado(4, 4); break;
    case 7: pieza = Linea(4, 4); break;
    }

    for (int r = 0; r < rotaciones; r++)
        pieza = rotarPieza(pieza, 4, 4);

    return pieza;
}



void liberarMatriz(int** matriz, int alto) {
    for (int i = 0; i < alto; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
