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
    int i = 0;
    while(i < code.size()){ // varredura para segfault
        if(code[i] == "01"){ // add
            refs.push_back(stoi(code[i+1]));
            i+=2;
            continue;
        }
        else if(code[i] == "02"){ // sub
            refs.push_back(stoi(code[i+1]));
            i+=2;
            continue;
        }
        else if(code[i] == "03"){ // mul
            refs.push_back(stoi(code[i+1]));
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "04"){ // div
            refs.push_back(stoi(code[i+1]));
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            continue;
        }
        else if(code[i] == "05"){ // jmp
            i += 2;
            continue;
        }
        else if(code[i] == "06"){ // jmpn
            i += 2;
            continue;
        }
        else if(code[i] == "07"){ // jmpp
            i += 2;
            continue;
        }
        else if(code[i] == "08"){ // jmpz
            i += 2;
            continue;
        }
        else if(code[i] == "09"){ // copy
            refs.push_back(stoi(code[i+1]));
            refs.push_back(stoi(code[i+2]));
            i += 3;
            continue;
        }
        else if(code[i] == "10"){ // load
            refs.push_back(stoi(code[i+1]));
            i += 2;
            continue;
        }
        else if(code[i] == "11"){ // store
            refs.push_back(stoi(code[i+1]));
            i += 2;
            continue;
        }
        else if(code[i] == "12"){ // input
            refs.push_back(stoi(code[i+1]));
            i += 2;
            continue;
        }
        else if(code[i] == "13"){ // output
            refs.push_back(stoi(code[i+1]));
            i += 2;
            continue;
        }
        else if(code[i] == "14"){ // stop
            break;
        }
    }
    it = min_element(refs.begin(), refs.end()); // posição da primeira label (menor valor referenciado)
    i = 0;
    // for(auto X: refs){
       //  cout << "REF: " << X << endl;
    // }
    while(i < code.size()){
        if(code[i] == "01"){ // add
            op_a = stoi(code[stoi(code[i+1])]);
            acc += op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "02"){ // sub
            op_a = stoi(code[stoi(code[i+1])]);
            acc -= op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "03"){ // mul
            op_a = stoi(code[stoi(code[i+1])]);
            acc *= op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "04"){ // div
            op_a = stoi(code[stoi(code[i+1])]);
            acc = acc/op_a;
            // cout << "<DEBUG> A: " << op_a << endl;
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "05"){ // jmp
            i = stoi(code[i+1]);
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            if(i>=*it){
                cout << *it << endl;
                cout << "SEGMENTATION FAULT" << endl;
                break;
            }
            getchar();
            continue;
        }
        else if(code[i] == "06"){ // jmpn
            if(acc<0){
                i = stoi(code[i + 1]);
                cout << "PC <- " << i << " ";
                cout << "ACC: " << acc << endl;
                if(i>=*it){
                    cout << *it << endl;
                    cout << "SEGMENTATION FAULT" << endl;
                    break;
                }
                getchar();
                continue;
            }
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            if(i>=*it){
                cout << *it << endl;
                cout << "SEGMENTATION FAULT" << endl;
                break;
            }
            getchar();
            continue;
        }
        else if(code[i] == "07"){ // jmpp
            if(acc>0){
                i = stoi(code[i + 1]);
                cout << "PC <- " << i << " ";
                cout << "ACC: " << acc << endl;
                if(i>=*it){
                    cout << *it << endl;
                    cout << "SEGMENTATION FAULT" << endl;
                    break;
                }
                getchar();
                continue;
            }
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            if(i>=*it){
                cout << *it << endl;
                cout << "SEGMENTATION FAULT" << endl;
                break;
            }
            getchar();
            continue;
        }
        else if(code[i] == "08"){ // jmpz
            if(acc==0){
                i = stoi(code[i + 1]);
                cout << "PC <- " << i << " ";
                cout << "ACC: " << acc << endl;
                if(i>=*it){
                    cout << *it << endl;
                    cout << "SEGMENTATION FAULT" << endl;
                    break;
            }
                getchar();
                continue;
            }
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            if(i>=*it){
                cout << *it << endl;
                cout << "SEGMENTATION FAULT" << endl;
                break;
            }
            getchar();
            continue;
        }
        else if(code[i] == "09"){ // copy
            op_a = stoi(code[stoi(code[i+1])]); // operando A
            code[stoi(code[i+2])] = to_string(op_a); // pega o contéudo do operando a e coloca no operando b
            i += 3;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "10"){ // load
            acc = stoi(code[stoi(code[i+1])]);
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "11"){ // store
            code[stoi(code[i+1])] = to_string(acc);
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            continue;
        }
        else if(code[i] == "12"){ // input
            long long int input = 0;
            cin >> input;
            code[stoi(code[i+1])] = to_string(input);
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << endl;
            getchar();
            getchar();
            continue;
        }
        else if(code[i] == "13"){ // output
            i += 2;
            cout << "PC <- " << i << " ";
            cout << "ACC: " << acc << " ";
            cout << "SAIDA: " << code[stoi(code[i-1])];
            getchar();
            continue;
        }
        else if(code[i] == "14"){ // stop
            break;
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
    int i = 0;
//    for(auto X: code){
//        cout << "line: " << i << " " << X << endl;
//        i++;
//    }
}

int main(int argc, char* argv[])
{
    char* file_name = argv[1];
    string file_name_str = argv[1];
    readFile(file_name);
    runObjCode();
    return 0;
}
