#include "Jugador.h"

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
}

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


void Jugador::anotarGol()

{
    goles++;
}

void Jugador::jugarPartido(int minutosJugados)

{
    minutos += minutosJugados;
}

void Jugador::recibirAmarilla()

{
    amarillas++;
}

void Jugador::recibirRoja()

{
    rojas++;
}

void Jugador::hacerFalta()

{
    faltas++;
}

void Jugador::mostrar()

{
    cout<<numero<<" - "<< nombre<<" "<< apellido
         << " | Goles: " <<goles<< endl;
}