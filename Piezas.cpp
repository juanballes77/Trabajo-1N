#include "Piezas.h"
#include <iostream>
#include <cctype> // para toupper
using namespace std;

char pedirOpcion() {
    char opcion;
    bool valido = false;

    do {
        cout << "Accion: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir:" << endl;
        cout << "Ingresa una opcion: ";
        cin >> opcion;


        opcion = toupper(opcion); // Convertir a mayuscula para validar

        switch (opcion) {
        case 'A':
        case 'D':
        case 'S':
        case 'W':
        case 'Q':
            valido = true;
            break;
        default:
            cout << "Entrada invalida. Intenta de nuevo" << endl;
        }
    } while (!valido);

    return opcion;
}

