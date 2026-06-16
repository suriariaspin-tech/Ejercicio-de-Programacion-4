#include <string.h>
#include "estructuras.h"

// Función para asignar el estado a una tarea
void AsignarEstado(struct Tarea *tarea, int estado) {
    if(estado == ESTADO_PENDIENTE) { // Si el estado es "Pendiente", asigna la cadena "Pendiente" al campo estado de la tarea
        strcpy(tarea->estado, "Pendiente");
    } else if(estado == ESTADO_EN_PROGRESO) { // Si el estado es "En Progreso", asigna la cadena "En Progreso" al campo estado de la tarea
        strcpy(tarea->estado, "En Progreso");
    } else {
        strcpy(tarea->estado, "Finalizada"); // Si el estado es "Finalizada", asigna la cadena "Finalizada" al campo estado de la tarea
    }
}
