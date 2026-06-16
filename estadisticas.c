#include <stdio.h>
#include "estadisticas.h"

void mostrarEstadisticas(
    int cantPendientes,
    int cantEnProceso,
    int cantFinalizadas
) {
    int total = cantPendientes + cantEnProceso + cantFinalizadas;
    float porcentaje = 0;

    if(total > 0) {
        porcentaje = (cantFinalizadas * 100.0f) / total;
    }

    printf("\n ESTADISTICAS \n");
    printf("Total de tareas: %d\n", total);
    printf("Pendientes: %d\n", cantPendientes);
    printf("En Progreso: %d\n", cantEnProceso);
    printf("Finalizadas: %d\n", cantFinalizadas);
    printf("Porcentaje completado: %.2f%%\n", porcentaje);
}
