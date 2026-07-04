#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct NodoPila {
    char cedula[20];
    struct NodoPila* siguiente;
} NodoPila;

typedef struct NodoCola {
    char cedula[20];
    struct NodoCola* siguiente;
} NodoCola;


typedef struct {
    NodoCola* frente;
    NodoCola* final;
} Cola;

void push(NodoPila** tope, const char* cedula) {
    NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible.\n");
        return;
    }
    strcpy(nuevo->cedula, cedula);
    nuevo->siguiente = *tope;
    *tope = nuevo;
}

bool pop(NodoPila** tope, char* destino) {
    if (*tope == NULL) return false;
    NodoPila* temp = *tope;
    strcpy(destino, temp->cedula);
    *tope = (*tope)->siguiente;
    free(temp);
    return true;
}

void mostrarPila(NodoPila* tope) {
    if (tope == NULL) {
        printf("La pila de cedulas esta vacia.\n");
        return;
    }
    printf("--- PILA DE CEDULAS (Tope al inicio) ---\n");
    NodoPila* actual = tope;
    while (actual != NULL) {
        printf("[ Cédula: %s ]\n", actual->cedula);
        actual = actual->siguiente;
    }
    printf("----------------------------------------\n");
}

void liberarPila(NodoPila** tope) {
    char basurero[20];
    while (pop(tope, basurero));
}

void inicializarCola(Cola* c) {
    c->frente = NULL;
    c->final = NULL;
}

void encolar(Cola* c, const char* cedula) {
    NodoCola* nuevo = (NodoCola*)malloc(sizeof(NodoCola));
    if (nuevo == NULL) {
        printf("Error: No hay memoria disponible.\n");
        return;
    }
    strcpy(nuevo->cedula, cedula);
    nuevo->siguiente = NULL;
    
    if (c->final == NULL) {
        c->frente = nuevo;
        c->final = nuevo;
    } else {
        c->final->siguiente = nuevo;
        c->final = nuevo;
    }
}

bool desencolar(Cola* c, char* destino) {
    if (c->frente == NULL) return false;
    NodoCola* temp = c->frente;
    strcpy(destino, temp->cedula);
    c->frente = c->frente->siguiente;
    
    if (c->frente == NULL) {
        c->final = NULL;
    }
    free(temp);
    return true;
}

void mostrarCola(Cola* c, const char* nombreCola) {
    if (c->frente == NULL) {
        printf("La %s esta vacia.\n", nombreCola);
        return;
    }
    printf("--- %s (Frente al inicio) ---\n", nombreCola);
    NodoCola* actual = c->frente;
    while (actual != NULL) {
        printf("[ Ciudadano CC: %s ] -> ", actual->cedula);
        actual = actual->siguiente;
    }
    printf("FIN\n----------------------------------------\n");
}

void liberarCola(Cola* c) {
    char basurero[20];
    while (desencolar(c, basurero));
}


void atenderCiudadano(Cola* colaPrincipal, Cola* colaPendientes, NodoPila** pilaCedulas) {
    char ciudadanoActual[20];
    
    
    if (!desencolar(colaPrincipal, ciudadanoActual)) {
        printf("\n[!] No hay ciudadanos en la cola principal de atencion.\n");
        return;
    }
    
    printf("\n[Atendiendo] Ciudadano con CC: %s\n", ciudadanoActual);
    
    NodoPila* pilaAuxiliar = NULL;
    char cedulaTemporal[20];
    bool encontrada = false;
    
    
    while (*pilaCedulas != NULL) {
        pop(pilaCedulas, cedulaTemporal);
        if (strcmp(cedulaTemporal, ciudadanoActual) == 0) {
            encontrada = true;
            break; 
        } else {
            push(&pilaAuxiliar, cedulaTemporal); 
        }
    }
    
    while (pilaAuxiliar != NULL) {
        pop(&pilaAuxiliar, cedulaTemporal);
        push(pilaCedulas, cedulaTemporal);
    }
    
    if (encontrada) {
        printf("[EXITO] ¡Cedula encontrada! Se le ha entregado su documento al ciudadano.\n");
    } else {
        printf("[PENDIENTE] La cedula no esta lista. El ciudadano pasa a la cola de pendientes.\n");
        encolar(colaPendientes, ciudadanoActual);
    }
}


int main() {
    
    NodoPila* pilaCedulas = NULL;
    Cola colaPrincipal;
    Cola colaPendientes;
    
    inicializarCola(&colaPrincipal);
    inicializarCola(&colaPendientes);
    
    int opcion;
    char bufferCedula[20];
    
    do {
        printf("\n=========================================\n");
        printf("  REGISTRADURIA - CONTROL DE CEDULAS\n");
        printf("=========================================\n");
        printf("1. Ingresar cedula disponible (A Pila)\n");
        printf("2. Registrar ciudadano en fila (A Cola Principal)\n");
        printf("3. Atender siguiente ciudadano (FIFO + LIFO)\n");
        printf("4. Consultar todas las cedulas en stock (Pila)\n");
        printf("5. Ver fila de ciudadanos pendientes (Cola)\n");
        printf("6. Ver fila principal de atencion (Cola)\n");
        printf("7. Salir del sistema (Liberar Memoria)\n");
        printf("Seleccione una opcion: ");
        
        if (scanf("%d", &opcion) != 1) {
            printf("Por favor, ingrese un numero valido.\n");
            while (getchar() != '\n'); 
            opcion = 0;
            continue;
        }
        
        switch (opcion) {
            case 1:
                printf("Ingrese el numero de cedula a almacenar: ");
                scanf("%s", bufferCedula);
                push(&pilaCedulas, bufferCedula);
                printf("[✓] Cedula %s agregada a la pila.\n", bufferCedula);
                break;
                
            case 2:
                printf("Ingrese la cedula del ciudadano que llega: ");
                scanf("%s", bufferCedula);
                encolar(&colaPrincipal, bufferCedula);
                printf("[✓] Ciudadano %s ingresó a la cola de atencion.\n", bufferCedula);
                break;
                
            case 3:
                atenderCiudadano(&colaPrincipal, &colaPendientes, &pilaCedulas);
                break;
                
            case 4:
                mostrarPila(pilaCedulas);
                break;
                
            case 5:
                mostrarCola(&colaPendientes, "COLA DE PENDIENTES");
                break;
                
            case 6:
                mostrarCola(&colaPrincipal, "COLA PRINCIPAL DE ATENCION");
                break;
                
            case 7:
                printf("\nCerrando sistema y liberando estructuras de la memoria...\n");
                liberarPila(&pilaCedulas);
                liberarCola(&colaPrincipal);
                liberarCola(&colaPendientes);
                printf("[✓] Memoria liberada correctamente. ¡Hasta luego!\n");
                break;
                
            default:
                printf("[!] Opcion invalida. Intente de nuevo.\n");
        }
    } while (opcion != 7);
    
    return 0;
}