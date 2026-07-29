#ifndef DESTINO_H
#define DESTINO_H

#include "pasajero.h"
#include "viaje.h"

typedef struct Destino {
    int codigo;
    char nombre[50];
    char empresa[50];
    Pasajero *frente;
    Pasajero *final;
    Pasajero *embarcadosFrente;
    Pasajero *embarcadosFinal;
    Viaje *raizViajes;
    struct Destino *sig;
} Destino;

Destino *crearDestino(int codigo, const char *nombre, const char *empresa);
Destino *agregarDestino(Destino **frente, Destino **final, Destino *nuevo);
Destino *buscarDestino(Destino *frente, int codigo);
void imprimirDestinos(Destino *frente);
void modificarDestino(Destino *destino, const char *nombre, const char *empresa);
int contarDestinos(Destino *frente);
int contarPasajerosEnEspera(Destino *destino);
int contarPasajerosEmbarcados(Destino *destino);
int contarPasajerosTotales(Destino *frente);
int contarPasajerosEmbarcadosTotales(Destino *frente);
int contarViajesTotales(Destino *frente);
int documentoExisteEnDestinos(Destino *frente, int documento);
Pasajero *buscarPasajeroEnDestino(Destino *destino, int documento, int *estado);
void imprimirPasajerosPorDestino(Destino *destino);
void liberarDestinos(Destino *frente);

#endif // DESTINO_H
