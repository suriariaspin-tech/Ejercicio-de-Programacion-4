#ifndef LISTA_H
#define LISTA_H

#include "tarea.h"

typedef struct Nodo {
    Tarea dato;
    struct Nodo *anterior;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *primero;
    Nodo *ultimo;
} Lista;

void inicializarLista(Lista *lista);
Nodo *crearNodo(Tarea tarea);
void insertarTareaFinal(Lista *lista, Tarea tarea);
Nodo *buscarTareaPorCodigo(Lista *lista, int codigo);
int extraerTareaPorCodigo(Lista *lista, int codigo, Tarea *tarea);
int contarTareas(Lista *lista);
void liberarLista(Lista *lista);

#endif
