#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define PROGRAM 1
#define LABEL 2
#define TYPE 3
#define ARRAY 4
#define OF 5
#define VAR 6
#define PROCEDURE 7
#define FUNCTION 8
#define BEGIN 9
#define END 10
#define IF 11
#define THEN 12
#define ELSE 13
#define WHILE 14
#define DO 15
#define OR 16
#define AND 17
#define DIV 18
#define NOT 19
#define IDENTIFIER 20
#define NUMBER 21
#define APARENTESES 22
#define FPARENTESES 23
#define PONTOVIRGULA 24
#define DOISPONTOS 25
#define MAIS 26
#define MENOS 27
#define BARRA 28
#define ACOLCHETES 29
#define FCOLCHETES 30
#define VIRGULA 31
#define MAIOR 32
#define MENOR 33
#define ASTERISCO 34
#define IGUAL 35
#define MAIORIGUAL 36
#define MENORIGUAL 37
#define ATRIBUICAO 38
#define MENORMAIOR 39
#define PONTO 40

// static const int program = 1, label = 2, type = 3, var = 4, procedure = 5, _function = 6, _begin = 7;
// static const int _while = 8, _not = 9;
// static const int op_parentheses = 10, cl_parentheses = 11, semiCOLON = 12, period = 13, comma = 14;
// static const int _equal = 15, colon = 16, op_bracket = 17, cl_bracket = 18, db_period = 19;
// static const int _else = 20, _div = 21, _and = 22, asterisk = 23, _goto = 24;
// static const int identifier = 25, number = 26, array = 27, _procedure = 28, _if = 29, _then = 30;
// static const int _end = 31, OF = 32, attrib = 33, _do = 34, _lesserGREATER = 35, _lesser = 36, _lessEQUAL = 37;
// static const int _greatEQUAL = 38, _greater = 39, _plus = 40, _minus = 41, _or = 42;
string PrintToken[] = {"zero", "PROGRAM", "LABEL", "TYPE", "ARRAY", "OF", "VAR", "PROCEDURE", "FUNCTION", "BEGIN","END", "IF", "THEN", "ELSE",
                       "WHILE", "DO", "OR", "AND", "DIV", "NOT", "IDENTIFIER", "NUMBER", "(", ")", ";", ":", "+", "-", "/", "[", "]", ",",
                       ">", "<", "*", "=", ">=", "<=", ":=", "<>", "."};


int current_token;
fstream file;
fstream output;

void PROGRAMA(), BLOCO(), TIPO(), PARAM_FORMAIS(), COMANDO(), COM_SEM_ROTULO(),EXPRESSAO(), EXP_SIMPLES(), TERMO(), FATOR();

int getToken() {
    if (!file.eof()) {
        file >> current_token;
        return current_token;
    } else return 0;
}

bool eat(int token) {
    cout << "Eating: [" << PrintToken[current_token] << "] (" << current_token << ")" << endl;
    if (token == current_token) {
        current_token = getToken();
        return true;
    } else {
        cout << "eat error. reading '" << PrintToken[current_token] << "'. expecting '" << PrintToken[token] << "'.\n";
        getToken();
        return false;
    }
}

void PROGRAMA() {
    switch (current_token) {
        case PROGRAM:
            eat(PROGRAM);
            eat(IDENTIFIER);
            eat(PONTOVIRGULA);
            BLOCO();
            eat(PONTO);
            break;
        default:
            cout << "expected program... PROGRAMA";
    }
}

void BLOCO() {

    switch (current_token){
        case LABEL:
            eat(LABEL);
            eat(NUMBER);
            while (current_token == VIRGULA) {
                eat(VIRGULA);
                eat(NUMBER);
            }
            eat(PONTOVIRGULA);
            break;
        case TYPE:
            eat(TYPE);
            while (current_token == IDENTIFIER) {
                eat(IDENTIFIER);
                eat(IGUAL);
                TIPO();
                eat(PONTOVIRGULA);
            }
            break;
        case VAR:
            eat(VAR);
            while (current_token == IDENTIFIER) {
                eat(IDENTIFIER);
                while (current_token == VIRGULA){
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                TIPO();
                eat(PONTOVIRGULA);
            }
            break;
        default:
            cout << "expected program BLOCO" << endl;
            break;
    }

    while (current_token == PROCEDURE || current_token == FUNCTION) {
        if (current_token == PROCEDURE) {
            eat(PROCEDURE);
            eat(IDENTIFIER);
            PARAM_FORMAIS();
        } else if (current_token == FUNCTION) {
            eat(FUNCTION);
            eat(IDENTIFIER);
            PARAM_FORMAIS();
            eat(DOISPONTOS);
            eat(IDENTIFIER);
        } else
            cout << "expected prgram BLOCO 2" << endl;

        eat(PONTOVIRGULA);
        BLOCO();
        eat(PONTOVIRGULA);
    }

    if(current_token == BEGIN) {
        eat(BEGIN);
        COMANDO();
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            COMANDO();
        }
        eat(END);
    }
}

void TIPO() {
    eat(IDENTIFIER);
}

