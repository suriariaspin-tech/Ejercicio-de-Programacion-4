#include <stdio.h>
#include "tablero_kanban.h"
#include "validaciones.h"

// Función para eliminar una tarea por su código
static void EliminarPorIndice(struct Tarea tareas[], int *cantidad, int indice) { // Se utiliza "static" para limitar el alcance de la función a este archivo
    for(int j = indice; j < *cantidad - 1; j++) { // Recorre el arreglo desde el índice de la tarea a eliminar hasta el final del arreglo
        tareas[j] = tareas[j + 1]; // Desplaza cada tarea una posición hacia atrás para sobrescribir la tarea a eliminar
    }
    (*cantidad)--; // Decrementa el contador de tareas para reflejar la eliminación
}

// Función para verificar si hay espacio en una columna del tablero
static int HayEspacioEnColumna(int cantidad, char nombreColumna[]) { // Se utiliza "static" para limitar el alcance de la función a este archivo
    if(cantidad >= MAX_TAREAS) { // Verifica si la cantidad de tareas en la columna es mayor o igual al máximo permitido
        printf("La columna de %s esta llena.\n", nombreColumna); 
        return 0; // Si la columna está llena, devuelve 0 indicando que no hay espacio
    }
    return 1; // Si la columna tiene espacio, devuelve 1 indicando que hay espacio disponible
}

// Función para mostrar el tablero Kanban con las tareas organizadas por estado
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

    if(cantPendientes == 0) { // Verifica si no hay tareas pendientes para mostrar un mensaje indicando que no hay tareas en esa columna
        printf("No hay tareas pendientes.\n");
    } else {
        for(int i = 0; i < cantPendientes; i++) { // Recorre el arreglo de tareas pendientes y muestra el código y título de cada tarea
            printf("[%d] %s\n", pendientes[i].codigo, pendientes[i].titulo);
        }
    }

    printf("\n     EN PROGRESO");
    printf("\n========================\n");

    if(cantEnProceso == 0) { // Verifica si no hay tareas en proceso para mostrar un mensaje indicando que no hay tareas en esa columna
        printf("No hay tareas en proceso.\n");
    } else {
        for(int i = 0; i < cantEnProceso; i++) { // Recorre el arreglo de tareas en proceso y muestra el código y título de cada tarea
            printf("[%d] %s\n", enProceso[i].codigo, enProceso[i].titulo);
        }
    }

    printf("\n      FINALIZADAS");
    printf("\n========================\n");

    if(cantFinalizadas == 0) { // Verifica si no hay tareas finalizadas para mostrar un mensaje indicando que no hay tareas en esa columna
        printf("No hay tareas finalizadas.\n");
    } else {
        for(int i = 0; i < cantFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas y muestra el código y título de cada tarea
            printf("[%d] %s\n", finalizadas[i].codigo, finalizadas[i].titulo);
        }
    }
}

