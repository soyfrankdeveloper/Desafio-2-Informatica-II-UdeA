#include "Partido.h"
#include <cmath>
#include <cstdlib>


// Constructor: inicializa equipos, fase, estadio y valores del partido
Partido::Partido(Equipo* eq1, Equipo* eq2, string f, string est)
{
    equipo1 = eq1;
    equipo2 = eq2;
    fase = f;
    estadio = est;
    fecha = ""; // se asigna después

    goles1 = 0;
    goles2 = 0;

    arbitros[0] = "codArbitro1";
    arbitros[1] = "codArbitro2";
    arbitros[2] = "codArbitro3";

    cantGoleadores1 = 0;
    cantGoleadores2 = 0;
}


//Asigna estadio donde se jugara el partido
void Partido::setEstadio(string e)
{
    estadio = e;
}

//Asigna arbitros a los partidos
void Partido::setArbitro(int i, string a)
{
    if(i>=0 && i<3)
    {
        arbitros[i]=a;
    }
}


// Asigna la fecha del partido
void Partido::setFecha(string f){
    fecha=f;
}

Equipo* Partido::getEquipo1(){ return equipo1; }
Equipo* Partido::getEquipo2(){ return equipo2; }


//Destructor
Partido::~Partido()

{
    //lo tiramos vacio para proteger la memoria dinamica del torneo
}


// Simula el partido completo:
// Calcula goles
// Simula jugadores
// Genera eventos (goles, faltas, tarjetas)
// Maneja prórroga si hay empate
// Simula un partido completo entre dos equipos
//

// Calcula goles esperados según rendimiento histórico
// Selecciona 11 jugadores por equipo
// Simula goles, tarjetas y faltas
// Maneja empate con prórroga y desempate
// Actualiza estadísticas del equip

// Usa un modelo basado en goles a favor/contra (lambda)
// Usa probabilidades con rand()
// Aplica reglas básicas de fútbol (90 + 30 min)

