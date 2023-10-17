# Trabalho 1 de Software Básico (CIC0104 - SOFTWARE BASICO - T02 (2023.2 - 46M34)
Prof: Bruno Luiggi Macchiavello Espinoza

Antonio Vinicius de Moura Rodrigues, 190084502

Isaque Augusto da Silva Santos, 190089245

# Instruções para compilação/execução:
OBS: o trabalho foi feito no windows usando o codeblocks utilizando o compilador g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0 pelo MinGW.
Utilizamos C++ 17.

# CODE::BLOCKS 20.03
1. Instalar o codeblocks-20.03mingw-setup.exe (https://www.codeblocks.org/downloads/binaries/#imagesoswindows48pnglogo-microsoft-windows), sem mudar nada no processo da instalação, apenas clicando em "Next".
2. Ao abrir o codeblocks pela primeira vez, será detectado o compilador GNU GCC. Selecionar "OK".
3. Para evitar mensagem de erro de versão no compilador, adicione a flag e "-std=c++17" indo em Settings > Compiler > Compiler Flags, conforme a imagem a seguir:

![Compiler Settings](https://drive.google.com/uc?export=view&id=1OBPT2n-3AhccdfLatkHrK876BUOv0PAv](https://doc-10-2s-docs.googleusercontent.com/docs/securesc/19jmq96dk8rf32n8aqba1avdg6o97buj/6hs6upa4pme425iavn4ksdsfnc63d0oh/1697547075000/08890417141497452303/08890417141497452303/1OBPT2n-3AhccdfLatkHrK876BUOv0PAv?e=view&ax=AI0foUozgfKsSqj4A7f8wHC-Dz3EEEFUUQw_hL7gjBinR0OTdIIddIhZg3qDofH0nn1jDWkxvtWNDsNZViXjP3eDNDwWHfpi2Ub5rcBMiKlIJKwX-SVvRe4cvd6EP8qhTX8amW8Epr-mhT2BpnKLaxBSLZFkdPNffSLPBCttJKZ0tEeoJEAApleObVWoh_9jFgxd4nylTLiyJJTikdwpkQVgQcZTb3iN9Pz3ql0elW8_9t3xWjoM46L9ZN0dy5BPSNsmYiWTlto1S_XHdWMRP5Na3iEEsr4ecSM876cl3HBFeCj5o-YQxlyNuRUclEqENsbdY5RLFeZOXPZpUW1Nn1uTUDl8dAmhtJmk0mQkfEOFyDyR7guiDDEQ34wxYg4qdRzzwgX13BtoGekGc8S86XXnGm2BAxcEvMo8n5h3KLCVvffbiTBWT-d875xeumPfI62BpEhz-RMjzXJVKKSm0arNgq7ePGH6GW5x7BoOajgfvWgzP7lwciphtJFYAkG-IKZMhOsxnZzRboG4e154RvJCNT1PZ5V4i5IX_Pp3aSx4Hwy4Dfo--iwFu8_zrsL-lA4la2oKuGwQ1Oa-n5AVsBbHO0JBDWrenqrPbN4ul5wluK8dyjhSdwsgZLbdOUNJv9yXP7kI8l7om29le6CMsA0MBhq3GN8jFg7NwvG6KflqGBc10ypVvunWcln7-fYfDP6DNkXOEGmjkZ8x-3XVFKOgkieKvId3jFoyumbc3W7t6SQQH5XHp_CoukFDBV8YhPKtzq87wT3hSfzGZA1iSfta1DJE_E-5l0-5BTcka7YUsDo4K9hjivvBS6YQ82tPe846siKeZRAAxohhwdH3Gi_SPWXN5ljM7iqBdAmee_R8v_R3pDcvfiqOO7AGu2tcI5MDNg&uuid=aa19f245-7649-401c-a09e-01dc5daacd28&authuser=0&nonce=e8bcrkmk2kju2&user=08890417141497452303&hash=cih2isdf6n78sfi40okpfsvnuqi3vdlr)https://doc-10-2s-docs.googleusercontent.com/docs/securesc/19jmq96dk8rf32n8aqba1avdg6o97buj/6hs6upa4pme425iavn4ksdsfnc63d0oh/1697547075000/08890417141497452303/08890417141497452303/1OBPT2n-3AhccdfLatkHrK876BUOv0PAv?e=view&ax=AI0foUozgfKsSqj4A7f8wHC-Dz3EEEFUUQw_hL7gjBinR0OTdIIddIhZg3qDofH0nn1jDWkxvtWNDsNZViXjP3eDNDwWHfpi2Ub5rcBMiKlIJKwX-SVvRe4cvd6EP8qhTX8amW8Epr-mhT2BpnKLaxBSLZFkdPNffSLPBCttJKZ0tEeoJEAApleObVWoh_9jFgxd4nylTLiyJJTikdwpkQVgQcZTb3iN9Pz3ql0elW8_9t3xWjoM46L9ZN0dy5BPSNsmYiWTlto1S_XHdWMRP5Na3iEEsr4ecSM876cl3HBFeCj5o-YQxlyNuRUclEqENsbdY5RLFeZOXPZpUW1Nn1uTUDl8dAmhtJmk0mQkfEOFyDyR7guiDDEQ34wxYg4qdRzzwgX13BtoGekGc8S86XXnGm2BAxcEvMo8n5h3KLCVvffbiTBWT-d875xeumPfI62BpEhz-RMjzXJVKKSm0arNgq7ePGH6GW5x7BoOajgfvWgzP7lwciphtJFYAkG-IKZMhOsxnZzRboG4e154RvJCNT1PZ5V4i5IX_Pp3aSx4Hwy4Dfo--iwFu8_zrsL-lA4la2oKuGwQ1Oa-n5AVsBbHO0JBDWrenqrPbN4ul5wluK8dyjhSdwsgZLbdOUNJv9yXP7kI8l7om29le6CMsA0MBhq3GN8jFg7NwvG6KflqGBc10ypVvunWcln7-fYfDP6DNkXOEGmjkZ8x-3XVFKOgkieKvId3jFoyumbc3W7t6SQQH5XHp_CoukFDBV8YhPKtzq87wT3hSfzGZA1iSfta1DJE_E-5l0-5BTcka7YUsDo4K9hjivvBS6YQ82tPe846siKeZRAAxohhwdH3Gi_SPWXN5ljM7iqBdAmee_R8v_R3pDcvfiqOO7AGu2tcI5MDNg&uuid=aa19f245-7649-401c-a09e-01dc5daacd28&authuser=0&nonce=e8bcrkmk2kju2&user=08890417141497452303&hash=cih2isdf6n78sfi40okpfsvnuqi3vdlr)
# TERMINAL WINDOWS
1. Verificar se o g++ está instalado, com o comando ``g++ --version``, atentando-se à versão do compilador.
2. Para compilar, o comando é: ``g++ -std=c++17 main.cpp -o main``.
3. Para executar, digite: ``.\main``.