// Función para cambiar el estado de una tarea moviéndola entre las columnas del tablero
void cambiarEstado(
    struct Tarea *pendientes,
    int *cantPendientes,
    struct Tarea *enProceso,
    int *cantEnProceso,
    struct Tarea *finalizadas,
    int *cantFinalizadas
) {
    int codigo; // Variable para almacenar el código de la tarea a mover
    int nuevoEstado; // Variable para almacenar el nuevo estado al que se desea mover la tarea
    int estadoDestino; // Variable para almacenar el estado destino al que se moverá la tarea
    struct Tarea auxiliar; // Variable auxiliar para almacenar temporalmente los datos de la tarea que se va a mover

    printf("Ingrese el codigo de la tarea a mover: ");
    ValidarEntero(&codigo);

    // Busca la tarea en la columna de pendientes para moverla a en proceso o finalizadas
    for(int i = 0; i < *cantPendientes; i++) { // Recorre el arreglo de tareas pendientes para buscar la tarea con el código ingresado
        if(pendientes[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            auxiliar = pendientes[i]; // Si encuentra la tarea, almacena sus datos en la variable auxiliar para luego moverla a la nueva columna
            LimpiarBuffer();

            printf("Ingrese el nuevo responsable: ");
            ValidarTexto(auxiliar.responsable, MAX_RESPONSABLE);

            do { // Bucle para solicitar el nuevo estado hasta que sea válido
                printf("Mover a:\n 1. En Progreso\n 2. Finalizada\n Opcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            // Determina el estado destino basado en la opción seleccionada por el usuario
            if(nuevoEstado == 1) {
                estadoDestino = ESTADO_EN_PROGRESO; // Si el nuevo estado es "En Progreso", asigna el estado destino como "En Progreso"
            } else {
                estadoDestino = ESTADO_FINALIZADA; // Si el nuevo estado es "Finalizada", asigna el estado destino como "Finalizada"
            }

            if(nuevoEstado == 1) { // Si el nuevo estado es "En Progreso", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantEnProceso, "en progreso")) { // Si no hay espacio en la columna de "En Progreso", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas en progreso.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(pendientes, cantPendientes, i); // Elimina la tarea del arreglo de pendientes utilizando la función EliminarPorIndice
                enProceso[*cantEnProceso] = auxiliar; // Agrega la tarea al arreglo de en proceso
                (*cantEnProceso)++; // Incrementa el contador de tareas en proceso para reflejar el movimiento de la tarea
            } else { // Si el nuevo estado es "Finalizada", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantFinalizadas, "finalizadas")) { // Si no hay espacio en la columna de "Finalizadas", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas finalizadas.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(pendientes, cantPendientes, i); // Elimina la tarea del arreglo de pendientes utilizando la función EliminarPorIndice
                finalizadas[*cantFinalizadas] = auxiliar; // Agrega la tarea al arreglo de finalizadas
                (*cantFinalizadas)++; // Incrementa el contador de tareas finalizadas para reflejar el movimiento de la tarea
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    // Busca la tarea en la columna de en proceso para moverla a pendientes o finalizadas
    for(int i = 0; i < *cantEnProceso; i++) { // Recorre el arreglo de tareas en proceso para buscar la tarea con el código ingresado
        if(enProceso[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            auxiliar = enProceso[i]; // Si encuentra la tarea, almacena sus datos en la variable auxiliar para luego moverla a la nueva columna

            do { // Bucle para solicitar el nuevo estado hasta que sea válido
                printf("Mover a:\n1. Pendiente\n2. Finalizada\nOpcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            // Determina el estado destino basado en la opción seleccionada por el usuario
            if(nuevoEstado == 1) {
                estadoDestino = ESTADO_PENDIENTE; // Si el nuevo estado es "Pendiente", asigna el estado destino como "Pendiente"
            } else {
                estadoDestino = ESTADO_FINALIZADA;  // Si el nuevo estado es "Finalizada", asigna el estado destino como "Finalizada"
            }

            if(nuevoEstado == 1) { // Si el nuevo estado es "Pendiente", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantPendientes, "pendientes")) { // Si no hay espacio en la columna de "Pendientes", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas pendientes.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(enProceso, cantEnProceso, i); // Elimina la tarea del arreglo de en proceso utilizando la función EliminarPorIndice
                pendientes[*cantPendientes] = auxiliar; // Agrega la tarea al arreglo de pendientes
                (*cantPendientes)++; // Incrementa el contador de tareas pendientes para reflejar el movimiento de la tarea
            } else { // Si el nuevo estado es "Finalizada", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantFinalizadas, "finalizadas")) { // Si no hay espacio en la columna de "Finalizadas", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas finalizadas.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(enProceso, cantEnProceso, i); // Elimina la tarea del arreglo de en proceso utilizando la función EliminarPorIndice
                finalizadas[*cantFinalizadas] = auxiliar; // Agrega la tarea al arreglo de finalizadas
                (*cantFinalizadas)++; // Incrementa el contador de tareas finalizadas para reflejar el movimiento de la tarea
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    // Busca la tarea en la columna de finalizadas para moverla a pendientes o en proceso
    for(int i = 0; i < *cantFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas para buscar la tarea con el código ingresado
        if(finalizadas[i].codigo == codigo) { // Compara el código de cada tarea con el código ingresado
            auxiliar = finalizadas[i]; // Si encuentra la tarea, almacena sus datos en la variable auxiliar para luego moverla a la nueva columna

            do { // Bucle para solicitar el nuevo estado hasta que sea válido
                printf("Mover a:\n1. Pendiente\n2. En Progreso\nOpcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2) {
                    printf("Opcion invalida.\n");
                }
            } while(nuevoEstado < 1 || nuevoEstado > 2);

            // Determina el estado destino basado en la opción seleccionada por el usuario
            if(nuevoEstado == 1) {
                estadoDestino = ESTADO_PENDIENTE; // Si el nuevo estado es "Pendiente", asigna el estado destino como "Pendiente"
            } else {
                estadoDestino = ESTADO_EN_PROGRESO; // Si el nuevo estado es "En Progreso", asigna el estado destino como "En Progreso"
            }

            if(nuevoEstado == 1) { // Si el nuevo estado es "Pendiente", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantPendientes, "pendientes")) { // Si no hay espacio en la columna de "Pendientes", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas pendientes.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(finalizadas, cantFinalizadas, i); // Elimina la tarea del arreglo de finalizadas utilizando la función EliminarPorIndice
                pendientes[*cantPendientes] = auxiliar; // Agrega la tarea al arreglo de pendientes
                (*cantPendientes)++; // Incrementa el contador de tareas pendientes para reflejar el movimiento de la tarea
            } else { // Si el nuevo estado es "En Progreso", verifica si hay espacio en esa columna antes de mover la tarea
                if(!HayEspacioEnColumna(*cantEnProceso, "en progreso")) { // Si no hay espacio en la columna de "En Progreso", muestra un mensaje indicando que la tarea no se puede mover y retorna sin realizar ningún cambio
                    printf("No hay espacio en la columna de tareas en progreso.\n");
                    return;
                }
                AsignarEstado(&auxiliar, estadoDestino); // Asigna el nuevo estado a la tarea utilizando la función AsignarEstado
                EliminarPorIndice(finalizadas, cantFinalizadas, i); // Elimina la tarea del arreglo de finalizadas utilizando la función EliminarPorIndice
                enProceso[*cantEnProceso] = auxiliar; // Agrega la tarea al arreglo de en proceso
                (*cantEnProceso)++; // Incrementa el contador de tareas en proceso para reflejar el movimiento de la tarea
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }

    printf("Tarea no encontrada.\n");
}