void Partido::simular()
{
    // Validación: si falta algún equipo no se simula
    if (equipo1==nullptr || equipo2==nullptr)
        return;

    // Parámetros del modelo
    const double MU = 1.35;
    const double ALPHA = 0.6;
    const double BETA = 0.4;

    // Datos históricos
    double gfA = equipo1->getGolesFavor();
    double gcB = equipo2->getGolesContra();

    double gfB = equipo2->getGolesFavor();
    double gcA = equipo1->getGolesContra();

    // Evitar división por cero
    if (gfA==0) gfA=1;
    if (gcB==0) gcB=1;
    if (gfB==0) gfB=1;
    if (gcA==0) gcA=1;

    // Modelo de goles esperados
    double lambdaA = MU * pow(gfA / MU, ALPHA) * pow(gcB / MU, BETA);
    double lambdaB = MU * pow(gfB / MU, ALPHA) * pow(gcA / MU, BETA);

    // Tope de goles por equipo
    int topeGolesA = max(0, (int)(lambdaA + ((rand() % 100) / 100.0)));
    int topeGolesB = max(0, (int)(lambdaB + ((rand() % 100) / 100.0)));

    // Posesión basada en ranking
    double r1 = equipo1->getRanking();
    double r2 = equipo2->getRanking();

    if (r1==0) r1=1;
    if (r2==0) r2=1;

    posesion1=(r2 / (r1+r2))*100;
    posesion2=(r1 / (r1+r2))*100;

    // Inicialización
    goles1=0;
    goles2=0;
    cantGoleadores1=0;
    cantGoleadores2=0;

    int usados1[26] = {0};

    // ================= EQUIPO 1 =================
    for (int i=0; i<11; i++)
    {
        int indice;

        // Selección aleatoria sin repetir jugadores
        do
        {
            indice = rand() % 26;
        }
        while (usados1[indice] == 1);

        usados1[indice] = 1;

        Jugador* jug=equipo1->getJugador(indice);

        if (jug!=nullptr)
        {
            jug->jugarPartido(90);

            // Gol
            if (goles1<topeGolesA)
            {
                if (rand()%100 < 4)
                {
                    jug->anotarGol();
                    goles1++;

                    goleadores1[cantGoleadores1++]=jug->getNumero();
                }
            }

            // Tarjetas
            int pAmarilla=rand()%10000;
            if (pAmarilla<600)
            {
                jug->recibirAmarilla();
                if (rand()%10000<115)
                {
                    jug->recibirAmarilla();
                    jug->recibirRoja();
                }
            }

            // Faltas
            int pFaltas=rand()%10000;
            if (pFaltas<1300)
            {
                jug->hacerFalta();
                if (rand() % 10000<275)
                {
                    jug->hacerFalta();
                    if (rand()%10000<70)
                        jug->hacerFalta();
                }
            }
        }
    }

    // ================= EQUIPO 2 =================
    int usados2[26] = {0};

    for (int i = 0; i < 11; i++)
    {
        int indice;

        do
        {
            indice = rand() % 26;
        }

        while (usados2[indice] == 1);

        usados2[indice] = 1;

        Jugador* jug = equipo2->getJugador(indice);

        if (jug != nullptr)
        {
            jug->jugarPartido(90);

            if (goles2<topeGolesB)
            {
                if (rand()%100 < 4)
                {
                    jug->anotarGol();
                    goles2++;

                    goleadores2[cantGoleadores2++]=jug->getNumero();
                }
            }

            // Tarjetas y faltas igual que equipo 1
        }
    }

    // Prorroga
    if (goles1==goles2)
    {
        // Sumar 30 minutos extra
        for (int i=0; i<26; i++)
        {
            if (usados1[i] == 1)
            {
                Jugador* j=equipo1->getJugador(i);
                if (j!=nullptr) j->jugarPartido(30);
            }
        }

        for (int i=0; i<26; i++)
        {
            if (usados2[i] == 1)
            {
                Jugador* j = equipo2->getJugador(i);
                if (j!=nullptr) j->jugarPartido(30);
            }
        }

        int r1=equipo1->getRanking();
        int r2=equipo2->getRanking();

        if (r1==0) r1=100;
        if (r2==0) r2=100;

        int probEquipo1 = (r2*100) / (r1+r2);

        if (rand() % 100 < probEquipo1)
            goles1++;
        else
            goles2++;
    }

    //registro
    equipo1->registrarPartido(goles1, goles2);
    equipo2->registrarPartido(goles2, goles1);

    // salisa
    cout << "Goleadores " << equipo1->getNombrePais() << ": ";
    for (int i = 0; i < cantGoleadores1; i++)
        cout << goleadores1[i] << " ";
    cout << endl;

    cout << "Goleadores " << equipo2->getNombrePais() << ": ";
    for (int i = 0; i < cantGoleadores2; i++)
        cout << goleadores2[i] << " ";
    cout << endl;
}

// Muestra toda la información del partido

// Imprime fase, fecha, estadio y árbitros
// Muestra marcador final
// Lista goleadores de ambos equipos
// Muestra posesión del balón

// Cómo lo hace:
// Usa los datos ya calculados en simular()
// Recorre los arreglos de goleadores para imprimirlos

void Partido::mostrar(){

    cout << "\n---------------------------------\n";

    // Datos generales del partido
    cout << "Fase: "<< fase << endl;
    cout << "Fecha: " << fecha << "  Hora: 00:00"<< endl;
    cout << "Estadio: " << estadio<< endl;

    // Árbitros asignados
    cout << "Arbitros: "
         <<arbitros[0] << ", "
         <<arbitros[1] << ", "
         <<arbitros[2] << endl;

    // Resultado final
    cout << equipo1->getNombrePais() <<" "<< goles1
         << " vs "
         << goles2 << " " << equipo2->getNombrePais() << endl;

    // Goleadores equipo 1
    cout << "Goleadores " << equipo1->getNombrePais() << ": ";
    for(int i=0; i<cantGoleadores1; i++){
        cout << goleadores1[i] << " ";
    }

    // Goleadores equipo 2
    cout << "\nGoleadores " << equipo2->getNombrePais() << ": ";
    for(int i=0; i<cantGoleadores2; i++){
        cout << goleadores2[i] << " ";
    }

    // Posesión del balón
    cout << "\nPosesion:\n";
    cout << equipo1->getNombrePais()<< ": " << posesion1 << "%\n";
    cout << equipo2->getNombrePais()<< ": " << posesion2 << "%\n";

    cout << "\n---------------------------------\n";
}