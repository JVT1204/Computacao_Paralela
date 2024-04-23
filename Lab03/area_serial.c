#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    return 5.0 + sin(x);
}

double calculate_area(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    
    for (int i = 1; i < n - 1; i++) {
        double x = a + i * h;
        sum += f(x);
    }
    
    return h * sum;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Insira a entrada: %s <a> <b> <n>\n", argv[0]);
        exit(1);
    }
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    double n = strtol(argv[3], NULL, 10);

    double area = calculate_area(a, b, n);
    printf("Área sob a curva: %.14e\n", area);

    return 0;
}