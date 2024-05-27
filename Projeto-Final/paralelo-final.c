#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h> // Para aritmética de precisão arbitrária
#include <omp.h>

// Função para calcular fatoriais e armazená-los em um vetor de precisão arbitrária
void fatorial(int n, mpfr_t* vet, int nBits) {
    mpfr_init2(vet[0], nBits); // Primeiro elemento do vetor com precisão especificada
    mpfr_set_ui(vet[0], 1.0, MPFR_RNDN); // Primeiro elemento como 1.0 (fatorial de 0)

    // Loop para calcular fatoriais para índices maiores que 0
    for (int i = 1; i <= n; i++) {
        mpfr_init2(vet[i], nBits); // Inicializa o elemento do vetor
        mpfr_mul_ui(vet[i], vet[i-1], i, MPFR_RNDN); // Calcula o fatorial e armazena no vetor
    }
}

// Função para calcular a soma das inversas dos fatoriais
void euler(int n, mpfr_t* vet, int nBits, mpfr_t partialSum) {
    int posicao = omp_get_thread_num(); // Obtém o número da thread atual
    int n_threads = omp_get_num_threads(); // Obtém o número total de threads

    int parcela = n / n_threads; // Quantidade de elementos por thread que irá processar
    int inicio = parcela * posicao; // Índice de início para a thread atual
    int fim; // Índice de fim para a thread atual
    if (posicao == n_threads - 1) { // Se for a última thread, processa até o fim do vetor
        fim = n;
    } else {
        fim = inicio + parcela; // Caso contrário, processa até o índice calculado
    }

    mpfr_t parcial_local, divisao; // Variáveis temporárias para cálculos locais

    mpfr_init2(parcial_local, nBits); // Inicializa variável temporária para soma parcial local
    mpfr_init2(divisao, nBits); // Inicializa variável temporária para a divisão
    mpfr_set_ui(divisao, 0, MPFR_RNDN); // Define a variável de divisão como 0

    // Loop para calcular a soma das inversas dos fatoriais
    for (int i = inicio; i < fim; i++) {
        mpfr_ui_div(parcial_local, 1, vet[i], MPFR_RNDN); // Calcula a inversa do fatorial
        mpfr_add(divisao, divisao, parcial_local, MPFR_RNDN); // Adiciona na soma parcial local
    }

    mpfr_add(partialSum, partialSum, divisao, MPFR_RNDN); // Adiciona a soma parcial local à soma parcial global
    
    // Libera a memória alocada
    mpfr_clear(parcial_local); 
    mpfr_clear(divisao);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("\nEntre três argumentos. 1: Quantidade de threads a serem executadas. 2: Iterações. 3: Número de bits\n");
        return 1;
    }
    // Converte os argumentos para inteiros
    int nThreads = strtol(argv[1], NULL, 10);
    int n = strtol(argv[2], NULL, 10);
    int nBits = strtol(argv[3], NULL, 10);

    mpfr_t global; // Declaração da variável para armazenar a soma das inversas dos fatoriais
    mpfr_init2(global, nBits); // Inicializa a variável global com a precisão especificada
    mpfr_set_ui(global, 0.0, MPFR_RNDN); // Define a variável global como 0.0

    mpfr_t* vet = (mpfr_t*) malloc(n * sizeof(mpfr_t)); // Aloca memória para o vetor de fatoriais
    fatorial(n, vet, nBits); // Calcula os fatoriais e armazena no vetor

    mpfr_t partialSum;
    mpfr_init2(partialSum, nBits); // Inicializa partialSum

    omp_set_num_threads(nThreads); // Define o número de threads a serem usadas
    #pragma omp parallel num_threads(nThreads)
    {
        euler(n, vet, nBits, global); // Chama a função para calcular a soma das inversas dos fatoriais
    }

//    printf("Resultado da aproximação de Euler: ");
    mpfr_out_str(stdout, 10, 0, global, MPFR_RNDN);
    printf("\n");

    // Libera a memória alocada
    mpfr_clear(global);
    mpfr_clear(partialSum);
    free(vet);

    return 0;
}
