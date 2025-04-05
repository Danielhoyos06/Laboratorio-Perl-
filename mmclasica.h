/**************************************************************
                Pontificia Universidad Javeriana
        Autor: Daniel Hoyps
        Fecha: Abril 2025
        Materia: Sistemas Operativos
        Tema: laboratorio en perl
        Fichero: Archivo que contiene las funciones a usar para su mnodularizacion.
        Objetivo: definicion de variables ya desplegadas en el archivo mmclasica.c para su modularizacion
****************************************************************/

#ifndef MMCLASICA_H
#define MMCLASICA_H

#include <pthread.h>  // Inclusión de la biblioteca para manejo de hilos

// Define el tamaño del bloque de datos en memoria (3 matrices grandes)
#define DATA_SIZE (1024*1024*64*3)

// Declaración de variables globales utilizadas para las matrices y el mutex
extern pthread_mutex_t MM_mutex;            // Mutex para sincronización de hilos
extern double *mA, *mB, *mC;                // Punteros a las matrices A, B y C
extern double MEM_CHUNK[DATA_SIZE];         // Bloque de memoria para almacenar las matrices

// Estructura que almacena los parámetros que cada hilo recibirá
struct parametros {
    int nH;   // Número total de hilos
    int idH;  // Identificador del hilo actual
    int N;    // Dimensión de la matriz
};


void llenar_matriz(int SZ);                         // Rellena las matrices A y B con datos iniciales
void print_matrix(int sz, double *matriz);          // Imprime el contenido de una matriz
void inicial_tiempo();                              // Inicia la medición del tiempo
void final_tiempo();                                // Finaliza y muestra la medición del tiempo
void *mult_thread(void *variables);                 // Función que ejecuta la multiplicación en cada hilo

#endif // MMCLASICA_H
