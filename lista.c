#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

void inicializarLista(Lista *lista) {
    lista->primero = NULL;
    lista->ultimo = NULL;
}

Nodo *crearNodo(Tarea tarea) {
    Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));
    if(nuevo == NULL) {
        fprintf(stderr, "Error de memoria al crear la tarea.\n");
        return NULL;
    }

    nuevo->dato = tarea;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertarTareaFinal(Lista *lista, Tarea tarea) {
    Nodo *nuevo = crearNodo(tarea);
    if(nuevo == NULL) {
        return;
    }

    if(lista->primero == NULL) {
        lista->primero = nuevo;
        lista->ultimo = nuevo;
    } else {
        lista->ultimo->siguiente = nuevo;
        nuevo->anterior = lista->ultimo;
        lista->ultimo = nuevo;
    }
}

Nodo *buscarTareaPorCodigo(Lista *lista, int codigo) {
    Nodo *actual = lista->primero;
    while(actual != NULL) {
        if(actual->dato.codigo == codigo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

int extraerTareaPorCodigo(Lista *lista, int codigo, Tarea *tarea) {
    Nodo *actual = buscarTareaPorCodigo(lista, codigo);
    if(actual == NULL) {
        return 0;
    }

    *tarea = actual->dato;

    if(actual->anterior != NULL) {
        actual->anterior->siguiente = actual->siguiente;
    } else {
        lista->primero = actual->siguiente;
    }

    if(actual->siguiente != NULL) {
        actual->siguiente->anterior = actual->anterior;
    } else {
        lista->ultimo = actual->anterior;
    }

    free(actual);
    return 1;
}

int contarTareas(Lista *lista) {
    int total = 0;
    Nodo *actual = lista->primero;
    while(actual != NULL) {
        total++;
        actual = actual->siguiente;
    }
    return total;
}

void liberarLista(Lista *lista) {
    Nodo *actual = lista->primero;
    while(actual != NULL) {
        Nodo *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    lista->primero = NULL;
    lista->ultimo = NULL;
}
