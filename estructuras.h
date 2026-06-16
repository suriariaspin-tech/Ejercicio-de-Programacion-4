#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_TAREAS 20
#define MAX_TITULO 100
#define MAX_RESPONSABLE 50
#define MAX_ESTADO 20

enum EstadoTarea {
    ESTADO_PENDIENTE = 1,
    ESTADO_EN_PROGRESO = 2,
    ESTADO_FINALIZADA = 3
};

// Modulo 1: definicion de la estructura principal del sistema.
struct Tarea {
    int codigo;
    char titulo[MAX_TITULO];
    char responsable[MAX_RESPONSABLE];
    char prioridad[20];
    char estado[MAX_ESTADO];
};

void AsignarEstado(struct Tarea *tarea, int estado);

#endif
