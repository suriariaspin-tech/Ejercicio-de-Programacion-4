/*
Nombres: Nicolás Menéndez, Joel Cruz y Suri Arias
Fecha: 09/06/2026
Descripción: Sistema Kanban para la gestión de tareas.
El programa permite registrar tareas, moverlas entre diferentes estados del tablero Kanban, buscar tareas, eliminarlas y visualizar el estado actual del proyecto.
Estados disponibles: Pendiente, En Progreso, Finalizada
Cada tarea posee un código único, un título, un responsable, una prioridad y un estado.
*/


#include <stdio.h>
#include "busquedas_consultas.h"
#include "estadisticas.h"
#include "estructuras.h"
#include "registro_eliminacion.h"
#include "tablero_kanban.h"
#include "validaciones.h"

int main() {

    // Arreglo para almacenar las tareas pendientes
    struct Tarea pendientes[MAX_TAREAS];

    // Arreglo para almacenar las tareas en progreso
    struct Tarea enProceso[MAX_TAREAS];

    // Arreglo para almacenar las tareas finalizadas
    struct Tarea finalizadas[MAX_TAREAS];

    // Contador de tareas pendientes
    int totalPendientes = 0;

    // Contador de tareas en progreso
    int totalEnProceso = 0;

    // Contador de tareas finalizadas
    int totalFinalizadas = 0;

    // Variable para almacenar la opción seleccionada
    int opcion;

    do {
        printf("1. Registrar tarea\n");
        printf("2. Mostrar tablero\n");
        printf("3. Mover tarea\n");
        printf("4. Buscar tarea\n");
        printf("5. Eliminar tarea\n");
        printf("6. Estadisticas\n");
        printf("7. Salir\n");

        do { // Bucle para solicitar la opción hasta que sea válida
            printf("Seleccione una opcion: ");
            ValidarEntero(&opcion); // Validar que la opción sea un número entero positivo
            if(opcion < 1 || opcion > 7) { // Verifica si la opción ingresada no es válida (menor a 1 o mayor a 6)
                printf("Opcion invalida. Intente nuevamente.\n");
            }
        } while(opcion < 1 || opcion > 7);


        switch(opcion) {
            case 1:
                // Registrar una nueva tarea
                registrarTarea(
                pendientes,
                &totalPendientes,
                enProceso,
                &totalEnProceso,
                finalizadas,
                &totalFinalizadas
                );

                break;

            case 2:
                // Mostrar tablero
                mostrarTablero(
                pendientes,
                totalPendientes,
                enProceso,
                totalEnProceso,
                finalizadas,
                totalFinalizadas
                );

                break;

            case 3:
                // Mover una tarea entre estados
                cambiarEstado(
                pendientes,
                &totalPendientes,
                enProceso,
                &totalEnProceso,
                finalizadas,
                &totalFinalizadas
                );

                break;

            case 4:
                // Buscar una tarea por código
                buscarTarea(
                    pendientes,
                    totalPendientes,
                    enProceso,
                    totalEnProceso,
                    finalizadas,
                    totalFinalizadas
                );

                break;

            case 5:
                // Eliminar una tarea del sistema
                eliminarTarea(
                    pendientes,
                    &totalPendientes,
                    enProceso,
                    &totalEnProceso,
                    finalizadas,
                    &totalFinalizadas
                );
                break;

            case 6:
                mostrarEstadisticas(
                totalPendientes,
                totalEnProceso,
                totalFinalizadas
                );
                break;

            case 7:
                printf("\nSaliendo del sistema...\n");
                break;
        }

    } while(opcion != 7);
    return 0;
}
