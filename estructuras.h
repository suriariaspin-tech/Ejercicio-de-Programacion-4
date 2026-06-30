#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_TITULO 100 // Define el tamaño máximo para el título de una tarea
#define MAX_RESPONSABLE 50 // Define el tamaño máximo para el nombre del responsable de una tarea
#define MAX_ESTADO 20 // Define el tamaño máximo para el estado de una tarea

#define ESTADO_PENDIENTE 1 // Define el valor entero para representar el estado "Pendiente" de una tarea
#define ESTADO_EN_PROGRESO 2 // Define el valor entero para representar el estado "En Progreso" de una tarea
#define ESTADO_FINALIZADA 3  // Define el valor entero para representar el estado "Finalizada" de una tarea

// Modulo 1: definicion de la estructura principal del sistema.
struct Tarea {
    int codigo;
    char titulo[MAX_TITULO];
    char responsable[MAX_RESPONSABLE];
    char prioridad[20];
    char estado[MAX_ESTADO];
};

typedef struct Nodo {
    struct Tarea dato;
    struct Nodo *anterior;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *primero;
    Nodo *ultimo;
} Lista;

void AsignarEstado(struct Tarea *tarea, int estado);

#endif
