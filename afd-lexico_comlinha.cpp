#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;
fstream outfile;


// EMMANUEL GALO / DANIEL FROSSARD/ LUIS FERNANDO MILANO
// ****o arquivo de saida outfile deve ser excluido apos cada execucao
// para compilar use  g++ -o afd04 afd-lexico04.cpp
void classifica(int estadoant, string palavra, int lin) {
    outfile.open("outfile.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    if (palavra.compare("begin") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("until") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("boolean") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("char") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("string") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("case") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("then") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("downto") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("and") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("while") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("write") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("do") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("end") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("integer") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("read") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("or") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("for") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("to") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
       outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("program") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("real") == 0) {
        //cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("repeat") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("if") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("else") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("goto") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("var") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("array") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("procedure") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("function") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if (palavra.compare("not") == 0) {
       // cout << palavra << " -> Palavra reservada\n";
        outfile << palavra << "#Palavra reservada#" << lin << endl;
    } else if ((palavra.compare(")") == 0) || (palavra.compare(";") == 0) || (palavra.compare("=") == 0) || (palavra.compare("+") == 0) ||
            (palavra.compare("-") == 0) || (palavra.compare("/") == 0) || (palavra.compare("{") == 0) || (palavra.compare("}") == 0) ||
            (palavra.compare(".") == 0) || (palavra.compare(",") == 0) || (palavra.compare("(") == 0) || (palavra.compare("*") == 0) ||
            (palavra.compare(">") == 0) || (palavra.compare(":") == 0) || (palavra.compare("<") == 0)) {
        //cout <<palavra << " -> Simbolo Simples\n";
        outfile <<palavra << "#Simbolo Simples#" << lin << endl;
    } else if ((palavra.compare(">:") == 0) || (palavra.compare(">=") == 0) || (palavra.compare("<=") == 0) || (palavra.compare("<>") == 0) ||
            (palavra.compare("..") == 0) || (palavra.compare(":=") == 0) || (palavra.compare("(*") == 0) || (palavra.compare("*)") == 0)) {
        //cout << palavra << " -> Simbolo Composto\n";
        outfile << palavra << "#Simbolo Composto#" << lin << endl;
    } else if (palavra.compare("0") == 0 || palavra.compare("1")==0 || palavra.compare("2") ==0|| palavra.compare("3")==0 || palavra.compare("4")== 0 || palavra.compare("5") == 0 || palavra.compare("6") == 0 || palavra.compare("7") ==0|| palavra.compare("8")==0 || palavra.compare("9")==0) {
         //cout<<palavra<<" ->numero"<<endl;
         outfile << palavra << "#numero#" << lin << endl;
    } else {
       // cout << palavra << " <- Identificador\n";
        outfile << palavra << "#Identificador#" << lin << "\n";
    }
    outfile.close();
}

