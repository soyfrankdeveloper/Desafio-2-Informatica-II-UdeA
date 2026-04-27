#ifndef TORNEO_H
#define TORNEO_H

#include <iostream>
#include <string>
#include <fstream>
#include "Equipo.h"
#include "Grupo.h"
#include "Partido.h"

using namespace std;

class Torneo {
private:
    Equipo* equipos[48];
    Grupo* grupos[12];

    // Punteros para las fases finales
    Equipo* octavos[16];
    Equipo* cuartos[8];
    Equipo* semis[4];
    Equipo* finalistas[2];
    Equipo* campeon;
    Equipo* subcampeon;
    Equipo* tercerLugar;
    Equipo* cuartoLugar;

public:
    Torneo();
    ~Torneo();

    bool cargarEquiposDesdeCSV(string rutaArchivo);
    void armarGrupos();
    void simularFaseGrupos();
    void simularFasesFinales();
    void mostrarEstadisticasFinales();
    void guardarDatos();
    void asignarFechasFaseGrupos();
};

#endif // TORNEO_H
