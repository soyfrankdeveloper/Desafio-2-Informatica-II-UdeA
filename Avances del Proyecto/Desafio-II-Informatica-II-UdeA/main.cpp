#include <iostream>
#include "Torneo.h"

#include <ctime>


using namespace std;

void mostrarMetricas(string funcionalidad, int iteracionesCalculadas) {
    // Calculamos la memoria adaptada al formato de 48 equipos
    int memTorneo = sizeof(Torneo);
    int memEquipos = 48 * sizeof(Equipo);
    int memJugadores = 48 * 26 * sizeof(Jugador);
    int memGrupos = 12 * sizeof(Grupo);
    int memPartidos = 72 * sizeof(Partido); // 12 grupos * 6 partidos = 72

    int variablesLocales = 512; // Margen para punteros locales y arreglos de llaves

    long memoriaTotalBytes = memTorneo + memEquipos + memJugadores + memGrupos + memPartidos + variablesLocales;

    cout << "\n------------------------------------------------" << endl;
    cout << " [METRICAS] - " << funcionalidad << endl;
    cout << " -> Iteraciones estimadas: " << iteracionesCalculadas << endl;
    cout << " -> Memoria en uso: " << memoriaTotalBytes << " bytes" << endl;
    cout << "------------------------------------------------\n" << endl;
}

int main()

{

    srand(time(0));
    Torneo torneo;
    int opcion=-1;

    do {
        cout<<"\n==================================="<<endl;
        cout<<"        UdeA World Cup 2026"<<endl;
        cout<<"==================================="<<endl;
        cout<<"1. Cargar equipos desde CSV"<<endl;
        cout<<"2. Armar grupos"<<endl;
        cout<<"3. Simular fase de grupos"<<endl;
        cout<<"4. Simular fases finales"<<endl;
        cout<<"5. Mostrar estadisticas finales"<<endl;
        cout<<"6. Guardar datos"<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opcion;

        switch(opcion){

        case 1:
            if(torneo.cargarEquiposDesdeCSV("selecciones_clasificadas_mundial.csv")) {
                cout<<"Equipos cargados correctamente"<<endl;
                mostrarMetricas("Carga de Equipos (CSV)", 48);
            } else {
                cout<<"Error al cargar archivo"<<endl;
            }
            break;

        case 2:
            torneo.armarGrupos();
            mostrarMetricas("Armado de Grupos (Sorteo Bombos)", 48 + (12 * 4) + 500);
            break;

        case 3:
            torneo.simularFaseGrupos();
            mostrarMetricas("Simulacion Fase de Grupos", 72 * 22); // 72 partidos * 22 jugadores simulados
            break;

        case 4:
            torneo.simularFasesFinales();
            mostrarMetricas("Simulacion Fases Finales", 32 * 22); // 32 partidos de ronda eliminatoria
            break;

        case 5:
            torneo.mostrarEstadisticasFinales();
            mostrarMetricas("Generacion de Estadisticas", 48 * 26); // Barrido de todos los jugadores
            break;

        case 6:
            torneo.guardarDatos();
            mostrarMetricas("Guardado de Datos...wha", 48 * 26);
            break;

        case 0:
            cout<<"Saliendo..."<<endl;
            break;

        default:
            if(opcion!=-1){
                cout<<"Opcion invalida"<<endl;
            }
        }
    }

    while(opcion!=0);

    return 0;
}