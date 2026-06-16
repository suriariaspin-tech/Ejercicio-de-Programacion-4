#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TAREAS 20
#define MAX_TITULO 100
#define MAX_RESPONSABLE 50

// Estructura para almacenar la información de cada tarea
struct Tarea {
    int codigo; // Código único de la tarea
    char titulo[MAX_TITULO]; // Título de la tarea
    char responsable[MAX_RESPONSABLE]; // Nombre del responsable
    char prioridad[20]; // Prioridad de la tarea (Alta, Media o Baja)
};


// FUNCIONES DE VALIDACIÓN

// Función para limpiar el buffer después de usar scanf
void LimpiarBuffer();

// Función para validar textos
void ValidarTexto(char texto[], int tamaño);

// Función para validar que el código sea un entero positivo
void ValidarCodigo(int *codigo);

// Función para validar que la prioridad sea Alta, Media o Baja
void ValidarPrioridad(char prioridad[]);

// Función para validar números enteros positivos
void ValidarEntero(int *numero);

// Función para verificar que el texto ingresado sea válido
int TextoValido(char texto[]);


// FUNCIONES PRINCIPALES

// Función para verificar si un código ya existe
int codigoExiste(
    struct Tarea pendientes[],
    int totalPendientes,

    struct Tarea progreso[],
    int totalProgreso,

    struct Tarea finalizadas[],
    int totalFinalizadas,

    int codigo
);

// Función para buscar una tarea por código
void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,

    struct Tarea progreso[],
    int totalProgreso,

    struct Tarea finalizadas[],
    int totalFinalizadas
);

// Función para eliminar una tarea
void eliminarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea progreso[],
    int *cantProgreso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
);




// Función para registrar una nueva tarea 
void registrarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea enProceso[],
    int *cantEnProceso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
);


// Función para mostrar el tablero Kanban
void mostrarTablero(
    struct Tarea pendientes[],
    int cantPendientes,

    struct Tarea enProceso[],
    int cantEnProceso,

    struct Tarea finalizadas[],
    int cantFinalizadas
);


// Función para mover una tarea de un estado a otro
void cambiarEstado(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea enProceso[],
    int *cantEnProceso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
);


// Función para mostrar estadísticas del tablero
void mostrarEstadisticas(
    int cantPendientes,
    int cantEnProceso,
    int cantFinalizadas
);



#endif