#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include "Jugador.h"
using namespace std;

int getGolesFavor();
int getGolesContra();
string getNombre();

void sumarGolesFavor(int g);
void sumarGolesContra(int g);

void sumarVictoria();
void sumarEmpate();
void sumarDerrota();
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

    int getGolesFavor();
    int getGolesContra();
    string getNombre();

    void sumarGolesFavor(int g);
    void sumarGolesContra(int g);

    void sumarVictoria();
    void sumarEmpate();
    void sumarDerrota();
};

#endif // EQUIPO_H
