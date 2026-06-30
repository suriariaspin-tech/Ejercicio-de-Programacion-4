#include <stdio.h>
#include <string.h>
#include "kanban.h"
#include "archivo.h"
#include "validaciones.h"

static int codigoExiste(Lista *pendientes, Lista *enProceso, Lista *finalizadas, int codigo) {
    if(buscarTareaPorCodigo(pendientes, codigo) != NULL) {
        return 1;
    }
    if(buscarTareaPorCodigo(enProceso, codigo) != NULL) {
        return 1;
    }
    if(buscarTareaPorCodigo(finalizadas, codigo) != NULL) {
        return 1;
    }
    return 0;
}

static Nodo *buscarTareaEnListas(Lista *pendientes, Lista *enProceso, Lista *finalizadas, int codigo) {
    Nodo *resultado = buscarTareaPorCodigo(pendientes, codigo);
    if(resultado != NULL) {
        return resultado;
    }
    resultado = buscarTareaPorCodigo(enProceso, codigo);
    if(resultado != NULL) {
        return resultado;
    }
    return buscarTareaPorCodigo(finalizadas, codigo);
}

void registrarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    Tarea nuevaTarea;

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
    ValidarPrioridad(&nuevaTarea.prioridad);

    AsignarEstado(&nuevaTarea, ESTADO_PENDIENTE);
    insertarTareaFinal(pendientes, nuevaTarea);
    guardarTareas(pendientes, enProceso, finalizadas);
    printf("\nTarea registrada correctamente.\n");
}

void modificarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    int codigo;
    Nodo *tareaNodo;

    printf("Ingrese el codigo de la tarea a modificar: ");
    ValidarEntero(&codigo);

    tareaNodo = buscarTareaEnListas(pendientes, enProceso, finalizadas, codigo);
    if(tareaNodo == NULL) {
        printf("Tarea no encontrada.\n");
        return;
    }

    printf("Ingrese el nuevo titulo: ");
    ValidarTexto(tareaNodo->dato.titulo, MAX_TITULO);
    printf("Ingrese el nuevo responsable: ");
    ValidarTexto(tareaNodo->dato.responsable, MAX_RESPONSABLE);
    ValidarPrioridad(&tareaNodo->dato.prioridad);

    guardarTareas(pendientes, enProceso, finalizadas);
    printf("Tarea modificada correctamente.\n");
}

void buscarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    int opcionBusqueda;

    printf("\nBUSCAR TAREA\n");
    printf("1. Buscar por codigo\n");
    printf("2. Buscar por responsable\n");

    do {
        printf("Seleccione una opcion: ");
        ValidarEntero(&opcionBusqueda);
        if(opcionBusqueda < 1 || opcionBusqueda > 2) {
            printf("Opcion invalida.\n");
        }
    } while(opcionBusqueda < 1 || opcionBusqueda > 2);

    if(opcionBusqueda == 1) {
        int codigo;
        Nodo *resultado;

        printf("Ingrese el codigo a buscar: ");
        ValidarEntero(&codigo);

        resultado = buscarTareaEnListas(pendientes, enProceso, finalizadas, codigo);
        if(resultado != NULL) {
            printf("\nCodigo: %d\n", resultado->dato.codigo);
            printf("Titulo: %s\n", resultado->dato.titulo);
            printf("Responsable: %s\n", resultado->dato.responsable);
            printf("Prioridad: %d\n", resultado->dato.prioridad);
            printf("Estado: %s\n", resultado->dato.estado);
        } else {
            printf("Tarea no encontrada.\n");
        }
    } else {
        char responsable[MAX_RESPONSABLE];
        int encontrado = 0;
        Nodo *actual;

        LimpiarBuffer();
        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE);

        actual = pendientes->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        actual = enProceso->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        actual = finalizadas->primero;
        while(actual != NULL) {
            if(strcmp(actual->dato.responsable, responsable) == 0) {
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente;
        }

        if(!encontrado) {
            printf("No se encontraron tareas.\n");
        }
    }
}

void eliminarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    int codigo;
    Tarea tarea;

    printf("Ingrese el codigo de la tarea a eliminar: ");
    ValidarEntero(&codigo);

    if(extraerTareaPorCodigo(pendientes, codigo, &tarea) ||
       extraerTareaPorCodigo(enProceso, codigo, &tarea) ||
       extraerTareaPorCodigo(finalizadas, codigo, &tarea)) {
        guardarTareas(pendientes, enProceso, finalizadas);
        printf("Tarea eliminada correctamente.\n");
    } else {
        printf("Tarea no encontrada.\n");
    }
}

void mostrarEstadisticas(int cantPendientes, int cantEnProceso, int cantFinalizadas) {
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

static void imprimirLista(Lista *lista) {
    Nodo *actual = lista->primero;
    while(actual != NULL) {
        printf("[%d] %s\n\n", actual->dato.codigo, actual->dato.titulo);
        actual = actual->siguiente;
    }
}

void mostrarTablero(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    printf("\n      PENDIENTES\n");
    printf("========================\n");
    if(pendientes->primero == NULL) {
        printf("No hay tareas pendientes.\n\n");
    } else {
        imprimirLista(pendientes);
    }

    printf("     EN PROGRESO\n");
    printf("========================\n");
    if(enProceso->primero == NULL) {
        printf("No hay tareas en proceso.\n\n");
    } else {
        imprimirLista(enProceso);
    }

    printf("      FINALIZADAS\n");
    printf("========================\n");
    if(finalizadas->primero == NULL) {
        printf("No hay tareas finalizadas.\n\n");
    } else {
        imprimirLista(finalizadas);
    }
}

void cambiarEstado(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    int codigo;
    int opcion;
    Tarea tarea;

    printf("Ingrese el codigo de la tarea a mover: ");
    ValidarEntero(&codigo);

    if(buscarTareaPorCodigo(pendientes, codigo) != NULL) {
        do {
            printf("Mover a:\n1. En Progreso\n2. Finalizada\nOpcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(pendientes, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_EN_PROGRESO);
                insertarTareaFinal(enProceso, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_FINALIZADA);
                insertarTareaFinal(finalizadas, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    if(buscarTareaPorCodigo(enProceso, codigo) != NULL) {
        do {
            printf("Mover a:\n1. Pendiente\n2. Finalizada\nOpcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(enProceso, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_PENDIENTE);
                insertarTareaFinal(pendientes, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_FINALIZADA);
                insertarTareaFinal(finalizadas, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    if(buscarTareaPorCodigo(finalizadas, codigo) != NULL) {
        do {
            printf("Mover a:\n1. Pendiente\n2. En Progreso\nOpcion: ");
            ValidarEntero(&opcion);
            if(opcion < 1 || opcion > 2) {
                printf("Opcion invalida.\n");
            }
        } while(opcion < 1 || opcion > 2);

        if(extraerTareaPorCodigo(finalizadas, codigo, &tarea)) {
            if(opcion == 1) {
                AsignarEstado(&tarea, ESTADO_PENDIENTE);
                insertarTareaFinal(pendientes, tarea);
            } else {
                AsignarEstado(&tarea, ESTADO_EN_PROGRESO);
                insertarTareaFinal(enProceso, tarea);
            }
            guardarTareas(pendientes, enProceso, finalizadas);
            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
