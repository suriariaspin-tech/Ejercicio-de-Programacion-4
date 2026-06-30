#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "archivo.h"

void guardarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    FILE *archivo = fopen("tareas.txt", "w");
    if(archivo == NULL) {
        fprintf(stderr, "Error al abrir tareas.txt: %s\n", strerror(errno));
        return;
    }

    Nodo *actual = pendientes->primero;
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    actual = enProceso->primero;
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    actual = finalizadas->primero;
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    fclose(archivo);
}

int cargarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
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
        Tarea tarea;
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
        tarea.prioridad = atoi(token);

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