void PARAM_FORMAIS() {
    eat(APARENTESES);
    while (current_token == VAR || current_token == IDENTIFIER || current_token == FUNCTION || current_token == PROCEDURE) {
        switch (current_token) {
            case VAR:
                eat(VAR);
                break;
            case IDENTIFIER:
                eat(IDENTIFIER);
                while (current_token == VIRGULA) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case FUNCTION:
                eat(FUNCTION);
                eat(IDENTIFIER);
                PARAM_FORMAIS();
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case PROCEDURE:
                eat(PROCEDURE);
                eat(IDENTIFIER);
                PARAM_FORMAIS();
                break;
            default:
                cout << "FUDEUUUU";
                break;
        }
        if (current_token == PONTOVIRGULA)
            eat(PONTOVIRGULA);
    }
    eat(FPARENTESES);
}

void COMANDO () {
    if (current_token == NUMBER) {
        eat(NUMBER);
        eat(DOISPONTOS);
    }
    COM_SEM_ROTULO();
}

void COM_SEM_ROTULO() {
    switch(current_token){
        case IDENTIFIER:
            eat(IDENTIFIER);
            if (current_token == ATRIBUICAO) {
                eat(ATRIBUICAO);
                EXPRESSAO();
            } else if (current_token == APARENTESES) {
                eat(APARENTESES);
                if (current_token ==  FPARENTESES) {
                    eat(FPARENTESES);
                }
                else {
                    EXPRESSAO();
                    while (current_token == VIRGULA) {
                        eat(VIRGULA);
                        EXPRESSAO();
                    }
                    eat(FPARENTESES);
                }
            }
            break;
        case BEGIN:
            eat(BEGIN);
            COM_SEM_ROTULO();
            while (current_token == PONTOVIRGULA) {
                eat(PONTOVIRGULA);
                COM_SEM_ROTULO();
            }
            eat(END);
            break;
        case IF:
            eat(IF);
            EXPRESSAO();
            eat(THEN);
            COM_SEM_ROTULO();
            if (current_token == ELSE) {
                eat(ELSE);
                COM_SEM_ROTULO();
            }
            break;
        case WHILE:
            eat(WHILE);
            EXPRESSAO();
            eat(DO);
            COM_SEM_ROTULO();
            break;
        default:
            break;
    }
}

void EXPRESSAO() {
    EXP_SIMPLES();
    switch (current_token) {
        case IGUAL:
            eat(IGUAL);
            EXP_SIMPLES();
            break;
        case MENORMAIOR:
            eat(MENORMAIOR);
            EXP_SIMPLES();
            break;
        case MENOR:
            eat(MENOR);
            EXP_SIMPLES();
            break;
        case MENORIGUAL:
            eat(MENORIGUAL);
            EXP_SIMPLES();
            break;
        case MAIORIGUAL:
            eat(MAIORIGUAL);
            EXP_SIMPLES();
            break;
        case MAIOR:
            eat(MAIOR);
            EXP_SIMPLES();
            break;
        default:
            break;
    }
}

void EXP_SIMPLES() {
    if (current_token == MAIS)
        eat(MAIS);
    else if(current_token == MENOS)
        eat(MENOS);

    TERMO();

    while (current_token == MAIS || current_token == MENOS || current_token == OR) {
        switch (current_token) {
            case MAIS:
                eat(MAIS);
                break;
            case MENOS:
                eat(MENOS);
                break;
            case OR:
                eat(OR);
                break;
        }
        TERMO();
    }
}

void TERMO() {
    FATOR();
    while (current_token == ASTERISCO|| current_token == DIV || current_token == AND) {
        switch (current_token) {
            case ASTERISCO:
                eat(ASTERISCO);
                break;
            case DIV:
                eat(DIV);
                break;
            case AND:
                eat(AND);
                break;
        }
        FATOR();
    }
}

void FATOR() {
    switch (current_token) {
        case IDENTIFIER:
            eat(IDENTIFIER);
            if (current_token == APARENTESES) {
                eat(APARENTESES);
                if (current_token ==  FPARENTESES) {
                    eat(FPARENTESES);
                } else {
                    EXPRESSAO();
                    while (current_token == VIRGULA) {
                        eat(VIRGULA);
                        EXPRESSAO();
                    }
                    eat(FPARENTESES);
                }
            }
            break;
        case NUMBER:
            eat(NUMBER);
            break;
        case APARENTESES:
            eat(APARENTESES);
            EXPRESSAO();
            eat(FPARENTESES);
            break;
        case NOT:
            eat(NOT);
            FATOR();
            break;
        default:
            cout << "opopopoplop" << endl;
            break;
    }
}

int main (int argc, char **argv) {
    if (argc != 3) {
        cerr << "Uso: lexico [Nome do Arquivo de Entrada] [Nome do Arquivo de Saida]" << endl;
        return(1);
    }
    file.open(argv[1], fstream::in);
    output.open(argv[2], fstream::out);

    if (!file.is_open()) {
        cout << "file not open (entrada)";
        return 0;
    }

    if (!output.is_open()) {
        cout << "file not open (saida)";
        return 0;
    }
    getToken();
    PROGRAMA();

    file.close();
    output.close();
    return 1;
}
