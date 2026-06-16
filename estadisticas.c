#include <stdio.h>
#include "estadisticas.h"

// Función para mostrar las estadísticas del sistema
void mostrarEstadisticas(
    int cantPendientes,
    int cantEnProceso,
    int cantFinalizadas
) {
    int total = cantPendientes + cantEnProceso + cantFinalizadas; // Calcula el total de tareas sumando las tareas pendientes, en proceso y finalizadas
    float porcentaje = 0; // Variable para almacenar el porcentaje de tareas finalizadas

    if(total > 0) { // Verifica si el total de tareas es mayor a 0 para evitar división por cero
        porcentaje = (cantFinalizadas * 100.0f) / total; // Calcula el porcentaje de tareas finalizadas
    }

    printf("\n ESTADISTICAS \n");
    printf("Total de tareas: %d\n", total);
    printf("Pendientes: %d\n", cantPendientes);
    printf("En Progreso: %d\n", cantEnProceso);
    printf("Finalizadas: %d\n", cantFinalizadas);
    printf("Porcentaje completado: %.2f%%\n", porcentaje);
}
