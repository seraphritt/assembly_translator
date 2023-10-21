#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
using namespace std;
//version: g++ (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
//using C++17

vector<string> code;
long long int acc = 0; // 64 bits
void runObjCode(){
    vector<long long int> refs;
    vector<long long int>::iterator it;
    long long int op_a = 0;
    long long int op_b = 0;
    int i = 0;
    while(i < code.size()){
        cout << "i:" << i << endl;
        if(refs.size() != 0){
            it = min_element(refs.begin(), refs.end());
            cout << "min: " << *it << endl;
        }
        if(code[i] == "01"){ // add
            cout << "PC <- " << i << " ";
            refs.push_back(stoi(code[i+1]));
            op_a = stoi(code[stoi(code[i+1])]);
            acc += op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            cout << "ACC: " << acc << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "02"){ // sub
            refs.push_back(stoi(code[i+1]));
            cout << "PC <- " << i << " ";
            op_a = stoi(code[stoi(code[i+1])]);
            acc -= op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            cout << "ACC: " << acc << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "03"){ // mul
            refs.push_back(stoi(code[i+1]));
            cout << "PC <- " << i << " ";
            op_a = stoi(code[stoi(code[i+1])]);
            acc *= op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            cout << "ACC: " << acc << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "04"){ // div
            refs.push_back(stoi(code[i+1]));
            cout << "PC <- " << i << " ";
            op_a = stoi(code[stoi(code[i+1])]);
            acc = acc/op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            cout << "ACC: " << acc << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "05"){ // jmp
            i = stoi(code[i+1]);
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            continue;
        }
        else if(code[i] == "06"){ // jmpn
            if(acc<0){
                i = stoi(code[i + 1]);
                cout << "PC <- " << i << " ";
                cout << "ACC: " << acc << endl;
                continue;
            }
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            i += 1;
        }
        else if(code[i] == "07"){ // jmpp
            if(acc>0){
                i = stoi(code[i + 1]);
                cout << "PC <- " << i << " ";
                cout << "ACC: " << acc << endl;
                continue;
                }
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            i += 1;
        }
    }
}


void readFile(string file_name){
    string each;
    string token;
    ifstream inFile; // inFile e o arquivo de leitura dos dados
    inFile.open(file_name, ios::in); // abre o arquivo para leitura
    if (!inFile)
    {
        cout << "Arquivo " << file_name << " nao pode ser aberto" << endl;
        abort();
    }
    while(inFile){
        getline(inFile, each, ' ');
        code.push_back(each);
    }
    for(auto X: code){
        cout << "line: " << X << endl;
    }
}

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    string file_name_str = argv[1];
    readFile(file_name);
    runObjCode();
    return 0;
}
