/*
 * Proyecto: Terminal Portuario
 * Materia: Estructura de Datos
 *
 * Este programa administra destinos, pasajeros y viajes
 * usando listas enlazadas, colas y un arbol AVL.
 *
 * main.c: aqui se muestra el menu principal y se llaman
 * las funciones que estan en los otros archivos.
 */

#include <stdio.h>
#include <stdlib.h>
#include "include/destino.h"
#include "include/menu.h"

int main() {

    // Puntero al inicio y al final de la lista de destinos
    Destino *frenteDestinos = NULL;
    Destino *finalDestinos = NULL;

    int opcion;   // guarda la opcion que elige el usuario

    opcion = -1; // le doy un valor inicial para que entre al while

    while (opcion != 0) {

        // Muestro el menu principal
        printf("\n");
        printf("=== Terminal Portuario ===\n");
        printf("1. Registrar destino\n");
        printf("2. Registrar pasajero\n");
        printf("3. Mostrar pasajeros por destino\n");
        printf("4. Registrar viaje programado\n");
        printf("5. Buscar viaje\n");
        printf("6. Mostrar arbol de viajes\n");
        printf("7. Realizar embarque\n");
        printf("8. Consultar pasajero (espera / embarcado)\n");
        printf("9. Modificar destino\n");
        printf("10. Mostrar estadisticas\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);

        // limpio el buffer del teclado para que no queden
        // caracteres pendientes de la lectura anterior
        fflush(stdin);

        // Segun la opcion que eligio el usuario, llamo la funcion correspondiente
        if (opcion == 1) {
            menuRegistrarDestino(&frenteDestinos, &finalDestinos);
        }
        else if (opcion == 2) {
            menuRegistrarPasajero(frenteDestinos);
        }
        else if (opcion == 3) {
            menuMostrarPasajerosPorDestino(frenteDestinos);
        }
        else if (opcion == 4) {
            menuRegistrarViaje(frenteDestinos);
        }
        else if (opcion == 5) {
            menuBuscarViaje(frenteDestinos);
        }
        else if (opcion == 6) {
            menuMostrarArbolViajes(frenteDestinos);
        }
        else if (opcion == 7) {
            menuEmbarcarPasajero(frenteDestinos);
        }
        else if (opcion == 8) {
            menuConsultarPasajero(frenteDestinos);
        }
        else if (opcion == 9) {
            menuModificarDestino(frenteDestinos);
        }
        else if (opcion == 10) {
            menuEstadisticas(frenteDestinos);
        }
        else if (opcion == 0) {
            printf("Saliendo...\n");
        }
        else {
            printf("Opcion no valida. Intente otra vez.\n");
        }

    }

    // Al salir del programa libero toda la memoria que se pidio con malloc
    liberarDestinos(frenteDestinos);

    return 0;
}
