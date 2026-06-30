/*
Nombres: Nicolás Menéndez, Joel Cruz y Suri Arias
Fecha: 09/06/2026
Descripción: Sistema Kanban para la gestión de tareas.
El programa permite registrar tareas, moverlas entre diferentes estados del tablero Kanban, buscar tareas, eliminarlas y visualizar el estado actual del proyecto.
Estados disponibles: Pendiente, En Progreso, Finalizada
Cada tarea posee un código único, un título, un responsable, una prioridad y un estado.
*/


#include <stdio.h>
#include "tarea.h"
#include "lista.h"
#include "archivo.h"
#include "kanban.h"
#include "validaciones.h"

int main() {
    Lista pendientes; // Lista para tareas pendientes
    Lista enProceso; // Lista para tareas en proceso
    Lista finalizadas; // Lista para tareas finalizadas

    inicializarLista(&pendientes); // Función para inicializar la lista de tareas pendientes
    inicializarLista(&enProceso); // Función para inicializar la lista de tareas en proceso
    inicializarLista(&finalizadas); // Función para inicializar la lista de tareas finalizadas

    cargarTareas(&pendientes, &enProceso, &finalizadas); // Función para cargar tareas desde un archivo al iniciar el programa

    int opcion;

    do {
        // Menú principal del sistema Kanban
        printf("\nSISTEMA KANBAN:\n");
        printf("1. Registrar tarea\n");
        printf("2. Mostrar tablero\n");
        printf("3. Buscar tarea\n");
        printf("4. Modificar tarea\n");
        printf("5. Cambiar estado\n");
        printf("6. Eliminar tarea\n");
        printf("7. Estadisticas\n");
        printf("8. Guardar datos\n");
        printf("9. Salir\n");

        do {
            printf("Seleccione una opcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 9) {
                printf("Opcion invalida. Intente nuevamente.\n");
            }
        } while(opcion < 1 || opcion > 9); // Bucle para validar que la opción ingresada esté dentro del rango permitido (1-9)

        switch(opcion) {
            case 1:
                registrarTarea(&pendientes, &enProceso, &finalizadas); // Función para registrar una nueva tarea
                break;
            case 2:
                mostrarTablero(&pendientes, &enProceso, &finalizadas); // Función para mostrar el tablero Kanban con las tareas en sus respectivos estados
                break;
            case 3:
                buscarTarea(&pendientes, &enProceso, &finalizadas); // Función para buscar una tarea por código o responsable
                break;
            case 4:
                modificarTarea(&pendientes, &enProceso, &finalizadas); // Función para modificar los detalles de una tarea existente
                break;
            case 5:
                cambiarEstado(&pendientes, &enProceso, &finalizadas); // Función para cambiar el estado de una tarea (moverla entre Pendiente, En Progreso y Finalizada)
                break;
            case 6:
                eliminarTarea(&pendientes, &enProceso, &finalizadas); // Función para eliminar una tarea
                break;
            case 7:
                mostrarEstadisticas(
                    contarTareas(&pendientes),
                    contarTareas(&enProceso),
                    contarTareas(&finalizadas)
                ); // Función para mostrar estadísticas del proyecto, incluyendo la cantidad de tareas en cada estado
                break;
            case 8:
                guardarTareas(&pendientes, &enProceso, &finalizadas); // Función para guardar las tareas en un archivo antes de salir del programa
                printf("Datos guardados en tareas.txt\n");
                break;
            case 9:
                printf("\nSaliendo del sistema...\n");
                guardarTareas(&pendientes, &enProceso, &finalizadas); // Guardar las tareas antes de salir
                printf("Datos guardados en tareas.txt\n");
                break;
        }
    } while(opcion != 9);

    liberarLista(&pendientes); // Función para liberar la memoria utilizada por la lista de tareas pendientes
    liberarLista(&enProceso); // Función para liberar la memoria utilizada por la lista de tareas en proceso
    liberarLista(&finalizadas); // Función para liberar la memoria utilizada por la lista de tareas finalizadas

    return 0;
}
