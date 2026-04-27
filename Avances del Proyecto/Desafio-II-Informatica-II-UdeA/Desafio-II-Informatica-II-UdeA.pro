TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Equipo.cpp \
        Grupo.cpp \
        Jugador.cpp \
        Partido.cpp \
        Torneo.cpp \
        main.cpp

HEADERS += \
    Equipo.h \
    Grupo.h \
    Jugador.h \
    Partido.h \
    Torneo.h

DISTFILES += \
    README.md
