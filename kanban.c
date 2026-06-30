#include <stdio.h>
#include <string.h>
#include "kanban.h"
#include "archivo.h"
#include "validaciones.h"

// Función para verificar si el código de la tarea ya existe en alguna de las listas
static int codigoExiste(Lista *pendientes, Lista *enProceso, Lista *finalizadas, int codigo) {
    if(buscarTareaPorCodigo(pendientes, codigo) != NULL) { // Si se encuentra la tarea en la lista de pendientes, retorna 1 (existe)
        return 1;
    }
    if(buscarTareaPorCodigo(enProceso, codigo) != NULL) { // Si se encuentra la tarea en la lista de en proceso, retorna 1 (existe)
        return 1;
    }
    if(buscarTareaPorCodigo(finalizadas, codigo) != NULL) { // Si se encuentra la tarea en la lista de finalizadas, retorna 1 (existe)
        return 1;
    }
    return 0; // Si no se encuentra en ninguna lista, retorna 0 (no existe)
}

// Función para buscar una tarea por código en todas las listas y retornar el nodo correspondiente
static Nodo *buscarTareaEnListas(Lista *pendientes, Lista *enProceso, Lista *finalizadas, int codigo) {
    Nodo *resultado = buscarTareaPorCodigo(pendientes, codigo); // Buscar en la lista de pendientes
    if(resultado != NULL) { // Si se encuentra la tarea en la lista de pendientes, retorna el nodo correspondiente
        return resultado;
    }
    resultado = buscarTareaPorCodigo(enProceso, codigo); // Buscar en la lista de en proceso
    if(resultado != NULL) { // Si se encuentra la tarea en la lista de en proceso, retorna el nodo correspondiente
        return resultado;
    }
    return buscarTareaPorCodigo(finalizadas, codigo); // Buscar en la lista de finalizadas y retornar el nodo correspondiente (si no se encuentra, retorna NULL)
}

// Función para registrar una nueva tarea en la lista de pendientes
void registrarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    Tarea nuevaTarea; // Estructura para almacenar los datos de la nueva tarea

    printf("Ingrese el codigo de la tarea: ");
    ValidarEntero(&nuevaTarea.codigo); // Validar que el código ingresado sea un número entero

    if(codigoExiste(pendientes, enProceso, finalizadas, nuevaTarea.codigo)) { // Verificar si el código ya existe en alguna de las listas
        printf("Error: el codigo ya existe.\n");
        return;
    }

    printf("Ingrese el titulo de la tarea: ");
    ValidarTexto(nuevaTarea.titulo, MAX_TITULO); // Validar que el título ingresado sea un texto válido (solo letras, números y espacios)
    printf("Ingrese el nombre del responsable: ");
    ValidarTexto(nuevaTarea.responsable, MAX_RESPONSABLE); // Validar que el nombre del responsable ingresado sea un texto válido (solo letras, números y espacios)
    ValidarPrioridad(&nuevaTarea.prioridad); // Validar que la prioridad ingresada sea 1, 2 o 3 (Alta, Media o Baja)

    AsignarEstado(&nuevaTarea, ESTADO_PENDIENTE); // Asignar el estado "Pendiente" a la nueva tarea
    insertarTareaFinal(pendientes, nuevaTarea); // Insertar la nueva tarea al final de la lista de pendientes
    guardarTareas(pendientes, enProceso, finalizadas); // Guardar las listas de tareas en el archivo para mantener los cambios realizados
    printf("\nTarea registrada correctamente.\n");
}

