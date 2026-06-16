#ifndef BUSQUEDAS_CONSULTAS_H
#define BUSQUEDAS_CONSULTAS_H

#include "estructuras.h"

// Modulo 3: funciones para buscar tareas y mostrar estadísticas.

void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas
);

#endif
