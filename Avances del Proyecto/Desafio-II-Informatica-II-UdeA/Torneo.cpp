#include "Torneo.h"
#include <sstream>
#include <cstdlib>


// Constructor: inicializa equipos, grupos y fases finales
Torneo::Torneo()
{
    for (int i=0; i<48; i++) equipos[i]=nullptr;
    for(int i=0; i<12;i++){
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


// Función auxiliar para fases eliminatorias

// Simula un partido entre dos equipos en fase directa
// Determina el ganador (sin empates finales)
// Retorna el equipo que avanza

// Crea un objeto Partido local
// Simula el partido y muestra resultado
// Usa los puntos obtenidos para decidir ganador
// Si hay empate, define ganador por penales (50/50)

static Equipo* jugarLlave(Equipo* eq1, Equipo* eq2, string fase){

    // Validación: si alguno es null, retorna el que exista
    if (eq1 == nullptr)
        return eq2;

    if (eq2 == nullptr)
        return eq1;

    // Mostrar enfrentamiento
    cout << " >>>" << eq1->getNombrePais()
         << " Vs " << eq2->getNombrePais()
         << " (" << fase << ")" << endl;

    // Crear partido (objeto local, no deja basura en memoria)
    Partido p(eq1, eq2, fase, "Estadio Mundial");

    // Configuración básica del partido
    p.setFecha("10/07/2026 00:00");

    p.setArbitro(0, "ARBITRO_1");
    p.setArbitro(1, "ARBITRO_2");
    p.setArbitro(2, "ARBITRO_3");

    // Guardar puntos previos para detectar resultado
    int ptsAntes = eq1->getPuntos();

    // Simular partido
    p.simular();
    p.mostrar();

    // Calcular puntos ganados por eq1
    int ptsGanados = eq1->getPuntos() - ptsAntes;

    // Victoria de eq1
    if(ptsGanados == 3)

    {
        cout << "  [avanza: " << eq1->getNombrePais()
        << " en tiempo reglamentario]";
        return eq1;
    }

    // Victoria de eq2
    if(ptsGanados == 0)

    {
        cout << "  [avanza: " << eq2->getNombrePais()
        << " en tiempo reglamentario]";
        return eq2;
    }

    // Empate → definición por penales
    if(rand() % 2 == 0)

    {
        cout << "  [empate. Avanza "
             << eq1->getNombrePais()
             << " por penales]";
        return eq1;
    }

    else

    {
        cout << "  [empate. Avanza "
             << eq2->getNombrePais()
             << " por penales]";
        return eq2;
    }
}


// Asigna fechas a todos los partidos de fase de grupos respetando:
// máximo 4 partidos por día
// mínimo 3 días de descanso entre partidos del mismo equipo
void Torneo::asignarFechasFaseGrupos()
{

    Partido* lista[72];
    int total = 0;

    // Recolectar partidos
    for(int g=0; g< 12; g++){
        for(int p =0; p <6; p++){
            lista[total] = grupos[g]->getPartido(p);
            total++;
        }
    }

    // Mezclar partidos
    for(int i=0; i<total; i++){
        int j=rand() % total;
        Partido* temp= lista[i];
        lista[i]= lista[j];
        lista[j]= temp;
    }

    int partidosPorDia[19];
    for(int i=0; i<19; i++)
    {
        partidosPorDia[i] = 0;
    }

    Equipo* equiposRegistro[48];
    int ultimoDia[48];

    int usados = 0;

    for(int i = 0; i < 48; i++)
    {
        equiposRegistro[i] = nullptr;
        ultimoDia[i] = -100;
    }

    // Asignar fechas
    for(int i = 0; i < total; i++)
    {

        Partido* partido = lista[i];

        Equipo* e1 = partido->getEquipo1();
        Equipo* e2 = partido->getEquipo2();

        if(!e1 || !e2){
            cout << "Error, partido con equipo \n";
            continue;
        }

        // obtener índice de e1
        int idx1= -1;

        for(int k=0; k<usados; k++)
        {
            if(equiposRegistro[k]==e1)
            {
                idx1 = k;
                break;
            }
        }

        if(idx1==-1)
        {
            equiposRegistro[usados] = e1;
            ultimoDia[usados] = -100;
            idx1 = usados;
            usados++;
        }

        // obtener índice de e2
        int idx2=-1;
        for(int k = 0; k < usados; k++)
        {
            if(equiposRegistro[k] == e2)
            {
                idx2 = k;
                break;
            }
        }
        if(idx2==-1){
            equiposRegistro[usados]=e2;
            ultimoDia[usados]=-100;
            idx2=usados;
            usados++;
        }

        bool asignado=false;

        for(int d=0; d<19; d++)
        {

            int diff1=(d - ultimoDia[idx1]+19)%19;
            int diff2=(d - ultimoDia[idx2]+19)%19;

            if(partidosPorDia[d]<4&& diff1>= 3 && diff2>= 3){

                int diaReal= 20+d;
                int mes= 6;

                if(diaReal > 30)

                {
                    diaReal-=30;
                    mes=7;
                }

                string dStr;
                if (diaReal<10)

                {
                    dStr = "0" + to_string(diaReal);
                }

                else

                {
                    dStr = to_string(diaReal);
                }

                string mStr;
                if (mes<10)
                {
                    mStr= "0" + to_string(mes);
                }

                else

                {
                    mStr = to_string(mes);
                }

                string fecha=dStr + "/" +mStr + "/2026 00:00";

                partido->setFecha(fecha);
                partido->setEstadio("Estadio Mundial");

                partido->setArbitro(0, "ARBITRO_1");
                partido->setArbitro(1, "ARBITRO_2");
                partido->setArbitro(2, "ARBITRO_3");

                partidosPorDia[d]++;
                ultimoDia[idx1]= d;
                ultimoDia[idx2]= d;

                asignado = true;
                break;
            }
        }

        if(!asignado){
            cout<< "No se pudo asignar fecha a un partido\n";
        }
    }

    cout <<"Fechas asignadas correctamente" << endl;
}


// Destructor: libera memoria de equipos y grupos
Torneo::~Torneo()
{
    for(int i=0; i<48;i++)

    {
        if(equipos[i]!= nullptr)delete equipos[i];//pd: nullptr es un puntero vacio que no apunta a ninguna direccion de memoria
    }

    for(int i=0; i<12;i++)

    {
        if(grupos[i]!= nullptr)delete grupos[i];//pd: no le aplicamos delete pq rompemos la memoria
    }
}


// Verifica si un equipo puede ser agregado a un grupo según reglas de confederación

// Solo se permiten equipos de la misma confederación si es UEFA (máximo 2)
// Para otras confederaciones, solo 1 equipo por grupo
bool esValido(Grupo* grupo, Equipo* nuevo)
{

    int conteoUEFA = 0;

    // Recorremos los equipos ya existentes en el grupo
    for(int i=0;i<4;i++)

    {
        Equipo* e =grupo->getEquipo(i);

        if(e !=nullptr)
        {

            string c1= e->getConfederacion();
            string c2= nuevo->getConfederacion();

            // Si pertenecen a la misma confederación
            if(c1==c2)
            {

                // Caso especial UEFA (máximo 2 equipos)
                if(c1 =="UEFA"){
                    conteoUEFA++;
                    if(conteoUEFA >= 2)
                        return false;
                }
                // Otras confederaciones: solo se permite uno
                else
                {
                    return false;
                }
            }
        }
    }

    // Si pasa todas las validaciones, es válido
    return true;
}



// Carga los equipos desde un archivo CSV
// Retorna true si se cargan exactamente 48 equipos

bool Torneo::cargarEquiposDesdeCSV(string rutaArchivo)
{

    ifstream archivo(rutaArchivo);
    string linea;

    // Validación de apertura del archivo
    if(!archivo.is_open())
    {
        cout<<"No se pudo abrir el archivo"<<endl;
        return false;
    }

    int i = 0;

    // Saltar encabezado del CSV
    getline(archivo, linea);

    // Leer línea por línea (máximo 48 equipos)
    while(getline(archivo, linea) && i< 48)
    {

        stringstream stream(linea);

        string rankingStr, pais, dummy;
        string gfStr, gcStr;

        // Lectura de campos usando ; como separador
        getline(stream, rankingStr, ';'); // Ranking
        getline(stream, pais, ';');       // País

        getline(stream, dummy, ';'); // Director (ignorado)
        getline(stream, dummy, ';'); // Federación (ignorado)

        string confed;
        getline(stream, confed, ';'); // Confederación

        getline(stream, gfStr, ';'); // Goles a favor
        getline(stream, gcStr, ';'); // Goles en contra

        // Validar que el país no esté vacío
        if(!pais.empty()){

            equipos[i] = new Equipo();

            // Asignación de datos básicos
            equipos[i]->setNombrePais(pais);
            equipos[i]->setConfederacion(confed);

            // Conversión de ranking con control de error
            try{
                equipos[i]->setRanking(stoi(rankingStr));
            }catch(...){
                equipos[i]->setRanking(0);
            }

            int gf = 10, gc = 10;

            // Conversión de goles con fallback por defecto
            try{
                gf = stoi(gfStr);
                gc = stoi(gcStr);
            }catch(...){}

            // Inicializa jugadores distribuyendo goles
            equipos[i]->inicializarJugadores(gf);

            // Simula un historial base del equipo
            equipos[i]->registrarPartido(gf, gc);

            i++;
        }
    }

    archivo.close();

    cout<<"Equipos cargados: "<<i<<endl;

    // Retorna true solo si se cargaron los 48 equipos
    return i == 48;
}


// Ordena un arreglo de equipos por ranking (de menor a mayor)
// Utiliza el algoritmo Bubble Sort
void ordenarEquiposPorRanking(Equipo* arr[], int n)
{

    // Recorre el arreglo múltiples veces
    for(int i=0;i<n-1;i++)
    {

        // Compara pares adyacentes
        for(int j=0;j<n-i-1;j++)
        {

            // Si el ranking actual es mayor que el siguiente, se intercambian
            if(arr[j]->getRanking()>arr[j+1]->getRanking())
            {

                Equipo* aux = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = aux;
            }
        }
    }
}


// Organiza los equipos en 12 grupos de 4 usando el sistema de bombos
// Reglas:
// Equipos ordenados por ranking
// Se reparten en 4 bombos de 12 equipos
// Se respeta restricción de confederaciones (función esValido)
// Se intenta asignación aleatoria con límite de intentos
void Torneo::armarGrupos()
{

    ordenarEquiposPorRanking(equipos, 48);

    int posUSA=-1;

    // Forzar USA cabeza de serie
    for(int i= 0; i<48; i++){
        if(equipos[i]->getNombrePais() == "USA"){
            posUSA = i;
            break;
        }
    }

    if(posUSA != -1)
    {
        Equipo* temp = equipos[0];
        equipos[0] = equipos[posUSA];
        equipos[posUSA] = temp;
    }

    // Crear bombos
    Equipo* bombos[4][12];

    int idx=0;
    for(int b=0; b<4; b++)
    {
        for(int j = 0; j < 12; j++)
        {
            bombos[b][j] = equipos[idx++];
        }
    }

    // Llenar grupos
    for(int g = 0; g < 12; g++)
    {

        bool asignadoCorrectamente = false;
        int intentosGrupo = 0;

        // Intentar armar el grupo varias vece
        while(!asignadoCorrectamente && intentosGrupo < 100)
        {

            intentosGrupo++;

            // limpiar grupo
            for(int x= 0; x< 4; x++)
            {
                grupos[g]->setEquipo(x, nullptr);
            }

            // usado SOLO para este grupo
            bool usado[4][12] = {false};

            bool fallo = false;

            for(int b =0; b< 4; b++)
            {

                int pos= -1;
                int intentos =0;

                while(intentos < 50)
                {

                    int r = rand() % 12;

                    if(!usado[b][r]){
                        if(esValido(grupos[g], bombos[b][r]))
                        {
                            pos = r;
                            break;
                        }
                    }

                    intentos++;
                }

                if(pos == -1)
                {
                    fallo = true;
                    break;
                }

                usado[b][pos] = true;
                grupos[g]->setEquipo(b, bombos[b][pos]);
            }

            if(!fallo)
            {
                asignadoCorrectamente = true;
            }
        }

        // Si después de muchos intentos no pudo
        if(!asignadoCorrectamente){
            cout << "Error: no se pudo armar el grupo " << char('A'+g) << endl;
        }

        grupos[g]->generarPartidos();
    }

    asignarFechasFaseGrupos();

    cout << "Grupos generados con bombos correctamente" << endl;
}


// Simula todos los partidos de la fase de grupos y muestra resultados
// Para cada grupo:
// Simula los 6 partidos
// Muestra cada partido individualmente
// Muestra la tabla final del grupo
void Torneo::simularFaseGrupos()

{

    // Recorrer los 12 grupos
    for(int i=0;i<12;i++){

        // Simula todos los partidos del grupo (actualiza estadísticas internas)
        grupos[i]->simularGrupo();

        // Mostrar cada uno de los 6 partidos del grupo
        for(int j=0;j<6;j++){
            grupos[i]->getPartido(j)->mostrar();
        }

        // Mostrar la tabla de posiciones del grupo ya ordenada
        grupos[i]->mostrarTabla();
    }
}


// Simula las fases eliminatorias hasta obtener el campeón
void Torneo::simularFasesFinales()

{

    cout << "\n========================================" << endl;
    cout << "       INICIANDO FASES ELIMINATORIAS    " << endl;
    cout << "========================================" << endl;

    // ================= CLASIFICACIÓN =================
    // Se obtienen los 3 mejores equipos de cada grupo:
    // 1 y 2 clasifican directo, y los mejores 3° también avanzan

    Equipo* primeros[12];
    Equipo* segundos[12];
    Equipo* terceros[12];

    // Obtener clasificados por grupo (ordenados previamente en la tabla)
    for(int i=0;i<12;i++){
        primeros[i]= grupos[i]->getClasificado(0);
        segundos[i]= grupos[i]->getClasificado(1);
        terceros[i] = grupos[i]->getClasificado(2);
    }

    // Ordenar terceros de mejor a peor para elegir los mejores
    ordenarArregloDescendente(terceros, 12);

    // Tomar los 8 mejores terceros
    Equipo* mejoresTerceros[8];
    for(int i=0;i<8;i++)

    {
        mejoresTerceros[i] = terceros[i];
    }

    // Ordenar segundos de mejor a peor
    ordenarArregloDescendente(segundos, 12);

    // Separar segundos en mejores y peores
    Equipo* mejoresSegundos[8];
    Equipo* peoresSegundos[4];

    for(int i=0;i<8;i++)

    {
        mejoresSegundos[i] = segundos[i];
    }

    for(int i=0;i<4;i++)

    {
        peoresSegundos[i] = segundos[8+i];
    }

    // ================= ARMADO DE LLAVES =================
    // Se construye el cuadro de 32 equipos (dieciseisavos)

    Equipo* dieciseisavos[32];
    int k = 0;

    // Regla 1: 8 primeros vs 8 mejores terceros
    for(int i=0;i<8;i++)
    {
        dieciseisavos[k++]= primeros[i];
        dieciseisavos[k++] =mejoresTerceros[i];
    }

    // Regla 2: 4 primeros restantes vs 4 peores segundos
    for(int i=0;i<4;i++)
    {
        dieciseisavos[k++]= primeros[8+i];
        dieciseisavos[k++]= peoresSegundos[i];
    }

    // Regla 3: los 8 mejores segundos se enfrentan entre sí
    for(int i=0;i<8;i+=2)
    {
        dieciseisavos[k++]= mejoresSegundos[i];
        dieciseisavos[k++]= mejoresSegundos[i+1];
    }

    // ================= SIMULACIÓN DE RONDAS =================

    cout << "\n--- DIECISEISAVOS (R16) ---" << endl;

    // 16 partidos → 16 ganadores (pasan a octavos)
    for(int i=0;i<16;i++)
    {
        octavos[i] = jugarLlave(dieciseisavos[i*2], dieciseisavos[i*2+1], "R16");
    }

    cout << "\n--- OCTAVOS DE FINAL ---" << endl;

    // 8 partidos → 8 ganadores (pasan a cuartos)
    for(int i = 0; i < 8; i++)
    {
        cuartos[i] = jugarLlave(octavos[i*2], octavos[i*2 + 1], "Octavos");
    }

    cout << "\n--- CUARTOS DE FINAL ---" << endl;

    // 4 partidos → 4 ganadores (pasan a semifinales)
    for(int i = 0; i < 4; i++)
    {
        semis[i] = jugarLlave(cuartos[i*2], cuartos[i*2 + 1], "Cuartos");
    }

    cout << "\n--- SEMIFINALES ---" << endl;

    // 2 partidos → 2 finalistas
    for(int i = 0; i < 2; i++)
    {
        finalistas[i] = jugarLlave(semis[i*2], semis[i*2 + 1], "Semifinal");
    }

    cout << "\n--- FINAL ---" << endl;

    // Final: define campeón
    campeon = jugarLlave(finalistas[0], finalistas[1], "FINAL");

    // Determinar subcampeón (el que no ganó la final)
    if(campeon ==finalistas[0])
    {
        subcampeon =finalistas[1];
    }

    else

    {
        subcampeon= finalistas[0];
    }

    // ================= TERCER PUESTO =================
    // Se enfrentan los perdedores de semifinales

    Equipo* perdedor1;
    Equipo* perdedor2;

    // Identificar perdedores de cada semifinal
    if(finalistas[0] ==semis[0])

    {
        perdedor1= semis[1];
    }else

    {
        perdedor1= semis[0];
    }

    if(finalistas[1] == semis[2])

    {
        perdedor2 = semis[3];
    }else

    {
        perdedor2 = semis[2];
    }

    cout << "\n--- TERCER PUESTO ---" << endl;

    // Partido por el tercer lugar
    tercerLugar = jugarLlave(perdedor1, perdedor2, "Tercer Puesto");

    // Determinar cuarto lugar
    if(tercerLugar == perdedor1)

    {
        cuartoLugar =perdedor2;
    }

    else

    {
        cuartoLugar= perdedor1;
    }
}

// Determina qué confederación tiene mayor cantidad de equipos en una fase
// Recibe el conteo por confederación y el nombre de la fase
// Muestra en consola la confederación dominante
void mostrarMayorConfederacion(int uefa, int conmebol, int concacaf, int caf, int afc, string fase)

{

    // Se toma UEFA como valor inicial de referencia
    int max = uefa;
    string nombre = "UEFA";

    // Comparación secuencial para encontrar el mayor valor
    if(conmebol > max)
    {
        max = conmebol;
        nombre = "CONMEBOL";
    }

    if(concacaf > max)
    {
        max = concacaf;
        nombre = "CONCACAF";
    }

    if(caf > max)
    {
        max = caf;
        nombre = "CAF";
    }

    if(afc > max)
    {
        max = afc;
        nombre = "AFC";
    }

    // Resultado final
    cout << ">>> Confederacion con mayor presencia en " << fase << ": "
         << nombre << " (" << max << " equipos)" << endl;
}


// Muestra estadísticas finales del torneo:
// campeón, top 4, goleadores, equipo más ofensivo y presencia por confederación
void Torneo::mostrarEstadisticasFinales()

{
    // Validación: si no hay campeón, no hay nada que mostrar
    if(!campeon)return;

    cout << "\n========================================"<< endl;
    cout<< "          ¡TENEMOS CAMPEON!             " << endl;
    cout << "========================================" << endl;
    cout << " >>>> " << campeon->getNombrePais()<< " ES EL CAMPEON DEL MUNDO <<<<" << endl;

    // ================= TOP 4 =================
    cout << "\n--- TOP 4 DEL MUNDIAL ---" << endl;
    cout<< "1. " << campeon->getNombrePais()<< endl;
    cout << "2. " << subcampeon->getNombrePais() << endl;
    cout<< "3. " << tercerLugar->getNombrePais()<< endl;
    cout << "4. " << cuartoLugar->getNombrePais() << endl;

    // ================= GOLEADOR DEL CAMPEÓN =================
    // Se recorre la plantilla del campeón y se toma el jugador con más goles
    Jugador* goleadorCampeon= nullptr;
    int maxGolesCampeon =-1;

    for(int i=0;i<26;i++)
    {
        Jugador* j =campeon->getJugador(i);
        if(j && j->getGoles() > maxGolesCampeon)
        {
            maxGolesCampeon= j->getGoles();
            goleadorCampeon= j;
        }
    }

    if(goleadorCampeon)
    {
        cout << "\nGoleador del campeon: "
             << goleadorCampeon->getNombre() << " "
             << goleadorCampeon->getApellido()
             << " (" << goleadorCampeon->getGoles() << " goles)" << endl;
    }

    // ================= TOP 3 GOLEADORES DEL TORNEO =================
    // Inserción ordenada en un arreglo de tamaño fijo (top 3)
    Jugador* top[3] = {nullptr, nullptr, nullptr};

    for(int i=0;i<48;i++)
    {
        if(equipos[i]){
            for(int j=0;j<26;j++)
            {
                Jugador* jug = equipos[i]->getJugador(j);

                if(jug)
                {
                    for(int k=0;k<3;k++)
                    {
                        if(top[k]==nullptr || jug->getGoles() > top[k]->getGoles()){
                            // Desplazar para mantener orden descendente
                            for(int m=2;m>k;m--)
                            {
                                top[m]=top[m-1];
                            }
                            top[k]=jug;
                            break;
                        }
                    }
                }
            }
        }
    }

    cout << "\n--- TOP 3 GOLEADORES ---" << endl;
    for(int i=0;i<3;i++)
    {
        if(top[i]){
            cout << i+1 << ". "
                 << top[i]->getNombre() << " "
                 << top[i]->getApellido()
                 << " (" << top[i]->getGoles() << " goles)" << endl;
        }
    }

    // ================= EQUIPO MÁS GOLEADOR Y BOTA DE ORO =================
    Equipo* equipoMasGoleador=equipos[0];
    Jugador* goleador=nullptr;
    int maxGoles=-1;

    // Barrido completo: identifica equipo con más goles y jugador con más goles
    for (int i = 0; i < 48; i++)
    {
        if (equipos[i] != nullptr)
        {

            if (equipoMasGoleador == nullptr ||
                equipos[i]->getGolesFavor() > equipoMasGoleador->getGolesFavor())
            {
                equipoMasGoleador = equipos[i];
            }

            for (int j = 0; j < 26; j++)
            {
                Jugador* jug = equipos[i]->getJugador(j);
                if (jug != nullptr && jug->getGoles() > maxGoles)
                {
                    maxGoles = jug->getGoles();
                    goleador = jug;
                }
            }
        }
    }

    cout<< " >>> Estadisticas del torneo"<< endl;

    if(equipoMasGoleador)
    {
        cout<<" Equipo más goleador de la temporada: "
             <<equipoMasGoleador->getNombrePais()
             <<" ("<< equipoMasGoleador->getGolesFavor()<< " goles. )"<<endl;
    }

    if (goleador)
    {
        cout<<" >>> Botas de Oro: "
             <<goleador->getNombre()<<" "<< goleador->getApellido()
             << " con "<< goleador->getGoles()<< " anotaciones."<<endl;
    }

    // ================= CONFEDERACIONES POR FASE =================
    int uefa=0, conmebol=0, concacaf=0, caf=0, afc=0;

    // -------- OCTAVOS --------
    for(int i=0;i<16;i++)
    {
        if(octavos[i])
        {
            string c = octavos[i]->getConfederacion();

            if(c=="UEFA") uefa++;
            else if(c=="CONMEBOL") conmebol++;
            else if(c=="CONCACAF") concacaf++;
            else if(c=="CAF") caf++;
            else if(c=="AFC") afc++;
        }
    }

    cout << "\n--- CONFEDERACIONES (OCTAVOS) ---" << endl;
    mostrarMayorConfederacion(uefa, conmebol, concacaf, caf, afc, "R16");

    cout << "UEFA: " << uefa << endl;
    cout << "CONMEBOL: " << conmebol << endl;
    cout << "CONCACAF: " << concacaf << endl;
    cout << "CAF: " << caf << endl;
    cout << "AFC: " << afc << endl;

    // Reinicio de contadores
    uefa=conmebol=concacaf=caf=afc=0;

    // -------- CUARTOS --------
    for(int i=0;i<8;i++)
    {
        if(cuartos[i])
        {
            string c = cuartos[i]->getConfederacion();

            if(c=="UEFA") uefa++;
            else if(c=="CONMEBOL") conmebol++;
            else if(c=="CONCACAF") concacaf++;
            else if(c=="CAF") caf++;
            else if(c=="AFC") afc++;
        }
    }

    cout << "\n--- CONFEDERACIONES (CUARTOS) ---" << endl;
    mostrarMayorConfederacion(uefa, conmebol, concacaf, caf, afc, "R8");

    cout << "UEFA: " << uefa << endl;
    cout << "CONMEBOL: " << conmebol << endl;
    cout << "CONCACAF: " << concacaf << endl;
    cout << "CAF: " << caf << endl;
    cout << "AFC: " << afc << endl;

    // Reinicio de contadores
    uefa=conmebol=concacaf=caf=afc=0;

    // -------- SEMIFINALES --------
    for(int i=0;i<4;i++){
        if(semis[i]){
            string c = semis[i]->getConfederacion();

            if(c=="UEFA") uefa++;
            else if(c=="CONMEBOL") conmebol++;
            else if(c=="CONCACAF") concacaf++;
            else if(c=="CAF") caf++;
            else if(c=="AFC") afc++;
        }
    }

    cout << "\n--- CONFEDERACIONES (SEMIFINALES) ---" << endl;
    mostrarMayorConfederacion(uefa, conmebol, concacaf, caf, afc, "R4");

    cout << "UEFA: " << uefa << endl;
    cout << "CONMEBOL: " << conmebol << endl;
    cout << "CONCACAF: " << concacaf << endl;
    cout << "CAF: " << caf << endl;
    cout << "AFC: " << afc << endl;
}


// Guarda la información de todos los jugadores en un archivo de texto
// Formato:
// EQUIPO;NombrePais
// J;numero;nombre;apellido;goles;minutos;amarillas;rojas;faltas;asistencias
void Torneo::guardarDatos(){

    // Abrir archivo en modo escritura
    ofstream archivo("jugadores.txt");

    // Validación: si no se pudo abrir, se cancela
    if(!archivo.is_open())
    {
        cout<<"Error al guardar archivo"<<endl;
        return;
    }

    // Recorrer todos los equipos del torneo
    for(int i=0;i<48;i++)
    {

        if(equipos[i])
        {

            // Escribir encabezado del equipo
            archivo << "EQUIPO;" << equipos[i]->getNombrePais() << endl;

            // Recorrer jugadores del equipo
            for(int j=0;j<26;j++)
            {

                Jugador* jug = equipos[i]->getJugador(j);

                if(jug){

                    // Escribir datos del jugador en formato delimitado por ';'
                    archivo << "J;"
                            << jug->getNumero() << ";"
                            << jug->getNombre() << ";"
                            << jug->getApellido() << ";"
                            << jug->getGoles() << ";"
                            << jug->getMinutos() << ";"
                            << jug->getAmarillas() << ";"
                            << jug->getRojas() << ";"
                            << jug->getFaltas() << ";"
                            << jug->getAsistencias()
                            << endl;
                }
            }
        }
    }

    // Cerrar archivo
    archivo.close();

    cout<<"Jugadores guardados correctamente"<<endl;
}