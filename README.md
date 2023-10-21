# Trabalho 1 de Software Básico (CIC0104 - SOFTWARE BASICO - T02 (2023.2 - 46M34)
Prof: Bruno Luiggi Macchiavello Espinoza

Antonio Vinicius de Moura Rodrigues, 190084502

Isaque Augusto da Silva Santos, 190089245

# Instruções para compilação/execução:
OBS: o trabalho foi feito no windows usando o codeblocks utilizando o compilador g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0 pelo MinGW.
Utilizamos C++ 17.

# MONTADOR

## CODE::BLOCKS 20.03
1. Instalar o codeblocks-20.03mingw-setup.exe (https://www.codeblocks.org/downloads/binaries/#imagesoswindows48pnglogo-microsoft-windows), sem mudar nada no processo da instalação, apenas clicando em "Next".
2. Ao abrir o codeblocks pela primeira vez, será detectado o compilador GNU GCC. Selecionar "OK".
3. Para evitar mensagem de erro de versão no compilador, adicione a flag e "-std=c++17" indo em Settings > Compiler > Compiler Flags, conforme a imagem a seguir:

![alt text](https://github.com/seraphritt/Trab_1_SB/blob/main/assets/Compiler_settings_2.png?raw=true)

4. Após isso, deve-se adicionar o nome do arquivo que será compilado. Isso pode ser feito em: Project > Set Program Arguments' . Selecione o modo em que está sendo feita a compilação (Debug ou Release) e escreva ``nome_do_arquivo.extensao`` no campo Program Arguments. A seguir temos duas imagens para melhor exemplificar.

![alt text](https://github.com/seraphritt/Trab_1_SB/blob/main/assets/Compiler_settings_2.png?raw=true)

![alt text](https://github.com/seraphritt/Trab_1_SB/blob/main/assets/Compiler_settings_2.png?raw=true)

5. Clique no ícone "Build and Run", comforme imagem.

![alt text](https://github.com/seraphritt/Trab_1_SB/blob/main/assets/Compiler_settings_2.png?raw=true)

## TERMINAL WINDOWS
1. Verificar se o g++ está instalado, com o comando ``g++ --version``, atentando-se à versão do compilador.
2. Para compilar, o comando é: ``g++ -std=c++17 main.cpp -o main``.
3. Para executar, digite: ``.\montador nome_do_arquivo.extensao``.
