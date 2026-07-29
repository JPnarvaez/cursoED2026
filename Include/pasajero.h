#ifndef PASAJERO_H
#define PASAJERO_H

typedef struct Pasajero {
    int documento;
    int tipoDocumento;
    int estado;
    char nombre[50];
    struct Pasajero *sig;
} Pasajero;

Pasajero *crearPasajero(int documento, int tipoDocumento, const char *nombre, int estado);
Pasajero *buscarPasajero(Pasajero *frente, int documento);
void liberarPasajeros(Pasajero *frente);
void encolarPasajero(Pasajero **frente, Pasajero **final, Pasajero *nuevo);
Pasajero *desencolarPasajero(Pasajero **frente, Pasajero **final);
void imprimirColaPasajeros(Pasajero *frente);
int contarPasajeros(Pasajero *frente);

#endif // PASAJERO_H