#include <stdio.h>
#include <string.h>
#include "registro_eliminacion.h"
#include "validaciones.h"
#include "guardar_tareas.h"

static int codigoExiste(Lista *pendientes, Lista *progreso, Lista *finalizadas, int codigo) {
    if(buscarTareaPorCodigo(pendientes, codigo) != NULL) {
        return 1;
    }
    if(buscarTareaPorCodigo(progreso, codigo) != NULL) {
        return 1;
    }
    if(buscarTareaPorCodigo(finalizadas, codigo) != NULL) {
        return 1;
    }
    return 0;
}

void registrarTarea(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    struct Tarea nuevaTarea;
    int estado;

    printf("Ingrese el codigo de la tarea: ");
    ValidarEntero(&nuevaTarea.codigo);

    if(codigoExiste(pendientes, enProceso, finalizadas, nuevaTarea.codigo)) {
        printf("Error: el codigo ya existe.\n");
        return;
    }

    printf("Ingrese el titulo de la tarea: ");
    ValidarTexto(nuevaTarea.titulo, MAX_TITULO);

    printf("Ingrese el nombre del responsable: ");
    ValidarTexto(nuevaTarea.responsable, MAX_RESPONSABLE);

    ValidarPrioridad(nuevaTarea.prioridad);

    AsignarEstado(&nuevaTarea, ESTADO_PENDIENTE);
    insertarTareaFinal(pendientes, nuevaTarea);

    guardarTareas(pendientes, enProceso, finalizadas);
    printf("\nTarea registrada correctamente.\n");
}

void modificarTarea(
    Lista *pendientes,
    Lista *enProceso,
    Lista *finalizadas
) {
    int codigo;
    Nodo *tareaNodo = NULL;

    printf("Ingrese el codigo de la tarea a modificar: ");
    ValidarEntero(&codigo);

    tareaNodo = buscarTareaPorCodigo(pendientes, codigo);
    if(tareaNodo == NULL) {
        tareaNodo = buscarTareaPorCodigo(enProceso, codigo);
    }
    if(tareaNodo == NULL) {
        tareaNodo = buscarTareaPorCodigo(finalizadas, codigo);
    }

    if(tareaNodo == NULL) {
        printf("Tarea no encontrada.\n");
        return;
    }

    printf("Ingrese el nuevo titulo: ");
    ValidarTexto(tareaNodo->dato.titulo, MAX_TITULO);
    printf("Ingrese el nuevo responsable: ");
    ValidarTexto(tareaNodo->dato.responsable, MAX_RESPONSABLE);
    ValidarPrioridad(tareaNodo->dato.prioridad);

    guardarTareas(pendientes, enProceso, finalizadas);
    printf("Tarea modificada correctamente.\n");
}

void eliminarTarea(
    Lista *pendientes,
    Lista *progreso,
    Lista *finalizadas
) {
    int codigo;
    struct Tarea tarea;

    printf("Ingrese el codigo de la tarea a eliminar: ");
    ValidarEntero(&codigo);

    if(extraerTareaPorCodigo(pendientes, codigo, &tarea) ||
       extraerTareaPorCodigo(progreso, codigo, &tarea) ||
       extraerTareaPorCodigo(finalizadas, codigo, &tarea)) {
        guardarTareas(pendientes, progreso, finalizadas);
        printf("Tarea eliminada correctamente.\n");
        return;
    }

    printf("Tarea no encontrada.\n");
}
