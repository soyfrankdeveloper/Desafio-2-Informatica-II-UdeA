UdeA World Cup 2026 Simulación de Torneo en C++

1. Descripción del proyecto

Este proyecto consiste en la simulación completa de un torneo de fútbol tipo mundial con 48 equipos, desarrollado en C++.

El sistema permite modelar desde la fase de grupos hasta la final, incluyendo estadísticas de equipos y jugadores, utilizando estructuras de datos, programación orientada a objetos y simulación probabilística.



2. Objetivo

Simular el comportamiento de un torneo real de fútbol teniendo en cuenta:

* Organización por grupos
* Restricciones por confederaciones
* Resultados probabilísticos de partidos
* Estadísticas individuales y colectivas
* Eliminatorias hasta obtener un campeón


3. Requisitos

Software

* Compilador C++ 
* Entorno de desarrollo Qt Creator o similar

Entrada requerida

* Archivo CSV con datos de equipos



4. Estructura del proyecto

/proyecto
 ├── main.cpp
 ├── Jugador.h / Jugador.cpp
 ├── Equipo.h / Equipo.cpp
 ├── Partido.h / Partido.cpp
 ├── Grupo.h / Grupo.cpp
 ├── Torneo.h / Torneo.cpp
 └── selecciones_clasificadas_mundial.csv


5. Flujo general del sistema

1. Se crea un objeto Torneo
2. Se cargan los equipos desde un archivo CSV
3. Se ordenan por ranking
4. Se distribuyen en grupos (12 grupos de 4 equipos)
5. Se generan y simulan partidos de grupo
6. Se calculan posiciones
7. Se clasifican equipos a eliminatorias
8. Se simulan fases finales
9. Se obtiene campeón, subcampeón y estadísticas
10. Se guardan datos en archivo externo


6. Arquitectura del sistema

El sistema está basado en programación orientada a objetos:

Clases principales:

 Clase    Responsabilidad                    
 
 Jugador  Representa un jugador individual   
 Equipo   Representa un equipo con jugadores 
 Partido  Simula un partido                  
 Grupo    Maneja la fase de grupos           
 Torneo   Controla todo el sistema           


7. Clase Jugador

Función

Representa un jugador con estadísticas individuales.

Atributos

* nombre, apellido → identificación
* número → camiseta
* goles → rendimiento ofensivo
* minutos → tiempo jugado
* amarillas, rojas → disciplina
* faltas → comportamiento defensivo
* asistencias → contribución ofensiva

Métodos principales

* anotarGol()
* jugarPartido(int minutos)
* recibirAmarilla()
* recibirRoja()
* hacerFalta()

Justificación de tipos

* int: conteo eficiente
* string: manejo de texto


8. Clase Equipo

Función

Representa un equipo y sus estadísticas.

Atributos

* nombrePais
* ranking
* confederación
* grupo
* jugadores (arreglo dinámico de 26 jugadores)

Estadísticas

* goles a favor / contra
* partidos ganados, empatados, perdidos

Métodos clave:

inicializarJugadores(int totalGoles):

Distribuye goles entre jugadores.

registrarPartido(int gf, int gc):

Actualiza estadísticas del equipo.

operator<

Permite ordenar equipos según:

1. Puntos
2. Diferencia de goles
3. Goles a favor
4. Aleatorio (desempate)

* Uso de punteros (Jugador*) para memoria dinámica
* int para cálculos rápidos


9. Clase Partido

Función

Simular un partido entre dos equipos.

Atributos

* Equipos participantes
* Goles
* Posesión
* Goleadores
* Árbitros
* Estadio y fecha

Método principal: simular()

Realiza:

* Cálculo probabilístico de goles
* Simulación de jugadores (11 por equipo)
* Generación de eventos:

  * goles
  * tarjetas
  * faltas
* Cálculo de posesión basado en ranking
* Prórroga y desempate

Justificación

* double para probabilidades
* arrays para eficiencia en memoria

10. Clase Grupo

Función

Gestiona un grupo de 4 equipos.

Atributos

* 4 equipos
* 6 partidos

Métodos

generarPartidos():

Todos contra todos (6 partidos)

simularGrupo():

Ejecuta partidos

mostrarTabla():

Ordena y muestra resultados

Algoritmo usado:

Ordenamiento tipo burbuja 


11. Clase Torneo

Función

Controla toda la simulación.

Atributos

* 48 equipos
* 12 grupos
* estructuras para eliminatorias


Métodos principales:

cargarEquiposDesdeCSV():

Lee archivo externo y crea equipos.

armarGrupos():

* Ordena por ranking
* Usa bombos
* Aplica reglas de confederación

simularFaseGrupos():

Simula todos los grupos.

simularFasesFinales():

* Clasifica equipos
* Genera llaves
* Simula eliminatorias

mostrarEstadisticasFinales():

* Campeón
* Goleadores
* Estadísticas globales

guardarDatos():

Guarda resultados en archivo .txt


12. Lógica de simulación

El sistema usa un modelo probabilístico basado en:

* Goles históricos
* Ranking FIFA (aproximado)
* Probabilidades aleatorias rand()

Esto permite resultados variables en cada ejecución.


13. Manejo de memoria

* Uso de `new` y `delete`
* Liberación en destructores:

  * Equipo
  * Grupo
  * Torneo

Evita fugas de memoria


14. Entrada de datos

Formato del CSV:

Ranking;Pais;...;Confederacion;GolesFavor;GolesContra


15. Salida del sistema

* Resultados en consola
* Archivo `jugadores.txt` con estadísticas


16. Limitaciones

* No usa base de datos
* No tiene interfaz gráfica
* Modelo probabilístico simplificado
* Uso de arrays en lugar de estructuras modernas



17. Métricas del sistema

El programa incluye una función para estimar:

* Memoria usada
* Número de iteraciones

Esto permite analizar el rendimiento del sistema.


19. Ejecución

1. Compilar el proyecto
2. Ejecutar `main.cpp`
3. Seleccionar opciones del menú:


    1. Cargar equipos
    2. Armar grupos
    3. Simular grupos
    4. Simular eliminatorias
    5. Ver estadísticas
    6. Guardar datos


El proyecto implementa de forma completa:

* Programación orientada a objetos
* Manejo de memoria dinámica
* Simulación probabilística
* Organización de estructuras complejas

Permite representar de forma funcional un torneo de fútbol completo.



