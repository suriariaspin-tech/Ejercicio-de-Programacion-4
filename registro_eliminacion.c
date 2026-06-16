#include <stdio.h>
#include "registro_eliminacion.h"
#include "validaciones.h"

static void EliminarPorIndice(struct Tarea tareas[], int *cantidad, int indice) {
    for(int j = indice; j < *cantidad - 1; j++) {
        tareas[j] = tareas[j + 1];
    }
    (*cantidad)--;
}

int codigoExiste(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas,
    int codigo
) {
    for(int i = 0; i < totalPendientes; i++) {
        if(pendientes[i].codigo == codigo) {
            return 1;
        }
    }

    for(int i = 0; i < totalProgreso; i++) {
        if(progreso[i].codigo == codigo) {
            return 1;
        }
    }

    for(int i = 0; i < totalFinalizadas; i++) {
        if(finalizadas[i].codigo == codigo) {
            return 1;
        }
    }

    return 0;
}

void registrarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea enProceso[],
    int *cantEnProceso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    struct Tarea nuevaTarea;
    int estado;
    int registrada = 0;

    printf("Ingrese el codigo de la tarea: ");
    ValidarCodigo(&nuevaTarea.codigo);
    LimpiarBuffer();

    if(codigoExiste(
        pendientes,
        *cantPendientes,
        enProceso,
        *cantEnProceso,
        finalizadas,
        *cantFinalizadas,
        nuevaTarea.codigo
    )) {
        printf("Error: el codigo ya existe.\n");
        return;
    }

    printf("Ingrese el titulo de la tarea: ");
    ValidarTexto(nuevaTarea.titulo, MAX_TITULO);

    printf("Ingrese el nombre del responsable: ");
    ValidarTexto(nuevaTarea.responsable, MAX_RESPONSABLE);

    ValidarPrioridad(nuevaTarea.prioridad);

    do {
        printf("\nSeleccione el estado inicial:\n");
        printf("1. Pendiente\n");
        printf("2. En Progreso\n");
        printf("3. Finalizada\n");
        printf("Opcion: ");

        ValidarEntero(&estado);

        if(estado < 1 || estado > 3) {
            printf("Opcion invalida. Intente nuevamente.\n");
        }
    } while(estado < 1 || estado > 3);

    if(estado == ESTADO_PENDIENTE) {
        if(*cantPendientes < MAX_TAREAS) {
            AsignarEstado(&nuevaTarea, ESTADO_PENDIENTE);
            pendientes[*cantPendientes] = nuevaTarea;
            (*cantPendientes)++;
            registrada = 1;
        } else {
            printf("La columna de pendientes esta llena.\n");
        }
    } else if(estado == ESTADO_EN_PROGRESO) {
        if(*cantEnProceso < MAX_TAREAS) {
            AsignarEstado(&nuevaTarea, ESTADO_EN_PROGRESO);
            enProceso[*cantEnProceso] = nuevaTarea;
            (*cantEnProceso)++;
            registrada = 1;
        } else {
            printf("La columna de en progreso esta llena.\n");
        }
    } else {
        if(*cantFinalizadas < MAX_TAREAS) {
            AsignarEstado(&nuevaTarea, ESTADO_FINALIZADA);
            finalizadas[*cantFinalizadas] = nuevaTarea;
            (*cantFinalizadas)++;
            registrada = 1;
        } else {
            printf("La columna de finalizadas esta llena.\n");
        }
    }

    if(registrada) {
        printf("\nTarea registrada correctamente.\n");
    }
}

void eliminarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea progreso[],
    int *cantProgreso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    int codigo;

    printf("Ingrese el codigo de la tarea a eliminar: ");
    ValidarEntero(&codigo);

    for(int i = 0; i < *cantPendientes; i++) {
        if(pendientes[i].codigo == codigo) {
            EliminarPorIndice(pendientes, cantPendientes, i);
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantProgreso; i++) {
        if(progreso[i].codigo == codigo) {
            EliminarPorIndice(progreso, cantProgreso, i);
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantFinalizadas; i++) {
        if(finalizadas[i].codigo == codigo) {
            EliminarPorIndice(finalizadas, cantFinalizadas, i);
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
