#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include "Jugador.h"
using namespace std;

class Equipo

{
private:
    string nombrePais;
    int ranking;

    int golesFavor;
    int golesContra;
    int ganados;
    int empatados;
    int perdidos;

    Jugador* jugadores;
    int cantidadJugadores;

public:

    Equipo();

    ~Equipo();

    void inicializarJugadores(int totalGoles);
    void mostrarEquipo();
};

#endif // EQUIPO_H
