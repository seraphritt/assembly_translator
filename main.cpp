#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <vector>

//version: g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
//using C++17
using namespace std;
vector<tuple<string, string, string>> instr_and_operandos;
vector<string> obj_content; // conteúdo a ser escrito no arquivo objeto
typedef vector<tuple<string, int>> table_type;
typedef vector<tuple<string, int, string>> instr_table_type;
table_type symbols_table;
vector<string> dire_table = {"SPACE", "CONST", "SECAO DATA", "SECAO TEXT", "SECAO", "DATA", "TEXT"}; // diretivas

vector<string> arquivo_obj;
// instrucao, num maximo de argumentos, OP code
vector<string> conteudo; // vetor que guarda o que sera escrito no arquivo objeto
instr_table_type instr_table = {make_tuple("ADD", 2, "01"), make_tuple("SUB", 2, "02"), make_tuple("MUL", 2, "03"), make_tuple("DIV", 2, "04"), make_tuple("JMP", 2, "05"), make_tuple("JMPN", 2, "06"), make_tuple("JMPP", 2, "07"), make_tuple("JMPZ", 2, "08"), make_tuple("COPY", 3, "09"), make_tuple("LOAD", 2, "10"), make_tuple("STORE", 2, "11"), make_tuple("INPUT", 2, "12"), make_tuple("OUTPUT", 2, "13"), make_tuple("STOP", 1, "14")};
int contador_linha = 0;
int contador_posicao = 0;



tuple<string, int> getLineGeneratedCode(tuple<string, string, string> operation, int address, int symbol_1_posit, int symbol_2_posit){
    string line_generated_code = "";
    int acres1;
    int acres2;
    bool has_operation = false;
    // TODO: identificar operadores como ROTULO+2 (acessar a posição 2 do vetor ROTULO)
    for(auto [X, Y, Z]: instr_table){
        if(X == get<0>(operation)){
            if(Y == 1){
                line_generated_code += string(Z) + " ";
            }else if(Y == 2){
                acres1 = 0;
                if(get<1>(operation).find("+") != string::npos){ // se houver + no operando da instrução
                    acres1 = stoi(get<1>(operation).substr(get<1>(operation).find("+") + 1, get<1>(operation).size() - get<1>(operation).find("+")));
                }
                line_generated_code += string(Z) + " " + to_string(symbol_1_posit) + " ";
            }else if(Y == 3){
                acres1 = 0;
                acres2 = 0;
                if(get<1>(operation).find("+") != string::npos){ // se houver + no operando da instrução
                    acres1 = stoi(get<1>(operation).substr(get<1>(operation).find("+") + 1, get<1>(operation).size() - get<1>(operation).find("+")));
                }
                if(get<2>(operation).find("+") != string::npos){ // se houver + no operando da instrução
                    acres2 = stoi(get<2>(operation).substr(get<2>(operation).find("+") + 1, get<2>(operation).size() - get<2>(operation).find("+")));
                }
                line_generated_code += string(Z) + " " + to_string(symbol_1_posit + acres1) + " " + to_string(symbol_2_posit + acres2) + " ";
            }
            address += Y; //posicao que ocupa
            has_operation = true;
        }
    }

    if(!has_operation){
        if(get<0>(operation) == "SPACE"){
            if(get<1>(operation) != ""){
                for(int i = 0; i < stoi(get<1>(operation)); i++){
                    line_generated_code += string("00") + string(" ");
                    address++;
                }
            }else{
                line_generated_code += string("00") + string(" ");
                address++;
            }
        }else if(get<0>(operation) == "CONST"){
            line_generated_code = get<1>(operation) + " ";
            address++;
        }
    }

    return make_tuple(line_generated_code, address);
}

vector<string> splitString(string input, char delimiter){
    vector<string> result;
    istringstream ss(input);
    string element;

    while (getline(ss, element, delimiter)) {
        result.push_back(element);
    }

    return result;
}

