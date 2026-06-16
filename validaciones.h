#ifndef VALIDACIONES_H
#define VALIDACIONES_H

// Modulo 6: funciones para validar entradas del usuario.

void LimpiarBuffer();
int TextoValido(char texto[]);
void ValidarTexto(char texto[], int tamano);
void ValidarCodigo(int *codigo);
void ValidarEntero(int *numero);
void ValidarPrioridad(char prioridad[]);

#endif
