#include "funciones.h"

// Función para limpiar el buffer después de usar scanf y evitar que el siguiente fgets se salte
void LimpiarBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF) { } // Lee y descarta caracteres hasta encontrar un salto de línea o el fin del archivo
}

// Función para validar que el texto ingresado no contenga caracteres no permitidos
int TextoValido(char texto[]) {
    for(int i = 0; texto[i] != '\0'; i++) { // Recorre cada carácter del texto
        if(!isalnum(texto[i]) && !isspace(texto[i]) && texto[i] != '-' && texto[i] != '.') { // Verifica si el carácter no es alfanumérico ni un espacio y no es un guion ni un punto
            return 0; // Si encuentra un carácter no permitido, retorna 0 (falso) 
        }
    }
    return 1; // Si todos los caracteres son válidos, retorna 1 (verdadero)
}

// Función para validar textos
void ValidarTexto(char texto[], int tamaño) {
    do { // Bucle para solicitar el texto hasta que sea válido
        fgets(texto, tamaño, stdin); // Lee el texto ingresado por el usuario
        texto[strcspn(texto, "\n")] = 0; // Elimina el salto de línea al final del texto
        if(strlen(texto) == 0) { // Verifica si el texto está vacío
            printf("La entrada no puede estar vacia. Ingrese nuevamente: ");
        }else if(!TextoValido(texto)) { // Verifica si el texto contiene caracteres no permitidos
            printf("Caracteres invalidos. Ingrese nuevamente: ");
        }
    } while(strlen(texto) == 0 || !TextoValido(texto));
}

// Función para validar que el código ingresado sea positivo
void ValidarCodigo(int *codigo) {
    while(scanf("%d", codigo) != 1 || *codigo <= 0) { // Verifica si la entrada no es un número entero o si es menor o igual a cero
        printf("Codigo invalido. Ingrese nuevamente: ");
        LimpiarBuffer(); // Limpia el buffer para evitar que el siguiente scanf se salte
    }
}

// Función para validar números enteros positivos
void ValidarEntero(int *numero) {
    while(scanf("%d", numero) != 1 || *numero <= 0) { // Verifica si la entrada no es un número entero o si es menor o igual a cero
        printf("Entrada invalida. Ingrese un numero entero positivo: ");
        LimpiarBuffer(); // Limpia el buffer para evitar que el siguiente scanf se salte
    }
}

// Función para validar la prioridad
void ValidarPrioridad(char prioridad[]) {
    int valido; // Variable para controlar la validez de la prioridad ingresada
    do { // Bucle para solicitar la prioridad hasta que sea válida
        valido = 1; // Asume que la prioridad es válida al inicio del bucle
        printf("Ingrese la prioridad (Alta / Media / Baja): ");
        fgets(prioridad, 20, stdin); // Lee la prioridad ingresada por el usuario
        prioridad[strcspn(prioridad, "\n")] = 0; // Elimina el salto de línea al final de la prioridad
        if(strcmp(prioridad, "Alta") != 0 &&
           strcmp(prioridad, "Media") != 0 &&
           strcmp(prioridad, "Baja") != 0) { // Verifica si la prioridad no es "Alta", "Media" o "Baja"
            valido = 0; // Si la prioridad no es válida, establece valido en 0 (falso)
            printf("Prioridad invalida.\n");
        }
    } while(!valido);
}

// Función para verificar que un código no se encuentre repetido
int codigoExiste(
    struct Tarea pendientes[],
    int totalPendientes,

    struct Tarea progreso[],
    int totalProgreso,

    struct Tarea finalizadas[],
    int totalFinalizadas,

    int codigo
) {
    for(int i = 0; i < totalPendientes; i++) { // Recorre el arreglo de tareas pendientes
        if(pendientes[i].codigo == codigo) { // Verifica si el código de la tarea pendiente coincide con el código ingresado
            return 1; // Si encuentra un código repetido, retorna 1 (verdadero)
        }
    }
    for(int i = 0; i < totalProgreso; i++) { // Recorre el arreglo de tareas en progreso
        if(progreso[i].codigo == codigo) { // Verifica si el código de la tarea en progreso coincide con el código ingresado
            return 1; // Si encuentra un código repetido, retorna 1 (verdadero)
        }
    }
    for(int i = 0; i < totalFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
        if(finalizadas[i].codigo == codigo) { // Verifica si el código de la tarea finalizada coincide con el código ingresado
            return 1; // Si encuentra un código repetido, retorna 1 (verdadero)
        }
    }
    return 0; // Si no encuentra ningún código repetido, retorna 0 (falso)
}

