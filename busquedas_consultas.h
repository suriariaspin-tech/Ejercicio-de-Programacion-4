#ifndef BUSQUEDAS_CONSULTAS_H
#define BUSQUEDAS_CONSULTAS_H

#include "estructuras.h"

void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas
);

#endif
