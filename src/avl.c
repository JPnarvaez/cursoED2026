#include <stdlib.h>
#include "avl.h"
#include "viaje.h"

int altura(Viaje *n) {
    // Un arbol vacio tiene altura cero.
    if (n == NULL) {
        return 0;
    }
    return n->altura;
}

int maximo(int a, int b) {
    // Se usa para actualizar la altura tomando el hijo mas alto.
    return (a > b) ? a : b;
}

int factorBalance(Viaje *n) {
    // Positivo significa que pesa mas el lado derecho; negativo, el izquierdo.
    if (n == NULL) {
        return 0;
    }
    return altura(n->der) - altura(n->izq);
}

Viaje *rotacionDerecha(Viaje *y) {
    // Esta rotacion corrige un arbol cargado hacia la izquierda.
    Viaje *x = y->izq;
    Viaje *subArbol = x->der;

    // x sube y el subarbol intermedio conserva su lugar correcto.
    x->der = y;
    y->izq = subArbol;

    // Despues de mover nodos, las alturas dejan de ser las anteriores.
    y->altura = 1 + maximo(altura(y->izq), altura(y->der));
    x->altura = 1 + maximo(altura(x->izq), altura(x->der));

    return x;
}

Viaje *rotacionIzquierda(Viaje *y) {
    // Esta es la version contraria: corrige un arbol cargado hacia la derecha.
    Viaje *x = y->der;
    Viaje *subArbol = x->izq;

    // x pasa a ser la nueva raiz de esta pequena parte del arbol.
    x->izq = y;
    y->der = subArbol;

    y->altura = 1 + maximo(altura(y->izq), altura(y->der));
    x->altura = 1 + maximo(altura(x->izq), altura(x->der));

    return x;
}

Viaje *buscarViaje(Viaje *raiz, int codigo) {
    // Como el AVL esta ordenado, cada comparacion descarta medio camino.
    if (raiz == NULL) {
        return NULL;
    }
    if (codigo == raiz->codigoViaje) {
        return raiz;
    }
    if (codigo < raiz->codigoViaje) {
        return buscarViaje(raiz->izq, codigo);
    }
    return buscarViaje(raiz->der, codigo);
}

Viaje *insertarAVL(Viaje *raiz, int codigo, int capacidad) {
    if (raiz == NULL) {
        // Llegamos al lugar donde debe vivir el nuevo viaje.
        Viaje *nuevo = malloc(sizeof(Viaje));
        if (nuevo == NULL) {
            return NULL;
        }
        nuevo->codigoViaje = codigo;
        nuevo->capacidad = capacidad;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        nuevo->altura = 1;
        return nuevo;
    }

    if (codigo < raiz->codigoViaje) {
        // Los codigos menores siempre van al subarbol izquierdo.
        raiz->izq = insertarAVL(raiz->izq, codigo, capacidad);
    } else if (codigo > raiz->codigoViaje) {
        // Los codigos mayores siempre van al subarbol derecho.
        raiz->der = insertarAVL(raiz->der, codigo, capacidad);
    } else {
        // No se permiten dos viajes con el mismo codigo.
        return raiz;
    }

    // Al volver de la recursion, actualizamos la altura de cada antecesor.
    raiz->altura = 1 + maximo(altura(raiz->izq), altura(raiz->der));
    int fb = factorBalance(raiz);

    // Caso izquierda-izquierda: una sola rotacion a la derecha.
    if (fb < -1 && codigo < raiz->izq->codigoViaje) {
        return rotacionDerecha(raiz);
    }

    // Caso izquierda-derecha: primero equilibramos el hijo y luego la raiz.
    if (fb < -1 && codigo > raiz->izq->codigoViaje) {
        raiz->izq = rotacionIzquierda(raiz->izq);
        return rotacionDerecha(raiz);
    }

    // Caso derecha-derecha: una sola rotacion a la izquierda.
    if (fb > 1 && codigo > raiz->der->codigoViaje) {
        return rotacionIzquierda(raiz);
    }

    // Caso derecha-izquierda: se hacen dos rotaciones en sentido contrario.
    if (fb > 1 && codigo < raiz->der->codigoViaje) {
        raiz->der = rotacionDerecha(raiz->der);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}
