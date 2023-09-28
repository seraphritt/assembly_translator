#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
//version: gcc (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
using namespace std;


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

void readFile(){
    string secao;



}
int main()
{
    writeFile();
    return 0;
}
