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
// instrução, num maximo de argumentos, OP code
instr_table_type instr_table = {make_tuple("ADD", 2, "01"), make_tuple("SUB", 2, "02"), make_tuple("MUL", 2, "03"), make_tuple("DIV", 2, "04"), make_tuple("JMP", 2, "05"), make_tuple("JMPN", 2, "06"), make_tuple("JMPP", 2, "07"), make_tuple("JMPZ", 2, "08"), make_tuple("COPY", 3, "09"), make_tuple("LOAD", 2, "10"), make_tuple("STORE", 2, "11"), make_tuple("INPUT", 2, "12"), make_tuple("OUTPUT", 2, "13"), make_tuple("STOP", 1, "14")};
int contador_linha = 1;
int contador_posicao = 0;
bool findInIntrTable(string instr, int posit){
    for(auto [X, Y, Z]: instr_table){
        if(X == instr){
            contador_posicao = contador_posicao + Y;
            return true;
        }
    }
    // retorna falso e irá procurar na tabela de diretivas
    return false;
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

vector<string> readFile(string file_name){
    vector<string> conteudo;
    vector<string> rotulo;
    vector<string> operacao;
    vector<string> operandos;
    // comentarios serão ignorados
    ifstream inFile; // inFile é o arquivo de leitura dos dados
    inFile.open(file_name);
    if (!inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){
        string line;
        string token;
        getline(inFile, line);
        cout << line;
        if(token[token.size() - 1] == ':'){
            if(findInSymbolsTable(token, contador_posicao)){
                cout << "Erro semantico: rotulo redefinido na linha " << 0;
                // retorna erro dizendo que na linha tal achou: redefinição de rótulo (semântico)
            }
        }
        else{
            if(findInIntrTable(token, contador_posicao)){
                cout << "Achou" << endl;
            }else{
                cout << "Procurar na tabela de diretivas" << endl;
                // procurar na tabela de diretivas
            }
        }
    }

        // procurar rotulo na tabela de rotulos
            // se achar o rotulo, devolva erro, símbolo redefinido (semântico)
        // se não, adicionar o rotulo na tabela de rótulos e o contador posição (contador de memória)
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
