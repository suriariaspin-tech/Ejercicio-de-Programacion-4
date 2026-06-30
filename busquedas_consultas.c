#include <stdio.h>
#include <string.h>
#include "busquedas_consultas.h"
#include "validaciones.h"
#include "guardar_tareas.h"

// Función para buscar tareas por código o responsable
void buscarTarea(
    Lista *pendientes,
    Lista *progreso,
    Lista *finalizadas
) {
    int opcionBusqueda;

    printf("\nBUSCAR TAREA\n");
    printf("1. Buscar por codigo\n");
    printf("2. Buscar por responsable\n");

    do {
        printf("Seleccione una opcion: ");
        ValidarEntero(&opcionBusqueda);

        if(opcionBusqueda < 1 || opcionBusqueda > 2) {
            printf("Opcion invalida.\n");
        }
    } while(opcionBusqueda < 1 || opcionBusqueda > 2);

    if(opcionBusqueda == 1) {
        int codigo;
        printf("Ingrese el codigo a buscar: ");
        ValidarEntero(&codigo);

        Nodo *tarea = buscarTareaPorCodigo(pendientes, codigo);
        if(tarea != NULL) {
            printf("\nCodigo: %d\n", tarea->dato.codigo);
            printf("Titulo: %s\n", tarea->dato.titulo);
            printf("Responsable: %s\n", tarea->dato.responsable);
            printf("Prioridad: %s\n", tarea->dato.prioridad);
            printf("Estado: %s\n", tarea->dato.estado);
            return;
        }

        tarea = buscarTareaPorCodigo(progreso, codigo);
        if(tarea != NULL) {
            printf("\nCodigo: %d\n", tarea->dato.codigo);
            printf("Titulo: %s\n", tarea->dato.titulo);
            printf("Responsable: %s\n", tarea->dato.responsable);
            printf("Prioridad: %s\n", tarea->dato.prioridad);
            printf("Estado: %s\n", tarea->dato.estado);
            return;
        }

        tarea = buscarTareaPorCodigo(finalizadas, codigo);
        if(tarea != NULL) {
            printf("\nCodigo: %d\n", tarea->dato.codigo);
            printf("Titulo: %s\n", tarea->dato.titulo);
            printf("Responsable: %s\n", tarea->dato.responsable);
            printf("Prioridad: %s\n", tarea->dato.prioridad);
            printf("Estado: %s\n", tarea->dato.estado);
            return;
        }

        printf("Tarea no encontrada.\n");
    } else {
        char responsable[MAX_RESPONSABLE];
        int encontrado = 0;

        LimpiarBuffer();
        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE);

        Nodo *actual = pendientes->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        actual = progreso->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        actual = finalizadas->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        if(!encontrado) {
            printf("No se encontraron tareas.\n");
        }
    }
}
