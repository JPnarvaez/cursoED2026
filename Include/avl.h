#ifndef AVL_H
#define AVL_H

#include "viaje.h"

int altura(Viaje *n);
int maximo(int a, int b);
int factorBalance(Viaje *n);
Viaje *rotacionDerecha(Viaje *y);
Viaje *rotacionIzquierda(Viaje *y);
Viaje *insertarAVL(Viaje *raiz, int codigo, int capacidad);
Viaje *buscarViaje(Viaje *raiz, int codigo);

#endif // AVL_H