int main(int argc, const char * argv[]) {
    int afd[14][9] =
    //  a-z 0-9 sb >,: <  (   *   .  E
        {{2 , 3, 4, 5, 7, 9, 11,  13, 0}, //estado 1
        { 2 , 2, 0, 0, 0, 0,  0,  0 , 0}, //estado 2
        { 0 , 3, 0, 0, 0, 0,  0,  0 , 0}, //estado 3
        { 0 , 0, 0, 0, 0, 0,  0,  0 , 0}, //estado 4
        { 0 , 0, 6, 0, 0, 0,  0,  0 , 0}, //estado 5
        { 0 , 0, 0, 0, 0, 0,  0,  0 , 0}, //estado 6
        { 0 , 0, 8, 8, 0, 0,  0,  0 , 0}, //estado 7
        { 0 , 0, 0, 0, 0, 0,  0,  0 , 0}, //estado 8
        { 0 , 0, 0, 0, 0, 0, 10,  0 , 0}, //estado 9
        { 0 , 0, 0, 0, 0, 0,  0,  0 , 0}, //estado 10
        { 0 , 0, 12, 0, 0, 0, 0,  0 , 0}, //estado 11
        { 0 , 0, 0, 0, 0, 0,  0,  0 , 0}, //estado 12
        { 0 , 0, 0, 0, 0, 0,  0,  14 , 0},//estado 13
        { 0 , 0, 0, 0, 0, 0, 0,  0 , 0}}; //estado 14

    char buffer;
    fstream file;
    int clinha = 0;
    bool slinha = false;
    string palavra = "";
    string ss = "";
    bool erro = false;
    bool errolexico = false;
    int estadoant = 0;
    int estado = 1;
    int linha = 1;
    // outfile.open ("oufile.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    file.open(argv[1],fstream::in);
    if (!file.is_open()) {
        cout << "Arquivo inexistente";
        exit(1);
    }
    while (buffer != EOF) {
        buffer = file.get();
        if (buffer >= 'a' && buffer <='z' || buffer >='A' && buffer <='Z') {
            if (estado == 1 || estado == 2) {
                palavra += buffer;
            } else if (estadoant != 3) {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][0];
           // outfile << "funcina";

            if (estadoant == 3 && erro) {
                palavra += buffer;
                errolexico = true;
                estado = 1;
                estadoant = 0;
            }
        } else if (buffer >='0' && buffer <='9') {
            if (estadoant == 0) erro = true;
            if (estado == 1 || estado == 2 || estado == 3) {
                palavra += buffer;
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][1];
        }

        else if (buffer == ')'  || buffer == ';' || buffer == '=' || buffer == '+' || buffer == '-' || buffer == '/' || buffer == '{'|| buffer == '}' || buffer == ',') {
            if (estado == 1 || estado == 5 || estado == 7 || estado == 11) {
                palavra += buffer;
                if (buffer == '{') {
                    while(buffer != '}') {
                        buffer = file.get();
                    }
                    file.unget();
                }
            }
            else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][2];
        }

        else if (buffer == '>' || buffer == ':') {
            if (estado == 1 || estado == 7) {
                palavra += buffer;
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][3];
        } else if (buffer == '<') {
            if (estado == 1) {
                palavra += buffer;
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][4];
        } else if (buffer == '(') {
            if (estado == 1) {
                palavra += buffer;
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][5];
        } else if (buffer == '*') {
            if (estado == 1 || estado == 9) {
                palavra += buffer;
                if (estado ==  9) {
                    bool sai =  true;
                    buffer = file.get();
                    while (sai) {
                        buffer = file.get();
                        if (buffer == '*') {
                            buffer = file.get();
                            if (buffer == ')') {
                                sai = false;
                                file.unget();
                            }
                        }
                        if (buffer == EOF) {
                            sai = false;
                            classifica(estadoant, palavra, linha);
                        }
                    }
                    file.unget();
                }
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][6];
        }
        else if (buffer == '.') {
            if (estado == 1 || estado == 13) {
                palavra += buffer;
            } else {
                file.unget();
            }
            estadoant = estado;
            estado = afd[estado-1][7];
        }
        else if (buffer == ' ' || buffer == '\n' || buffer == '\t' || buffer == EOF) {
            estadoant = estado;
            estado = 0;
            if (buffer == '\n') {
                slinha = true;
                cout << linha << endl;
            }
            //buffer = file.get();
            while (buffer == ' ' || buffer == '\n' || buffer == '\t') {
                buffer = file.get();
                if (buffer == '\n') {
                    slinha = true;
                    clinha ++;
                    cout << linha << endl;
                }
            }
            file.unget();
        }
        else {
            bool fim = false;
            errolexico = true;
            palavra += buffer;
        }

        if (estado == 0) {
            if (errolexico == true) {
                cout<<"erro lexico na linha "<<linha<<" palavra = "<<palavra<<endl;
                palavra = "";
                estado = 1;
                estadoant = 0;
                errolexico = false;
                exit(0);
            }

            if (palavra.compare("") != 0) {
                cout << "linha antes de classificar: " << linha <<endl;
                classifica(estadoant, palavra, linha);
                if (slinha) linha++;
                slinha = false;
                linha = linha + clinha;
                clinha = 0;
                palavra = "";
                estado = 1;
                estadoant = 0;
            }
        }
    }
}
