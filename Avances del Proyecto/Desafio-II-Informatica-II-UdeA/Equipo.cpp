#include "Equipo.h"

Equipo::Equipo()

{
    nombrePais="";
    ranking=0;

    golesFavor=0;
    golesContra=0;
    ganados=0;
    empatados=0;
    perdidos=0;

    cantidadJugadores=26;

    jugadores = new Jugador[cantidadJugadores];
}

Equipo::~Equipo()

{
    delete[] jugadores;
}


void Equipo::inicializarJugadores(int totalGoles)

{
    for (int i = 0; i < cantidadJugadores; i++)

    {
        jugadores[i].setNombre("nombre"+to_string(i+1));
        jugadores[i].setApellido("apellido"+to_string(i+1));
        jugadores[i].setNumero(i+1);
    }

    int golesPorJugador=totalGoles/cantidadJugadores;

    for (int i=0; i<cantidadJugadores; i++)

    {
        for (int j=0; j<golesPorJugador; j++)

        {
            jugadores[i].anotarGol();
        }
    }
}


void Equipo::mostrarEquipo()

{
    cout << "Pais: "<<nombrePais<<endl;
    cout << "Ranking: "<<ranking<<endl;

    for (int i=0; i<cantidadJugadores; i++)

    {
        jugadores[i].mostrar();
    }
}