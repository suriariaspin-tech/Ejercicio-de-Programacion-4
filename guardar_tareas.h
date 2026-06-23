#ifndef GUARDAR_TAREAS_H
#define GUARDAR_TAREAS_H

// Guardar tareas en archivos de texto
void guardarPendientes(
    struct Tarea pendientes[],
    int cantPendientes
);

void guardarEnProceso(
    struct Tarea enProceso[],
    int cantEnProceso
);

void guardarFinalizadas(
    struct Tarea finalizadas[],
    int cantFinalizadas
);

#endif