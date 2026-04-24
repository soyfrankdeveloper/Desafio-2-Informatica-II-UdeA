#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Equipo.h"
#include "Partido.h"

using namespace std;

class Grupo{

private:
    char letra;
    Equipo* equipos[4];
    Partido* partidos[6];

public:
    Grupo(char l='A');
    ~Grupo();       //vamos limpiando la memoria,xd

    void setEquipo(int pos, Equipo* eq);

    void generarPartidos();
    void simularGrupo();
    void mostrarTabla();

    Equipo* getClasificado(int posicion);
};

template <class T>
void ordenarArregloDescendente(T* arreglo[],int tam){
    for(int i=0; i<tam -1;i++){
        for(int j=0; j<tam-i-1;j++){
            if(*arreglo[j+1]<*arreglo[j]){
                T* aux = arreglo[j];
                arreglo[j]=arreglo[j+1];
                arreglo[j+1]=aux;
            }
        }
    }
}


#endif // GRUPO_H