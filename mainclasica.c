
/**************************************************************
                Pontificia Universidad Javeriana
        Autor: Daniel Hoyps
        Fecha: Abril 2025
        Materia: Sistemas Operativos
        Tema: laboratorio en perl
        Fichero: Archivo main en el cual se llaman las funciones desarrolladas en mmclasica.c y definidas en mmclasica.h.
        Objetivo: multiplicacion de matrices mediante la entrada de las filas x columnas, y los hilos 
****************************************************************/


#include "mmclasica.h"       // Archivo de cabecera con variables y funciones declaradas
#include <stdio.h>           // Para funciones de entrada/salida
#include <stdlib.h>          // Para uso de atoi, malloc, etc.

int main(int argc, char *argv[]) {
    // Verifica si se pasaron los argumentos necesarios
    if (argc < 3) {
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        return -1;
    }

    int SZ = atoi(argv[1]);        // Convierte el primer argumento a entero: tamaño de la matriz
    int n_threads = atoi(argv[2]); // Convierte el segundo argumento a entero: número de hilos

    pthread_t p[n_threads];        // Arreglo para almacenar los identificadores de los hilos
    pthread_attr_t atrMM;          // Atributos de los hilos

    // Asigna las posiciones de memoria para las matrices A, B y C en el bloque MEM_CHUNK
    mA = MEM_CHUNK;                // mA apunta al inicio del bloque de memoria
    mB = mA + SZ * SZ;             // mB se ubica justo después de mA
    mC = mB + SZ * SZ;             // mC se ubica después de mB

    llenar_matriz(SZ);             // Llena las matrices A y B con valores, y la C con ceros
    print_matrix(SZ, mA);          // Imprime la matriz A (si SZ <= 12)
    print_matrix(SZ, mB);          // Imprime la matriz B (si SZ <= 12)

    inicial_tiempo();              // Inicia la medición del tiempo de ejecución

    pthread_mutex_init(&MM_mutex, NULL);                // Inicializa el mutex
    pthread_attr_init(&atrMM);                          // Inicializa los atributos del hilo
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Define que los hilos son unibles

    // Crea los hilos y les pasa los parámetros correspondientes
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
        datos->idH = j;           // ID del hilo actual
        datos->nH = n_threads;    // Número total de hilos
        datos->N = SZ;            // Tamaño de la matriz
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos); // Crea el hilo y ejecuta mult_thread
    }

    // Espera a que todos los hilos terminen su ejecución
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

    final_tiempo();               // Finaliza la medición y muestra el tiempo de ejecución
    print_matrix(SZ, mC);         // Imprime la matriz resultante (si SZ <= 12)

    pthread_attr_destroy(&atrMM);      // Libera los recursos de los atributos
    pthread_mutex_destroy(&MM_mutex); // Libera el mutex
    pthread_exit(NULL);               // Finaliza de forma segura

    return 0;
}
