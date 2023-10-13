# PSEUDOCODIGO SECOND_PASS

```
Contador_posição = 0
Contador_linha = 1
Enquanto arquivo fonte não chegou ao fim, faça:
Obtém uma linha do fonte
    Separa os elementos da linha: rótulo,operação,operandos, comentários
    Ignora o rótulo e os comentários
    Para cada operando que é símbolo
    Procura operando na TS
        Se não achou: Erro, símbolo indefinido
    Procura operação na tabela de instruções
    Se achou:
        contador_posição = contador_posição + tamanho da instrução
        Se número e tipo dos operandos está correto então
            gera código objeto conforme formato da instrução
        Senão: Erro, operando inválido
    Senão:
        Procura operação na tabela de diretivas
        Se achou:
            Chama subrotina que executa a diretiva
            Contador_posição = valor retornado pela subrotina
        Senão: Erro, operação não identificada
    Contador_linha = contador_linha + 1
```