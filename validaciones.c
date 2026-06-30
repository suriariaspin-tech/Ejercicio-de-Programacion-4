#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"

// Función para limpiar el buffer de entrada, eliminando cualquier carácter restante hasta el salto de línea o el fin de archivo
void LimpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) { }
}

// Función para validar que el texto ingresado no contenga caracteres no permitidos (solo letras, números y espacios)
int TextoValido(char texto[]) {
    for(int i = 0; texto[i] != '\0'; i++) { // BUCLE para verificar cada caracter del texto y validar que solo contenga letras, números y espacios
        if(!isalpha(texto[i]) && !isdigit(texto[i]) && !isspace(texto[i])) { // Si se encuentra un caracter que no es letra ni número ni espacio, se considera inválido
            return 0; // Si el texto es inválido, se devuelve 0
        }
    }
    return 1; // Si el texto es válido, se devuelve 1
}

// Función para validar la entrada de texto, asegurándose de que no esté vacía y solo contenga caracteres válidos
void ValidarTexto(char texto[], int tamaño) {
    do {
        fgets(texto, tamaño, stdin);
        texto[strcspn(texto, "\n")] = 0; // Elimina el salto de línea al final del texto ingresado
        if(strlen(texto) == 0) { // Si el texto está vacío, se muestra un mensaje de error y se solicita ingresar nuevamente
            printf("La entrada no puede estar vacia. Ingrese nuevamente: ");
        } else if(!TextoValido(texto)) {
            printf("Solo se permiten letras, numeros y espacios. Ingrese nuevamente: ");
        }
    } while(strlen(texto) == 0 || !TextoValido(texto)); // Buccle para validar que el texto no esté vacío y que no contenga caracteres no permitidos
}

// Función para validar que la entrada sea un número entero positivo
void ValidarEntero(int *numero) {
    while(scanf("%d", numero) != 1 || *numero <= 0) { // Bucle para validar que la entrada sea un número entero y positivo
        printf("Valor invalido. Ingrese un numero positivo: ");
        LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada inválida
    }
    LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada válida
}

// Función para validar la prioridad de una tarea, asegurándose de que sea 1, 2 o 3
void ValidarPrioridad(int *prioridad) {
    do {
        printf("Ingrese la prioridad (1-Alta / 2-Media / 3-Baja): ");
        ValidarEntero(prioridad);

        if(*prioridad < 1 || *prioridad > 3) {
            printf("Prioridad invalida.\n");
        }
    } while(*prioridad < 1 || *prioridad > 3);
}
