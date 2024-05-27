#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h> // Para aritmética de precisão arbitrária

// Função para calcular fatoriais e armazená-los em um vetor de precisão arbitrária
void fatorial(int n, mpfr_t* vet, int nBits) {
    mpfr_init2(vet[0], nBits); // Primeiro elemento do vetor com precisão especificada
    mpfr_set_d(vet[0], 1.0, MPFR_RNDU); // Primeiro elemento como 1.0

    mpfr_init2(vet[1], nBits); // Segundo elemento do vetor com precisão especificada
    mpfr_set_d(vet[1], 1.0, MPFR_RNDU); // Segundo elemento como 1.0

    for (long int i = 2; i < n; ++i) { // Loop para calcular fatoriais para índices maiores que 1
        mpfr_init2(vet[i], nBits); // Inicializa o elemento do vetor
        mpfr_mul_si(vet[i], vet[i-1], i, MPFR_RNDU); // Calcula o fatorial e armazena no vetor
    }
    return;
}

// Função para calcular a soma das inversas dos fatoriais
void soma(int n, mpfr_t* vet, int nBits, mpfr_t* globalPointer) {
    mpfr_t divisao, um; // Variáveis temporárias para cálculos locais

    mpfr_init2(divisao, nBits); // Inicializa a variável temporária divisao
    mpfr_set_d(divisao, 1.0, MPFR_RNDU); // Define divisao como 1.0

    mpfr_init2(um, nBits); // Inicializa variável temporária um
    mpfr_set_d(um, 1.0, MPFR_RNDU); // Define um como 1.0

    for (int i = 0; i < n; i++) { // Loop para calcular a soma das inversas dos fatoriais
        mpfr_div(divisao, um, vet[i], MPFR_RNDU); // Calcula a inversa do fatorial
        mpfr_add(*globalPointer, *globalPointer, divisao, MPFR_RNDU); // Adiciona na soma global
    }
    // Libera a memória alocada
    mpfr_clear(divisao);
    mpfr_clear(um);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("\nEntre dois argumentos. 1: Iterações. 2: Número de bits\n");
        return 1;
    }
    // Converte os argumentos para inteiros
    int n = strtol(argv[1], NULL, 10);
    int nBits = strtol(argv[2], NULL, 10);

    mpfr_t global; // Declaração da variável para armazenar a soma das inversas dos fatoriais
    mpfr_init2(global, nBits); // Inicializa a variável global com a precisão especificada
    mpfr_set_d(global, 0.0, MPFR_RNDU); // Define a variável global como 0.0

    mpfr_t* vet = (mpfr_t*) malloc(n * sizeof(mpfr_t)); // Aloca memória para o vetor de fatoriais

    fatorial(n, vet, nBits); // Calcula os fatoriais e armazena no vetor

    soma(n, vet, nBits, &global); // Calcula a soma das inversas dos fatoriais

//    printf("Resultado da aproximação de Euler: ");
//    mpfr_out_str(stdout, 10, 0, global, MPFR_RNDU);
//    printf("\n");

    mpfr_clear(global); // Libera a memória alocada para a variável global

    return 0;
}