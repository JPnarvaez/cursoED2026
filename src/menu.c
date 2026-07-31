#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "destino.h"
#include "menu.h"
#include "pasajero.h"
#include "avl.h"
#include "viaje.h"

static void leerLinea(char *buffer, int tamanio) {
    if (fgets(buffer, tamanio, stdin) == NULL) {
        return;
    }
    size_t longitud = strlen(buffer);
    if (longitud > 0 && buffer[longitud - 1] == '\n') {
        buffer[longitud - 1] = '\0';
    }
}

static int leerEntero(const char *texto) {
    char buffer[64];
    int valor = 0;
    while (1) {
        printf("%s", texto);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }
        if (sscanf(buffer, "%d", &valor) == 1) {
            return valor;
        }
        printf("Entrada no valida. Intente otra vez.\n");
    }
}

static const char *tipoDocumentoTexto(int tipo) {
    switch (tipo) {
        case 1: return "Cedula de Ciudadania";
        case 2: return "Pasaporte";
        case 3: return "Tarjeta de Identidad";
        default: return "Tipo desconocido";
    }
}

static const char *estadoTexto(int estado) {
    return estado == 1 ? "Embarcado" : "En espera";
}

static int tipoDocumentoValido(int tipo) {
    return tipo == 1 || tipo == 2 || tipo == 3;
}

void menuRegistrarDestino(Destino **frente, Destino **final) {
    int codigo = leerEntero("Codigo de destino: ");
    if (codigo <= 0) {
        printf("El codigo debe ser un numero positivo.\n");
        return;
    }
    if (buscarDestino(*frente, codigo) != NULL) {
        printf("Ya existe un destino con codigo %d.\n", codigo);
        return;
    }
    char nombre[50];
    char empresa[50];
    printf("Nombre del destino: ");
    leerLinea(nombre, sizeof(nombre));
    printf("Empresa responsable: ");
    leerLinea(empresa, sizeof(empresa));

    Destino *nuevo = crearDestino(codigo, nombre, empresa);
    if (nuevo == NULL) {
        printf("No se pudo crear el destino. Memoria insuficiente.\n");
        return;
    }
    agregarDestino(frente, final, nuevo);
    printf("Destino registrado correctamente.\n");
}

void menuRegistrarPasajero(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles. Registre un destino primero.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    int documento = leerEntero("Documento del pasajero: ");
    if (documento <= 0) {
        printf("Documento invalido. Debe ser un numero positivo.\n");
        return;
    }
    if (documentoExisteEnDestinos(frente, documento)) {
        printf("Ya existe un pasajero con documento %d en el sistema.\n", documento);
        return;
    }
    printf("Tipo de documento (1=Cedula de Ciudadania, 2=Pasaporte, 3=Tarjeta de Identidad): ");
    int tipoDocumento = leerEntero("");
    if (!tipoDocumentoValido(tipoDocumento)) {
        printf("Tipo de documento no permitido.\n");
        return;
    }

    char nombre[50];
    printf("Nombre del pasajero: ");
    leerLinea(nombre, sizeof(nombre));

    Pasajero *nuevo = crearPasajero(documento, tipoDocumento, nombre, 0);
    if (nuevo == NULL) {
        printf("No se pudo crear el pasajero. Memoria insuficiente.\n");
        return;
    }
    encolarPasajero(&destino->frente, &destino->final, nuevo);
    printf("Pasajero registrado en la cola de %s.\n", destino->nombre);
}

void menuMostrarPasajerosPorDestino(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    printf("\nDestino %d: %s (%s)\n", destino->codigo, destino->nombre, destino->empresa);
    printf("Pasajeros en espera: %d\n", contarPasajeros(destino->frente));
    if (destino->frente == NULL) {
        printf("  No hay pasajeros en espera.\n");
    } else {
        Pasajero *actual = destino->frente;
        int posicion = 1;
        while (actual != NULL) {
            printf("  %d. Documento: %d, Tipo: %s, Nombre: %s, Estado: %s\n",
                   posicion,
                   actual->documento,
                   tipoDocumentoTexto(actual->tipoDocumento),
                   actual->nombre,
                   estadoTexto(actual->estado));
            actual = actual->sig;
            posicion++;
        }
    }
    printf("Primer pasajero en espera: ");
    if (destino->frente == NULL) {
        printf("Ninguno\n");
    } else {
        printf("Documento %d, Nombre %s\n", destino->frente->documento, destino->frente->nombre);
    }
    printf("\nPasajeros embarcados: %d\n", contarPasajeros(destino->embarcadosFrente));
    if (destino->embarcadosFrente == NULL) {
        printf("  No hay pasajeros embarcados.\n");
    } else {
        Pasajero *actual = destino->embarcadosFrente;
        int posicion = 1;
        while (actual != NULL) {
            printf("  %d. Documento: %d, Tipo: %s, Nombre: %s, Estado: %s\n",
                   posicion,
                   actual->documento,
                   tipoDocumentoTexto(actual->tipoDocumento),
                   actual->nombre,
                   estadoTexto(actual->estado));
            actual = actual->sig;
            posicion++;
        }
    }
}

void menuRegistrarViaje(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles. Registre un destino primero.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    int codigoViaje = leerEntero("Codigo viaje: ");
    if (codigoViaje <= 0) {
        printf("Codigo de viaje invalido.\n");
        return;
    }
    if (buscarViaje(destino->raizViajes, codigoViaje) != NULL) {
        printf("Ya existe un viaje con codigo %d en este destino.\n", codigoViaje);
        return;
    }
    int capacidad = leerEntero("Capacidad maxima del viaje: ");
    if (capacidad <= 0) {
        printf("Capacidad invalida. Debe ser mayor a 0.\n");
        return;
    }
    destino->raizViajes = insertarAVL(destino->raizViajes, codigoViaje, capacidad);
    if (destino->raizViajes == NULL) {
        printf("No se pudo registrar el viaje. Memoria insuficiente.\n");
        return;
    }
    printf("Viaje registrado correctamente en %s.\n", destino->nombre);
}

