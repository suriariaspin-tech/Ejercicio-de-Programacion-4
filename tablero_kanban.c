#include <stdio.h>
#include "tablero_kanban.h"
#include "validaciones.h"
#include "guardar_tareas.h"

static void imprimirLista(Lista *lista) {
    if(lista->primero == NULL) {
        printf("No hay tareas.\n");
        return;
    }

    Nodo *actual = lista->primero;
    while(actual != NULL) {
        printf("[%d] %s\n\n", actual->dato.codigo, actual->dato.titulo);
        actual = actual->siguiente;
    }
}

void mostrarTablero(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    printf("\n      PENDIENTES\n");
    printf("========================\n");
    if(pendientes->primero == NULL) {
        printf("No hay tareas pendientes.\n\n");
    } else {
        imprimirLista(pendientes);
    }

    printf("     EN PROGRESO\n");
    printf("========================\n");
    if(enProceso->primero == NULL) {
        printf("No hay tareas en proceso.\n\n");
    } else {
        imprimirLista(enProceso);
    }

    printf("      FINALIZADAS\n");
    printf("========================\n");
    if(finalizadas->primero == NULL) {
        printf("No hay tareas finalizadas.\n\n");
    } else {
        imprimirLista(finalizadas);
    }
}

void cambiarEstado(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    int codigo;
    int opcion;
    struct Tarea tarea;

    printf("Ingrese el codigo de la tarea a mover: ");
    ValidarEntero(&codigo);

    if(buscarTareaPorCodigo(pendientes, codigo) != NULL) {
        do {
            printf("Mover a:\n");
            printf("1. En Progreso\n");
            printf("2. Finalizada\n");
            printf("Opcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(pendientes, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_EN_PROGRESO);
                insertarTareaFinal(enProceso, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_FINALIZADA);
                insertarTareaFinal(finalizadas, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    if(buscarTareaPorCodigo(enProceso, codigo) != NULL) {
        do {
            printf("Mover a:\n");
            printf("1. Pendiente\n");
            printf("2. Finalizada\n");
            printf("Opcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(enProceso, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_PENDIENTE);
                insertarTareaFinal(pendientes, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_FINALIZADA);
                insertarTareaFinal(finalizadas, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    if(buscarTareaPorCodigo(finalizadas, codigo) != NULL) {
        do {
            printf("Mover a:\n");
            printf("1. Pendiente\n");
            printf("2. En Progreso\n");
            printf("Opcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(finalizadas, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_PENDIENTE);
                insertarTareaFinal(pendientes, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_EN_PROGRESO);
                insertarTareaFinal(enProceso, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
