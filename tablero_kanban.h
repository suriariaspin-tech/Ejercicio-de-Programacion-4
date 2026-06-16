#ifndef TABLERO_KANBAN_H
#define TABLERO_KANBAN_H

#include "estructuras.h"

// Modulo 4: funciones para mostrar el tablero y cambiar el estado de las tareas.

void mostrarTablero(
    struct Tarea pendientes[],
    int cantPendientes,
    struct Tarea enProceso[],
    int cantEnProceso,
    struct Tarea finalizadas[],
    int cantFinalizadas
);

void cambiarEstado(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea enProceso[],
    int *cantEnProceso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
);

#endif
