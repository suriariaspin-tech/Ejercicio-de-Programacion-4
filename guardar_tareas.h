#ifndef GUARDAR_TAREAS_H
#define GUARDAR_TAREAS_H

#include "estructuras.h"

void inicializarLista(Lista *lista);
Nodo *crearNodo(struct Tarea tarea);
void insertarTareaFinal(Lista *lista, struct Tarea tarea);
int extraerTareaPorCodigo(Lista *lista, int codigo, struct Tarea *tarea);
Nodo *buscarTareaPorCodigo(Lista *lista, int codigo);
int contarTareas(Lista *lista);
void liberarLista(Lista *lista);

void guardarTareas(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

int cargarTareas(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
);

#endif