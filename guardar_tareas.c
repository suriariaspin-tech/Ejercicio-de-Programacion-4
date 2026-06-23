#include <stdio.h>
#include "estructuras.h"
#include "guardar_tareas.h"

// Guardar tareas pendientes en un archivo de texto
void guardarPendientes(
    struct Tarea pendientes[],
    int cantPendientes
) {
    FILE *archivo;

    archivo = fopen("pendientes.txt", "w");

    if(archivo == NULL) {
        printf("Error al abrir pendientes.txt\n");
        return;
    }

    for(int i = 0; i < cantPendientes; i++) {
        fprintf(
            archivo,
            "%d|%s|%s|%s\n",
            pendientes[i].codigo,
            pendientes[i].titulo,
            pendientes[i].responsable,
            pendientes[i].prioridad
        );
    }

    fclose(archivo);
}

// Guardar tareas en proceso en un archivo de texto
void guardarEnProceso(
    struct Tarea enProceso[],
    int cantEnProceso
) {
    FILE *archivo;

    archivo = fopen("enproceso.txt", "w");

    if(archivo == NULL) {
        printf("Error al abrir enproceso.txt\n");
        return;
    }

    for(int i = 0; i < cantEnProceso; i++) {
        fprintf(
            archivo,
            "%d|%s|%s|%s\n",
            enProceso[i].codigo,
            enProceso[i].titulo,
            enProceso[i].responsable,
            enProceso[i].prioridad
        );
    }

    fclose(archivo);
}

// Guardar tareas finalizadas en un archivo de texto
void guardarFinalizadas(
    struct Tarea finalizadas[],
    int cantFinalizadas
) {
    FILE *archivo;

    archivo = fopen("finalizadas.txt", "w");

    if(archivo == NULL) {
        printf("Error al abrir finalizadas.txt\n");
        return;
    }

    for(int i = 0; i < cantFinalizadas; i++) {
        fprintf(
            archivo,
            "%d|%s|%s|%s\n",
            finalizadas[i].codigo,
            finalizadas[i].titulo,
            finalizadas[i].responsable,
            finalizadas[i].prioridad
        );
    }

    fclose(archivo);
}