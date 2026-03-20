#include "Piezas.h"
#include <iostream>
#include <cctype> // para toupper
using namespace std;

char pedirOpcion() {
    char opcion;
    int devolver;
    bool valido = false;

    do {
        cout << endl;
        cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir:" << endl;
        cout << "Ingresa una opcion: ";
        cin >> opcion;


        opcion = toupper(opcion); // Convertir a mayuscula para validar

        switch (opcion) {
        case 'A':
            devolver = 1;
            valido = true;
            break;
        case 'D':
            devolver = 2;
            valido = true;
            break;
        case 'S':
            devolver = 3;
            valido = true;
            break;
        case 'W':
            devolver = 4;
            valido = true;
            break;
        case 'Q':
            devolver = 5;
            valido = true;
            break;
        default:
            cout << "Entrada invalida. Intenta de nuevo" << endl;
        }
    } while (!valido);

    return devolver;
}

int** Cuadrado(int filas, int columnas) {
    // Reservar memoria para la matriz
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    // Llenar la matriz con el patrón
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || i == filas-1 || j == 0 || j == columnas-1) {
                matriz[i][j] = 0; // borde gris
            } else if (i == 1 || i == filas-2 || j == 1 || j == columnas-2) {
                matriz[i][j] = 1; // borde negro
            } else {
                matriz[i][j] = 2; // centro amarillo
            }
        }
    }

    return matriz;
}

int** Linea(int filas, int columnas) {
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            if (j == 2) {
                matriz[i][j] = 1; // línea vertical en la tercera columna
            } else {
                matriz[i][j] = 0; // espacio vacío
            }
        }
    }
    return matriz;
}
// Genera una matriz 4x4 con la figura solicitada
int** Figura1(int filas , int columnas ) {

    int** matriz = new int*[filas];

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = 0; // inicializar todo en 0
        }
    }

    // Fila 1: 1110
    matriz[1][0] = 1;
    matriz[1][1] = 1;
    matriz[1][2] = 1;
    matriz[1][3] = 0; // explícito, aunque ya está en 0

    // Fila 2: 0010 → un 1 en la tercera columna (índice 2)
    matriz[2][2] = 1;

    return matriz;
}

