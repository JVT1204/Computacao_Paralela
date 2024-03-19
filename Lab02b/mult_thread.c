#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int block_size = 50;                 // Define o tamanho do bloco para a divisão das operações da matriz
int m = 1000;                        // Tamanho da matriz
int n = 1000;                        // Tamanho da matriz
int thread_count;                    // Número de threads
int **A;                             // Matriz A
int *x;                              // Vetor x
int *y;                              // Vetor y (resultado da multiplicação)

void *Pth_mat_vect(void *rank) {
    long my_rank = (long)rank;      // Número da thread
    int local_m = m / thread_count; // Número de linhas processadas por thread
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;
    int i, j;

    // Multiplicação da matriz por vetor
    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    return NULL;
}

int main() {

    // Número de blocos (ou threads)
    thread_count = n/block_size;  // Calcula o número de threads com base no tamanho do bloco
    
    // Aloca memória para a matriz A e inicializa seus elementos
    A = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j + 1;   // Inicializa os elementos da matriz A
        }
    }

    // Aloca memória para o vetor x e inicializa seus elementos
    x = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        x[i] = i + 1;   // Inicializa os elementos do vetor x
    }

    // Aloca memória para o vetor y
    y = (int *)malloc(m * sizeof(int));

    pthread_t *thread_handles;
    thread_handles = (pthread_t *)malloc(thread_count * sizeof(pthread_t));

    // Cria threads para executar a multiplicação da matriz por vetor
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread);
    }

    // Aguarda o término de todas as threads
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

 // Libera memória alocada
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}