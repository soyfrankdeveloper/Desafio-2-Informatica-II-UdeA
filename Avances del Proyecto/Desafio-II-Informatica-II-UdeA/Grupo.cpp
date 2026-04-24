#include "Grupo.h"

Grupo::Grupo(char l)

{
    letra = l;

    for(int i=0;i<4;i++) equipos[i]=nullptr;
    for(int i=0;i<6;i++) partidos[i]=nullptr;
}

void Grupo::setEquipo(int pos, Equipo* eq)

{
    if(pos>=0 && pos<4)
        equipos[pos]=eq;
}

void Grupo::generarPartidos(){

    int k=0;

    for(int i=0;i<4;i++)

    {
        for(int j=i+1;j<4;j++)

        {
            partidos[k]= new Partido(equipos[i], equipos[j], "fecha", "estadio");
            k++;
        }
    }
}

void Grupo::simularGrupo()

{

    cout<<"Grupo "<<letra<<endl;

    for(int i=0;i<6;i++)

    {
        partidos[i]->simular();
    }
}

void Grupo::mostrarTabla(){

    cout<<"\nTabla Grupo "<<letra<<endl;

    for(int i=0;i<4;i++){
        cout<<equipos[i]->getNombrePais()<<" | "
             <<"Pts: "<<equipos[i]->getPuntos()<<" | "
             <<"DG: "<<equipos[i]->getDiferenciaGoles()<<endl;
    }
}