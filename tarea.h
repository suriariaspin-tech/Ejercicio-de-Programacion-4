#ifndef TAREA_H
#define TAREA_H

#define MAX_TITULO 100
#define MAX_RESPONSABLE 50
#define MAX_ESTADO 20

#define ESTADO_PENDIENTE 1
#define ESTADO_EN_PROGRESO 2
#define ESTADO_FINALIZADA 3

typedef struct {
    int codigo;
    char titulo[MAX_TITULO];
    char responsable[MAX_RESPONSABLE];
    int prioridad;
    char estado[MAX_ESTADO];
} Tarea;

void AsignarEstado(Tarea *tarea, int estado);

#endif
