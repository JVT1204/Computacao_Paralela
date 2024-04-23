# Solução paralela utilizando OpenMP

# Sobre o projeto

Laboratório dedicado construir uma solução paralela utilizando OpenMP, calculando 
a área sobre sob a curva através da soma de trapézios da figura abaixo:

![alt](/assets/Prints_Lab03/figura_enunciado_Lab03.png)

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

![alt](/assets/Prints_Lab03/cpu_info_Lab03.png)

# Exercício 1

### Print execução serial:

#### O tempo de execução serial não apresentou mudanças significativas durante o acréscimo dos núcleos de processamento

![alt](/assets/Prints_Lab03/print_area_serial.png)

### Print execução paralelo

#### Para o tempo de execução paralelo, foi possível perceber uma mudança importante durante o acréscimo dos núcleos de processamento, o que fez com que o tempo total da execução fosse diminuído cada vez mais

![alt](/assets/Prints_Lab03/print_area_paralelo.png)

### Print tempo de execução serial x paralelo

![alt](/assets/Prints_Lab03/areaparalelo_x_areaserial.png)

# Exercício 2

#### Para a versão serial, o speedup não houve mudança, sempre ficando na margem de 1, ou seja, não houve melhora de desempenho como acréscimo dos núcleos de processamento

![alt](/assets/Prints_Lab03/speedup_area_serial.png)

#### Já para a versão paralela, houve aumento de performance significativa como mostra o gráfico a seguir

![alt](/assets/Prints_Lab03/speedup_area_paralelo.png)

# Exercício 3

#### Com a introdução da diretiva critical no programa, somente uma das threads poderá modificar a variável de soma calculadas pelas threads. Mesmo que o speedup tenha a melhora de desempenho, graças ao fator critical que só permite uma thread por vez no uso da variável de soma, faz com que esse código não se distancie tanto do tempo de execução da verssão paralela

![alt](/assets/Prints_Lab03/print_area_critical.png)

![alt](/assets/Prints_Lab03/speedup_area_critical.png)
