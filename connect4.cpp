/**
 *
 * @file connect4.cpp
 *
 * @brief Trabajo Final informática. Conecta 4.
 *
 *
 * @version 1.0
 * @author Carlos Marín Pérez
 * @date 28-12-2020
 */

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <ctime>


using namespace std;

struct jugador {

    string nombre = "Default";
    char caracter = 'X';
};

struct general {

    int tamX = 0, tamY = 0;
    jugador uno, dos;

};

int partidas = 0; // Comprueba si los jugadores son nuevos o recurrentes
int valTurno; // 0 -> Jugador uno | 1-> Jugador dos

const int MAX = 10;
typedef int tablero[MAX][MAX];


void comienzo(tablero t, general&); //Crea una matriz con bordes y casillas imitando un tablero. (también sirve para resetear)
void datos(general&); // Pide todos los datos necesarios para el correcto funcionamiento del juego.

int aleatorio(); // Elije aleatoriamente cual de los dos jugadores empieza la partida.
void turno(tablero t, general&); // Sistema de turnos
void juego(tablero t, general&); //Introducirá las fichas en el tablero tras recibir la columna validada introducida por el usuario, intervienen los turnos.
bool compruebaColumnas(tablero t, general, int); //Función encargada de comprobar que una columna es o no válida (Llena = False | vacia = true), recibe una columna (número)
void validador(tablero t, general); //Con paso por referencia comprueba que la columna introducida por el usuario existe, recibe una letra y la combierte en el número de la columna si existe.

void visual(tablero t, general); //Función encargada de mostrar el tablero, dependiendo del turno mostrará el nombre del jugador.
bool victoria(tablero t, general); // Función que determina si un jugador ha ganado o perdido, se ejecuta cada turno)


general partida;
tablero t;


// Funcion principal
int main()
{   
    
    char movimiento = ' ';

    cout << "-------------------------------------------------------------" << endl;
    cout << "          Conecta 4 - Trabajo final de informatica           " << endl;
    cout << "    Por Carlos Marin Perez y Alejandro Plasencia Querol      " << endl;
    cout << "-------------------------------------------------------------" << endl;


    if (partidas == 0)
    {
        datos(partida);
    }

    else {

        cout << ".Bienvenidos de Nuevo.";
    }

    comienzo(t, partida);
    while (victoria(t, partida) == false) {

        turno(t, partida);
    }

    visual(t, partida);

    cout << endl;

    if (valTurno == 0)
    {   
        cout << "--------------------------------------------------------------" << endl;

        cout << "Victoria por parte de " << partida.uno.nombre << " o Empate" << endl;

        cout << "--------------------------------------------------------------" << endl << endl;
    }

    else if (valTurno == 1)
    {   
        cout << "--------------------------------------------------------------" << endl;

        cout << "Victoria por parte de  " << partida.dos.nombre << " o Empate" << endl;

        cout << "--------------------------------------------------------------" << endl << endl;
    }

    char opc;

    cout << "Deseas volver a jugar? (S/N)" << endl;
    cin >> opc;

    switch (opc)
    {
    case 's':
    case 'S':
        main();
        break;
    case 'n':
    case 'N':
        cout << "Gracias por jugar, hasta la próxima.";
        break;
    default:
        break;
    }

    return 0;
}

void datos(general& partida){

    cout << endl;
    cout << "Bienvenidos nuevos jugadores!" << endl;
    cout << "Introduzca las dimensiones del tablero (casillas)" << endl;
    
    do
    {

        cout << "El numero de columnas del tablero: ";
        cin >> partida.tamX;

    } while (partida.tamX < 5 || partida.tamX > 10);

    do
    {

        cout << "El numero de filas del tablero: ";
        cin >> partida.tamY;

    } while (partida.tamY < 5 || partida.tamY > 10);

    

    cout << "-JUGADOR 1-" << endl;
    cout << "Nombre: ";
    cin >> partida.uno.nombre;
    cout << "Caracter: ";
    cin >> partida.uno.caracter;

    cout << "-JUGADOR 2-" << endl;
    cout << "Nombre: ";
    cin >> partida.dos.nombre;
    cout << "Caracter: ";
    cin >> partida.dos.caracter;
}

