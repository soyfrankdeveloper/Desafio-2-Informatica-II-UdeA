#include "Jugador.h"


// Constructor: inicializa estadísticas en 0
Jugador::Jugador()

{
    nombre="";
    apellido="";
    numero=0;
    goles=0;
    minutos=0;
    amarillas=0;
    rojas=0;
    faltas=0;
    asistencias = 0;
}


//getters
int Jugador::getMinutos(){ return minutos; }
int Jugador::getAmarillas(){ return amarillas; }
int Jugador::getRojas(){ return rojas; }
int Jugador::getFaltas(){ return faltas; }
int Jugador::getAsistencias(){ return asistencias; }

void Jugador::setNombre(string n)

{
    nombre=n;
}

void Jugador::setApellido(string a)

{
    apellido=a;
}

void Jugador::setNumero(int num)

{
    numero=num;
}


string Jugador::getNombre()

{
    return nombre;
}

string Jugador::getApellido()

{
    return apellido;
}

int Jugador::getNumero()

{
    return numero;
}

int Jugador::getGoles()

{
    return goles;
}


// Aumenta en 1 el número de goles del jugador
void Jugador::anotarGol()

{
    goles++;
}


// Suma minutos jugados al jugador
void Jugador::jugarPartido(int minutosJugados)

{
    minutos += minutosJugados;
}


// Registra una tarjeta amarilla
void Jugador::recibirAmarilla()

{
    amarillas++;
}


// Registra una tarjeta roja
void Jugador::recibirRoja()

{
    rojas++;
}


// Registra una falta cometida
void Jugador::hacerFalta()

{
    faltas++;
}


// Muestra los datos del jugador (nombre, número, goles)
void Jugador::mostrar()

{
    cout<<numero<<" - "<< nombre<<" "<< apellido
         << " | Goles: " <<goles<< endl;
}