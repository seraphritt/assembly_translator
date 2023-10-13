#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

//version: g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
//using C++17
using namespace std;
vector<string> instr_and_operandos;
typedef vector<tuple<string, int>> table_type;
typedef vector<tuple<string, int, string>> instr_table_type;
table_type symbols_table;
vector<string> dire_table = {"SPACE", "CONST", "SECAO DATA", "SECAO TEXT"}; // diretivas
// instru��o, num maximo de argumentos, OP code
vector<string> conteudo; // vetor que guarda o que ser� escrito no arquivo objeto
instr_table_type instr_table = {make_tuple("ADD", 2, "01"), make_tuple("SUB", 2, "02"), make_tuple("MUL", 2, "03"), make_tuple("DIV", 2, "04"), make_tuple("JMP", 2, "05"), make_tuple("JMPN", 2, "06"), make_tuple("JMPP", 2, "07"), make_tuple("JMPZ", 2, "08"), make_tuple("COPY", 3, "09"), make_tuple("LOAD", 2, "10"), make_tuple("STORE", 2, "11"), make_tuple("INPUT", 2, "12"), make_tuple("OUTPUT", 2, "13"), make_tuple("STOP", 1, "14")};
int contador_linha = 1;
int contador_posicao = 0;


bool findInIntrTable(string instr, int posit){
    if(instr != "\0"){
        istringstream a(instr); // tipo para usar o getline() e separar em espa�os
        string s;
        cout << "instr" << instr << endl;
        while (getline( a, s, ' ') ) {
            if((s != ""))
                instr_and_operandos.push_back(s);
        }

        for(auto [X, Y, Z]: instr_table){
            if(X == instr_and_operandos[0]){
                contador_posicao = contador_posicao + Y;
                return true;
            }
        }
    }
    // retorna falso e ir� procurar na tabela de diretivas
    return false;
}
bool findInDireTable(string dire){
    string dire1 = "";
    string dire2 = "";
    if((dire != "SECAO DATA") & (dire != "SECAO TEXT")){
        istringstream iss(dire);
        string s;
        while (getline(iss, s, ' ')) {
            if((s != " ") & (s != "\t") & (dire1 == "")){
                dire1 = s;
            }else if((s != " ") & (s != "\t") & (dire1 != "")){
                dire2 = s;
            }
        }
    }
    for(auto X: dire_table){
        if(dire1 != ""){
            if(X == dire1){
                if(X == "CONST"){
                    contador_posicao += 1;
                }else if((X == "SPACE") & (dire2 == "")){
                    contador_posicao += 1;
                }
                else if((X == "SPACE") & (dire2 != "")){
                    contador_posicao += stoi(dire2);
                }
                return true;    // se achar o token na tabela de diretivas, retorna true
            }
        }else if(X == dire){
            return true;    // se achar o token na tabela de diretivas, retorna true
        }
    }
    return false;   // retorna falso
}
bool findInSymbolsTable(string label, int posit){
    for(auto [X, Y]: symbols_table ){
        if(X == label){
            return true;
        }
    }
    symbols_table.push_back(make_tuple(label, posit));
    return false;
}

