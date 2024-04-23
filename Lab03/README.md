# Solução paralela utilizando OpenMP

# Sobre o projeto

Laboratório dedicado construir uma solução paralela utilizando OpenMP, calculando 
a área sobre sob a curva através da soma de trapézios da figura abaixo:

![alt](/assets/figura_enunciado_Lab03.png)

# Integrantes

- Bruno Lauand Ferrão - 10401081
- Fernando Pegoraro Bilia - 10402097
- João Vitor Tortorello - 10402674

# Iniciando

## Pré Requisitos

- git
- gcc
- terminal AWS

## Instalação

1. Clone o repositório com o seguinte comando:\
`git clone https://github.com/JVT1204/Computacao_Paralela.git && cd Computacao_Paralela && cd Lab03`

2. Execute a compilação com o seguinte comando\
`gcc -o exe area_serial.c -lm`
`gcc -o exe area_paralelo.c -fopenmp -lm`
`gcc -o exe area_critical.c -fopenmp -lm`

3. Um arquivo chamado `exe` foi criado na pasta. Rode-o usando:\
`./exe a b n`
`./exe a b n NUM_THREADS`
`./exe a b n NUM_THREADS`

## Prints

### Cpu info

# Exercício 1 e 2

### Print tempo de execução serial e Speedup

### Print tempo de execução paralela e Speedup

# Exercício 3