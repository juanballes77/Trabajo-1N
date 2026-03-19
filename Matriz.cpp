#include "Matriz.h"
#include <iostream>
using namespace std;

char** crearMatriz(int ancho, int alto) {
    char** matriz = new char*[alto];
    for (int i = 0; i < alto; i++) {
        matriz[i] = new char[ancho + 2];
        for (int j = 0; j < ancho + 2; j++) {
            if (j == 0 || j == ancho + 1) {
                matriz[i][j] = '|';
            } else {
                matriz[i][j] = '.';
            }

        }
    }

    return matriz;
}

void imprimirMatriz(char** matriz, int ancho, int alto) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho + 2; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void liberarMatriz(char** matriz, int alto) {
    for (int i = 0; i < alto; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}
