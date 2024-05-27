# Última versão do projeto final

# Sobre o projeto

Construir uma solução parelela que obtenha a melhor aproximação para serie de Taylor calculando o valor de E(Euler).

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
`git clone https://github.com/JVT1204/Computacao_Paralela.git && cd Computacao_Paralela && Projeto-Final`

2. Execute a compilação com os seguintes comandos:\
    #### Versão serial: `gcc -o exe serial-final.c -lmpfr`

    #### Versão paralela:`gcc -o exe paralelo-final.c -fopenmp -lmpfr`

    #### Versão paralela com critical:`gcc -o exe critical-final.c -fopenmp -lmpfr`

3. Um arquivo chamado `exe` foi criado na pasta. Rode-o usando:\
    #### Versão serial: `time taskset -c 0 ./exe 1 [Quantidade de iterações] [Número de Bits]`

    #### Versão paralela: `time taskset -c 0 ./exe [Número de Threads] [Quantidade de iterações] [Número de Bits]`

    #### Versão paralela com critical: `time taskset -c 0 ./exe [Número de Threads] [Quantidade de iterações] [Número de Bits]`
    
# Prints

### CPU info

![alt](/assets/Prints_Projeto-Final/cpu_info_Projeto-Final.png)

# Exercício 1

### Tempo de execução serial para 1,2,4,6 e 8 processadores:

![alt](/assets/Prints_Projeto-Final/execucao_final_serial.png)

### Tempo de execução paralela para 1,2,4,6 e 8 processadores:

![alt](/assets/Prints_Projeto-Final/execucao_final_paralelo.png)

### Gráfico contendo os tempos de execução serial e paralelo para 1,2,4,6 e 8 processadores:

![alt](/assets/Prints_Projeto-Final/grafico_execucao_1.png)

# Exercício 2

### Speedup para 1,2,4,6 e 8 processadores das execuções serial e paralela

![alt](/assets/Prints_Projeto-Final/speedup_final_serial.png)

![alt](/assets/Prints_Projeto-Final/speedup_final_paralelo.png)

# Exercício 3

### Introduzindo a diretiva critical em nossa solução, faz com que o programa apenas utilize uma thread para execução do bloco por vez, fazendo com que não surja problemas devido a concorrência.

![alt](/assets/Prints_Projeto-Final/execucao_final_critical.png)

![alt](/assets/Prints_Projeto-Final/speedup_final_critical.png)
