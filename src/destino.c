#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "destino.h"
#include "avl.h"
#include "pasajero.h"
#include "viaje.h"

Destino *crearDestino(int codigo, const char *nombre, const char *empresa) {
    // Reservamos memoria y copiamos los datos basicos del destino.
    Destino *nuevo = malloc(sizeof(Destino));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->codigo = codigo;
    strncpy(nuevo->nombre, nombre, sizeof(nuevo->nombre) - 1);
    nuevo->nombre[sizeof(nuevo->nombre) - 1] = '\0';
    strncpy(nuevo->empresa, empresa, sizeof(nuevo->empresa) - 1);
    nuevo->empresa[sizeof(nuevo->empresa) - 1] = '\0';
    // Cada destino comienza con sus colas, viajes y enlace vacios.
    nuevo->frente = NULL;
    nuevo->final = NULL;
    nuevo->embarcadosFrente = NULL;
    nuevo->embarcadosFinal = NULL;
    nuevo->raizViajes = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

Destino *agregarDestino(Destino **frente, Destino **final, Destino *nuevo) {
    // La lista usa dos punteros: uno al primero y otro al ultimo.
    if (nuevo == NULL) {
        return NULL;
    }
    if (*final == NULL) {
        *frente = nuevo;
        *final = nuevo;
    } else {
        (*final)->sig = nuevo;
        *final = nuevo;
    }
    return nuevo;
}

Destino *buscarDestino(Destino *frente, int codigo) {
    // Recorremos la lista hasta encontrar el codigo solicitado.
    while (frente != NULL) {
        if (frente->codigo == codigo) {
            return frente;
        }
        frente = frente->sig;
    }
    return NULL;
}

void modificarDestino(Destino *destino, const char *nombre, const char *empresa) {
    // Si no existe el destino, no hay nada que modificar.
    if (destino == NULL) {
        return;
    }
    strncpy(destino->nombre, nombre, sizeof(destino->nombre) - 1);
    destino->nombre[sizeof(destino->nombre) - 1] = '\0';
    strncpy(destino->empresa, empresa, sizeof(destino->empresa) - 1);
    destino->empresa[sizeof(destino->empresa) - 1] = '\0';
}

void imprimirDestinos(Destino *frente) {
    // Mostramos cada destino junto con sus pasajeros y viajes.
    if (frente == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }
    while (frente != NULL) {
        printf("Destino %d: %s (%s)\n", frente->codigo, frente->nombre, frente->empresa);
        printf("  Pasajeros en espera: %d\n", contarPasajeros(frente->frente));
        imprimirColaPasajeros(frente->frente);
        printf("  Pasajeros embarcados: %d\n", contarPasajeros(frente->embarcadosFrente));
        imprimirColaPasajeros(frente->embarcadosFrente);
        printf("  Viajes disponibles:\n");
        if (frente->raizViajes == NULL) {
            printf("    No hay viajes registrados.\n");
        } else {
            imprimirViajesInorden(frente->raizViajes);
        }
        printf("\n");
        frente = frente->sig;
    }
}

int contarDestinos(Destino *frente) {
    // Cada nodo de la lista representa un destino.
    int total = 0;
    while (frente != NULL) {
        total += 1;
        frente = frente->sig;
    }
    return total;
}

int contarPasajerosEnEspera(Destino *destino) {
    // La cola frente contiene a quienes aun esperan embarcar.
    return contarPasajeros(destino->frente);
}

int contarPasajerosEmbarcados(Destino *destino) {
    // La segunda cola conserva a quienes ya fueron embarcados.
    return contarPasajeros(destino->embarcadosFrente);
}

int contarPasajerosTotales(Destino *frente) {
    // Sumamos las dos colas de cada destino.
    int total = 0;
    while (frente != NULL) {
        total += contarPasajeros(frente->frente);
        total += contarPasajeros(frente->embarcadosFrente);
        frente = frente->sig;
    }
    return total;
}

int contarPasajerosEmbarcadosTotales(Destino *frente) {
    // Este conteo solo considera pasajeros que ya embarcaron.
    int total = 0;
    while (frente != NULL) {
        total += contarPasajeros(frente->embarcadosFrente);
        frente = frente->sig;
    }
    return total;
}

int contarViajesTotales(Destino *frente) {
    // Cada destino tiene su propio arbol de viajes.
    int total = 0;
    while (frente != NULL) {
        total += contarViajes(frente->raizViajes);
        frente = frente->sig;
    }
    return total;
}

int documentoExisteEnDestinos(Destino *frente, int documento) {
    // Revisamos tanto pasajeros en espera como embarcados.
    while (frente != NULL) {
        if (buscarPasajero(frente->frente, documento) != NULL || buscarPasajero(frente->embarcadosFrente, documento) != NULL) {
            return 1;
        }
        frente = frente->sig;
    }
    return 0;
}

Pasajero *buscarPasajeroEnDestino(Destino *destino, int documento, int *estado) {
    // Primero buscamos en espera y, si no aparece, en embarcados.
    Pasajero *encontrado = buscarPasajero(destino->frente, documento);
    if (encontrado != NULL) {
        if (estado != NULL) {
            *estado = 0;
        }
        return encontrado;
    }
    encontrado = buscarPasajero(destino->embarcadosFrente, documento);
    if (encontrado != NULL) {
        if (estado != NULL) {
            *estado = 1;
        }
    }
    return encontrado;
}

void imprimirPasajerosPorDestino(Destino *destino) {
    // Es una vista resumida de las dos colas de un solo destino.
    if (destino == NULL) {
        printf("Destino no encontrado.\n");
        return;
    }
    printf("Destino %d: %s (%s)\n", destino->codigo, destino->nombre, destino->empresa);
    printf("  Pasajeros en espera: %d\n", contarPasajeros(destino->frente));
    imprimirColaPasajeros(destino->frente);
    printf("  Pasajeros embarcados: %d\n", contarPasajeros(destino->embarcadosFrente));
    imprimirColaPasajeros(destino->embarcadosFrente);
}

void liberarDestinos(Destino *frente) {
    // Liberamos tambien las estructuras que cuelgan de cada destino.
    while (frente != NULL) {
        Destino *siguiente = frente->sig;
        liberarPasajeros(frente->frente);
        liberarPasajeros(frente->embarcadosFrente);
        liberarViajes(frente->raizViajes);
        free(frente);
        frente = siguiente;
    }
}
