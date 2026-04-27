#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include <string>
#include "Jugador.h"
using namespace std;


class Equipo

{
private:
    string nombrePais;
    int ranking;
    string confederacion;
    char grupo;


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

    bool operator<(const Equipo& otro)const;

    //getters
    string getNombrePais()const;
    int getRanking()const;
    int getGolesFavor()const;
    int getGolesContra()const;
    int getPuntos()const;
    int getDiferenciaGoles()const;
    int getGanados()const;
    int getEmpatados()const;
    int getPerdidos()const;
    int getPartidosJugados()const;
    char getGrupo() const { return grupo; }
    string getConfederacion() const;
    void setConfederacion(string c);


    Jugador* getJugador(int Indice); //para sacar los 11 titulares

    //setters
    void setNombrePais(string nombre);
    void setRanking(int r);
    void setGrupo(char g){ grupo = g; }
    void registrarPartido(int golesAnotados, int golesRecibidos);
};

#endif // EQUIPO_H
