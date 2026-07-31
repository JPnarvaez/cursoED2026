#include <stdio.h>
#include <stdlib.h>
#include "viaje.h"

Viaje *crearViaje(int codigo, int capacidad) {
    // Un viaje nace como nodo independiente del arbol AVL.
    Viaje *nuevo = malloc(sizeof(Viaje));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->codigoViaje = codigo;
    nuevo->capacidad = capacidad;
    nuevo->altura = 1;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

void imprimirViajesInorden(Viaje *raiz) {
    // Inorden imprime los codigos de menor a mayor.
    if (raiz == NULL) {
        return;
    }
    imprimirViajesInorden(raiz->izq);
    printf("  Codigo: %d, Capacidad: %d\n", raiz->codigoViaje, raiz->capacidad);
    imprimirViajesInorden(raiz->der);
}

void imprimirViajesPreorden(Viaje *raiz, int nivel) {
    // Preorden permite ver la forma del arbol y su nivel de profundidad.
    if (raiz == NULL) {
        return;
    }
    // La sangria ayuda a distinguir visualmente cada nivel.
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }
    printf("- Codigo: %d, Capacidad: %d, Altura: %d\n", raiz->codigoViaje, raiz->capacidad, raiz->altura);
    imprimirViajesPreorden(raiz->izq, nivel + 1);
    imprimirViajesPreorden(raiz->der, nivel + 1);
}

int contarViajes(Viaje *raiz) {
    // Contamos la raiz y luego todos los nodos de ambos lados.
    if (raiz == NULL) {
        return 0;
    }
    return 1 + contarViajes(raiz->izq) + contarViajes(raiz->der);
}

void liberarViajes(Viaje *raiz) {
    // Primero liberamos los hijos para no perder sus direcciones.
    if (raiz == NULL) {
        return;
    }
    liberarViajes(raiz->izq);
    liberarViajes(raiz->der);
    free(raiz);
}