bool findInIntrTable(string instr, int posit){
    int tam = 0;
    int qtd = 0;
    if(instr != "\0"){
        istringstream a(instr); // tipo para usar o getline() e separar em espa�os
        vector<string> s;
        string ss;
        cout << "instr: " << instr << endl;
        if(instr.find("COPY") == string::npos){ // se não for copy, separa os operandos por espaço (só tem 1 operando) ou 0 no caso do stop e space
            while (getline( a, ss, ' ') ) {
                if((ss != "" && ss != "SECAO" && ss != "DATA" && ss != "TEXT")){
                    s.push_back(ss);
                    qtd += 1;
                    cout << ss << endl;
                    tam = instr_and_operandos.size();
                }
            }
            if(s.size() == 1){
                instr_and_operandos.push_back(make_tuple(s[0], "", ""));
            }else if(s.size() == 2){
                instr_and_operandos.push_back(make_tuple(s[0], s[1], ""));
                if(s[0] != "CONST"){
                    instr_and_operandos.push_back(make_tuple("BUBBLE", "", ""));
                }if(s[0] == "SPACE" && s[1] != ""){
                    for(int i = 0; i < stoi(s[1]) - 2; i++){
                        instr_and_operandos.push_back(make_tuple("BUBBLE", "", ""));
                    }
                }
                 // as instruções bubble são para fazer com que o contador posição esteja certo
            }

        }else{
            // se for copy, separa por vírgula
            ss = splitString(instr, ' ')[1]; // ss = splitOperands_space(instr)[1];

            while (getline( a, ss, ',') ) {
                if((ss != "" && ss != "SECAO" && ss != "DATA" && ss != "TEXT")){
                    s.push_back(ss);
                    cout << ss << endl;
                }
            }qtd += 3;
            instr_and_operandos.push_back(make_tuple("COPY", s[0], s[1]));
            instr_and_operandos.push_back(make_tuple("BUBBLE", "", "")); // as instruções bubble são para fazer com que o contador posição esteja certo
            instr_and_operandos.push_back(make_tuple("BUBBLE", "", ""));
            s[0] = "COPY";
        }

        if(instr_and_operandos.size() != 0 && s.size() != 0){
            for(auto [X, Y, Z]: instr_table){
                if(X == s[0]){
                    contador_posicao = contador_posicao + Y;
                    return true;
                }
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
    obj_content = {"Places", "Faces"};
    ofstream outFile;
    outFile.open("codigo.obj", ios::out); // abre o arquivo para escrita
    if (! outFile)
    {
        cout << "Arquivo codigo.obj nao pode ser aberto" << endl;
        abort();
    }
    for(auto X: obj_content){ // escrevendo cada posição do vetor no arquivo
        outFile << X;
    }
    outFile.close(); // se o programador omitir a chamada ao metodo close
}
void to_token(string linha){
    string token;
    int comment = 0;
    int index_comeco = 0;
    int rotulo_fim  = 0;
    bool label = false;
    bool entrou = false;
    for(int i = 0; i < linha.size(); i++){ // se tiver label, acha e coloca na tabela de simbolos
        if((linha[i] != ' ') & (linha[i] != '\t') & (!entrou)){
            index_comeco = i;
            entrou = true;
            continue;
        }
        if(linha[i] == ':'){ // se achar 2 pontos pega tudo que vem antes dos dois pontos e isso e o rotulo/label
            label = true; // se tiver essa flag usa-se o rotulo_fim, ou seja, a ultima posicao do rotulo
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
               } // se achou na tabela de simobolos tem erro

        }
        if(linha[i] == ';'){ // anota a posicao onde esta o comentario, para que o que vier depois seja ignorado
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
    if(token.size() != 0){ // para evitar que leia uma string ""
        if(!findInIntrTable(token, contador_posicao)){
            if(!findInDireTable(token)){
                cout << "ERRO SINTATICO: OPERACAO NAO RECONHECIDA" << endl;
            }
        }
    }

}
void readFile(string file_name){
    vector<string> rotulo;
    vector<string> operacao;
    vector<string> operandos;
    // comentarios serao ignorados
    string token;
    ifstream inFile; // inFile e o arquivo de leitura dos dados
    inFile.open(file_name, ios::in); // abre o arquivo para leitura
    if (!inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){ // tem que ler linha por linha e nao palavra por palavra
        // criar funcao que separa que le uma linha e separa os espacos e os operandos
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
                // retorna erro dizendo que na linha tal achou: redefinicao de rotulo (semantico)
            }
        }
        if(!findInIntrTable(token, contador_posicao)){ // se nao achar a instrucao na tabela de instrucoes, procurar na tabela de diretivas
            if(!findInDireTable(token, contador_linha)){
                cout << "Erro sintatico: operacao nao identificada " << endl;
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
        // se achar o rotulo, devolva erro, simbolo redefinido (semantico)
        // se nao, adicionar o rotulo na tabela de rotulos e o contador posicao (contador de memoria)
    }
    inFile.close();
}
void secondPass(string file_name){
    contador_linha = 1; // zerando o contador_linha
    contador_posicao = 0; // zerando o contador_posicao
    bool achou_1 = false;
    bool achou_2 = false;

    int address = 0;
    ofstream outputFile("codigo_gerado.txt", std::ios::trunc);

    for(int i = 0; i < instr_and_operandos.size(); i++){ // se for uma operação, olha o operando. se o operando for um símbolo, procura na tabela de símbolos
        cout << endl << "operacoes: " << get<0>(instr_and_operandos[i]) << endl;
        cout << "operandos_1: " << get<1>(instr_and_operandos[i]) << endl;
        cout << "operandos_2: " << get<2>(instr_and_operandos[i]) << endl;

        tuple<string, string, string> operation = instr_and_operandos[i];
        int symbol_1_posit = 15; // verificar se e possivel inicializar com 15 (nao existe operacao com esse opcode numerico)
        int symbol_2_posit = 15;

        for(auto [X, Y]: symbols_table){
            if(X == get<1>(instr_and_operandos[i])){ // para cada operando que e símbolo, se achar na tabela de diretivas
                // TODO: se achar + na string, fazer uma substring que recorte do começo até antes do símbolo de +
                achou_1 = true;
                symbol_1_posit = Y;
                cout << "operando_1_rotulo :" << get<0>(instr_and_operandos[Y]) << endl;
                cout << "SIMBOLO: " << X << " " << "POSICAO: " << Y << endl;
            }
            if(X == get<2>(instr_and_operandos[i])){
                // TODO: se achar + na string, fazer uma substring que recorte do começo até antes do símbolo de +
                achou_2 = true;
                symbol_2_posit = Y;
                cout << "operando_2_rotulo :" << get<0>(instr_and_operandos[Y]) << endl;
                cout << "SIMBOLO: " << X << " " << "POSICAO: " << Y << endl;
            }
        }

        if((!achou_1 && get<1>(instr_and_operandos[i]) != "" && get<0>(instr_and_operandos[i]) != "SPACE" && get<0>(instr_and_operandos[i]) != "CONST") || (!achou_2 && get<2>(instr_and_operandos[i]) != "" && get<0>(instr_and_operandos[i]) != "SPACE" && get<0>(instr_and_operandos[i]) != "CONST")){
            cout << "ERRO, SIMBOLO INDEFINIDO" << endl;
        }

        if (!outputFile.is_open()) { // verifica see possivel abrir o arquivo onde salvamos o codigo gerado
            cout << "Erro ao abrir o arquivo codigo_gerado.txt" << endl;
            abort();
        }

        tuple<string, int> result_generated_code_func  = getLineGeneratedCode(operation, address, symbol_1_posit, symbol_2_posit);

        string line_generated_code = get<0>(result_generated_code_func);
        address = get<1>(result_generated_code_func);

        outputFile << line_generated_code;
    }

    outputFile.close(); // Fecha o arquivo codigo_gerado
}

void organizeFile(string file_name){
    ifstream inFile; // inFile   o arquivo de leitura dos dados
    ofstream outFile(file_name);
    bool entra = false;
    int secao_data_index_line = -1;
    int secao_text_index_line = -1;
    int conta_linhas = 0;
    inFile.open("codigo.asm", ios::in); // abre o arquivo para leitura
    if (!inFile)
    {
        cout << "Arquivo codigo.asm nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){
        string line;
        getline(inFile, line);
        if(line == "SECAO TEXT"){
            secao_text_index_line = conta_linhas;
        }else if(line == "SECAO DATA"){
            secao_data_index_line = conta_linhas;
        }
        conta_linhas++;
        cout << "OrganizeFile: " << line << endl;
    }
    inFile.close();
    inFile.open("codigo.asm", ios::in);
    if((secao_text_index_line > secao_data_index_line) && (secao_text_index_line != -1)){ // isso significa que secao data vem antes de text
        while(inFile){
            string line;
            getline(inFile, line);
            if(line == "SECAO TEXT" || entra){
                if(line == "" || line == "\n"){
                    continue;
                }
                entra = true;
                outFile << line;
                outFile << "\n";
            }else if(line == "SECAO DATA"){
                continue;
            }
        }
        inFile.close();
        inFile.open("codigo.asm", ios::in);
        while(inFile){
            string line;
            getline(inFile, line);
            if(line == "SECAO TEXT"){
                break;
            }
            if(line == "SECAO DATA" || entra){
                entra = true;
                if(line == "" || line == "\n"){
                    continue;
                }
                outFile << line;
                outFile << "\n";
            }
        }
    }
    inFile.close();

}

int main()
{
    ifstream in("codigo.asm");
    ofstream out("codigo_temp.asm"); // codigo sem tab, transformando todos os tabs em espacos

    if (!in || !out){
        cout << "ERRO AO LER ARQUIVO" << endl;
        return 1; // retorna um indicando o erro
    }
    // limpa o arquivo, tirando todos os tabs e substituindo por espaços
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
    organizeFile("codigo_temp.asm");// TODO: implementar aqui uma funçao que verifica se a seção de texto está primeiro e a de dados depois. se não estiver, modificar o arq de entrada para que text venha sempre antes de dados
    readFile("codigo_temp.asm");
    for(auto [X, Y, Z]: instr_table){
        cout << "X: " << X << " Y: " << Y << " Z: " << Z << endl;
    }
    // imprimindo tabela de simbolos
    for(auto [X, Y]: symbols_table){
        cout << "SIMBOLO: " << X << " " << "POSICAO: " << Y << endl;
    }
    secondPass("codigo_temp.asm");
    writeFile();
    return 0;
}
