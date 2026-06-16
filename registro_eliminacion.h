#ifndef REGISTRO_ELIMINACION_H
#define REGISTRO_ELIMINACION_H

#include "estructuras.h"

// Modulo 2: funciones para registrar y eliminar tareas.

void registrarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea enProceso[],
    int *cantEnProceso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
);

void eliminarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea progreso[],
    int *cantProgreso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
);

#endif
