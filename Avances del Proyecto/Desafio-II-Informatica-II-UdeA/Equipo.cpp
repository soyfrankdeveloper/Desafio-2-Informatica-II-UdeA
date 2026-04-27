#include "Equipo.h"


// Constructor de la clase Equipo
// Objetivo:
// Inicializar un equipo con valores por defecto y crear su plantilla base de jugadores.

// Que hace:
// Inicializa atributos básicos del equipo (nombre, ranking, estadísticas).
// Define que cada equipo tendrá 26 jugadores.
// Reserva memoria dinámica para almacenar esos jugadores.

// Asigna valores iniciales simples (0 o cadena vacía).
// Usa new para crear un arreglo dinámico de objetos Jugador.

// No se inicializan los datos individuales de los jugadores aquí,
// solo se reserva el espacio en memoria. La carga real se hace después.

Equipo::Equipo()
{
    // Inicialización del nombre del país (vacío)
    nombrePais = "";

    // Ranking inicial (sin asignar)
    ranking = 0;

    // Estadísticas iniciales del equipo
    golesFavor = 0;
    golesContra = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;

    // Cantidad fija de jugadores por equipo (requisito del sistema)
    cantidadJugadores = 26;

    // Reserva de memoria dinámica para los jugadores
    // Se crea un arreglo de 26 objetos Jugador
    jugadores = new Jugador[cantidadJugadores];
}


//getters

string Equipo::getNombrePais()const {return nombrePais;}
int Equipo::getRanking()const {return ranking;}
int Equipo::getGolesFavor() const{return golesFavor;}
int Equipo::getGolesContra()const{return golesContra;}
int Equipo::getGanados()const {return ganados;}
int Equipo::getEmpatados()const {return empatados;}
int Equipo::getPerdidos()const {return perdidos;}
string Equipo::getConfederacion() const {
    return confederacion;
}

int Equipo::getPartidosJugados()const
{
    return ganados + empatados + perdidos;
}

//setters
void Equipo::setNombrePais(string nombre){nombrePais=nombre;}
void Equipo::setRanking(int r){ranking = r;}
void Equipo::setConfederacion(string c) {
    confederacion = c;
}


//calculos para la tabla
int Equipo::getPuntos()const {return(ganados*3)+(empatados *1);}
int Equipo::getDiferenciaGoles()const{return golesFavor-golesContra;}

// Destructor de la clase Equipo

// Liberar la memoria dinámica reservada para el arreglo de jugadores.

// Elimina el arreglo de objetos Jugador creado con new[] en el constructor.

// Utiliza delete[] porque la memoria fue reservada como un arreglo dinámico.

// Si no se implementa este destructor, se produce una fuga de memoria
// ya que el arreglo de jugadores no se libera al destruir el objeto.

Equipo::~Equipo()
{
    delete[] jugadores;
}


// Inicializa jugadores y reparte los goles del equipo
// totalGoles: cantidad total de goles del equipo

// Asigna nombre, apellido y número a cada jugador.
// Distribuye los goles entre todos.

// Divide los goles equitativamente.
// Reparte los sobrantes a los primeros jugadores.

void Equipo::inicializarJugadores(int totalGoles)
{
    // Inicializar datos básicos
    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadores[i].setNombre("nombre" + to_string(i + 1));
        jugadores[i].setApellido("apellido" + to_string(i + 1));
        jugadores[i].setNumero(i + 1);
    }

    int golesPorJugador = totalGoles / cantidadJugadores;
    int sobrantes = totalGoles % cantidadJugadores;

    // Asignar goles base
    for (int i = 0; i < cantidadJugadores; i++)
    {
        for (int j = 0; j < golesPorJugador; j++)
        {
            jugadores[i].anotarGol();
        }
    }

    // Asignar goles sobrantes
    for (int i = 0; i < sobrantes; i++)
    {
        jugadores[i].anotarGol();
    }
}


// Muestra la información del equipo y sus jugadores

// Imprime el nombre del país y su ranking
// Recorre y muestra todos los jugadores

// Usa un ciclo para acceder al arreglo de jugadores
// Llama al método mostrar() de cada jugador

void Equipo::mostrarEquipo()
{
    cout << "Pais: " << nombrePais << endl;
    cout << "Ranking: " << ranking << endl;

    // Recorrer todos los jugadores del equipo
    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadores[i].mostrar();
    }
}


// Sobrecarga del operador < para ordenar equipos (tabla de posiciones)

// Define el criterio de comparación entre dos equipos
// Permite ordenar equipos según reglas del torneo

// 1. Compara puntos (mayor puntos = mejor equipo)
// 2. Si empatan, usa diferencia de goles
// 3. Si siguen empatados, usa goles a favor
// 4. Si todo es igual, decide aleatoriamente (sorteo)

bool Equipo::operator<(const Equipo& otro) const
{
    // Comparar puntos
    if(this->getPuntos() != otro.getPuntos())
        return this->getPuntos() > otro.getPuntos();

    // Comparar diferencia de goles
    if(this->getDiferenciaGoles() != otro.getDiferenciaGoles())
        return this->getDiferenciaGoles() > otro.getDiferenciaGoles();

    // Comparar goles a favor
    if(this->golesFavor != otro.golesFavor)
        return this->golesFavor > otro.golesFavor;

    // Desempate por sorteo
    int r = rand() % 2;

    if(r == 0)
        return true;
    else
        return false;
}


//retornamos el puntero al jugador para simular sus eventos del partido
// Devuelve un jugador según su posición
// Retorna nullptr si el índice es inválido
Jugador* Equipo::getJugador(int Indice)
{
    if(Indice >=0 && Indice <cantidadJugadores)return &jugadores[Indice];
    return nullptr;
}


//vamos actualizando el historial del equipo despues de un partido
// Actualiza estadísticas después de un partido
// golesAnotados: goles que hizo el equipo
// golesRecibidos: goles que le hicieron
void Equipo::registrarPartido(int golesAnotados, int golesRecibidos)
{
    golesFavor += golesAnotados;
    golesContra += golesRecibidos;
    if (golesAnotados >golesRecibidos)ganados++;
    else if (golesAnotados==golesRecibidos)empatados++;
    else perdidos++;
}
