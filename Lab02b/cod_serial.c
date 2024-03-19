#include <stdio.h>         // Inclui a biblioteca de entrada e saída padrão.
#include <stdlib.h>        // Inclui a biblioteca padrão do C, que inclui funções como alocação de memória e outras operações.
#include <pthread.h>       // Inclui a biblioteca pthread, necessária para programação paralela em POSIX.

int m, n, thread_count;    // Variáveis globais para armazenar o tamanho da matriz, o número de threads e dimensões da matriz.
int** A;                   // Matriz A.
int* x;                    // Vetor x.
int* y;                    // Vetor y (resultado da multiplicação).

void *Pth_mat_vect(void *rank) {  // Função executada por cada thread.
    long my_rank = (long) rank;    // Número da thread.
    int i, j;                      // Índices para iteração.
    int local_m = m / thread_count; // Número de linhas a serem processadas por cada thread.
    int my_first_row = my_rank * local_m; // Primeira linha a ser processada pela thread.
    int my_last_row = (my_rank + 1) * local_m - 1; // Última linha a ser processada pela thread.

    // Loop para multiplicar as linhas da matriz pelo vetor.
    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;  // Inicializa o elemento y[i].
        // Loop para calcular o produto escalar de cada linha de A com x.
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];  // Multiplica e acumula os valores.
        }
    }

    return NULL;
}

int main() {  // Função principal do programa.
    printf("Número de threads: ");  // Solicita o número de threads ao usuário.
    scanf("%d", &thread_count);     // Lê o número de threads.

    m = 5;
    n = 5;
    
    // Aloca memória para a matriz A e lê seus elementos.
    A = (int **) malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        A[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j + 1;
        }
    }

    // Aloca memória para o vetor x e lê seus elementos.
    x = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        x[i] = i + 1;
    }

    // Aloca memória para o vetor y.
    y = (int *) malloc(m * sizeof(int));

    pthread_t *thread_handles;  // Declaração de um array para armazenar identificadores de threads.
    thread_handles = (pthread_t *) malloc(thread_count * sizeof(pthread_t));  // Aloca memória para os identificadores.

    // Cria as threads e as associa à função Pth_mat_vect.
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    // Aguarda o término das threads.
    for (long thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    // Imprime a matriz A.
    printf("\nMatriz A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    // Imprime o vetor x.
    printf("\nMatriz X:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", x[i]);
    }

    // Imprime o vetor y (resultado da multiplicação).
    printf("\nMultiplicação da matriz Y:\n");
    for (int i = 0; i < m; i++) {
    printf("y[%d] = %d\n", i, y[i]); // Adiciona um printf detalhado para cada elemento de y.
    }

    // Libera a memória alocada.
    free(thread_handles);
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}