void writeFile(){
    int numero;
    string nome;
    ofstream outFile; //
    outFile.open("sa�da.txt", ios::out); // abre o arquivo para escrita
    if (! outFile)
    {
        cout << "Arquivo saida.txt nao pode ser aberto" << endl;
        abort();
    }
    cout << "Entre com o numero e nome do funcion�rio\n" << "Fim de arquivo (Ctrl-Z) termina a entrada de dados\n\n? ";
    while(cin >> numero >> nome)
    {
        outFile << numero << " " << nome << "\n";
        cout << "?";
    }
    outFile.close(); // se o programador omitir a chamada ao m�todo close
}
void to_token(string linha){
    string token;
    int comment = 0;
    int index_comeco = 0;
    int rotulo_fim  = 0;
    bool label = false;
    bool entrou = false;
    for(int i = 0; i < linha.size(); i++){ // se tiver label, acha e coloca na tabela de s�mbolos
        if((linha[i] != ' ') & (linha[i] != '\t') & (!entrou)){
            index_comeco = i;
            entrou = true;
            continue;
        }
        if(linha[i] == ':'){ // se achar 2 pontos pega tudo que vem antes dos dois pontos e isso � o r�tulo/label
            label = true; // se tiver essa flag usa-se o rotulo_fim, ou seja, a ultima posi�ao do r�tulo
            token = linha.substr(index_comeco, i - index_comeco);
            int j = i + 1;
            while(j<linha.size()){
                if((linha[j] != ' ') & (linha[j] != '\t')){
                    rotulo_fim = j;
                    break;
                }
                j++;
            }
            if(findInSymbolsTable(token, contador_posicao)){
               cout << "ERRO SEMANTICO: SIMBOLO REDEFINIDO" << endl;
               } // se achou na tabela de s�mobolos tem erro

        }
        if(linha[i] == ';'){ // anota a posicao onde est� o comentario, para que o que vier depois seja ignorado
            comment = i;
        }
    }
    int offset = 0;
    if(comment != 0){
        offset = linha.size() - comment;
    }
    if(label){
        token = linha.substr(rotulo_fim, linha.size() - offset);
    }else{
        token = linha.substr(index_comeco, linha.size() - offset);
    }
    if(!findInIntrTable(token, contador_posicao)){
        if(!findInDireTable(token)){
            cout << "ERRO SINTATICO: OPERACAO NAO RECONHECIDA" << endl;
        }
    }

}
void readFile(string file_name){
    vector<string> rotulo;
    vector<string> operacao;
    vector<string> operandos;
    // comentarios ser�o ignorados
    string token;
    ifstream inFile; // inFile � o arquivo de leitura dos dados
    inFile.open(file_name, ios::in); // abre o arquivo para leitura
    if (!inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){ // tem que ler linha por linha e n�o palavra por palavra
        // criar fun��o que separa que l� uma linha e separa os espa�os e os operandos
        string line;
        getline(inFile, line);
        to_token(line);
        contador_linha += 1;
        cout << "[contador posicao]" << contador_posicao << endl;
        cout << "[contador linha]" << contador_linha << endl;
        /* cout << token << endl;
        if(token[token.size() - 1] == ':'){
            if(findInSymbolsTable(token, contador_posicao)){
                cout << "Erro semantico: rotulo redefinido na linha " << contador_linha;
                // retorna erro dizendo que na linha tal achou: redefini��o de r�tulo (sem�ntico)
            }
        }
        if(!findInIntrTable(token, contador_posicao)){ // se n�o achar a instru��o na tabela de instru��es, procurar na tabela de diretivas
            if(!findInDireTable(token, contador_linha)){
                cout << "Erro sint�tico: opera��o n�o identificada " << endl;
            }
            else{
                if(token == "SPACE"){
                    space = true;
                    continue;
                }
            }
        }
    } */

        // procurar rotulo na tabela de rotulos
            // se achar o rotulo, devolva erro, s�mbolo redefinido (sem�ntico)
        // se n�o, adicionar o rotulo na tabela de r�tulos e o contador posi��o (contador de mem�ria)
    }
    inFile.close();
}
void secondPass(string file_name){
    // PSEUDOCODIGO
    // Contador_posição = 0
    // Contador_linha = 1
    // Enquanto arquivo fonte não chegou ao fim, faça:
    //     Obtém uma linha do fonte
    //     Separa os elementos da linha: rótulo,operação,operandos,comentários
    //     Ignora o rótulo e os comentários
    //     Para cada operando que é símbolo
    //     Procura operando na TS
    //         Se não achou: Erro, símbolo indefinido
    //     Procura operação na tabela de instruções
    //     Se achou:
    //         contador_posição = contador_posição + tamanho da instrução
    //         Se número e tipo dos operandos está correto então
    //             gera código objeto conforme formato da instrução
    //         Senão: Erro, operando inválido
    //     Senão:
    //         Procura operação na tabela de diretivas
    //         Se achou:
    //             Chama subrotina que executa a diretiva
    //             Contador_posição = valor retornado pela subrotina
    //         Senão: Erro, operação não identificada
    //     Contador_linha = contador_linha + 1

    contador_linha = 1; // zerando o contador_linha
    contador_posicao = 0; // zerando o contador_posicao
    // imprimindo instruções e operações e tabela de símbolos
    // na segunda passagem olhamos apenas para as operações e os operandos, apenas para ajudar a debugar
    bool operando = false; // primeiro vem a operação e depois o operando
    for(auto X : instr_and_operandos){
        cout << "INSTR AND OPERANDOS: " << X << endl;
    }
    for(auto [X, Y]: symbols_table ){
        cout << "TABELA DE SIMBOLOS: " << "X: " << X << " Y: " << Y << endl;
    }

    for(auto W : instr_and_operandos){ // se for uma operação, olha o operando. se o operando for um símbolo, procura na tabela de símbolos
        if(operando){
            cout << "OPERANDO: " << W << endl; // TODO: Separar operandos do copy em 2, porque eles são separados por vírgula na msm linha
            operando = false;
            continue;
        }
        for(auto [X, Y, Z] : instr_table){
            if(W == X){
                operando = true;
                break;
            }
        }
    }

    /*string token;
    ifstream inFile; // inFile e o arquivo de leitura dos dados
    inFile.open(file_name, ios::in); // abre o arquivo para leitura
    if (!inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){ // TODO: getline não deveria ser dentro do WHILE?
        string line;
        getline(inFile, line);

        int index_comeco = 0;
        bool entrou = false;
        int label_posit = 0;
        int comment_posit = 0;

        for(int i = 0; i < line.size(); i++){
            if((line[i] != ' ') & (line[i] != '\t') & (!entrou)){
                index_comeco = i;
                entrou = true;
                continue;
            }
            if(line[i] == ':'){
                label_posit = i;
            }
            if(line[i] == ';'){
                comment_posit = i;
            }
        }

        int offset = 0;

        if(label_posit != 0){
            offset += line.size() + label_posit; // ignora os rotulos // TODO: Aqui tem que colocar - 1?
        }
        if(comment_posit != 0){
            offset += line.size() - comment_posit;
        }
        */

        // TODO: criar funcao que encontra operando como simbolo na linha

        // TODO: verificar se o operando encontrado existe na TS

        // if(label){
        //     token = linha.substr(rotulo_fim, linha.size() - offset);
        // }else{
        //     token = linha.substr(index_comeco, linha.size() - offset);
        // }
        // if(!findInIntrTable(token, contador_posicao)){
        //     if(!findInDireTable(token)){
        //         cout << "ERRO SINTATICO: OPERACAO NAO RECONHECIDA" << endl;
        //     }
        // }

    // inFile.close();
}
int main()
{
    ifstream in("codigo.asm");
    ofstream out("codigo_no_tab.asm"); // codigo sem tab, transformando todos os tabs em espa�os

    if (!in || !out){
        cout << "ERRO AO LER ARQUIVO" << endl;
        return 1; // retorna um indicando o erro
    }

    char c;
    while (in.get(c)) {
        if (c == '\t')
            out << ""; // 4 spaces
        else
            out << c;
    }
    out.close();
    in.close();
    if (out){
        cout << "SUCESSO" << endl;
    }
    else{
        return 1;
    }
    readFile("codigo_no_tab.asm");
    for(auto [X, Y, Z]: instr_table){
        cout << "X: " << X << " Y: " << Y << " Z: " << Z << endl;
    }
    secondPass("codigo_no_tab.asm");
    return 0;
}
