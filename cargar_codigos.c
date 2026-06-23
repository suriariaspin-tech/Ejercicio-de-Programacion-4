#include <stdio.h>
#include "cargar_codigos.h"

void cargarCodigos()
{
    FILE *archivo;

    char linea[100];

    archivo = fopen("codigos.txt", "r");

    if(archivo == NULL)
    {
        printf("Error al abrir codigos.txt\n");
        return;
    }

    printf("\n=== CODIGOS CARGADOS ===\n");

    while(fgets(linea, sizeof(linea), archivo) != NULL)
    {
        printf("%s", linea);
    }

    fclose(archivo);

    printf("\n========================\n");
}