void comienzo(tablero t, general& partida){

    for (int i = 0; i < partida.tamY; i++)
    {
        for (int j = 0; j < partida.tamX; j++)
        {
            t[i][j] = 0;
        }
    }
    
}

int aleatorio() {

    int aleatorio;

    srand(time(0));

    aleatorio = rand() % 2;

    return aleatorio;
}

void turno(tablero t, general& partida){

    if (partidas == 0)
    {
        valTurno = aleatorio();
        partidas = 1;
    }

    if (valTurno == 0)
    {
        valTurno = 1;
    }

    else
    {
        valTurno = 0;
    }

    juego(t, partida);
}

bool compruebaColumnas(tablero t, general partida, int col) {

    bool apto = false;

    if (t[0][col] == 0)
    {
        apto = true;
    }

    else if (t[0][col] == 1 || t[0][col] == 2)
    {
        apto = false;
    }

    return apto;
}

void validador(tablero t, general partida, int& seleccion) {

    char letra;

    do
    {

        cout << endl;
        cout << "Escriba la columna deseada: ";
        cin >> letra;


        switch (letra)
        {

        case 'a':
        case 'A':
            seleccion = 0;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'b':
        case 'B':
            seleccion = 1;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'c':
        case 'C':
            seleccion = 2;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'd':
        case 'D':
            seleccion = 3;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'e':
        case 'E':
            seleccion = 4;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'f':
        case 'F':
            seleccion = 5;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'g':
        case 'G':
            seleccion = 6;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'h':
        case 'H':
            seleccion = 7;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'i':
        case 'I':
            seleccion = 8;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;
        case 'j':
        case 'J':
            seleccion = 9;

            if (compruebaColumnas(t, partida, seleccion) == false)
            {
                cout << "La columna seleccionada esta llena, por favor, elija otra.";
                Sleep(2000);
                visual(t, partida);
                validador(t, partida, seleccion);
            }

            break;

        default:

            cout << "No es posible colocar la ficha en esa posicion";
            Sleep(2000);
            visual(t, partida);
            validador(t, partida, seleccion);
            break;
        }

    } while (compruebaColumnas(t, partida, seleccion) == false);

}

void juego(tablero t, general& partida){

    visual(t, partida);

    char col;
    
    int seleccion = 0;
    validador(t, partida, seleccion);


    if (valTurno == 0 )
    {   
        for (int i = partida.tamY - 1; i >= 0; i--)
        {

            if (t[i][seleccion] == 0)
            {
                t[i][seleccion] = 1;
                i = -1;
            }

        }
    }
    else
    {
        for (int i = partida.tamY - 1; i >= 0; i--)
        {

            if (t[i][seleccion] == 0)
            {
                t[i][seleccion] = 2;
                i = -1;
            }

        }
    }

}

