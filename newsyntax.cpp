#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define BEGIN 1
#define UNTIL 2
#define BOOLEAN 3
#define CHAR 4
#define STRING 5
#define CASE 6
#define THEN 7
#define DOWNTO 8
#define AND 9
#define WHILE 10
#define WRITE 11
#define DO 12
#define END 13
#define INTEGER 14
#define READ 15
#define OR 16
#define FOR 17
#define TO 18
#define PROGRAM 19
#define REAL 20
#define REPEAT 21
#define IF 22
#define ELSE 23
#define GOTO 24
#define VAR 25
#define ARRAY 26
#define PROCEDURE 27
#define FUNCTION 28
#define NOT 29
#define APARENTESES 30
#define FPARENTESES 31
#define PONTOVIRGULA 32
#define IGUAL 33
#define MAIS 34
#define MENOS 35
#define BARRA 36
#define ACHAVES 37
#define FCHAVES 38
#define PONTO 39
#define VIRGULA 40
#define ASTERISCO 41
#define MAIOR 42
#define MENOR 43
#define DOISPONTOS 44
#define MAIORDOISPONTOS 45
#define MAIORIGUAL 46
#define MENORIGUAL 47
#define MENORMAIOR 48
#define PONTOPONTO 49
#define DOISPONTOSIGUAL 50
#define ACOMMENTS 51
#define FCOMMENTS 52
#define DIGITO 53
#define IDENTIFICADOR 54

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