// Función para modificar los datos de una tarea existente
void modificarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    int codigo;
    Nodo *tareaNodo; // Puntero al nodo que contiene la tarea a modificar

    printf("Ingrese el codigo de la tarea a modificar: ");
    ValidarEntero(&codigo); // Validar que el código ingresado sea un número entero

    tareaNodo = buscarTareaEnListas(pendientes, enProceso, finalizadas, codigo); // Buscar la tarea en todas las listas y obtener el nodo correspondiente
    if(tareaNodo == NULL) { // Si no se encuentra la tarea, mostrar un mensaje de error y retornar
        printf("Tarea no encontrada.\n");
        return;
    }

    printf("Ingrese el nuevo titulo: ");
    ValidarTexto(tareaNodo->dato.titulo, MAX_TITULO); // Validar que el nuevo título ingresado sea un texto válido (solo letras, números y espacios)
    printf("Ingrese el nuevo responsable: ");
    ValidarTexto(tareaNodo->dato.responsable, MAX_RESPONSABLE); // Validar que el nuevo responsable ingresado sea un texto válido (solo letras, números y espacios)
    ValidarPrioridad(&tareaNodo->dato.prioridad); // Validar que la nueva prioridad ingresada sea 1, 2 o 3 (Alta, Media o Baja)

    guardarTareas(pendientes, enProceso, finalizadas); // Guardar las listas de tareas en el archivo para mantener los cambios realizados
    printf("Tarea modificada correctamente.\n");
}

// Función para buscar tareas por código o responsable
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
    } while(opcionBusqueda < 1 || opcionBusqueda > 2); // Bucle para validar que la opción ingresada esté dentro del rango permitido (1-2)

    if(opcionBusqueda == 1) { // Si la opción seleccionada es 1, se busca la tarea por código
        int codigo;
        Nodo *resultado; // Puntero al nodo que contiene la tarea encontrada

        printf("Ingrese el codigo a buscar: ");
        ValidarEntero(&codigo);

        resultado = buscarTareaEnListas(pendientes, enProceso, finalizadas, codigo); // Buscar la tarea en todas las listas y obtener el nodo correspondiente
        if(resultado != NULL) { // Si se encuentra la tarea, mostrar sus datos
            printf("\nCodigo: %d\n", resultado->dato.codigo);
            printf("Titulo: %s\n", resultado->dato.titulo);
            printf("Responsable: %s\n", resultado->dato.responsable);
            printf("Prioridad: %d\n", resultado->dato.prioridad);
            printf("Estado: %s\n", resultado->dato.estado);
        } else {
            printf("Tarea no encontrada.\n");
        }
    } else { // Si la opción seleccionada es 2, se busca la tarea por responsable
        char responsable[MAX_RESPONSABLE];
        int encontrado = 0;
        Nodo *actual; // Puntero al nodo actual que se está recorriendo en la lista

        LimpiarBuffer(); // Limpiar el buffer de entrada para evitar problemas al leer cadenas de texto
        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE); // Validar que el nombre del responsable ingresado sea un texto válido (solo letras, números y espacios)

        actual = pendientes->primero; // Iniciar el recorrido desde el primer nodo de la lista de pendientes
        while(actual != NULL) { // Recorrer la lista de pendientes hasta llegar al final (NULL)
            if(strcmp(actual->dato.responsable, responsable) == 0) { // Si el responsable de la tarea coincide con el ingresado, mostrar los datos de la tarea
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente; // Avanzar al siguiente nodo de la lista
        }

        actual = enProceso->primero; // Iniciar el recorrido desde el primer nodo de la lista de en proceso
        while(actual != NULL) { // Recorrer la lista de en proceso hasta llegar al final (NULL)
            if(strcmp(actual->dato.responsable, responsable) == 0) { // Si el responsable de la tarea coincide con el ingresado, mostrar los datos de la tarea
                printf("\n[%d] %s - %s\n", actual->dato.codigo, actual->dato.titulo, actual->dato.estado);
                encontrado = 1;
            }
            actual = actual->siguiente; // Avanzar al siguiente nodo de la lista
        }

        actual = finalizadas->primero; // Iniciar el recorrido desde el primer nodo de la lista de finalizadas
        while(actual != NULL) { //
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
