#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double f(double x) {
    return 5.0 + sin(x);
}

double calculate_area(double a, double b, double n) {
    int pos = omp_get_thread_num();
    int NUM_THREADS = omp_get_num_threads();

    double h = (b - a) / n;
    double local_n = n / NUM_THREADS;
    double local_a = a + pos * local_n * h;
    double local_b = local_a + h * local_n;
    double sum = (f(local_a) + f(local_b)) / 2.0;
    
    for (int i = 1; i <= local_n - 1; i++) {
        double x = local_a + i * h;
        sum += f(x);
    }
    
    sum = sum * h;
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Insira a entrada: %s <a> <b> <n> <NUM_THREADS>\n", argv[0]);
        exit(1);
    }
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    int n = strtol(argv[3], NULL, 10);
    int NUM_THREADS = strtol(argv[4], NULL, 10);
    double area = 0.0;

#   pragma omp parallel num_threads(NUM_THREADS)
    {
		double sum = 0.0;
		sum += calculate_area(a, b, n);

#   pragma omp critical
            {
                area += sum;
            }
	}

    printf("Área sob a curva: %.14e\n", area);

    return 0;
}