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
public:
    Partido(Equipo* eq1=nullptr, Equipo* eq2=nullptr, string f= "", string est="");
    ~Partido();

    void simular();
};

#endif // PARTIDO_H