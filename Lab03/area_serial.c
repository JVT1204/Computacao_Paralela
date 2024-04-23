#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função f(x) que retorna 5.0 mais o seno de x
double f(double x) {
    return 5.0 + sin(x);
}

// Função para calcular a área sob a curva usando a regra do trapézio
double calculate_area(double a, double b, int n) {
    double h = (b - a) / n; // Calcula a largura de cada trapézio
    double sum = (f(a) + f(b)) / 2.0; // Calcula a média das alturas nos pontos inicial e final do intervalo
    
    // Soma as alturas dos pontos intermediários multiplicadas pela largura do trapézio
    // Começa em i = 1 para evitar recalcular os pontos inicial e final
    // Termina em n - 1 para evitar calcular o ponto final duas vezes
    for (int i = 1; i < n - 1; i++) {
        double x = a + i * h; // Calcula a coordenada x do ponto intermediário
        sum += f(x); // Adiciona a altura do ponto intermediário à soma
    }
    // Multiplica a soma pela largura do trapézio para obter a área total
    return h * sum;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Insira a entrada: %s <a> <b> <n>\n", argv[0]);
        exit(1);
    }
    // Converte os argumentos fornecidos de strings para números apropriados
    double a = strtod(argv[1], NULL);
    double b = strtod(argv[2], NULL);
    int n = strtol(argv[3], NULL, 10);
    double area = calculate_area(a, b, n); // Calcula a área sob a curva para o intervalo [a, b] com n trapézios
    printf("Área sob a curva: %.14e\n", area);

    return 0;
}
