#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Equipo.h"
#include "Partido.h"

using namespace std;

class Grupo{

private:
    char letra;
    Equipo* equipos[4];
    Partido* partidos[6];

public:
    Grupo(char l='A');

    void setEquipo(int pos, Equipo* eq);

    void generarPartidos();
    void simularGrupo();
    void mostrarTabla();
};

#endif // GRUPO_H
