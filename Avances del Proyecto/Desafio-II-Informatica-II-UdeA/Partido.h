#ifndef PARTIDO_H
#define PARTIDO_H
#include <iostream>
#include <string>
#include "Equipo.h"

using namespace std;
class Partido{
private:
    Equipo* equipo1;
    Equipo* equipo2;
    int goles1;
    int goles2;
    string fecha;
    string estadio;
    int goleadores1[11];
    int goleadores2[11];
    int cantGoleadores1;
    int cantGoleadores2;
    double posesion1;
    double posesion2;
    string arbitros[3];
    string fase;

public:

    Partido(Equipo* eq1, Equipo* eq2, string fase, string estadio);
    ~Partido();

    void simular();
    void mostrar();
    void setFecha(string f);
    Equipo* getEquipo1();
    Equipo* getEquipo2();

    void setEstadio(string e);
    void setArbitro(int i, string a);
};

#endif // PARTIDO_H