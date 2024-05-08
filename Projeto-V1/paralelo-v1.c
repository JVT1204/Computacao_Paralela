#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h> // Para aritmética de precisão arbitrária
#include <omp.h>

// Função para calcular fatoriais e armazená-los em um vetor de precisão arbitrária
void fatorial(int n, mpfr_t* vet, int nBits) {
    mpfr_init2(vet[0], nBits); // Primeiro elemento do vetor com precisão especificada
    mpfr_set_d(vet[0], 1.0, MPFR_RNDU); // Primeiro elemento como 1.0

    mpfr_init2(vet[1], nBits); // Segundo elemento do vetor com precisão especificada
    mpfr_set_d(vet[1], 1.0, MPFR_RNDU); // Segundo elemento como 1.0

    // Loop para calcular fatoriais para índices maiores que 1
    for (long int i = 2; i < n; ++i) {
        mpfr_init2(vet[i], nBits); // Inicializa o elemento do vetor
        mpfr_mul_si(vet[i], vet[i-1], i, MPFR_RNDU); // Calcula o fatorial e armazena no vetor
    }
    return;
}

// Função para calcular a soma das inversas dos fatoriais
void soma(int n, mpfr_t* vet, int nBits, mpfr_t* partialSum) {
    int posicao = omp_get_thread_num(); // Obtém o número da thread atual
    int n_threads = omp_get_num_threads(); // Obtém o número total de threads

    int parcela = n / n_threads; // Quantidade de elementos por thread
    int inicio = parcela * posicao; // Índice de início para a thread atual
    int fim; // Índice de fim para a thread atual
    if (posicao == n_threads - 1) {
        fim = n;
    } else {
        fim = inicio + parcela;
    }

    mpfr_t parcial_local, divisao, um; // Variáveis temporárias para cálculos locais

    mpfr_init2(parcial_local, nBits); // Inicializa variável temporária para soma parcial local
    mpfr_set_d(parcial_local, 0.0, MPFR_RNDU); // Define soma parcial local como 0.0

    mpfr_init2(divisao, nBits); // Inicializa variável temporária divisão
    mpfr_set_d(divisao, 1.0, MPFR_RNDU); // Define divisão como 1.0

    mpfr_init2(um, nBits); // Inicializa variável temporária um
    mpfr_set_d(um, 1.0, MPFR_RNDU); // Define um como 1.0

    // Loop para calcular a soma das inversas dos fatoriais
    for (int i = inicio; i < fim; i++) {
        mpfr_div(divisao, um, vet[i], MPFR_RNDU); // Calcula a inversa do fatorial
        mpfr_add(parcial_local, parcial_local, divisao, MPFR_RNDU); // Adiciona na soma parcial local
    }

    mpfr_set(*partialSum, parcial_local, MPFR_RNDU);
    
    // Libera a memória alocada
    mpfr_clear(divisao); 
    mpfr_clear(parcial_local);
    mpfr_clear(um);
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
    mpfr_set_d(global, 0.0, MPFR_RNDU); // Define a variável global como 0.0

    mpfr_t* vet = (mpfr_t*) malloc(n * sizeof(mpfr_t)); // Aloca memória para o vetor de fatoriais

    fatorial(n, vet, nBits); // Calcula os fatoriais e armazena no vetor

    mpfr_t partialSum;
    mpfr_init2(partialSum, nBits); // Inicializa partialSum

    #pragma omp parallel num_threads(nThreads)
    {
        soma(n, vet, nBits, &partialSum); // Chama a função para calcular a soma das inversas dos fatoriais
        mpfr_add(global, global, partialSum, MPFR_RNDU);
    }

    printf("Resultado da aproximação de Euler: ");
    mpfr_out_str(stdout, 10, 0, global, MPFR_RNDU);
    printf("\n");

    // Libera a memória alocada
    mpfr_clear(global);
    mpfr_clear(partialSum);

    return 0;
}
