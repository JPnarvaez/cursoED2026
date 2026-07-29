#ifndef MENU_H
#define MENU_H

#include "destino.h"

void menuRegistrarDestino(Destino **frente, Destino **final);
void menuRegistrarPasajero(Destino *frente);
void menuMostrarPasajerosPorDestino(Destino *frente);
void menuRegistrarViaje(Destino *frente);
void menuBuscarViaje(Destino *frente);
void menuMostrarArbolViajes(Destino *frente);
void menuEmbarcarPasajero(Destino *frente);
void menuConsultarPasajero(Destino *frente);
void menuModificarDestino(Destino *frente);
void menuEstadisticas(Destino *frente);

#endif // MENU_H
