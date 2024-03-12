#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // Biblioteca suporte a threads

#define m 2 // Número de linhas da matriz
#define n 2 // Número de colunas da matriz
#define quantidade_threads 1 // Define o número de threads a serem criadas

double A[m][n]; // Matriz A
double x[n];    // Vetor x
double y[m];    // Vetor y

// Função executada por cada thread para multiplicar a matriz pelo vetor
void *multiplica_matriz_vetor(void* rank) {
    long meu_rank = (long) rank; // Identificador da thread
    int i, j;
    int linhas_locais = m / quantidade_threads; // Calcula o número de linhas que cada thread será responsável
    int minha_primeira_linha = meu_rank * linhas_locais; // Calcula a primeira linha atribuída à thread
    int minha_ultima_linha = (meu_rank + 1) * linhas_locais - 1; // Calcula a última linha atribuída à thread

    // Loop sobre as linhas atribuídas à thread
    for (i = minha_primeira_linha; i <= minha_ultima_linha; i++) {
        y[i] = 0.0; // Inicializa a entrada do vetor y para esta linha
        // Loop sobre as colunas da matriz
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j]; // Multiplica e acumula os valores da matriz e do vetor
            printf("Thread %ld: y[%d] += %lf * %lf\n", meu_rank, i, A[i][j], x[j]);
        }
    }

    return NULL;
}

int main() {
    pthread_t threads[quantidade_threads]; // Declaração do array de threads
    long i;

    // Preenche a matriz A e o vetor x com valores de exemplo
    for (i = 0; i < m; i++) {
        for (long j = 0; j < n; j++) {
            A[i][j] = 4.0 * j; // Valor de exemplo para a matriz A
        }
        x[i] = 3.0; // Valor de exemplo para o Vetor x
    }

    // Cria threads e executa a função multiplica_matriz_vetor
    for (i = 0; i < quantidade_threads; i++) {
        pthread_create(&threads[i], NULL, multiplica_matriz_vetor, (void*)i);
    }

    // Aguarda até que todas as threads terminem
    for (i = 0; i < quantidade_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprime o vetor y
    printf("\n");
    for (i = 0; i < m; i++) {
        printf("y[%ld] = %lf\n", i, y[i]);

    return 0;
    }
}