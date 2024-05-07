# Primeira versão do projeto final

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
`git clone https://github.com/JVT1204/Computacao_Paralela.git && cd Computacao_Paralela && Projeto-V1`

2. Execute a compilação com os seguintes comandos:\
`gcc -o exe serial-v1.c -lmpfr`

    `gcc -o exe paralelo-v1.c -fopenmp -lmpfr`


3. Um arquivo chamado `exe` foi criado na pasta. Rode-o usando:\
    #### Exemplos de execuções
    `./exe 10 1000`

    `./exe 30 300`

## Prints

### CPU info

![alt](/assets/Prints_Projeto-V1/cpu_info_Projeto-V1.png)

### Prints de execução

![alt](/assets/Prints_Projeto-V1/print_serial-v1.png)

![alt](/assets/Prints_Projeto-V1/print_paralelo-v1.png)