bool victoria(tablero t, general partida) {

    bool estado = false;

    int acomulados = 0;

    //horizontal

    for (int i = 0; i < partida.tamY; i++)
    {
        for (int j = 0; j < partida.tamX; j++)
        {

            //Jugador 1

            if (valTurno == 0)
            {

                if (t[i][j] == 1)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 2)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[i][j] == 2)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 1)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

        }

        acomulados = 0;
    }


    // Vertical

    acomulados = 0;

    for (int i = 0; i < partida.tamX; i++)
    {
        for (int j = 0; j < partida.tamY; j++)
        {

            //Jugador 1

            if (valTurno == 0)
            {

                if (t[j][i] == 1)
                {
                    acomulados += 1;
                }
                else if (t[j][i] == 2)
                {
                    acomulados = 0;
                }
                else if (t[j][i] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[j][i] == 2)
                {
                    acomulados += 1;
                }
                else if (t[j][i] == 1)
                {
                    acomulados = 0;
                }
                else if (t[j][i] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

        }

        acomulados = 0;
    }

    //OBLICUO

    // DESDE abajo

    //1ª parte

    int corte = 3;

    for (int x = corte; x < partida.tamY; x++)
    {
        int j = 0;
        for (int i = x; i >= 0; i--)
        {
            //Jugador 1

            if (valTurno == 0)
            {

                if (t[i][j] == 1)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 2)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[i][j] == 2)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 1)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

            j++;

        }

        acomulados = 0;
    }

    // 2ª Parte

    int comienzo = 1;
    int columna = partida.tamY - 1;
    int i;

    for (int x= comienzo; x < partida.tamX-3; x++)
    {
        i = columna;
        for (int j = x; j < partida.tamY; i--)
        {
            //Jugador 1

            if (valTurno == 0)
            {

                if (t[i][j] == 1)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 2)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[i][j] == 2)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 1)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

            j++;

        }

        acomulados = 0;

    }

    // DESDE arriba

    //1ª parte

    corte = partida.tamY-4;

    for (int x = corte; x >= 0; x--)
    {
        int j = 0;
        for (int i = x; i < partida.tamY; i++)
        {
            //Jugador 1

            if (valTurno == 0)
            {

                if (t[i][j] == 1)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 2)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[i][j] == 2)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 1)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

            j++;

        }

        acomulados = 0;
    }

    // 2ª Parte

    comienzo = 1;
    columna = 0;

    for (int x = comienzo; x < partida.tamX - 3; x++)
    {
        i = columna;
        for (int j = x; j < partida.tamY; i++)
        {
            //Jugador 1

            if (valTurno == 0)
            {

                if (t[i][j] == 1)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 2)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            //Jugador 2

            if (valTurno == 1)
            {

                if (t[i][j] == 2)
                {
                    acomulados += 1;
                }
                else if (t[i][j] == 1)
                {
                    acomulados = 0;
                }
                else if (t[i][j] == 0)
                {
                    acomulados = 0;
                }

            }

            if (acomulados == 4)
            {
                estado = true;
                break;
            }

            j++;

        }

        acomulados = 0;

    }

    // empate

    acomulados = 0;

    for (int j = 0; j < partida.tamX; j++)
    {   
        if (t[0][j] == 1)
        {
            acomulados++;
        }

        else if (t[0][j] == 2)
        {
            acomulados++;
        }

        else if (t[0][j] == 0)
        {
            acomulados = 0;
        }
        
    }

    if (acomulados == partida.tamX)
    {
        estado = true;
    }

    return estado;

}

void visual(tablero t, general partida){

    system("CLS");

    if (valTurno == 0)
    {   
        cout << "------------------------------------------------" << endl;
        cout <<  "Es el turno de " << partida.uno.nombre << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
    }
    else if (valTurno == 1)
    {   
        cout << "------------------------------------------------" << endl;
        cout <<  "Es el turno de " << partida.dos.nombre << endl;
        cout << "------------------------------------------------" << endl;
        cout << endl;
    }
    

    // TABLERO
    for (int i = 0; i < partida.tamY; i++)
    {
        //1ª FILA

        if (i == 0) {

            for (int a = 0; a < partida.tamX; a++) {

                cout << " ";
                cout << " ";

                switch (a)
                {
                case 0:
                    cout << "A";
                    break;
                case 1:
                    cout << "B";
                    break;
                case 2:
                    cout << "C";
                    break;
                case 3:
                    cout << "D";
                    break;
                case 4:
                    cout << "E";
                    break;
                case 5:
                    cout << "F";
                    break;
                case 6:
                    cout << "G";
                    break;
                case 7:
                    cout << "H";
                    break;
                case 8:
                    cout << "I";
                    break;
                case 9:
                    cout << "J";
                    break;
                default:
                    break;
                }

                cout << " ";
            }
            cout << endl;


            cout << "|";
            for (int a = 0; a < partida.tamX; a++) {


                cout << " ";
                cout << " ";
                cout << " ";
                cout << "|";

            }
        }
        cout << endl;

        //2ª FILA

        cout << "|";
        for (int j = 0; j < partida.tamX; j++)
        {

            cout << " ";

            if (t[i][j] == 0)
            {
                cout << " ";
            }

            else if (t[i][j] == 1)
            {
                cout << partida.uno.caracter;
            }

            else if (t[i][j] == 2)
            {
                cout << partida.dos.caracter;
            }

            cout << " ";
            cout << "|";


        }
        cout << endl;

        //3ª FILA
        cout << "|";

        for (int a = 0; a < partida.tamX; a++) {

            cout << "-";
            cout << "-";
            cout << "-";
            cout << "|";
        }
    }

    cout << endl;
}
