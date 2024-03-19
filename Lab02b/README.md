# Multiplicação matriz-vetor utilizando threads (serial e paralelo)

# Sobre o projeto

Laboratório dedicado a melhorar o paralelismo do Lab02a, mostrando tempo de execução
serial e paralelo do código

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
`git clone https://github.com/JVT1204/Computacao_Paralela.git && cd Computacao_Paralela && cd Lab02b`

2. Execute a compilação com o seguinte comando\
`gcc cod_serial.c -o ex`
`gcc mult_thread.c -o arquivo`

3. Um arquivo chamado `arquivo` foi criado na pasta. Rode-o usando:\
`./ex`
`./arquivo`

## Prints

### Print tempo de execução serial

![alt](/assets/tempo_serial.png)

### Print tempo de execução paralela

![alt](/assets/tempo_paralelo.png)

### Cpu info

![alt](/assets/cpu_info.png)