// Función para buscar una tarea por código
void buscarTarea(
    struct Tarea pendientes[],
    int totalPendientes,

    struct Tarea progreso[],
    int totalProgreso,

    struct Tarea finalizadas[],
    int totalFinalizadas
) {
    int opcionBusqueda;

    printf("\nBUSCAR TAREA\n");
    printf("1. Buscar por codigo\n");
    printf("2. Buscar por responsable\n");

    do{
        printf("Seleccione una opcion: ");
        ValidarEntero(&opcionBusqueda);

        if(opcionBusqueda < 1 || opcionBusqueda > 2){
            printf("Opcion invalida.\n");
        }

    }while(opcionBusqueda < 1 || opcionBusqueda > 2);
    

    if(opcionBusqueda == 1){
        int codigo;
        printf("Ingrese el codigo a buscar: ");
        ValidarEntero(&codigo); // Validar que el código sea un número entero positivo
        for(int i = 0; i < totalPendientes; i++) { // Recorre el arreglo de tareas pendientes
            if(pendientes[i].codigo == codigo) { // Verifica si el código de la tarea pendiente coincide con el código ingresado
                printf("\nCodigo: %d\n", pendientes[i].codigo);
                printf("Titulo: %s\n", pendientes[i].titulo);
                printf("Responsable: %s\n", pendientes[i].responsable);
                printf("Prioridad: %s\n", pendientes[i].prioridad);
                printf("Estado: Pendiente\n");
                return;
            }
        }
        for(int i = 0; i < totalProgreso; i++) { // Recorre el arreglo de tareas en progreso
            if(progreso[i].codigo == codigo) { // Verifica si el código de la tarea en progreso coincide con el código ingresado
                printf("\nCodigo: %d\n", progreso[i].codigo);
                printf("Titulo: %s\n", progreso[i].titulo);
                printf("Responsable: %s\n", progreso[i].responsable);
                printf("Prioridad: %s\n", progreso[i].prioridad);
                printf("Estado: En Progreso\n");
                return;
            }
        }
        for(int i = 0; i < totalFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
            if(finalizadas[i].codigo == codigo) { // Verifica si el código de la tarea finalizada coincide con el código ingresado
                printf("\nCodigo: %d\n", finalizadas[i].codigo);
                printf("Titulo: %s\n", finalizadas[i].titulo);
                printf("Responsable: %s\n", finalizadas[i].responsable);
                printf("Prioridad: %s\n", finalizadas[i].prioridad);
                printf("Estado: Finalizada\n");
                return;
            }
        }
        printf("Tarea no encontrada.\n");
    }
    else
    {
        char responsable[MAX_RESPONSABLE];
        LimpiarBuffer();

        printf("Ingrese el nombre del responsable: ");
        ValidarTexto(responsable, MAX_RESPONSABLE);

        int encontrado = 0;

        for(int i=0;i<totalPendientes;i++){
            if(strcmp(pendientes[i].responsable,responsable)==0){
                printf("\n[%d] %s\n",
                pendientes[i].codigo,
                pendientes[i].titulo);
                encontrado = 1;
            }
        }

        for(int i=0;i<totalProgreso;i++){
            if(strcmp(progreso[i].responsable,responsable)==0){
                printf("\n[%d] %s\n",
                progreso[i].codigo,
                progreso[i].titulo);
                encontrado = 1;
            }
        }

        for(int i=0;i<totalFinalizadas;i++){
            if(strcmp(finalizadas[i].responsable,responsable)==0){
                printf("\n[%d] %s\n",
                finalizadas[i].codigo,
                finalizadas[i].titulo);
                encontrado = 1;
            }
        }

        if(!encontrado){
            printf("No se encontraron tareas.\n");
        }
    }
}

