#include <iostream>
using namespace std;

// Funcion que crea la matriz dinamicamente con punteros
char** crearMatriz(int ancho, int alto) {
    // Reservar memoria para las filas
    char** matriz = new char*[alto];
    for (int i = 0; i < alto; i++) {
        matriz[i] = new char[ancho + 2]; // +2 por las columnas de limite
        // Inicializar con '.'
        for (int j = 0; j < ancho + 2; j++) {
            if (j == 0 || j == ancho + 1) {
                matriz[i][j] = '|'; // columnas de limite
            } else {
                matriz[i][j] = '.';
            }
        }
    }
    return matriz;
}

// Funcion para imprimir la matriz
void imprimirMatriz(char** matriz, int ancho, int alto) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho + 2; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

// Funcion para liberar la memoria
void liberarMatriz(char** matriz, int alto) {
    for (int i = 0; i < alto; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int main() {
    int ancho, alto;

    cout << "Ingresa el ancho de la matriz (minimo 8 y multiplo de 8): ";
    cin >> ancho;

    cout << "Ingresa el alto de la matriz (minimo 8): ";
    cin >> alto;

    // Validaciones
    if (ancho < 8 || ancho % 8 != 0) {
        cout << "Error: el ancho debe ser al menos 8 y multiplo de 8." << endl;
        return 1;
    }

    if (alto < 8) {
        cout << "Error: el alto debe ser al menos 8." << endl;
        return 1;
    }

    // Crear matriz
    char** matriz = crearMatriz(ancho, alto);

    cout << "Matriz creada de " << alto << " filas y " << ancho + 2 << " columnas (con limites):" << endl;
    imprimirMatriz(matriz, ancho, alto);

    // Liberar memoria
    liberarMatriz(matriz, alto);

    return 0;
}
