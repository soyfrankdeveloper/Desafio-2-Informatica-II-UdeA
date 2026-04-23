#include "Partido.h"
#include <cmath>
#include <cstdlib>
#include <iostream>

Partido::Partido(Equipo*eq1, Equipo*eq2,string f, string est){
    equipo1=eq1;
    equipo2=eq2;
    fecha=f;
    estadio=est;
    goles1=0;
    goles2=0;
}

Partido::~Partido(){
    //lo tiramos vacio para proteger la memoria dinamica del torneo
}

void Partido::simular(){
    if (equipo1==nullptr || equipo2==nullptr)return;

    const double MU=1.35;
    const double ALPHA=0.6;
    const double BETA=0.4;

    //obtenemos los datos historicos
    double gfA=equipo1->getGolesFavor();
    double gcB=equipo2->getGolesContra();

    double gfB=equipo2->getGolesFavor();
    double gcA=equipo1->getGolesContra();

    goles1=0;
    goles2=0;

    //ponemos una validacion para evitar la divicion por cero por si un equipo no tiene goles
    if(gfA==0) gfA=1; if(gcB==0)gcB=1;
    if(gfB==0) gfB=1; if(gcA==0)gcA=1;

    double lambdaA=MU*pow(gfA/MU, ALPHA)*pow(gcB/MU,BETA);
    double lambdaB=MU*pow(gfB/MU, ALPHA)*pow(gcA/MU,BETA);

    int topeGolesA=(int)round(lambdaA);
    int topeGolesB=(int)round(lambdaB);

    //agregamos aleatoriedad a los goles
    goles1=rand()%(topeGolesA+1);
    goles2=rand()%(topeGolesB+1);

    //actualizamos estadisticas de los equipos
    equipo1->sumarGolesFavor(goles1);
    equipo1->sumarGolesContra(goles2);

    equipo2->sumarGolesFavor(goles2);
    equipo2->sumarGolesContra(goles1);

    if(goles1>goles2){
        equipo1->sumarVictoria();
        equipo2->sumarDerrota();
    }else if(goles1<goles2){
        equipo2->sumarVictoria();
        equipo1->sumarDerrota();
    }else{
        equipo1->sumarEmpate();
        equipo2->sumarEmpate();
    }

    //mostramos resultado del partido
    cout<<goles1<<" - "<<goles2<<endl;

}