// Función para eliminar una tarea
void eliminarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea progreso[],
    int *cantProgreso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    int codigo;
    printf("Ingrese el codigo de la tarea a eliminar: ");
    ValidarEntero(&codigo); // Validar que el código sea un número entero positivo
    for(int i = 0; i < *cantPendientes; i++) { // Recorre el arreglo de tareas pendientes
        if(pendientes[i].codigo == codigo) { // Verifica si el código de la tarea pendiente coincide con el código ingresado
            for(int j = i; j < *cantPendientes - 1; j++) { // Desplaza las tareas restantes hacia la izquierda para llenar el espacio de la tarea eliminada
                pendientes[j] = pendientes[j + 1]; // Copia la tarea siguiente en la posición actual
            }
            (*cantPendientes)--; // Decrementa el contador de tareas pendientes
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }
    for(int i = 0; i < *cantProgreso; i++) { // Recorre el arreglo de tareas en progreso
        if(progreso[i].codigo == codigo) { // Verifica si el código de la tarea en progreso coincide con el código ingresado
            for(int j = i; j < *cantProgreso - 1; j++) { // Desplaza las tareas restantes hacia la izquierda para llenar el espacio de la tarea eliminada
                progreso[j] = progreso[j + 1]; // Copia la tarea siguiente en la posición actual
            }
            (*cantProgreso)--; // Decrementa el contador de tareas en progreso
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }

    for(int i = 0; i < *cantFinalizadas; i++) { // Recorre el arreglo de tareas finalizadas
        if(finalizadas[i].codigo == codigo) { // Verifica si el código de la tarea finalizada coincide con el código ingresado
            for(int j = i; j < *cantFinalizadas - 1; j++) { // Desplaza las tareas restantes hacia la izquierda para llenar el espacio de la tarea eliminada
                finalizadas[j] = finalizadas[j + 1]; // Copia la tarea siguiente en la posición actual
            }
            (*cantFinalizadas)--; // Decrementa el contador de tareas finalizadas
            printf("Tarea eliminada correctamente.\n");
            return;
        }
    }
    printf("Tarea no encontrada.\n");


}

// Función para registrar una nueva tarea 
void registrarTarea(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea enProceso[],
    int *cantEnProceso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
) {
    struct Tarea nuevaTarea;
    int estado;

    printf("Ingrese el codigo de la tarea: ");
    ValidarCodigo(&nuevaTarea.codigo);
    LimpiarBuffer();

    // Verificar que el código no esté repetido 
    if(codigoExiste(
        pendientes,
        *cantPendientes,
        enProceso,
        *cantEnProceso,
        finalizadas,
        *cantFinalizadas,
        nuevaTarea.codigo
    )) {
        printf("Error: el codigo ya existe.\n");
        return;
    }


    printf("Ingrese el titulo de la tarea: ");
    ValidarTexto(nuevaTarea.titulo, MAX_TITULO);


    printf("Ingrese el nombre del responsable: ");
    ValidarTexto(nuevaTarea.responsable, MAX_RESPONSABLE);


    ValidarPrioridad(nuevaTarea.prioridad);


    // Seleccionar en qué columna del Kanban se guardará la tarea
    do {
        printf("\nSeleccione el estado inicial:\n");
        printf("1. Pendiente\n");
        printf("2. En Progreso\n");
        printf("3. Finalizada\n");
        printf("Opcion: ");

        ValidarEntero(&estado);

        if(estado < 1 || estado > 3) {
            printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while(estado < 1 || estado > 3);


    // Guardar la tarea 
    if(estado == 1) {

        if(*cantPendientes < MAX_TAREAS) {
            pendientes[*cantPendientes] = nuevaTarea;
            (*cantPendientes)++;
        } else {
            printf("La columna de pendientes está llena.\n");
        }

    } else if(estado == 2) {

        if(*cantEnProceso < MAX_TAREAS) {
            enProceso[*cantEnProceso] = nuevaTarea;
            (*cantEnProceso)++;
        } else {
            printf("La columna de en progreso está llena.\n");
        }

    } else {

        if(*cantFinalizadas < MAX_TAREAS) {
            finalizadas[*cantFinalizadas] = nuevaTarea;
            (*cantFinalizadas)++;
        } else {
            printf("La columna de finalizadas está llena.\n");
        }
    }

    printf("\nTarea registrada correctamente.\n");
}



// Función para mostrar el tablero Kanban completo
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
    if (cantPendientes == 0)
    {
        printf("No hay tareas pendientes.\n");
    }else{
        for(int i = 0; i < cantPendientes; i++) {
            printf("[%d] %s\n",
            pendientes[i].codigo,
            pendientes[i].titulo);
        }
    }



    printf("\n     EN PROGRESO");
    printf("\n========================\n");
    if (cantEnProceso == 0)
    {
        printf("No hay tareas en proceso.\n");
    }else{
        for(int i = 0; i < cantEnProceso; i++) {
            printf("[%d] %s\n",
            enProceso[i].codigo,
            enProceso[i].titulo);
        }
    }



    printf("\n      FINALIZADAS");
    printf("\n========================\n");
    if (cantFinalizadas == 0)
    {
        printf("No hay tareas finalizadas.\n");
    }else{
        for(int i = 0; i < cantFinalizadas; i++) {
            printf("[%d] %s\n",
            finalizadas[i].codigo,
            finalizadas[i].titulo);
        }
    }
}

// Función para mover una tarea a otra columna
void cambiarEstado(
    struct Tarea pendientes[],
    int *cantPendientes,

    struct Tarea enProceso[],
    int *cantEnProceso,

    struct Tarea finalizadas[],
    int *cantFinalizadas
) {

    int codigo;
    int nuevoEstado;
    struct Tarea auxiliar;

    printf("Ingrese el codigo de la tarea a mover: ");
    ValidarEntero(&codigo);


    // Buscar en pendientes
    for(int i = 0; i < *cantPendientes; i++) {

        if(pendientes[i].codigo == codigo) {

            auxiliar = pendientes[i];

            LimpiarBuffer();

            printf("Ingrese el nuevo responsable: ");
            ValidarTexto(auxiliar.responsable, MAX_RESPONSABLE);

            for(int j = i; j < *cantPendientes - 1; j++) {
                pendientes[j] = pendientes[j + 1];
            }

            (*cantPendientes)--;

            do{
                printf("Mover a:\n 1. En Progreso\n 2. Finalizada\n Opcion: ");
                ValidarEntero(&nuevoEstado);

                if(nuevoEstado < 1 || nuevoEstado > 2){
                    printf("Opcion invalida.\n");
                }
            }while(nuevoEstado < 1 || nuevoEstado > 2);

            if(nuevoEstado == 1) {
                enProceso[*cantEnProceso] = auxiliar;
                (*cantEnProceso)++;
            } else {
                finalizadas[*cantFinalizadas] = auxiliar;
                (*cantFinalizadas)++;
            }

            printf("Tarea movida correctamente.\n");
            return;
        }
    }


    // Buscar en proceso
    for(int i = 0; i < *cantEnProceso; i++) {

        if(enProceso[i].codigo == codigo) {

            auxiliar = enProceso[i];

            for(int j = i; j < *cantEnProceso - 1; j++) {
                enProceso[j] = enProceso[j+1];
            }

            (*cantEnProceso)--;


            printf("Mover a:\n1. Pendiente\n2. Finalizada\nOpcion: ");
            ValidarEntero(&nuevoEstado);


            if(nuevoEstado == 1) {
                pendientes[*cantPendientes] = auxiliar;
                (*cantPendientes)++;
            } else {
                finalizadas[*cantFinalizadas] = auxiliar;
                (*cantFinalizadas)++;
            }


            printf("Tarea movida correctamente.\n");
            return;
        }
    }


    // Buscar en finalizadas
    for(int i = 0; i < *cantFinalizadas; i++) {

        if(finalizadas[i].codigo == codigo) {

            auxiliar = finalizadas[i];


            for(int j = i; j < *cantFinalizadas - 1; j++) {
                finalizadas[j] = finalizadas[j+1];
            }

            (*cantFinalizadas)--;


            printf("Mover a:\n1. Pendiente\n2. En Progreso\nOpcion: ");
            ValidarEntero(&nuevoEstado);


            if(nuevoEstado == 1) {
                pendientes[*cantPendientes] = auxiliar;
                (*cantPendientes)++;
            } else {
                enProceso[*cantEnProceso] = auxiliar;
                (*cantEnProceso)++;
            }


            printf("Tarea movida correctamente.\n");
            return;
        }
    }


    printf("Tarea no encontrada.\n");
}


// Función para mostrar estadísticas del tablero
void mostrarEstadisticas(
    int cantPendientes,
    int cantEnProceso,
    int cantFinalizadas
) {

    int total = cantPendientes +
                cantEnProceso +
                cantFinalizadas;

    float porcentaje = 0;


    if(total > 0) {
        porcentaje = (cantFinalizadas * 100.0) / total;
    }


    printf("\n ESTADISTICAS \n");
    printf("Total de tareas: %d\n", total);
    printf("Pendientes: %d\n", cantPendientes);
    printf("En Progreso: %d\n", cantEnProceso);
    printf("Finalizadas: %d\n", cantFinalizadas);
    printf("Porcentaje completado: %.2f%%\n", porcentaje);
}
