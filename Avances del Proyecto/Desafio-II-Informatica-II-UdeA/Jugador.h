#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador

{

private:

    string nombre;
    string apellido;
    int numero;

    int goles;
    int minutos;
    int amarillas;
    int rojas;
    int faltas;
    int asistencias;

public:

    Jugador();

    void setNombre(string n);
    void setApellido(string a);
    void setNumero(int num);

    string getNombre();
    string getApellido();
    int getNumero();
    int getGoles();
    int getAsistencias() const { return asistencias; }
    int getMinutos();
    int getAmarillas();
    int getRojas();
    int getFaltas();
    int getAsistencias();

    void anotarGol();
    void jugarPartido(int minutosJugados);
    void recibirAmarilla();
    void recibirRoja();
    void hacerFalta();

    void mostrar();

};

#endif // JUGADOR_H
