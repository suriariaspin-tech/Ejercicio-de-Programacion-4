#include <string.h>
#include "tarea.h"

void AsignarEstado(Tarea *tarea, int estado) {
    if(estado == ESTADO_PENDIENTE) {
        strcpy(tarea->estado, "Pendiente");
    } else if(estado == ESTADO_EN_PROGRESO) {
        strcpy(tarea->estado, "En Progreso");
    } else {
        strcpy(tarea->estado, "Finalizada");
    }
}
