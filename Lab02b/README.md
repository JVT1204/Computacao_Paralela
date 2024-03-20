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

3. Um arquivo chamado `arquivo` ou `ex` foi criado na pasta. Rode-o usando:\
`./ex`
`./arquivo`

## Prints

### Cpu info - foi possível a utilização de no máximo 6 núcleos

![alt](/assets/cpu_info.png)

# Exercício 1 e 2

### Print tempo de execução serial e Speedup

![alt](/assets/tempo_serial.png)
![alt](/assets/serial.png)

### Print tempo de execução paralela e Speedup

![alt](/assets/tempo_paralelo.png)
![alt](/assets/paralelo.png)

# Exercício 3

Retirando a interação com o usuário dentro do código e automatizando a matriz e threads a serem
utilizadas, ao retirar os "prints", o código não exige tanto do processador deixando a execução
cada vez mais rápida. O código mult_thread não apresenta esses assuntos e tenta ser o mais
paralelo possível para esse caso.