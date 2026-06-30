#ifndef REGISTRO_ELIMINACION_H
#define REGISTRO_ELIMINACION_H

#include "estructuras.h"

// Modulo 2: funciones para registrar, modificar y eliminar tareas.

void registrarTarea(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

void modificarTarea(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

void eliminarTarea(
    Lista *pendientes,
    Lista *progreso,
    Lista *finalizadas
);

#endif
