#ifndef REGISTRO_ELIMINACION_H
#define REGISTRO_ELIMINACION_H

#include "estructuras.h"

int codigoExiste(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas,
    int codigo
);

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
