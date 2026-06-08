
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_CONTENEDORES 30

int pesos[MAX_CONTENEDORES];
int cantidad = 0;
int ordenado = 0;

/* FUNCIONES */
void registrarManual();
void generarAleatorios();
void mostrarContenedores();

void quickSort(int arr[], int inicio, int fin);
int particion(int arr[], int inicio, int fin);

void mergeSort(int arr[], int izquierda, int derecha);
void merge(int arr[], int izquierda, int medio, int derecha);

void shellSort(int arr[], int n);

int busquedaBinaria(int arr[], int n, int valor);

int main()
{
    int opcion;

    srand(time(NULL));
    do
    {
        printf("\n=====================================\n");
        printf(" SISTEMA DE ORGANIZACION DE CONTENEDORES\n");
        printf(" MUELLE DE CARGA\n");
        printf("=====================================\n");

        printf("1. Registrar peso manualmente\n");
        printf("2. Generar pesos aleatorios\n");
        printf("3. Mostrar contenedores\n");
        printf("4. Ordenar contenedores Metodo 1 (Quick Sort)\n");
        printf("5. Ordenar contenedores Metodo 2 (Merge Sort)\n");
        printf("6. Ordenar contenedores Metodo 3 (Shell Sort)\n");
        printf("7. Buscar contenedor\n");
        printf("8. Salir\n");

        printf("\nSeleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarManual();
                break;

            case 2:
                generarAleatorios();
                break;

            case 3:
                mostrarContenedores();
                break;

            case 4:
                if(cantidad > 0)
                {
                    quickSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("\nArreglo ordenado con Quick Sort.\n");
                }
                break;

            case 5:
                if(cantidad > 0)
                {
                    mergeSort(pesos, 0, cantidad - 1);
                    ordenado = 1;
                    printf("\nArreglo ordenado con Merge Sort.\n");
                }
                break;

            case 6:
                if(cantidad > 0)
                {
                    shellSort(pesos, cantidad);
                    ordenado = 1;
                    printf("\nArreglo ordenado con Shell Sort.\n");
                }
                break;

            case 7:
            {
                int pesoBuscado;
                int posicion;

                if(!ordenado)
                {
                    printf("\nDebe ordenar primero el arreglo.\n");
                    break;
                }

                printf("Ingrese el peso a buscar: ");
                scanf("%d", &pesoBuscado);

                posicion = busquedaBinaria(pesos, cantidad, pesoBuscado);

                if(posicion != -1)
                {
                    printf("Contenedor encontrado en posicion %d\n",
                           posicion);
                }
                else
                {
                    printf("Contenedor no encontrado.\n");
                }

                break;
            }

            case 8:
                printf("\nPrograma finalizado.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    } while(opcion != 8);

    return 0;
}

/* REGISTRO MANUAL */
void registrarManual()
{
    int i;

    printf("\nCantidad de contenedores (max 30): ");
    scanf("%d", &cantidad);

    if(cantidad > MAX_CONTENEDORES)
    {
        cantidad = MAX_CONTENEDORES;
    }

    for(i = 0; i < cantidad; i++)
    {
        printf("Peso contenedor %d: ", i + 1);
        scanf("%d", &pesos[i]);
    }

    ordenado = 0;
}

/* ALEATORIOS */
void generarAleatorios()
{
    int i;

    printf("\nCantidad de contenedores (max 30): ");
    scanf("%d", &cantidad);

    if(cantidad > MAX_CONTENEDORES)
    {
        cantidad = MAX_CONTENEDORES;
    }

    for(i = 0; i < cantidad; i++)
    {
        pesos[i] = 1000 + rand() % 30000;
    }

    ordenado = 0;

    printf("\nPesos generados correctamente.\n");
}

/* MOSTRAR */
void mostrarContenedores()
{
    int i;

    if(cantidad == 0)
    {
        printf("\nNo hay contenedores registrados.\n");
        return;
    }

    printf("\nLISTA DE CONTENEDORES\n");

    for(i = 0; i < cantidad; i++)
    {
        printf("Contenedor %d -> %d kg\n",
               i + 1,
               pesos[i]);
    }
}

/* QUICK SORT */
int particion(int arr[], int inicio, int fin)
{
    int pivote = arr[fin];
    int i = inicio - 1;
    int j, temp;

    for(j = inicio; j < fin; j++)
    {
        if(arr[j] < pivote)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[fin];
    arr[fin] = temp;

    return i + 1;
}

void quickSort(int arr[], int inicio, int fin)
{
    if(inicio < fin)
    {
        int pi = particion(arr, inicio, fin);

        quickSort(arr, inicio, pi - 1);
        quickSort(arr, pi + 1, fin);
    }
}

/* MERGE SORT */
void merge(int arr[], int izquierda, int medio, int derecha)
{
    int i, j, k;

    int n1 = medio - izquierda + 1;
    int n2 = derecha - medio;

    int L[n1], R[n2];

    for(i = 0; i < n1; i++)
        L[i] = arr[izquierda + i];

    for(j = 0; j < n2; j++)
        R[j] = arr[medio + 1 + j];

    i = 0;
    j = 0;
    k = izquierda;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < n1)
        arr[k++] = L[i++];

    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(int arr[], int izquierda, int derecha)
{
    if(izquierda < derecha)
    {
        int medio = (izquierda + derecha) / 2;

        mergeSort(arr, izquierda, medio);
        mergeSort(arr, medio + 1, derecha);

        merge(arr, izquierda, medio, derecha);
    }
}

/* SHELL SORT */
void shellSort(int arr[], int n)
{
    int salto, i, j, temp;

    for(salto = n / 2; salto > 0; salto /= 2)
    {
        for(i = salto; i < n; i++)
        {
            temp = arr[i];

            for(j = i; j >= salto &&
                arr[j - salto] > temp; j -= salto)
            {
                arr[j] = arr[j - salto];
            }

            arr[j] = temp;
        }
    }
}

/* BUSQUEDA BINARIA */
int busquedaBinaria(int arr[], int n, int valor)
{
    int inicio = 0;
    int fin = n - 1;

    while(inicio <= fin)
    {
        int medio = (inicio + fin) / 2;

        if(arr[medio] == valor)
            return medio;

        if(arr[medio] < valor)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }

    return -1;
}