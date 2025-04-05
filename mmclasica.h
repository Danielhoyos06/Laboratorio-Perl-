#ifndef MMCLASICA_H
#define MMCLASICA_H

#include <pthread.h>

#define DATA_SIZE (1024*1024*64*3)

extern pthread_mutex_t MM_mutex;
extern double *mA, *mB, *mC;
extern double MEM_CHUNK[DATA_SIZE];

struct parametros {
    int nH;
    int idH;
    int N;
};

// Prototipos de funciones
void llenar_matriz(int SZ);
void print_matrix(int sz, double *matriz);
void inicial_tiempo();
void final_tiempo();
void *mult_thread(void *variables);

#endif
