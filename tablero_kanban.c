#include <stdio.h>
#include "tablero_kanban.h"
#include "validaciones.h"

static void EliminarPorIndice(struct Tarea tareas[], int *cantidad, int indice) {
    for(int j = indice; j < *cantidad - 1; j++) {
        tareas[j] = tareas[j + 1];
    }
    (*cantidad)--;
}

static int HayEspacioEnColumna(int cantidad, char nombreColumna[]) {
    if(cantidad >= MAX_TAREAS) {
        printf("La columna de %s esta llena.\n", nombreColumna);
        return 0;
    }
    return 1;
}

void mostrarTablero(
    struct Tarea pendientes[],
    int cantPendientes,
    struct Tarea enProceso[],
    int cantEnProceso,
    struct Tarea finalizadas[],
    int cantFinalizadas
) {
    printf("\n      PENDIENTES");
    printf("\n========================\n");

    if(cantPendientes == 0) {
        printf("No hay tareas pendientes.\n");
    } else {
        for(int i = 0; i < cantPendientes; i++) {
            printf("[%d] %s\n", pendientes[i].codigo, pendientes[i].titulo);
        }
    }

    printf("\n     EN PROGRESO");
    printf("\n========================\n");

    if(cantEnProceso == 0) {
        printf("No hay tareas en proceso.\n");
    } else {
        for(int i = 0; i < cantEnProceso; i++) {
            printf("[%d] %s\n", enProceso[i].codigo, enProceso[i].titulo);
        }
    }

    printf("\n      FINALIZADAS");
    printf("\n========================\n");

    if(cantFinalizadas == 0) {
        printf("No hay tareas finalizadas.\n");
    } else {
        for(int i = 0; i < cantFinalizadas; i++) {
            printf("[%d] %s\n", finalizadas[i].codigo, finalizadas[i].titulo);
        }
    }
}

void cambiarEstado(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea enProceso[],
    int *cantEnProceso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    int codigo;
    int nuevoEstado;
    int estadoDestino;
    struct Tarea auxiliar;

    printf("Ingrese el codigo de la tarea a mover: ");
    ValidarEntero(&codigo);

    for(int i = 0; i < *cantPendientes; i++) {
        if(pendientes[i].codigo == codigo) {
            auxiliar = pendientes[i];
            LimpiarBuffer();

            printf("Ingrese el nuevo responsable: ");
            ValidarTexto(auxiliar.responsable, MAX_RESPONSABLE);

            do {
                printf("Mover a:\n 1. En Progreso\n 2. Finalizada\n Opcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            estadoDestino = (nuevoEstado == 1) ? ESTADO_EN_PROGRESO : ESTADO_FINALIZADA;

            if(nuevoEstado == 1) {
                if(!HayEspacioEnColumna(*cantEnProceso, "en progreso")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(pendientes, cantPendientes, i);
                enProceso[*cantEnProceso] = auxiliar;
                (*cantEnProceso)++;
            } else {
                if(!HayEspacioEnColumna(*cantFinalizadas, "finalizadas")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(pendientes, cantPendientes, i);
                finalizadas[*cantFinalizadas] = auxiliar;
                (*cantFinalizadas)++;
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantEnProceso; i++) {
        if(enProceso[i].codigo == codigo) {
            auxiliar = enProceso[i];

            do {
                printf("Mover a:\n1. Pendiente\n2. Finalizada\nOpcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            estadoDestino = (nuevoEstado == 1) ? ESTADO_PENDIENTE : ESTADO_FINALIZADA;

            if(nuevoEstado == 1) {
                if(!HayEspacioEnColumna(*cantPendientes, "pendientes")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(enProceso, cantEnProceso, i);
                pendientes[*cantPendientes] = auxiliar;
                (*cantPendientes)++;
            } else {
                if(!HayEspacioEnColumna(*cantFinalizadas, "finalizadas")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(enProceso, cantEnProceso, i);
                finalizadas[*cantFinalizadas] = auxiliar;
                (*cantFinalizadas)++;
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantFinalizadas; i++) {
        if(finalizadas[i].codigo == codigo) {
            auxiliar = finalizadas[i];

            do {
                printf("Mover a:\n1. Pendiente\n2. En Progreso\nOpcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            estadoDestino = (nuevoEstado == 1) ? ESTADO_PENDIENTE : ESTADO_EN_PROGRESO;

            if(nuevoEstado == 1) {
                if(!HayEspacioEnColumna(*cantPendientes, "pendientes")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(finalizadas, cantFinalizadas, i);
                pendientes[*cantPendientes] = auxiliar;
                (*cantPendientes)++;
            } else {
                if(!HayEspacioEnColumna(*cantEnProceso, "en progreso")) {
                    return;
                }

                AsignarEstado(&auxiliar, estadoDestino);
                EliminarPorIndice(finalizadas, cantFinalizadas, i);
                enProceso[*cantEnProceso] = auxiliar;
                (*cantEnProceso)++;
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
