# Terminal Portuario Buenaventura

## Descripcion

Este es un proyecto de la materia de Estructuras de Datos. El programa simula algunas operaciones de un terminal portuario, como registrar destinos, pasajeros y viajes.

La aplicacion funciona desde un menu en la consola y utiliza memoria dinamica para crear y eliminar los datos durante la ejecucion.

## Estructuras de datos utilizadas

- Lista enlazada para guardar los destinos en el orden en que se registran.
- Cola FIFO para organizar los pasajeros de cada destino.
- Arbol AVL para almacenar los viajes programados de cada destino.
- Nodos y punteros para relacionar destinos, pasajeros y viajes.

El arbol AVL se mantiene balanceado mediante rotaciones. Por esta razon, las busquedas de viajes son mas eficientes que en un arbol que puede quedar completamente inclinado.

## Funciones principales

- Registrar, buscar y modificar destinos.
- Registrar pasajeros y evitar documentos repetidos.
- Mostrar los pasajeros que estan esperando o que ya fueron embarcados.
- Registrar y buscar viajes por su codigo.
- Mostrar el arbol de viajes.
- Realizar el embarque del primer pasajero de la cola.
- Consultar estadisticas del terminal.
- Liberar la memoria utilizada al salir del programa.

## Organizacion del proyecto

```text
Terminal Portuario Buenaventura/
|-- main.c
|-- Makefile
|-- README.md
|-- include/
|   |-- avl.h
|   |-- destino.h
|   |-- menu.h
|   |-- pasajero.h
|   `-- viaje.h
`-- src/
    |-- avl.c
    |-- destino.c
    |-- menu.c
    |-- pasajero.c
    `-- viaje.c
```

## Compilacion en Windows

Desde la carpeta principal del proyecto se puede usar el siguiente comando:

```bash
gcc -Wall -Wextra -Werror -std=c11 -I include main.c src/avl.c src/destino.c src/menu.c src/pasajero.c src/viaje.c -o terminal_portuario.exe
```

Tambien se puede ejecutar la tarea de VS Code llamada `Compilar Terminal`.

## Ejecucion

Despues de compilar, se ejecuta con:

```bash
./terminal_portuario.exe
```

En PowerShell tambien se puede utilizar:

```powershell
.\terminal_portuario.exe
```

## Opciones del menu

1. Registrar destino
2. Registrar pasajero
3. Mostrar pasajeros por destino
4. Registrar viaje programado
5. Buscar viaje
6. Mostrar arbol de viajes
7. Realizar embarque
8. Consultar pasajero, ya sea en espera o embarcado
9. Modificar destino
10. Mostrar estadisticas
0. Salir

## Limpieza

Al seleccionar la opcion `0`, el programa libera los destinos, pasajeros y viajes creados con `malloc`. Esto evita dejar memoria reservada despues de cerrar la aplicacion.
