# Solução paralela utilizando OpenMP

# Sobre o projeto

Laboratório dedicado construir uma solução paralela utilizando OpenMP, calculando 
a área sobre sob a curva através da soma de trapézios da figura abaixo:

![alt](/assets/figura_enunciado_Lab03.png)

O cálculo dos diferentes trapézios é dividido entre as threads para que no final a área
total seja somada, descobrindo assim o resultado da integral

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

2. Execute a compilação com os seguintes comandos:\
`gcc -o exe area_serial.c -lm`

    `gcc -o exe area_paralelo.c -fopenmp -lm`

    `gcc -o exe area_critical.c -fopenmp -lm`

3. Um arquivo chamado `exe` foi criado na pasta. Rode-o usando:\
`./exe a b n`

   `./exe a b n NUM_THREADS`

   `./exe a b n NUM_THREADS`

   #### Exemplo: ./exe 0 10 1000000000

4. Explicação sobre o que colocar no lugar dos argumentos acima:\
` a: Variável "a" do código`
` b: Variável "b" do código`
` n: Quantidade de trapézios que irão ser calculados`
` NUM_THREADS: Quantidade de threads a serem utilizadas`

## Exercícios

#### O código `area_paralelo.c` apresenta uma versão paralela do cálculo da integral sem a utilização do prag critical
#### O código `area_serial.c` apresenta uma versão serial do cálculo da integral
#### O código `area_critical.c` apresenta uma versão paralela do cálculo da integral com a utilização do prag critical
#### Pragma omp critical especifica uma seção do código em que uma thread por vez pode entrar. Se a seção crítica já estiver sendo executada por outra thread, a thread atual aguardará até que a outra thread saia da seção crítica antes de entrar. Isso garante que o código dentro da seção crítica seja executado por apenas uma thread de cada vez, mantendo a integridade dos dados compartilhados.

### Cpu info

![alt](/assets/cpu_info_Lab03.png)

# Exercício 1 e 2

### Print tempo de execução serial e Speedup

### Print tempo de execução paralela e Speedup

# Exercício 3