# **Trabalho 1 de Software Básico CIC0104 - SOFTWARE BASICO - T02 (2023.2 - 46M34)**

## **Integrantes da Equipe**
- Antônio Vinicius de Moura Rodrigues (190084502)
- Isaque Augusto da Silva Santos (190089245)

## **Descrição**
Este projeto é uma implementação de um tradutor em C++ que utiliza o algoritmo de 2 passagens para uma linguagem de montagem simples. O tradutor desempenha o papel de um Assembler para a linguagem hipotética abaixo:

| Opcode Simbólico | Opcode Numérico | Tamanho (palavras) | Ação                |
|------------------|-----------------|--------------------|---------------------|
| ADD              | 01              | 2                  | ACC + mem(OP)       |
| SUB              | 02              | 2                  | ACC - mem(OP)       |
| MUL              | 03              | 2                  | ACC * mem(OP)       |
| DIV              | 04              | 2                  | ACC / mem(OP)       |
| JMP              | 05              | 1                  | PC = OP             |
| JMPN             | 06              | 1                  | Se ACC < 0, PC = OP |
| JMPP             | 07              | 1                  | Se ACC > 0, PC = OP |
| JMPZ             | 08              | 1                  | Se ACC = 0, PC = OP |
| COPY             | 09              | 2                  | mem(OP2) = mem(OP1) |
| LOAD             | 10              | 2                  | ACC = mem(OP)       |
| STORE            | 11              | 2                  | mem(OP) = ACC       |
| INPUT            | 12              | 2                  | mem(OP) = entrada   |
| OUTPUT           | 13              | 2                  | saída = mem(OP)     |
| STOP             | 14              | 1                  | Suspende a execução |


## **Instruções para compilação/execução**

### Ambiente de Desenvolvimento

- IDE: ``Code::Blocks``
- Compilador: ``g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0 pelo MinGW``
- Versão do C++: ``17``

### Configuração do Code::Blocks 20.03

1. Instalar o [codeblocks-20.03mingw-setup.exe](https://www.codeblocks.org/downloads/binaries/#imagesoswindows48pnglogo-microsoft-windows), sem mudar nada no processo da instalação, apenas clicando em "Next".
2. Ao abrir o codeblocks pela primeira vez, será detectado o compilador GNU GCC. Selecionar "OK".
3. Para evitar mensagem de erro de versão no compilador, adicione a flag e "-std=c++17" indo em Settings > Compiler > Compiler Flags, conforme a imagem a seguir:

![alt text](https://github.com/seraphritt/Trab_1_SB/blob/main/assets/images/Compiler_settings_2.png?raw=true)

4. Após isso, deve-se adicionar o nome do arquivo que será compilado. Isso pode ser feito em: Project > Set Program Arguments' . Selecione o modo em que está sendo feita a compilação (Debug ou Release) e escreva ``nome_do_arquivo.extensao`` no campo Program Arguments.

5. Clique no ícone "Build and Run".

### Compilação/execução do **Montador** via Terminal

1. Verificar se o g++ está instalado, com o comando ``g++ --version``, atentando-se à versão do compilador.
2. Para compilar, o comando é: ``g++ -std=c++17 montador.cpp -o montador``.
3. Para executar, digite: ``.\montador <path>\nome_do_arquivo.extensao``.

### Compilação/execução do **Simulador** via Terminal

1. Verificar se o g++ está instalado, com o comando ``g++ --version``, atentando-se à versão do compilador.
2. Para compilar, o comando é: ``g++ -std=c++17 simulador.cpp -o simulador``.
3. Para executar, digite: ``.\simulador <path>\codigo_gerado.obj``.

Obs: Para executar no terminal do linux, basta usar os mesmos comandos substituindo as barras invertidas (``\``) por barras normais (``/``).
