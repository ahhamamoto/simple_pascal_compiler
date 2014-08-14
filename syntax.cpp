#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define PROGRAM 1
#define LABEL 2
#define TYPE 3
#define VAR 4
#define PROCEDURE 5
#define FUNCTION 6
#define BEGIN 7
#define END 8
#define IF 9
#define THEN 10
#define ELSE 11
#define WHILE 12
#define DO 13
#define OR 14
#define DIV 15
#define END 16
#define NOT 17
#define PONTOVIRGULA 18
#define PONTO 19
#define VIRGULA 20
#define DOISPONTOS 21
#define APARENTESES 22
#define FPARENTESES 23
#define IGUAL 24
#define MENOR 25
#define MAIOR 26
#define MAIS 27
#define MENOS 28
#define ASTERISCO 29
#define ACOLCHETES 30
#define FCOLCHETES 31
#define DOISPONTOSIGUAL 32
#define MENORMAIOR 33
#define MENORIGUAL 34
#define MAIORIGUAL 35
#define IDENTIFICADOR 36
#define NUMERO 37

using namespace std;

int current_token;
fstream input;
fstream output;

string PrintToken[] = {};

int getToken() {
    if (!input.eof()) {
        input >> current_token;
        return current_token;
    } else return 0;
}

bool eat(int token) {
    cout << "Consumindo: [" << PrintToken[current_token] << "] (" << current_token << ")" << endl;
    if (token == current_token) {
        current_token = getToken();
        return true;
    } else {
        cout << "Erro: Consumindo=>[" << PrintToken[current_token] << "]  Esperado=>[" << PrintToken[token] << "] \n";
        getToken();
        return false;
    }
}

int main(int argc, char **argv) {
	if (argc != 3) {
        cerr << "Uso: lexico [Nome do Arquivo de Entrada] [Nome do Arquivo de Saida]" << endl;
        return(1);
    }
    input.open(argv[1], fstream::in);
    output.open(argv[2], fstream::out);

    if (!input.is_open()) {
        cout << "file not open (entrada)";
        return 0;
    }

    if (!output.is_open()) {
        cout << "file not open (saida)";
        return 0;
    }

    return 1;	
}