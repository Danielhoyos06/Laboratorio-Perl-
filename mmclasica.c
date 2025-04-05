
/**************************************************************
                Pontificia Universidad Javeriana
        Autor: Daniel Hoyps
        Fecha: Abril 2025
        Materia: Sistemas Operativos
        Tema: laboratorio en perl
        Fichero: Archivo que contiene las funciones a usar.
        Objetivo: despliegue de desarollo de funciones que seran implementadas en el archivo mainclasica.c y mmclasica.h
****************************************************************/


#include "mmclasica.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


pthread_mutex_t MM_mutex;
 double MEM_CHUNK[DATA_SIZE]; // Bloque grande de memoria estática

double *mA, *mB, *mC;               // Punteros a matrices A, B y C
struct timeval start, stop;        // Variables para medir tiempo

// Llena matrices A y B con valores; C se inicializa en cero
void llenar_matriz(int SZ) {
    srand48(time(NULL));
    for (int i = 0; i < SZ * SZ; i++) {
        mA[i] = 1.1 * i;
        mB[i] = 2.2 * i;
        mC[i] = 0;
    }
}

// Imprime las matrices llenadas
void print_matrix(int sz, double *matriz) {
    if (sz < 12) {
        for (int i = 0; i < sz * sz; i++) {
            if (i % sz == 0) printf("\n");
            printf(" %.3f ", matriz[i]);
        }
        printf("\n>-------------------->\n");
    }
}

// Inicia conteo de tiempo
void inicial_tiempo() {
    gettimeofday(&start, NULL);
}

// Finaliza conteo y muestra duración en microsegundos
void final_tiempo() {
    gettimeofday(&stop, NULL);
    stop.tv_sec -= start.tv_sec;
    printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
}

// Función que ejecuta cada hilo para realizar multiplicación parcial
void *mult_thread(void *variables) {
    struct parametros *data = (struct parametros *)variables;
    int idH = data->idH;
    int nH  = data->nH;
    int N   = data->N;

    // Rango de filas que este hilo va a procesar
    int ini = (N / nH) * idH;
    int fin = (N / nH) * (idH + 1);

    for (int i = ini; i < fin; i++) {
        for (int j = 0; j < N; j++) {
            double *pA = mA + (i * N); // Fila i de A
            double *pB = mB + j;       // Columna j de B
            double sumaTemp = 0.0;

            for (int k = 0; k < N; k++, pA++, pB += N) {
                sumaTemp += (*pA * *pB); // Producto escalar fila × columna
            }

            mC[i * N + j] = sumaTemp; // Guarda resultado en C
        }
    }

    // Mutex bloqueado y desbloqueado para sincronización
    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);

    pthread_exit(NULL); // Finaliza el hilo
}

