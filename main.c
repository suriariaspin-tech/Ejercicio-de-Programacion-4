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
#include "cargar_codigos.h"

int main() {
    cargarCodigos();

    Lista pendientes;
    Lista enProceso;
    Lista finalizadas;

    inicializarLista(&pendientes);
    inicializarLista(&enProceso);
    inicializarLista(&finalizadas);

    cargarTareas(&pendientes, &enProceso, &finalizadas);

    int opcion;

    do {
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
        } while(opcion < 1 || opcion > 9);

        switch(opcion) {
            case 1:
                registrarTarea(&pendientes, &enProceso, &finalizadas);
                break;
            case 2:
                mostrarTablero(&pendientes, &enProceso, &finalizadas);
                break;
            case 3:
                buscarTarea(&pendientes, &enProceso, &finalizadas);
                break;
            case 4:
                modificarTarea(&pendientes, &enProceso, &finalizadas);
                break;
            case 5:
                cambiarEstado(&pendientes, &enProceso, &finalizadas);
                break;
            case 6:
                eliminarTarea(&pendientes, &enProceso, &finalizadas);
                break;
            case 7:
                mostrarEstadisticas(
                    contarTareas(&pendientes),
                    contarTareas(&enProceso),
                    contarTareas(&finalizadas)
                );
                break;
            case 8:
                guardarTareas(&pendientes, &enProceso, &finalizadas);
                printf("Datos guardados en tareas.txt\n");
                break;
            case 9:
                printf("\nSaliendo del sistema...\n");
                guardarTareas(&pendientes, &enProceso, &finalizadas);
                break;
        }
    } while(opcion != 9);

    liberarLista(&pendientes);
    liberarLista(&enProceso);
    liberarLista(&finalizadas);

    return 0;
}
