#include <iostream>
#include "Matriz.h"
#include "Piezas.h"
using namespace std;

int main() {
    int ancho, alto;
    char entrada;

    do {
        cout << "Ingresa el ancho del tablero: ";
        cin >> ancho;
        if (ancho < 8 || ancho % 8 != 0) {
            cout << "Error: el ancho debe ser al menos 8 y multiplo de 8" << endl;
        }
    } while (ancho < 8 || ancho % 8 != 0);

    // Bucle para validar alto
    do {
        cout << "Ingresa el alto del tablero: ";
        cin >> alto;
        if (alto < 8) {
            cout << "Error: el alto debe ser al menos 8" << endl;
        }
    } while (alto < 8);

    cout<<endl;

    char** matriz = crearMatriz(ancho, alto);
    imprimirMatriz(matriz, ancho, alto);
    pedirOpcion();




    liberarMatriz(matriz, alto);
    return 0;
}
