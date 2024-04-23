#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

// Função f(x) que retorna 5.0 mais o seno de x
double f(double x) {
    return 5.0 + sin(x);
}

// Função para calcular a área sob a curva para um dado intervalo [a, b] dividido em n trapézios
double calculate_area(double a, double b, double n) {
    int pos = omp_get_thread_num(); // Obtém o número identificador da thread atual
    int NUM_THREADS = omp_get_num_threads(); // Obtém o número total de threads em execução

    double h = (b - a) / n; // Largura de cada trapézio
    double local_n = n / NUM_THREADS; // Número de trapézios que cada thread deve processar
    double local_a = a + pos * local_n * h; // Ponto inicial do intervalo que a thread atual vai processar
    double local_b = local_a + h * local_n; // Ponto final do intervalo que a thread atual vai processar
    double sum = (f(local_a) + f(local_b)) / 2.0; // Área dos trapézios que a thread irá processar
    
    // Soma as áreas dos trapézios calculadas
    for (int i = 1; i <= local_n - 1; i++) {
        double x = local_a + i * h;
        sum += f(x);
    }
    
    // Multiplica a soma pela largura do trapézio para obter a área total processada pela thread
    sum = sum * h;
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Insira a entrada: %s <a> <b> <n> <NUM_THREADS>\n", argv[0]);
        exit(1);
    }
    // Converte os argumentos fornecidos de strings para números apropriados
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    int n = strtol(argv[3], NULL, 10);
    int NUM_THREADS = strtol(argv[4], NULL, 10);
    double area = 0.0;

// Inicia uma região paralela, especificando o número de threads
#   pragma omp parallel num_threads(NUM_THREADS)
    {
		double sum = 0.0;

        // Calcula a área sob a curva para o intervalo [a, b] com n trapézios
		sum += calculate_area(a, b, n);
        // Atualiza a área total com a área calculada pela thread
		area += sum;
	}

    printf("Área sob a curva: %.14e\n", area);

    return 0;
}