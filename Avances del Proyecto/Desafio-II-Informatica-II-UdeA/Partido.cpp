#include "Partido.h"
#include <cmath>
#include <cstdlib>

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

    //ponemos una validacion para evitar la divicion por cero por si un equipo no tiene goles
    if(gfA==0) gfA=1; if(gcB==0)gcB=1;
    if(gfB==0) gfB=1; if(gcA==0)gcA=1;

    double lambdaA=MU*pow(gfA/MU, ALPHA)*pow(gcB/MU,BETA);
    double lambdaB=MU*pow(gfB/MU, ALPHA)*pow(gcA/MU,BETA);

    int topeGolesA=(int)round(lambdaA);
    int topeGolesB=(int)round(lambdaB);

    //goles
    goles1=0;
    goles2=0;

    //simulacion de equipo 1
    for(int i=0;i<11;i++){
        Jugador*jug=equipo1->getJugador(i);
        jug->jugarPartido(90);      //tiempo promedio de juego es 90 minutos

        if(goles1<topeGolesA){
            if(rand()%100<4){
                jug->anotarGol();
                goles1++;
            }
        }
        //tarjetass
        //probabilidades de la primera amarilla es de un 6% y de una segunda 1.15%
        //pd: usamos rand()%10000 para mejorar los decimales(1.15=115 de 10000)
        int pAmarilla=rand()%10000;
        if (pAmarilla<600){             //6% primera amarilla
            jug->recibirAmarilla();
            if (rand()%10000 <115){     //1.15% segunda amarilla
                jug->recibirAmarilla();
                jug->recibirRoja();         //damos una roja por 2 amarillas

            }

        }

        //faltas
        int pFaltas=rand()%10000;
        if (pFaltas<1300){          //13% primera falta
            jug->hacerFalta();
            if(rand()%10000<275){   //2.75% segunda
                jug->hacerFalta();
                if(rand()%10000<70){  //0.7% tercera
                    jug->hacerFalta();

                }
            }
        }
    }

    //equipo2
    for(int i=0; i<11;i++){
        Jugador* jug=equipo2->getJugador(i);
        jug->jugarPartido(90);

        //goles
        if(goles2<topeGolesB){
            if(rand()%100<4){
                jug->anotarGol();
                goles2++;
            }
        }

        //tarjetas
        int pAmarilla=rand()%10000;
        if(pAmarilla<600){
            jug->recibirAmarilla();
            if(rand()%10000<115){
                jug->recibirAmarilla();
                jug->recibirRoja();
            }
        }
        //faltas
        int pFalta=rand()%10000;
        if(pFalta<1300){
            jug->hacerFalta();
            if(rand()%10000<275){
                jug->hacerFalta();
                if(rand()%10000<70){
                    jug->hacerFalta();
                }
            }
        }
    }
    equipo1->registrarPartido(goles1, goles2);
    equipo2->registrarPartido(goles2, goles1);
}