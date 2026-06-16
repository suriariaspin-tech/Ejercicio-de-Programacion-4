#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "validaciones.h"

static void SalirPorFinEntrada() {
    printf("\nEntrada finalizada.\n");
    exit(0);
}

void LimpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) { }
}

int TextoValido(char texto[]) {
    for(int i = 0; texto[i] != '\0'; i++) {
        if(!isalnum((unsigned char)texto[i]) &&
           !isspace((unsigned char)texto[i]) &&
           texto[i] != '-' &&
           texto[i] != '.') {
            return 0;
        }
    }
    return 1;
}

void ValidarTexto(char texto[], int tamano) {
    do {
        if(fgets(texto, tamano, stdin) == NULL) {
            SalirPorFinEntrada();
        }

        texto[strcspn(texto, "\n")] = 0;

        if(strlen(texto) == 0) {
            printf("La entrada no puede estar vacia. Ingrese nuevamente: ");
        } else if(!TextoValido(texto)) {
            printf("Caracteres invalidos. Ingrese nuevamente: ");
        }
    } while(strlen(texto) == 0 || !TextoValido(texto));
}

void ValidarCodigo(int *codigo) {
    int resultado;

    while((resultado = scanf("%d", codigo)) != 1 || *codigo <= 0) {
        if(resultado == EOF) {
            SalirPorFinEntrada();
        }

        printf("Codigo invalido. Ingrese nuevamente: ");
        LimpiarBuffer();
    }
}

void ValidarEntero(int *numero) {
    int resultado;

    while((resultado = scanf("%d", numero)) != 1 || *numero <= 0) {
        if(resultado == EOF) {
            SalirPorFinEntrada();
        }

        printf("Entrada invalida. Ingrese un numero entero positivo: ");
        LimpiarBuffer();
    }
}

void ValidarPrioridad(char prioridad[]) {
    int valido;

    do {
        valido = 1;
        printf("Ingrese la prioridad (Alta / Media / Baja): ");

        if(fgets(prioridad, 20, stdin) == NULL) {
            SalirPorFinEntrada();
        }

        prioridad[strcspn(prioridad, "\n")] = 0;

        if(strcmp(prioridad, "Alta") != 0 &&
           strcmp(prioridad, "Media") != 0 &&
           strcmp(prioridad, "Baja") != 0) {
            valido = 0;
            printf("Prioridad invalida.\n");
        }
    } while(!valido);
}
