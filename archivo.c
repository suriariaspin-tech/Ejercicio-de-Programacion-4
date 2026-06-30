#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "archivo.h"

// Función para guardar las tareas en un archivo de texto
void guardarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    FILE *archivo = fopen("tareas.txt", "w");
    if(archivo == NULL) {
        fprintf(stderr, "Error al abrir tareas.txt: %s\n", strerror(errno));
        return;
    } // Abrir el archivo en modo escritura, lo que sobrescribirá el contenido existente

    Nodo *actual = pendientes->primero; // Iterar sobre la lista de tareas pendientes y escribir cada tarea en el archivo
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    actual = enProceso->primero; // Iterar sobre la lista de tareas en proceso y escribir cada tarea en el archivo
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    actual = finalizadas->primero; // Iterar sobre la lista de tareas finalizadas y escribir cada tarea en el archivo
    while(actual != NULL) {
        fprintf(archivo, "%d|%s|%s|%d|%s\n",
                actual->dato.codigo,
                actual->dato.titulo,
                actual->dato.responsable,
                actual->dato.prioridad,
                actual->dato.estado);
        actual = actual->siguiente;
    }

    fclose(archivo); // Cerrar el archivo después de escribir todas las tareas
}

// Función para cargar las tareas desde un archivo de texto
int cargarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas) {
    FILE *archivo = fopen("tareas.txt", "r");
    if(archivo == NULL) {
        archivo = fopen("tareas.txt", "w");
        if(archivo != NULL) {
            fclose(archivo);
        }
        return 0;
    } // Abrir el archivo en modo lectura, si no existe, crear uno nuevo y retornar 0

    char linea[256]; // Leer cada línea del archivo y extraer los datos de la tarea
    while(fgets(linea, sizeof(linea), archivo) != NULL) {
        Tarea tarea; // Estructura para almacenar los datos de la tarea leída del archivo
        char *token = strtok(linea, "|"); // Extraer el código de la tarea
        if(token == NULL) {
            continue;
        } // Copiar el código de la tarea a la estructura
        tarea.codigo = atoi(token); // Convertir el código de la tarea a entero

        token = strtok(NULL, "|"); // Extraer el título de la tarea
        if(token == NULL) {
            continue;
        } // Copiar el título de la tarea a la estructura
        strncpy(tarea.titulo, token, MAX_TITULO); // Asegurarse de que el título no exceda el tamaño máximo definido
        tarea.titulo[MAX_TITULO - 1] = '\0'; // Asegurarse de que la cadena esté terminada en nulo

        token = strtok(NULL, "|"); // Extraer el responsable de la tarea
        if(token == NULL) {
            continue;
        } // Copiar el responsable de la tarea a la estructura
        strncpy(tarea.responsable, token, MAX_RESPONSABLE); // Asegurarse de que el responsable no exceda el tamaño máximo definido
        tarea.responsable[MAX_RESPONSABLE - 1] = '\0'; // Asegurarse de que la cadena esté terminada en nulo

        token = strtok(NULL, "|"); // Extraer la prioridad de la tarea
        if(token == NULL) {
            continue;
        } // Copiar la prioridad de la tarea a la estructura
        tarea.prioridad = atoi(token); // Convertir la prioridad de la tarea a entero

        token = strtok(NULL, "|\r\n"); // Extraer el estado de la tarea
        if(token == NULL) {
            continue;
        } // Copiar el estado de la tarea a la estructura
        strncpy(tarea.estado, token, MAX_ESTADO); // Asegurarse de que el estado no exceda el tamaño máximo definido
        tarea.estado[MAX_ESTADO - 1] = '\0'; // Asegurarse de que la cadena esté terminada en nulo

        if(strcmp(tarea.estado, "Pendiente") == 0) { // Si el estado de la tarea es "Pendiente", se inserta en la lista de pendientes
            insertarTareaFinal(pendientes, tarea);
        } else if(strcmp(tarea.estado, "En Progreso") == 0) { // Si el estado de la tarea es "En Progreso", se inserta en la lista de en proceso
            insertarTareaFinal(enProceso, tarea);
        } else if(strcmp(tarea.estado, "Finalizada") == 0) { // Si el estado de la tarea es "Finalizada", se inserta en la lista de finalizadas
            insertarTareaFinal(finalizadas, tarea);
        } else {
            AsignarEstado(&tarea, ESTADO_PENDIENTE); // Si el estado de la tarea no es válido, se asigna el estado "Pendiente" por defecto y se inserta en la lista de pendientes
            insertarTareaFinal(pendientes, tarea);
        }
    }

    fclose(archivo); // Cerrar el archivo después de leer todas las tareas
    return 1; // Retornar 1 para indicar que se cargaron las tareas correctamente
}
