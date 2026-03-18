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

int main() {
    int ancho, alto;

    // Bucle para validar ancho
    do {
        cout << "Ingresa el ancho de la matriz (minimo 8 y multiplo de 8): ";
        cin >> ancho;
        if (ancho < 8 || ancho % 8 != 0) {
            cout << "Error: el ancho debe ser al menos 8 y multiplo de 8." << endl;
        }
    } while (ancho < 8 || ancho % 8 != 0);

    // Bucle para validar alto
    do {
        cout << "Ingresa el alto de la matriz (minimo 8): ";
        cin >> alto;
        if (alto < 8) {
            cout << "Error: el alto debe ser al menos 8." << endl;
        }
    } while (alto < 8);

    // Crear matriz
    char** matriz = crearMatriz(ancho, alto);

    cout << "Matriz creada de " << alto << " filas y " << ancho + 2 << " columnas (con limites):" << endl;
    imprimirMatriz(matriz, ancho, alto);

    liberarMatriz(matriz, alto);

    return 0;
}
