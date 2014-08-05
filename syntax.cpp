#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define PROGRAM "PROGRAM"
#define LABEL "LABEL"
#define TYPE "TYPE"
#define ARRAY "ARRAY"
#define OF "OF"
#define VAR "VAR"
#define PROCEDURE "PROCEDURE"
#define FUNCTION "FUNCTION"
#define BEGIN "BEGIN"
#define END "END"
#define IF "IF"
#define THEN "THEN"
#define ELSE "ELSE"
#define WHILE "WHILE"
#define DO "DO"
#define OR "OR"
#define AND "AND"
#define DIV "DIV"
#define NOT "NOT"
#define IDENTIFIER "IDENTIFIER"
#define NUMBER "NUMBER"
#define APARENTESES "("
#define FPARENTESES ")"
#define PONTOVIRGULA ";"
#define DOISPONTOS ":"
#define MAIS "+"
#define MENOS "-"
#define BARRA "/"
#define ACOLCHETES "["
#define FCOLCHETES "]"
#define VIRGULA ","
#define MAIOR ">"
#define MENOR "<"
#define ASTERISCO "*"
#define IGUAL "="
#define MAIORIGUAL ">="
#define MENORIGUAL "<="
#define ATRIBUICAO ":="
#define MENORMAIOR "<>"

// static const int program = 1, label = 2, type = 3, var = 4, procedure = 5, _function = 6, _begin = 7;
// static const int _while = 8, _not = 9;
// static const int op_parentheses = 10, cl_parentheses = 11, semiCOLON = 12, period = 13, comma = 14;
// static const int _equal = 15, colon = 16, op_bracket = 17, cl_bracket = 18, db_period = 19;
// static const int _else = 20, _div = 21, _and = 22, asterisk = 23, _goto = 24;
// static const int identifier = 25, number = 26, array = 27, _procedure = 28, _if = 29, _then = 30;
// static const int _end = 31, OF = 32, attrib = 33, _do = 34, _lesserGREATER = 35, _lesser = 36, _lessEQUAL = 37;
// static const int _greatEQUAL = 38, _greater = 39, _plus = 40, _minus = 41, _or = 42;
static const string tn[] = {"zero", "program", "label", "type", "var", "procedure", "function", "begin", "while", "not",
                            "(", ")", ";", ".", ",", "=", ":", "[", "]", "..",
                            "else", "div", "and", "*", "goto", "identifier", "number", "array", "procedure", "if",
                            "then", "end", "of", ":=", "do", "<>", "<", "<=",
                            ">=", ">", "+", "-", "or"};

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
    if (token == current_token) {
        current_token = getToken();
        return true;
    } else {
        cout << "eat error. reading '" << tn[current_token] << "'. expecting '" << tn[token] << "'.\n";
        getToken();
        return false;
    }
}

void PROGRAMA() {
    switch (current_token) {
        case PROGRAM:
            eat(PROGRAM);
            eat(IDENTIFIER);
            if(current_token == APARENTESES){
                eat(APARENTESES);
                eat(IDENTIFIER);
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(FPARENTESES);
            }
            eat(PONTOVIRGULA);
            BLOCO();
            break;
        default:
            cout << "expected 'program...'\n";
    }
}

void BLOCO() {
    if (current_token == LABEL) {
        eat(LABEL);
        eat(NUMBER);
        while ( current_token == VIRGULA ) {
            eat(VIRGULA);
            eat(NUMBER);
        }
        eat(PONTOVIRGULA);
    }

    if (current_token == TYPE) {
        eat(TYPE);
        do {
            eat(IDENTIFIER);
            eat(IGUAL);
            TIPO();
            eat(PONTOVIRGULA);
        } while(current_token == IDENTIFIER);
    }

    if (current_token == VAR) {
        eat(VAR);
        while(current_token == IDENTIFIER){
            eat(IDENTIFIER);
            while (current_token == VIRGULA) {
                eat(VIRGULA);
                eat(IDENTIFIER);
            }
            eat(DOISPONTOS);
            TIPO();
            eat(PONTOVIRGULA);
        }
    }

    if (current_token == PROCEDURE || current_token == FUNCTION) {
        while (current_token == PROCEDURE || current_token == FUNCTION){
            if (current_token == PROCEDURE) {
                eat(PROCEDURE);
                eat(IDENTIFIER);
                if(current_token != PONTOVIRGULA)
                    PARAM_FORMAIS();
            } else if (current_token == FUNCTION) {
                eat(FUNCTION);
                eat(IDENTIFIER);
                if (current_token == DOISPONTOS)
                    eat(DOISPONTOS);
                else{
                    PARAM_FORMAIS();
                    eat(DOISPONTOS);
                }
                
                eat(IDENTIFIER);
            }

            eat(SEMICOLON);
            BLOCO();
            eat(SEMICOLON);
        }
    }

    if (current_token == BEGIN) {
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
    switch (current_token) {
            case VAR:
                eat(VAR);
                eat(IDENTIFIER);
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case IDENTIFIER:
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case FUNCTION:
                eat(FUNCTION);
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case PROCEDURE:
                eat(PROCEDURE);
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                break;
        }
    while(current_token == PONTOVIRGULA){
        switch (current_token) {
            case VAR:
                eat(VAR);
                eat(IDENTIFIER);
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case IDENTIFIER:
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case FUNCTION:
                eat(FUNCTION);
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                eat(DOISPONTOS);
                eat(IDENTIFIER);
                break;
            case PROCEDURE:
                eat(PROCEDURE);
                eat(IDENTIFIER);
                while (current_token == VIRGULA ) {
                    eat(VIRGULA);
                    eat(IDENTIFIER);
                }
                break;
        }
    }
    eat(FPARENTESES);;
}

void COMANDO () {
    if (current_token == NUMBER) {
        eat(NUMBER);
        eat(DOISPONTOS);
    }
    COM_SEM_ROTULO();
}

void COM_SEM_ROTULO() {
    switch (current_token) {
        case IDENTIFIER:
            eat(IDENTIFIER);
            if(current_token == ATRIBUICAO) {
                eat(ATRIBUICAO);
                EXPRESSAO();
            }
            else if(current_token == ACOLCHETES) {
                eat(ACOLCHETES);
                EXPRESSAO();
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FCOLCHETES);
            }
            else if(current_token == APARENTESES) {
                eat(APARENTESES);
                EXPRESSAO();
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FPARENTESES);
            }
            break;
        case BEGIN:
            eat(BEGIN);
            COMANDO();
            if (current_token == PONTOVIRGULA) {
                eat(PONTOVIRGULA);
                COMANDO();
            }
            eat(END);
            break;
        case IF:
            eat (IF);
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
            cout << "expected...";
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
            break;
    }
}

void EXP_SIMPLES() {
    if (current_token == PLUS)
        eat(PLUS);
    else if(current_token == MINUS)
        eat(MINUS);
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
            if(current_token == ACOLCHETES) {
                eat(ACOLCHETES);
                EXPRESSAO();
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FCOLCHETES);
            }
            else if(current_token == APARENTESES) {
                eat(APARENTESES);
                EXPRESSAO();
                while(current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FPARENTESES);
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
        }
}

int main () {
    file.open("outputlexic.txt", fstream::in);
    output.open("outputsyntax.txt", fstream::out);
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
