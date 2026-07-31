#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pasajero.h"

Pasajero *crearPasajero(int documento, int tipoDocumento, const char *nombre, int estado) {
    // Creamos un pasajero y guardamos una copia segura de su nombre.
    Pasajero *nuevo = malloc(sizeof(Pasajero));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->documento = documento;
    nuevo->tipoDocumento = tipoDocumento;
    nuevo->estado = estado;
    strncpy(nuevo->nombre, nombre, sizeof(nuevo->nombre) - 1);
    nuevo->nombre[sizeof(nuevo->nombre) - 1] = '\0';
    nuevo->sig = NULL;
    return nuevo;
}

Pasajero *buscarPasajero(Pasajero *frente, int documento) {
    // Se revisa la cola nodo por nodo hasta hallar el documento.
    while (frente != NULL) {
        if (frente->documento == documento) {
            return frente;
        }
        frente = frente->sig;
    }
    return NULL;
}

void encolarPasajero(Pasajero **frente, Pasajero **final, Pasajero *nuevo) {
    // Encolar agrega al final para respetar el orden de llegada.
    if (nuevo == NULL) {
        return;
    }
    if (*final == NULL) {
        *frente = nuevo;
        *final = nuevo;
    } else {
        (*final)->sig = nuevo;
        *final = nuevo;
    }
}

Pasajero *desencolarPasajero(Pasajero **frente, Pasajero **final) {
    // Desencolar siempre retira al primero, como en una fila real.
    if (*frente == NULL) {
        return NULL;
    }
    Pasajero *salida = *frente;
    *frente = (*frente)->sig;
    // Si sale el ultimo pasajero, la cola queda completamente vacia.
    if (*frente == NULL) {
        *final = NULL;
    }
    salida->sig = NULL;
    return salida;
}

void imprimirColaPasajeros(Pasajero *frente) {
    // Recorremos la cola sin modificarla para mostrar su contenido.
    if (frente == NULL) {
        printf("    No hay pasajeros en la cola.\n");
        return;
    }
    printf("    Pasajeros en cola:\n");
    while (frente != NULL) {
        printf("      Documento: %d, Tipo: %d, Estado: %d, Nombre: %s\n",
               frente->documento,
               frente->tipoDocumento,
               frente->estado,
               frente->nombre);
        frente = frente->sig;
    }
}

int contarPasajeros(Pasajero *frente) {
    // Contamos los nodos de la cola hasta llegar a NULL.
    int total = 0;
    while (frente != NULL) {
        total += 1;
        frente = frente->sig;
    }
    return total;
}

void liberarPasajeros(Pasajero *frente) {
    // Guardamos el siguiente antes de liberar el nodo actual.
    while (frente != NULL) {
        Pasajero *siguiente = frente->sig;
        free(frente);
        frente = siguiente;
    }
}
