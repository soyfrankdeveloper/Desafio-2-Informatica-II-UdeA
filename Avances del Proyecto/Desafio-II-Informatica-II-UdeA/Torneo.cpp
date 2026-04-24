#include "Torneo.h"
#include <sstream>
#include <cstdlib>

//funcion auxiliar para eliminatorias
static Equipo* jugarLlave(Equipo* eq1, Equipo* eq2, string fase){
    if (!eq1 || !eq2)return eq1 ? eq1:eq2;      //el ? es un operador ternario, es un if-else acortado.

    cout<<" >>>"<< eq1->getNombrePais()<< " Vs "<< eq2->getNombrePais()<<" (" << fase<<")"<<endl;

    //hacemos un objeto local para simular sin dejar basura residual en la memoria
    Partido p(eq1, eq2, fase, "Estadio UdeA");

    int ptsAntes= eq1->getPuntos();
    p.simular();
    int ptsGanados =eq1-> getPuntos()-ptsAntes;

    if(ptsGanados ==3){
        cout<< "  [avanza: "<<eq1->getNombrePais()<< " en tiempo reglamentario";
        return eq1;
    }

    if(ptsGanados ==0){
        cout<< "  [avanza: "<<eq2->getNombrePais()<< " en tiempo reglamentario";
        return eq2;
    }

    //sumó 1 punto, empataron. penales con probabilidad 50/50
    if(rand()%2==0){
        cout<< "   [empate. Avanza "<< eq1->getNombrePais()<< " por Penales]";
        return eq1;
    }else{
        cout<< "    [empate. Avanza "<< eq2->getNombrePais()<< " por Penales]";
        return eq2;
    }

}
Torneo::Torneo(){
    for (int i=0; i<32; i++) equipos[i]=nullptr;
    for(int i=0; i<8;i++){
        char letra ='A'+i;
        grupos[i]=new Grupo(letra);
    }
    //inicializamos punteros de fase final, xd
    for(int i=0; i<16; i++) octavos[i] = nullptr;
    for(int i=0; i<8; i++) cuartos[i] = nullptr;
    for(int i=0; i<4; i++) semis[i] = nullptr;
    for(int i=0; i<2; i++) finalistas[i] = nullptr;
    campeon = nullptr;

}
Torneo::~Torneo(){
    for(int i=0; i<32;i++){
        if(equipos[i]!= nullptr)delete equipos[i];//pd: nullptr es un puntero vacio que no apunta a ninguna direccion de memoria

    }
    for(int i=0; i<8;i++){
        if(equipos[i]!= nullptr)delete equipos[i];//pd: no le aplicamos delete pq rompemos la memoria
    }


}
bool Torneo::cargarEquiposDesdeCSV(string rutaArchivo){
    ifstream archivo(rutaArchivo);
    string linea;

    if(!archivo.is_open())return false;

    int i=0;
    while(getline(archivo, linea)&& i<32){
        stringstream stream(linea);
        string pais, rankingStr;
        getline(stream, pais, ',');
        getline(stream, rankingStr, ',');

        if (!pais.empty() && pais != "Pais") {
            equipos[i] = new Equipo();
            equipos[i]->setNombrePais(pais);

            try {
                equipos[i]->setRanking(stoi(rankingStr));
            } catch(...) {
                equipos[i]->setRanking(0);
            }

            equipos[i]->inicializarJugadores(50); // Le damos un historial base de goles a la plantilla
            i++;
        }
    }
    archivo.close();
    return true;
}

void Torneo::armarGrupos(){
    int indexEquipo=0;
    for (int i=0; i<8; i++){
        for(int j=0; j<4; j++){
            if (indexEquipo <32&& equipos[indexEquipo]!=nullptr){
                grupos[i]->setEquipo(j, equipos[indexEquipo]);
                indexEquipo++;
            }
        }
        grupos[i]->generarPartidos();

    }
}
void Torneo::simularFaseGrupos(){
    for(int i=0;i<8;i++){
        grupos[i]->simularGrupo();
        grupos[i]->mostrarTabla();
    }
}

void Torneo::simularFasesFinales(){
    cout << "\n========================================" << endl;
    cout << "       INICIANDO FASES ELIMINATORIAS    " << endl;
    cout << "========================================" << endl;

    //extraemos a los 16 clasificados luego de la fase de grupos.
    int k=0;
    for (int i=0;i<8;i+=2){
        octavos[k++] = grupos[i]->getClasificado(0);
        octavos[k++] = grupos[i+1]->getClasificado(1);
        octavos[k++] = grupos[i+1]->getClasificado(0);
        octavos[k++] = grupos[i]->getClasificado(1);
    }

    // 2. OCTAVOS DE FINAL
    cout << "\n--- OCTAVOS DE FINAL ---" << endl;
    for(int i = 0; i < 8; i++) cuartos[i] = jugarLlave(octavos[i*2], octavos[i*2 + 1], "Octavos");

    // 3. CUARTOS DE FINAL
    cout << "\n--- CUARTOS DE FINAL ---" << endl;
    for(int i = 0; i < 4; i++) semis[i] = jugarLlave(cuartos[i*2], cuartos[i*2 + 1], "Cuartos");

    // 4. SEMIFINALES
    cout << "\n--- SEMIFINALES ---" << endl;
    for(int i = 0; i < 2; i++) finalistas[i] = jugarLlave(semis[i*2], semis[i*2 + 1], "Semifinal");

    // 5. LA GRAN FINAL
    cout << "\n--- LA GRAN FINAL ---" << endl;
    campeon = jugarLlave(finalistas[0], finalistas[1], "FINAL");

}

void Torneo::mostrarEstadisticasFinales(){
    if(!campeon)return;
    cout << "\n========================================" << endl;
    cout << "          ¡TENEMOS CAMPEON!             " << endl;
    cout << "========================================" << endl;
    cout << " >>>> " << campeon->getNombrePais() << " ES EL CAMPEON DEL MUNDO <<<<" << endl;

    Equipo* equipoMasGoleador=equipos[0];
    Jugador* goleador=nullptr;
    int maxGoles=-1;

    //tiramos un barrido para encontrar al equipo mas goleador y al goleador individual
    for (int i = 0; i < 32; i++) {
        if (equipos[i] != nullptr) {
            if (equipoMasGoleador == nullptr || equipos[i]->getGolesFavor() > equipoMasGoleador->getGolesFavor()) {
                equipoMasGoleador = equipos[i];
            }
            for (int j = 0; j < 26; j++) {
                Jugador* jug = equipos[i]->getJugador(j);
                if (jug != nullptr && jug->getGoles() > maxGoles) {
                    maxGoles = jug->getGoles();
                    goleador = jug;
                }
            }
        }
    }
    cout<< " >>> Estadisticas del torneo"<< endl;
    if(equipoMasGoleador){
        cout<<" Equipo más goleador de la temporada: "<<equipoMasGoleador->getNombrePais()
             <<" ("<< equipoMasGoleador->getGolesFavor()<< " goles."<<endl;
    }
    if (goleador){
        cout<<" >>> Botas de Oro: "<<goleador->getNombre()<<" "<< goleador->getApellido()
        << " con "<< goleador->getGoles()<< " anotaciones."<<endl;

    }
    cout<< "========================================="<<endl;
}
