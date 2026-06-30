#ifndef ARCHIVO_H
#define ARCHIVO_H

#include "lista.h"

void guardarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
int cargarTareas(Lista *pendientes, Lista *enProceso, Lista *finalizadas);

#endif
