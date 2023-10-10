# Trabalho 1 de Software Básico (CIC0104 - SOFTWARE BASICO - T02 (2023.2 - 46M34)
Prof: Bruno Luiggi Macchiavello Espinoza

Antonio Vinicius de Moura Rodrigues, 190084502

Isaque Augusto da Silva Santos, 190089245

# Instruções para compilação/execução:
OBS: o trabalho foi feito no windows usando o codeblocks utilizando o compilador g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0 pelo MinGW.
Utilizamos C++ 17.
CODE::BLOCKS 20.03
1. Instalar o codeblocks-20.03mingw-setup.exe (https://www.codeblocks.org/downloads/binaries/#imagesoswindows48pnglogo-microsoft-windows), sem mudar nada no processo da instalação, apenas clicando em "Next".
2. Ao abrir o codeblocks pela primeira vez, será detectado o compilador GNU GCC. Selecionar "OK".
3. Para evitar mensagem de erro de versão no compilador, adicione as flags "-std=c17" e "-std=c++17" indo em Settings > Compiler > Compiler Flags, conforme a imagem a seguir:

![Compiler Settings](https://drive.google.com/uc?export=view&id=1droauMWWHUefOvngrm2W97Klhb5NmcDD)

TERMINAL WINDOWS
1. Verificar se o g++ está instalado, com o comando ``g++ --version``, atentando-se à versão do compilador.
2. Para compilar, o comando é: ``g++ -std=c++17 main.cpp -o main``.
3. Para executar, digite: ``./main``.
