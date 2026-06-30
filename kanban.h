#ifndef KANBAN_H
#define KANBAN_H

#include "lista.h"

void registrarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
void modificarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
void buscarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
void eliminarTarea(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
void mostrarEstadisticas(int cantPendientes, int cantEnProceso, int cantFinalizadas);
void mostrarTablero(Lista *pendientes, Lista *enProceso, Lista *finalizadas);
void cambiarEstado(Lista *pendientes, Lista *enProceso, Lista *finalizadas);

#endif
