#ifndef VIAJE_H
#define VIAJE_H

typedef struct Viaje {
    int codigoViaje;
    int capacidad;
    int altura;
    struct Viaje *izq;
    struct Viaje *der;
} Viaje;

Viaje *crearViaje(int codigo, int capacidad);
void liberarViajes(Viaje *raiz);
void imprimirViajesInorden(Viaje *raiz);
void imprimirViajesPreorden(Viaje *raiz, int nivel);
int contarViajes(Viaje *raiz);

#endif // VIAJE_H
