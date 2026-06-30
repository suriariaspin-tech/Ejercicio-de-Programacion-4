#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "guardar_tareas.h"

void inicializarLista(Lista *lista) {
    lista->primero = NULL;
    lista->ultimo = NULL;
}

Nodo *crearNodo(struct Tarea tarea) {
    Nodo *nuevo = (Nodo *) malloc(sizeof(Nodo));
    if(nuevo == NULL) {
        return NULL;
    }
    nuevo->dato = tarea;
    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;
    return nuevo;
}

void insertarTareaFinal(Lista *lista, struct Tarea tarea) {
    Nodo *nuevo = crearNodo(tarea);
    if(nuevo == NULL) {
        fprintf(stderr, "Error de memoria al crear la tarea.\n");
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

int extraerTareaPorCodigo(Lista *lista, int codigo, struct Tarea *tarea) {
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

void guardarTareas(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    FILE *archivo = fopen("tareas.txt", "w");
    if(archivo == NULL) {
        fprintf(stderr, "Error al abrir tareas.txt: %s\n", strerror(errno));
        return;
    }

    Nodo *actual = pendientes->primero;
    while(actual != NULL) {
        fprintf(
            archivo,
            "%d|%s|%s|%s|%s\n",
            actual->dato.codigo,
            actual->dato.titulo,
            actual->dato.responsable,
            actual->dato.prioridad,
            actual->dato.estado
        );
        actual = actual->siguiente;
    }

    actual = enProceso->primero;
    while(actual != NULL) {
        fprintf(
            archivo,
            "%d|%s|%s|%s|%s\n",
            actual->dato.codigo,
            actual->dato.titulo,
            actual->dato.responsable,
            actual->dato.prioridad,
            actual->dato.estado
        );
        actual = actual->siguiente;
    }

    actual = finalizadas->primero;
    while(actual != NULL) {
        fprintf(
            archivo,
            "%d|%s|%s|%s|%s\n",
            actual->dato.codigo,
            actual->dato.titulo,
            actual->dato.responsable,
            actual->dato.prioridad,
            actual->dato.estado
        );
        actual = actual->siguiente;
    }

    fclose(archivo);
}

int cargarTareas(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    FILE *archivo = fopen("tareas.txt", "r");
    if(archivo == NULL) {
        archivo = fopen("tareas.txt", "w");
        if(archivo != NULL) {
            fclose(archivo);
        }
        return 0;
    }

    char linea[256];
    while(fgets(linea, sizeof(linea), archivo) != NULL) {
        struct Tarea tarea;
        char *token = strtok(linea, "|");
        if(token == NULL) {
            continue;
        }
        tarea.codigo = atoi(token);

        token = strtok(NULL, "|");
        if(token == NULL) {
            continue;
        }
        strncpy(tarea.titulo, token, MAX_TITULO);
        tarea.titulo[MAX_TITULO - 1] = '\0';

        token = strtok(NULL, "|");
        if(token == NULL) {
            continue;
        }
        strncpy(tarea.responsable, token, MAX_RESPONSABLE);
        tarea.responsable[MAX_RESPONSABLE - 1] = '\0';

        token = strtok(NULL, "|");
        if(token == NULL) {
            continue;
        }
        strncpy(tarea.prioridad, token, sizeof(tarea.prioridad));
        tarea.prioridad[sizeof(tarea.prioridad) - 1] = '\0';

        token = strtok(NULL, "|\r\n");
        if(token == NULL) {
            continue;
        }
        strncpy(tarea.estado, token, MAX_ESTADO);
        tarea.estado[MAX_ESTADO - 1] = '\0';

        if(strcmp(tarea.estado, "Pendiente") == 0) {
            insertarTareaFinal(pendientes, tarea);
        } else if(strcmp(tarea.estado, "En Progreso") == 0) {
            insertarTareaFinal(enProceso, tarea);
        } else if(strcmp(tarea.estado, "Finalizada") == 0) {
            insertarTareaFinal(finalizadas, tarea);
        } else {
            AsignarEstado(&tarea, ESTADO_PENDIENTE);
            insertarTareaFinal(pendientes, tarea);
        }
    }

    fclose(archivo);
    return 1;
}