void menuBuscarViaje(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    int codigoViaje = leerEntero("Codigo del viaje: ");
    Viaje *viaje = buscarViaje(destino->raizViajes, codigoViaje);
    if (viaje == NULL) {
        printf("No se encontro el viaje %d en el destino %s.\n", codigoViaje, destino->nombre);
        return;
    }
    printf("Viaje encontrado: Codigo %d, Capacidad %d, Altura del arbol %d\n",
           viaje->codigoViaje,
           viaje->capacidad,
           viaje->altura);
}

void menuMostrarArbolViajes(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    if (destino->raizViajes == NULL) {
        printf("No hay viajes registrados para %s.\n", destino->nombre);
        return;
    }
    printf("Arbol de viajes para %s:\n", destino->nombre);
    imprimirViajesPreorden(destino->raizViajes, 0);
}

void menuEmbarcarPasajero(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos disponibles.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    Pasajero *pasajero = desencolarPasajero(&destino->frente, &destino->final);
    if (pasajero == NULL) {
        printf("No hay pasajeros en la cola de %s.\n", destino->nombre);
        return;
    }
    pasajero->estado = 1;
    encolarPasajero(&destino->embarcadosFrente, &destino->embarcadosFinal, pasajero);
    printf("Pasajero embarcado: %s, Documento %d, Destino %s.\n",
           pasajero->nombre,
           pasajero->documento,
           destino->nombre);
}

void menuConsultarPasajero(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }
    int documento = leerEntero("Documento del pasajero: ");
    if (documento <= 0) {
        printf("Documento invalido.\n");
        return;
    }
    Destino *destino = frente;
    while (destino != NULL) {
        int estado = 0;
        Pasajero *pasajero = buscarPasajeroEnDestino(destino, documento, &estado);
        if (pasajero != NULL) {
            printf("Pasajero encontrado en destino %s (%s):\n", destino->nombre, destino->empresa);
            printf("  Documento: %d\n", pasajero->documento);
            printf("  Nombre: %s\n", pasajero->nombre);
            printf("  Tipo de documento: %s\n", tipoDocumentoTexto(pasajero->tipoDocumento));
            printf("  Estado: %s\n", estadoTexto(estado));
            return;
        }
        destino = destino->sig;
    }
    printf("No se encontro ningun pasajero con documento %d.\n", documento);
}

void menuModificarDestino(Destino *frente) {
    if (frente == NULL) {
        printf("No hay destinos registrados.\n");
        return;
    }
    int codigo = leerEntero("Codigo del destino a modificar: ");
    Destino *destino = buscarDestino(frente, codigo);
    if (destino == NULL) {
        printf("Destino %d no encontrado.\n", codigo);
        return;
    }
    char nombre[50];
    char empresa[50];
    printf("Nuevo nombre del destino: ");
    leerLinea(nombre, sizeof(nombre));
    printf("Nueva empresa responsable: ");
    leerLinea(empresa, sizeof(empresa));
    modificarDestino(destino, nombre, empresa);
    printf("Destino modificado correctamente.\n");
}

void menuEstadisticas(Destino *frente) {
    int destinos = contarDestinos(frente);
    int totalEspera = 0;
    int totalEmbarcados = 0;
    int totalViajes = contarViajesTotales(frente);
    Destino *destinoMax = NULL;
    Destino *destinoMin = NULL;

    Destino *actual = frente;
    while (actual != NULL) {
        int espera = contarPasajerosEnEspera(actual);
        totalEspera += espera;
        totalEmbarcados += contarPasajerosEmbarcados(actual);

        if (destinoMax == NULL || espera > contarPasajerosEnEspera(destinoMax)) {
            destinoMax = actual;
        }
        if (destinoMin == NULL || espera < contarPasajerosEnEspera(destinoMin)) {
            destinoMin = actual;
        }
        actual = actual->sig;
    }

    double promedioEspera = destinos > 0 ? (double)totalEspera / destinos : 0.0;
    double promedioEmbarcadosPorViaje = totalViajes > 0 ? (double)totalEmbarcados / totalViajes : 0.0;
    int totalRegistrados = totalEspera + totalEmbarcados;

    printf("\n--- Estadisticas del Terminal Portuario ---\n");
    printf("Destinos registrados: %d\n", destinos);
    printf("Viajes registrados: %d\n", totalViajes);
    printf("Pasajeros en espera: %d\n", totalEspera);
    printf("Pasajeros embarcados: %d\n", totalEmbarcados);
    printf("Pasajeros totales registrados: %d\n", totalRegistrados);
    printf("Promedio de pasajeros en espera por destino: %.2f\n", promedioEspera);
    printf("Promedio de pasajeros embarcados por viaje: %.2f\n", promedioEmbarcadosPorViaje);
    if (destinoMax != NULL) {
        printf("Destino con mayor cantidad de pasajeros en espera: %s (%d)\n",
               destinoMax->nombre,
               contarPasajerosEnEspera(destinoMax));
    }
    if (destinoMin != NULL) {
        printf("Destino con menor cantidad de pasajeros en espera: %s (%d)\n",
               destinoMin->nombre,
               contarPasajerosEnEspera(destinoMin));
    }
    printf("-------------------------------------------\n");
}
