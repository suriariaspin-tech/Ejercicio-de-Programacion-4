#include <stdio.h>
#include <string.h>
#include "busquedas_consultas.h"
#include "validaciones.h"

void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas
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

        for(int i = 0; i < totalPendientes; i++) {
            if(pendientes[i].codigo == codigo) {
                printf("\nCodigo: %d\n", pendientes[i].codigo);
                printf("Titulo: %s\n", pendientes[i].titulo);
                printf("Responsable: %s\n", pendientes[i].responsable);
                printf("Prioridad: %s\n", pendientes[i].prioridad);
                printf("Estado: %s\n", pendientes[i].estado);
                return;
            }
        }

        for(int i = 0; i < totalProgreso; i++) {
            if(progreso[i].codigo == codigo) {
                printf("\nCodigo: %d\n", progreso[i].codigo);
                printf("Titulo: %s\n", progreso[i].titulo);
                printf("Responsable: %s\n", progreso[i].responsable);
                printf("Prioridad: %s\n", progreso[i].prioridad);
                printf("Estado: %s\n", progreso[i].estado);
                return;
            }
        }

        for(int i = 0; i < totalFinalizadas; i++) {
            if(finalizadas[i].codigo == codigo) {
                printf("\nCodigo: %d\n", finalizadas[i].codigo);
                printf("Titulo: %s\n", finalizadas[i].titulo);
                printf("Responsable: %s\n", finalizadas[i].responsable);
                printf("Prioridad: %s\n", finalizadas[i].prioridad);
                printf("Estado: %s\n", finalizadas[i].estado);
                return;
            }
        }

        printf("Tarea no encontrada.\n");
    } else {
        char responsable[MAX_RESPONSABLE];
        int encontrado = 0;

        LimpiarBuffer();
        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE);

        for(int i = 0; i < totalPendientes; i++) {
            if(strcmp(pendientes[i].responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n",
                    pendientes[i].codigo,
                    pendientes[i].titulo,
                    pendientes[i].estado);
                encontrado = 1;
            }
        }

        for(int i = 0; i < totalProgreso; i++) {
            if(strcmp(progreso[i].responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n",
                    progreso[i].codigo,
                    progreso[i].titulo,
                    progreso[i].estado);
                encontrado = 1;
            }
        }

        for(int i = 0; i < totalFinalizadas; i++) {
            if(strcmp(finalizadas[i].responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n",
                    finalizadas[i].codigo,
                    finalizadas[i].titulo,
                    finalizadas[i].estado);
                encontrado = 1;
            }
        }

        if(!encontrado) {
            printf("No se encontraron tareas.\n");
        }
    }
}
