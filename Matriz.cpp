#include "Matriz.h"
#include <iostream>
#include "Piezas.h"
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


/*void imprimirMatriz(int** matriz, int filas, int columnas) {


    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas + 2; j++) {
            if (matriz[i][j] == 0) cout << ".";
            else if (matriz[i][j] == 3) cout << "|";
        }
        cout << endl;
    }
}*/

int** insertarPieza(int** tablero, int altoTablero, int anchoTablero,
                    int altoPieza, int anchoPieza, int valorFigura) {
    int columnasTablero = anchoTablero + 2;
    int espacio=0;

    // Generar la pieza automáticamente con Cuadrado (o cualquier otra función)
    int** pieza = Figura1(altoPieza, anchoPieza);

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

int** moverPieza(int** tablero, int altoTablero, int anchoTablero, int accion) {
    int columnasTablero = anchoTablero + 2;

    // Crear una copia temporal del tablero con todo igual
    int** nuevoTablero = new int*[altoTablero];
    for (int i = 0; i < altoTablero; i++) {
        nuevoTablero[i] = new int[columnasTablero];
        for (int j = 0; j < columnasTablero; j++) {
            nuevoTablero[i][j] = tablero[i][j];
        }
    }

    // Limpiar las posiciones actuales de la pieza (los 1)
    for (int i = 0; i < altoTablero; i++) {
        for (int j = 0; j < columnasTablero; j++) {
            if (tablero[i][j] == 1) {
                nuevoTablero[i][j] = 0; // espacio vacío
            }
        }
    }

    bool puedeMover = true;

    // Antes de mover, comprobamos si hay borde lateral
    if (accion == 1) { // izquierda
        for (int i = 0; i < altoTablero; i++) {
            for (int j = 0; j < columnasTablero; j++) {
                if (tablero[i][j] == 1 && tablero[i][j-1] == 3) {
                    puedeMover = false;
                }
            }
        }
    } else if (accion == 2) { // derecha
        for (int i = 0; i < altoTablero; i++) {
            for (int j = 0; j < columnasTablero; j++) {
                if (tablero[i][j] == 1 && tablero[i][j+1] == 3) {
                    puedeMover = false;
                }
            }
        }
    }

    // Reubicar la pieza según la acción
    for (int i = 0; i < altoTablero; i++) {
        for (int j = 0; j < columnasTablero; j++) {
            if (tablero[i][j] == 1) {
                if (accion == 1 && j > 1 && puedeMover) { // izquierda
                    nuevoTablero[i][j-1] = 1;
                } else if (accion == 2 && j < columnasTablero-2 && puedeMover) { // derecha
                    nuevoTablero[i][j+1] = 1;
                } else if (accion == 3 && i < altoTablero-1) { // abajo
                    nuevoTablero[i+1][j] = 1;
                } else if (accion == 4) {
                    // 1. Detectar límites de la pieza
                    int minI = altoTablero, maxI = -1, minJ = columnasTablero, maxJ = -1;
                    for (int i = 0; i < altoTablero; i++) {
                        for (int j = 0; j < columnasTablero; j++) {
                            if (tablero[i][j] == 1) {
                                if (i < minI) minI = i;
                                if (i > maxI) maxI = i;
                                if (j < minJ) minJ = j;
                                if (j > maxJ) maxJ = j;
                            }
                        }
                    }

                    int altoPieza = maxI - minI + 1;
                    int anchoPieza = maxJ - minJ + 1;

                    // 2. Extraer submatriz
                    int** pieza = new int*[altoPieza];
                    for (int i = 0; i < altoPieza; i++) {
                        pieza[i] = new int[anchoPieza];
                        for (int j = 0; j < anchoPieza; j++) {
                            pieza[i][j] = tablero[minI + i][minJ + j];
                        }
                    }

                    // 3. Simular rotación
                    int** rotada = new int*[anchoPieza];
                    for (int i = 0; i < anchoPieza; i++) {
                        rotada[i] = new int[altoPieza];
                        for (int j = 0; j < altoPieza; j++) {
                            rotada[i][j] = pieza[altoPieza - 1 - j][i];
                        }
                    }

                    // 4. Comprobar colisiones
                    bool puedeRotar = true;
                    for (int i = 0; i < anchoPieza; i++) {
                        for (int j = 0; j < altoPieza; j++) {
                            if (rotada[i][j] == 1) {
                                int tableroI = minI + i;
                                int tableroJ = minJ + j;

                                // fuera de límites verticales
                                if (tableroI >= altoTablero) {
                                    puedeRotar = false;
                                }
                                // choque contra borde lateral
                                else if (tablero[tableroI][tableroJ] == 3) {
                                    puedeRotar = false;
                                }
                                // choque contra otro 1 que no pertenece a la pieza actual
                                else if (tablero[tableroI][tableroJ] == 1 &&
                                         !(tableroI >= minI && tableroI <= maxI &&
                                           tableroJ >= minJ && tableroJ <= maxJ)) {
                                    puedeRotar = false;
                                }
                            }
                        }
                    }

                    // 5. Aplicar rotación solo si es válida
                    if (puedeRotar) {
                        for (int i = 0; i < anchoPieza; i++) {
                            for (int j = 0; j < altoPieza; j++) {
                                if (rotada[i][j] == 1) {
                                    nuevoTablero[minI + i][minJ + j] = 1;
                                }
                            }
                        }
                    } else {
                        // si no puede rotar, se deja igual
                        for (int i = 0; i < altoTablero; i++) {
                            for (int j = 0; j < columnasTablero; j++) {
                                if (tablero[i][j] == 1) {
                                    nuevoTablero[i][j] = 1;
                                }
                            }
                        }
                    }

                    // Liberar memoria temporal
                    for (int i = 0; i < altoPieza; i++) delete[] pieza[i];
                    delete[] pieza;
                    for (int i = 0; i < anchoPieza; i++) delete[] rotada[i];
                    delete[] rotada;

                } else {
                    // si no puede moverse, se queda en el mismo sitio
                    nuevoTablero[i][j] = 1;
                }
            }
        }
    }

    // Liberar el tablero anterior
    for (int i = 0; i < altoTablero; i++) {
        delete[] tablero[i];
    }
    delete[] tablero;

    return nuevoTablero;
}













void liberarMatriz(int** matriz, int alto) {
    for (int i = 0; i < alto; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
