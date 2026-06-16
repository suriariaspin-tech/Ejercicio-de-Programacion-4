#include <stdio.h>
#include <string.h>
#include "busquedas_consultas.h"
#include "validaciones.h"

// Función para buscar tareas por código o responsable
void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas
) {
    int opcionBusqueda; // Variable para almacenar la opción de búsqueda seleccionada por el usuario

    printf("\nBUSCAR TAREA\n");
    printf("1. Buscar por codigo\n");
    printf("2. Buscar por responsable\n");

    do { // Bucle para solicitar la opción de búsqueda hasta que sea válida
        printf("Seleccione una opcion: ");
        ValidarEntero(&opcionBusqueda);

        if(opcionBusqueda < 1 || opcionBusqueda > 2) {
            printf("Opcion invalida.\n");
        }
    } while(opcionBusqueda < 1 || opcionBusqueda > 2);

    if(opcionBusqueda == 1) { // Si la opción de búsqueda es por código
        int codigo; // Variable para almacenar el código ingresado por el usuario

        printf("Ingrese el codigo a buscar: ");
        ValidarEntero(&codigo);

        for(int i = 0; i < totalPendientes; i++) { // Recorre el arreglo de tareas pendientes
            if(pendientes[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
                printf("\nCodigo: %d\n", pendientes[i].codigo);
                printf("Titulo: %s\n", pendientes[i].titulo);
                printf("Responsable: %s\n", pendientes[i].responsable);
                printf("Prioridad: %s\n", pendientes[i].prioridad);
                printf("Estado: %s\n", pendientes[i].estado);
                return;
            }
        }

        for(int i = 0; i < totalProgreso; i++) { // Recorre el arreglo de tareas en progreso
            if(progreso[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
                printf("\nCodigo: %d\n", progreso[i].codigo);
                printf("Titulo: %s\n", progreso[i].titulo);
                printf("Responsable: %s\n", progreso[i].responsable);
                printf("Prioridad: %s\n", progreso[i].prioridad);
                printf("Estado: %s\n", progreso[i].estado);
                return;
            }
        }

        for(int i = 0; i < totalFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
            if(finalizadas[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
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
        char responsable[MAX_RESPONSABLE]; // Variable para almacenar el nombre del responsable ingresado por el usuario
        int encontrado = 0; // Variable para indicar si se encontraron tareas asociadas al responsable ingresado

        LimpiarBuffer();
        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE);

        for(int i = 0; i < totalPendientes; i++) { // Recorre el arreglo de tareas pendientes
            if(strcmp(pendientes[i].responsable, responsable) == 0) { // Compara el nombre del responsable de cada tarea con el nombre ingresado
                printf("\n[%d] %s - %s\n",
                    pendientes[i].codigo,
                    pendientes[i].titulo,
                    pendientes[i].estado);
                encontrado = 1; // Si se encuentra al menos una tarea asociada al responsable ingresado, se establece la variable "encontrado" en 1 para indicar que se encontraron tareas
            }
        }

        for(int i = 0; i < totalProgreso; i++) { // Recorre el arreglo de tareas en progreso
            if(strcmp(progreso[i].responsable, responsable) == 0) { // Compara el nombre del responsable de cada tarea con el nombre ingresado
                printf("\n[%d] %s - %s\n",
                    progreso[i].codigo,
                    progreso[i].titulo,
                    progreso[i].estado);
                encontrado = 1; // Si se encuentra al menos una tarea asociada al responsable ingresado, se establece la variable "encontrado" en 1 para indicar que se encontraron tareas
            }
        }

        for(int i = 0; i < totalFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
            if(strcmp(finalizadas[i].responsable, responsable) == 0) { // Compara el nombre del responsable de cada tarea con el nombre ingresado
                printf("\n[%d] %s - %s\n",
                    finalizadas[i].codigo,
                    finalizadas[i].titulo,
                    finalizadas[i].estado);
                encontrado = 1; // Si se encuentra al menos una tarea asociada al responsable ingresado, se establece la variable "encontrado" en 1 para indicar que se encontraron tareas
            }
        }

        if(!encontrado) {
            printf("No se encontraron tareas.\n");
        }
    }
}
