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

//sobrecarga de operador, xd
bool Equipo::operator<(const Equipo& otro)const{
    if(this->getPuntos()!=otro.getPuntos())
        return this ->getPuntos()>otro.getPuntos();
    if(this->getDiferenciaGoles()!=otro.getDiferenciaGoles())
        return this ->getDiferenciaGoles()> otro.getDiferenciaGoles();

    return this ->golesFavor >otro.golesFavor;
}


//getters

string Equipo::getNombrePais()const {return nombrePais;}
int Equipo::getRanking()const {return ranking;}
int Equipo::getGolesFavor() const{return golesFavor;}
int Equipo::getGolesContra()const{return golesContra;}

//calculos para la tabla
int Equipo::getPuntos()const {return(ganados*3)+(empatados *1);}
int Equipo::getDiferenciaGoles()const{return golesFavor-golesContra;}

//retornamos el puntero al jugador para simular sus eventos del partido
Jugador* Equipo::getJugador(int Indice){
    if(Indice >=0 && Indice <cantidadJugadores)return &jugadores[Indice];
    return nullptr;
}

//setters
void Equipo::setNombrePais(string nombre){nombrePais=nombre;}
void Equipo::setRanking(int r){ranking = r;}

//vamos actualizando el historial del equipo despues de un partido
void Equipo::registrarPartido(int golesAnotados, int golesRecibidos){
    golesFavor += golesAnotados;
    golesContra += golesRecibidos;
    if (golesAnotados >golesRecibidos)ganados++;
    else if (golesAnotados==golesRecibidos)empatados++;
    else perdidos++;
}