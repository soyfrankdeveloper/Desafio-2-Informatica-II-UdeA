#include "Grupo.h"


// Constructor: crea un grupo con letra y sin equipos asignados
Grupo::Grupo(char l)

{
    letra = l;

    for(int i=0;i<4;i++) equipos[i]=nullptr;
    for(int i=0;i<6;i++) partidos[i]=nullptr;
}


// Devuelve el equipo en una posición del grupo
// i: índice del equipo (0 a 3)

// Permite acceder a un equipo del grupo

// Verifica que el índice esté en rango
// Retorna el puntero al equipo o nullptr si es inválido

Equipo* Grupo::getEquipo(int i)
{
    if (i >= 0 && i < 4)
        return equipos[i];

    return nullptr;
}


// Asigna un equipo a una posición del grupo
// pos: índice del grupo (0 a 3)
// eq: puntero al equipo a asignar

// Coloca el equipo en la posición indicada.
// Actualiza el grupo al que pertenece el equipo

// Verifica que la posición sea válida
// Guarda el puntero en el arreglo
// Si el equipo existe, le asigna la leta del grupo

void Grupo::setEquipo(int pos, Equipo* eq)
{
    if (pos >= 0 && pos < 4)
    {
        equipos[pos] = eq;

        // Asignar letra de grupo al equipo
        if (eq != nullptr)
        {
            eq->setGrupo(letra);
        }
    }
}


// Devuelve un partido del grupo
// i: índice del partido (0 a 5)

// Permite acceder a uno de los 6 partidos del grupo

// Verifica que el índice esté dentro del rango válido
// Retorna el puntero al partido o nullptr si es inválido

Partido* Grupo::getPartido(int i)
{
    if (i >= 0 && i < 6)
        return partidos[i];

    return nullptr;
}


// Genera los 6 partidos del grupo (todos contra todos)

// Crea los enfrentamientos entre los 4 equipos del grupo
// Cada equipo juega contra los otros una sola vez

// Usa dos bucles para formar todas las combinaciones posibles
// Crea un objeto Partido por cada cruce
// Guarda cada partido en el arreglo

void Grupo::generarPartidos()
{
    int k = 0;

    // Generar combinaciones sin repetir equipos
    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            partidos[k] = new Partido(equipos[i], equipos[j], "Grupos", "nombreSede");
            k++;
        }
    }
}


// Devuelve el tercer clasificado del grupo

// Ordena los equipos según su rendimiento.
// Retorna el equipo en la posición 3 (índice 2).

// Usa una función de ordenamiento descendente.
// Accede directamente al tercer elemento del arreglo.

Equipo* Grupo::getTercero()
{
    ordenarArregloDescendente(equipos, 4);
    return equipos[2]; // tercer lugar
}


// Simula todos los partidos del grupo

// Ejecuta la simulación de los 6 partidos del grupo
// Muestra el resultado de cada partido

// Recorre el arreglo de partidos
// Llama a simular() y luego a mostrar() en cada uno


void Grupo::simularGrupo()
{
    cout << "Grupo " << letra << endl;

    // Recorrer los partidos del grupo
    for (int i = 0; i < 6; i++)
    {
        if (partidos[i] != nullptr)
        {
            partidos[i]->simular();
            partidos[i]->mostrar();
        }
    }
}


// Muestra la tabla de posiciones del grupo

// Ordena los equipos según su rendimiento
// Imprime la tabla con estadísticas
// Indica los equipos clasificados

// Ordena una copia del arreglo (para no alterar el original)
// Recorre los equipos y muestra sus datos


void Grupo::mostrarTabla()
{
    // Copia para no modificar el orden real del grupo
    Equipo* copia[4];

    for(int i = 0; i < 4; i++)
        copia[i] = equipos[i];

    ordenarArregloDescendente(copia, 4);

    cout << "\n========================================" << endl;
    cout << "           GRUPO " << letra << endl;
    cout << "========================================" << endl;

    cout << "Equipo\tPJ\tPG\tPE\tPP\tDG\tPTS" << endl;

    // Mostrar tabla
    for(int i = 0; i < 4; i++)
    {
        if(copia[i] != nullptr)
        {
            cout << copia[i]->getNombrePais() << "\t"
                 << copia[i]->getPartidosJugados() << "\t"
                 << copia[i]->getGanados() << "\t"
                 << copia[i]->getEmpatados() << "\t"
                 << copia[i]->getPerdidos() << "\t"
                 << copia[i]->getDiferenciaGoles() << "\t"
                 << copia[i]->getPuntos()
                 << endl;
        }
    }

    cout << "----------------------------------------" << endl;

    // Mostrar clasificados
    if(copia[0] != nullptr && copia[1] != nullptr)
    {
        cout << "Clasificados: "
             << copia[0]->getNombrePais() << " y "
             << copia[1]->getNombrePais() << endl;
    }
}


// Devuelve un equipo según su posición en la tabla
// posicion: índice (0 = primero, 1 = segundo, etc.)

// Obtiene un equipo ordenado por rendimiento.

// Crea una copia del arreglo de equipos.
// Ordena la copia.
// Retorna el equipo en la posición solicitada.

Equipo* Grupo::getClasificado(int posicion)
{
    // Copiar para no modificar el grupo original
    Equipo* copia[4];

    for(int i = 0; i < 4; i++)
        copia[i] = equipos[i];

    ordenarArregloDescendente(copia, 4);

    if (posicion >= 0 && posicion < 4)
        return copia[posicion];

    return nullptr;
}


// Destructor: libera memoria de los partidos
Grupo::~Grupo()

{

    for(int i=0;i<6;i++)

    {
        if(partidos[i]!=nullptr)
            delete partidos[i];
    }
}
