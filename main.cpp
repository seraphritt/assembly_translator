#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

//version: gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
//using C++17
using namespace std;

typedef vector<tuple<string, int>> table_type;
typedef vector<tuple<string, int, string>> instr_table_type;
table_type symbols_table;
vector<string> dire_table = {"SPACE", "CONST"}; // diretivas
// instrução, num maximo de argumentos, OP code
vector<string> conteudo; // vetor que guarda o que será escrito no arquivo objeto
instr_table_type instr_table = {make_tuple("ADD", 2, "01"), make_tuple("SUB", 2, "02"), make_tuple("MUL", 2, "03"), make_tuple("DIV", 2, "04"), make_tuple("JMP", 2, "05"), make_tuple("JMPN", 2, "06"), make_tuple("JMPP", 2, "07"), make_tuple("JMPZ", 2, "08"), make_tuple("COPY", 3, "09"), make_tuple("LOAD", 2, "10"), make_tuple("STORE", 2, "11"), make_tuple("INPUT", 2, "12"), make_tuple("OUTPUT", 2, "13"), make_tuple("STOP", 1, "14")};
int contador_linha = 1;
int contador_posicao = 0;


bool findInIntrTable(string instr, int posit){
    istringstream a(instr); // tipo para usar o getline() e separar em espaços
    string s;
    while (getline( a, s, ' ') ) {
        if(s != " ")
            cout << s << endl;
    }
    for(auto [X, Y, Z]: instr_table){
        if(X == instr){
            contador_posicao = contador_posicao + Y;
            return true;
        }
    }
    // retorna falso e irá procurar na tabela de diretivas
    return false;
}
bool findInDireTable(string dire){
    for(auto X: dire_table){
        if(X == dire){
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
    outFile.open("saída.txt", ios::out); // abre o arquivo para escrita
    if (! outFile)
    {
        cout << "Arquivo saida.txt nao pode ser aberto" << endl;
        abort();
    }
    cout << "Entre com o numero e nome do funcionário\n" << "Fim de arquivo (Ctrl-Z) termina a entrada de dados\n\n? ";
    while(cin >> numero >> nome)
    {
        outFile << numero << " " << nome << "\n";
        cout << "?";
    }
    outFile.close(); // se o programador omitir a chamada ao método close
}
void to_token(string linha){
    bool comeco = true;
    string token;
    int comment = 0;
    int index_comeco = 0;
    int rotulo_fim  = 0;
    for(int i = 0; i < linha.size(); i++){ // se tiver label, acha e coloca na tabela de símbolos
        if(linha[i] == ' '){
            index_comeco = i;
            continue;
        }
        if(linha[i] == ':'){ // se achar 2 pontos pega tudo que vem antes dos dois pontos e isso é o rótulo/label
            token = linha.substr(index_comeco, i - index_comeco);
            cout << token << endl;
            rotulo_fim = i;
            if(findInSymbolsTable(token, contador_posicao)){
               cout << "ERRO SEMANTICO: SIMBOLO REDEFINIDO" << endl;
               } // se achou na tabela de símobolos tem erro

        }
        if(linha[i] == ';'){ // anota a posicao onde está o comentario, para que o que vier depois seja ignorado
            comment = i;
        }
    }
    token = linha.substr(rotulo_fim, linha.size() - rotulo_fim - (linha.size() - comment));
    cout << "FF" << token << endl;
    if(!findInIntrTable(token, contador_posicao)){
        if(!findInDireTable(token)){
            cout << "ERRO SINTATICO: OPERACAO NAO RECONHECIDA" << endl;
        }
    }

}
vector<string> readFile(string file_name){
    vector<string> conteudo;
    bool space = false;
    vector<string> rotulo;
    vector<string> operacao;
    vector<string> operandos;
    // comentarios serão ignorados
    string token;
    ifstream inFile; // inFile é o arquivo de leitura dos dados
    inFile.open(file_name, ios::in); // abre o arquivo para leitura
    if (! inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){ // tem que ler linha por linha e não palavra por palavra
        // criar função que separa que lê uma linha e separa os espaços e os operandos
        string line;
        getline(inFile, line);
        cout << line << endl;
        to_token(line);
        /* cout << token << endl;
        if(token[token.size() - 1] == ':'){
            if(findInSymbolsTable(token, contador_posicao)){
                cout << "Erro semantico: rotulo redefinido na linha " << contador_linha;
                // retorna erro dizendo que na linha tal achou: redefinição de rótulo (semântico)
            }
        }
        if(!findInIntrTable(token, contador_posicao)){ // se não achar a instrução na tabela de instruções, procurar na tabela de diretivas
            if(!findInDireTable(token, contador_linha)){
                cout << "Erro sintático: operação não identificada " << endl;
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
            // se achar o rotulo, devolva erro, símbolo redefinido (semântico)
        // se não, adicionar o rotulo na tabela de rótulos e o contador posição (contador de memória)
    }
    inFile.close();
    return conteudo;
}
int main()
{
    readFile("codigo.asm");
    for (auto [X, Y, Z] : instr_table){
        cout << X << " " << Y << " " << Z << endl;
    }
    return 0;
}
