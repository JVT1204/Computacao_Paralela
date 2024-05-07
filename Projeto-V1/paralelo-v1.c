#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <mpfr.h>

void fatorial(int n, mpfr_t* vet, int nBits) {
    mpfr_init2(vet[0], nBits);
    mpfr_set_d(vet[0], 1.0, MPFR_RNDU);

    mpfr_init2(vet[1], nBits);
    mpfr_set_d(vet[1], 1.0, MPFR_RNDU);

    for (long int i = 2; i < n; ++i) {
        mpfr_init2(vet[i], nBits);
        mpfr_mul_si(vet[i], vet[i-1], i, MPFR_RNDU);
    }
    return;
}

void soma(int n, mpfr_t* vet, int nBits, mpfr_t* globalPointer) {
    int posicao = omp_get_thread_num();
    int n_threads = omp_get_num_threads();

    int parcela = n / n_threads;
    int inicio = parcela * posicao;
    int fim = (posicao == n_threads - 1) ? n : inicio + parcela;

    mpfr_t parcial_local, divisao, um;

    mpfr_init2(parcial_local, nBits);
    mpfr_set_d(parcial_local, 0.0, MPFR_RNDU);

    mpfr_init2(divisao, nBits);
    mpfr_set_d(divisao, 1.0, MPFR_RNDU);

    mpfr_init2(um, nBits);
    mpfr_set_d(um, 1.0, MPFR_RNDU);

    for (int i = inicio; i < fim; i++) {
        mpfr_div(divisao, um, vet[i], MPFR_RNDU);
        mpfr_add(parcial_local, parcial_local, divisao, MPFR_RNDU);
    }

    #pragma omp critical
    {
        mpfr_add(*globalPointer, *globalPointer, parcial_local, MPFR_RNDU);
    }

    mpfr_clear(divisao);
    mpfr_clear(parcial_local);
    mpfr_clear(um);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("\nEntre três argumentos. 1: Quantidade de threads a serem executadas. 2: Iterações. 3: Número de bits\n");
        return 1;
    }

    int nThreads = strtol(argv[1], NULL, 10);
    int n = strtol(argv[2], NULL, 10);
    int nBits = strtol(argv[3], NULL, 10);

    mpfr_t global;
    mpfr_init2(global, nBits);
    mpfr_set_d(global, 0.0, MPFR_RNDU);

    mpfr_t* vet = (mpfr_t*) malloc(n * sizeof(mpfr_t));

    fatorial(n, vet, nBits);

    #pragma omp parallel num_threads(nThreads)
    {
        soma(n, vet, nBits, &global);
    }

    printf("Resultado da aproximação de Euler: ");
    mpfr_out_str(stdout, 10, 0, global, MPFR_RNDU);
    printf("\n");

    mpfr_clear(global);

    return 0;
}