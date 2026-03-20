#include <iostream>
#include "Matriz.h"
#include "Piezas.h"
using namespace std;

int main() {
    int ancho, alto, accion;
    bool condicion=false;
    char entrada;
    do {
        cout << "Ingresa el ancho del tablero: ";
        cin >> ancho;

        if (cin.fail()) { // si la entrada no es un número
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta lo que quedó en el buffer
            cout << "Error: debes ingresar un numero entero." << endl;
            continue; // vuelve a pedir
        }

        if (ancho < 8 || ancho % 8 != 0) {
            cout << "Error: el ancho debe ser al menos 8 y multiplo de 8" << endl;
        }
    } while (ancho < 8 || ancho % 8 != 0);


    // Bucle para validar alto
    do {
        cout << "Ingresa el alto del tablero: ";
        cin >> alto;

        if (cin.fail()) { // si la entrada no es un numero
            cin.clear();              // limpia el estado de error
            cin.ignore(1000, '\n');   // descarta lo que quedo en el buffer
            cout << "Error: debes ingresar un numero entero" << endl;
            alto = 0; // fuerza a repetir el ciclo
            continue;
        }

        if (alto < 8) {
            cout << "Error: el alto debe ser al menos 8" << endl;
        }
    } while (alto < 8);



    cout<<endl;
    int** matriz = crearMatriz(ancho, alto);
    matriz = insertarPieza(matriz, alto, ancho, 4, 4, 1);

    int** copiaMatriz = crearMatriz(ancho, alto);

    while(true){



        for (int i = 0; i < alto; i++) {
            for (int j = 0; j < ancho + 2; j++) {
                if (matriz[i][j] == 0) cout << ".";
                else if (matriz[i][j] == 3) cout << "|";
                else if (matriz[i][j] == 1) cout << "#";
            }
            cout << endl;
        }

        accion=pedirOpcion();
        switch (accion) {
        case 1:
            // mover izquierda
            matriz=moverPieza(matriz, alto, ancho, 1);
            break;
        case 2:
            // mover derecha
            matriz=moverPieza(matriz, alto, ancho, 2);
            break;
        case 3:
            // mover abajo
            matriz=moverPieza(matriz, alto, ancho, 3);
            break;
        case 4:
            // reservado para futura acción
            matriz=moverPieza(matriz, alto, ancho, 4);
            break;
        default:
            // acción no reconocida
            break;
        }


        if(!puedeBajar(matriz, copiaMatriz, alto, ancho + 2)){
            cout<<"hola"<<endl;

            for (int i = 0; i < alto; i++)
                for (int j = 0; j < ancho + 2; j++)
                    if (matriz[i][j] == 1)
                        copiaMatriz[i][j] = 1;

            for (int i = 0; i < alto; i++) {
                for (int j = 0; j < ancho + 2; j++) {
                    if (copiaMatriz[i][j] == 0) cout << ".";
                    else if (copiaMatriz[i][j] == 3) cout << "|";
                    else if (copiaMatriz[i][j] == 1) cout << "#";
                }
                cout << endl;
            }
            cout << endl;
            eliminarFilasLlenas(copiaMatriz, alto, ancho + 2);

            for (int i = 0; i < alto; i++) {
                for (int j = 0; j < ancho + 2; j++) {
                    if (copiaMatriz[i][j] == 0) cout << ".";
                    else if (copiaMatriz[i][j] == 3) cout << "|";
                    else if (copiaMatriz[i][j] == 1) cout << "#";
                }
                cout << endl;
            }
            cout << endl;

            liberarMatriz(matriz, alto);
            matriz = crearMatriz(ancho, alto);
            matriz = insertarPieza(matriz, alto, ancho, 4, 4, 1);



        }

        if(accion==5){
            liberarMatriz(copiaMatriz, alto);
            liberarMatriz(matriz, alto);
            break;
        }




    }


    return 0;
}
