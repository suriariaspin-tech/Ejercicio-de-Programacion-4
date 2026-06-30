#ifndef TABLERO_KANBAN_H
#define TABLERO_KANBAN_H

#include "estructuras.h"

// Modulo 4: funciones para mostrar el tablero y cambiar el estado de las tareas.

void mostrarTablero(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

void cambiarEstado(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

#endif
