#include <stdio.h>
#include "registro_eliminacion.h"
#include "validaciones.h"

// Función para eliminar una tarea por su código
static void EliminarPorIndice(struct Tarea tareas[], int *cantidad, int indice) { // Se utiliza "static" para limitar el alcance de la función a este archivo
    for(int j = indice; j < *cantidad - 1; j++) { // Recorre el arreglo desde el índice de la tarea a eliminar hasta el final del arreglo
        tareas[j] = tareas[j + 1]; // Desplaza cada tarea una posición hacia atrás para sobrescribir la tarea a eliminar
    }
    (*cantidad)--; // Decrementa el contador de tareas para reflejar la eliminación
}

// Función para verificar si un código de tarea ya existe en el sistema
static int codigoExiste(
    struct Tarea pendientes[],
    int totalPendientes,
    struct Tarea progreso[],
    int totalProgreso,
    struct Tarea finalizadas[],
    int totalFinalizadas,
    int codigo
) { // Se utiliza "static" para limitar el alcance de la función a este archivo
    for(int i = 0; i < totalPendientes; i++) { // Recorre el arreglo de tareas pendientes
        if(pendientes[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            return 1; // Si encuentra una coincidencia, devuelve 1 indicando que el código ya existe
        }
    }

    for(int i = 0; i < totalProgreso; i++) { // Recorre el arreglo de tareas en progreso
        if(progreso[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            return 1; // Si encuentra una coincidencia, devuelve 1 indicando que el código ya existe
        }
    }

    for(int i = 0; i < totalFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
        if(finalizadas[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            return 1; // Si encuentra una coincidencia, devuelve 1 indicando que el código ya existe
        }
    }
    return 0; // Si no encuentra el código en ninguno de los arreglos, devuelve 0 indicando que el código no existe
}

// Función para registrar una nueva tarea en el sistema
void registrarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea enProceso[],
    int *cantEnProceso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    struct Tarea nuevaTarea; // Variable para almacenar los datos de la nueva tarea
    int estado; // Variable para almacenar el estado inicial de la tarea
    int registrada = 0; // Variable para indicar si la tarea fue registrada exitosamente

    printf("Ingrese el codigo de la tarea: ");
    ValidarEntero(&nuevaTarea.codigo);

    if(codigoExiste(
        pendientes,
        *cantPendientes,
        enProceso,
        *cantEnProceso,
        finalizadas,
        *cantFinalizadas,
        nuevaTarea.codigo
    )) { // Verifica si el código ingresado ya existe en el sistema
        printf("Error: el codigo ya existe.\n");
        return;
    }

    printf("Ingrese el titulo de la tarea: ");
    ValidarTexto(nuevaTarea.titulo, MAX_TITULO);

    printf("Ingrese el nombre del responsable: ");
    ValidarTexto(nuevaTarea.responsable, MAX_RESPONSABLE);

    ValidarPrioridad(nuevaTarea.prioridad);

    do { // Bucle para solicitar el estado inicial de la tarea hasta que sea válido
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

    if(estado == ESTADO_PENDIENTE) { // Si el estado seleccionado es "Pendiente"
        if(*cantPendientes < MAX_TAREAS) { // Verifica si hay espacio en la columna de pendientes
            AsignarEstado(&nuevaTarea, ESTADO_PENDIENTE);
            pendientes[*cantPendientes] = nuevaTarea; // Agrega la nueva tarea al arreglo de pendientes
            (*cantPendientes)++; // Incrementa el contador de tareas pendientes
            registrada = 1; // Indica que la tarea fue registrada exitosamente
        } else {
            printf("La columna de pendientes esta llena.\n");
        }
    } else if(estado == ESTADO_EN_PROGRESO) { // Si el estado seleccionado es "En Progreso"
        if(*cantEnProceso < MAX_TAREAS) { // Verifica si hay espacio en la columna de en progreso
            AsignarEstado(&nuevaTarea, ESTADO_EN_PROGRESO); // Asigna el estado "En Progreso" a la nueva tarea
            enProceso[*cantEnProceso] = nuevaTarea; // Agrega la nueva tarea al arreglo de en progreso
            (*cantEnProceso)++; // Incrementa el contador de tareas en progreso
            registrada = 1; // Indica que la tarea fue registrada exitosamente
        } else {
            printf("La columna de en progreso esta llena.\n");
        }
    } else {
        if(*cantFinalizadas < MAX_TAREAS) { // Verifica si hay espacio en la columna de finalizadas
            AsignarEstado(&nuevaTarea, ESTADO_FINALIZADA); // Asigna el estado "Finalizada" a la nueva tarea
            finalizadas[*cantFinalizadas] = nuevaTarea; // Agrega la nueva tarea al arreglo de finalizadas
            (*cantFinalizadas)++; // Incrementa el contador de tareas finalizadas
            registrada = 1; // Indica que la tarea fue registrada exitosamente
        } else {
            printf("La columna de finalizadas esta llena.\n");
        }
    }

    if(registrada) {
        printf("\nTarea registrada correctamente.\n");
    }
}

// Función para eliminar una tarea por su código
void eliminarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,
    struct Tarea progreso[],
    int *cantProgreso,
    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    int codigo; // Variable para almacenar el código de la tarea a eliminar

    printf("Ingrese el codigo de la tarea a eliminar: ");
    ValidarEntero(&codigo);

    for(int i = 0; i < *cantPendientes; i++) { // Recorre el arreglo de tareas pendientes
        if(pendientes[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            EliminarPorIndice(pendientes, cantPendientes, i); // Elimina la tarea del arreglo de pendientes utilizando la función EliminarPorIndice
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantProgreso; i++) { // Recorre el arreglo de tareas en progreso
        if(progreso[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            EliminarPorIndice(progreso, cantProgreso, i); // Elimina la tarea del arreglo de en progreso utilizando la función EliminarPorIndice
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
        if(finalizadas[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            EliminarPorIndice(finalizadas, cantFinalizadas, i); // Elimina la tarea del arreglo de finalizadas utilizando la función EliminarPorIndice
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
