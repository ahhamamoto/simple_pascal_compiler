#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define PROGRAM 1
#define LABEL 2
#define TYPE 3
#define VAR 4
#define START_PROCEDURE 5
#define FUNCTION 6
#define BEGIN 7
#define WHILE 8
#define NOT 9
#define LPARENTHESES 10
#define RPARENTHESES 11
#define SEMICOLON 12
#define PERIOD 13
#define COMMA 14
#define EQUAL 15
#define COLON 16
#define LBRACKET 17
#define RBRACKET 18
#define DBPERIOD 19
#define ELSE 20
#define DIV 21
#define AND 22
#define ASTERISK 23
#define GOTO 24
#define IDENTIFIER 25
#define NUMBER 26
#define ARRAY 27
#define END_PROCEDURE 28
#define IF 29
#define THEN 30
#define END 31
#define OF 32
#define ATTRIB 33
#define DO 34
#define LESSER_GREATER 35
#define LESSER 36
#define LESS_EQUAL 37
#define GREAT_EQUAL 38
#define GREATER 39
#define PLUS 40
#define MINUS 41
#define OR 42

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
            eat(LPARENTHESES);
            eat(IDENTIFIER);
            while ( current_token == COMMA ) {
                eat(COMMA);
                eat(IDENTIFIER);
            }
            eat(RPARENTHESES);
            eat(SEMICOLON);
            BLOCO();
            eat(PERIOD);
            break;
        default:
            cout << "expected 'program...'\n";
    }
}

void BLOCO() {
    if (current_token == LABEL) {
        eat(LABEL);
        eat(NUMBER);
        while ( current_token == COMMA ) {
            eat(COMMA);
            eat(NUMBER);
        }
        eat(SEMICOLON);
    }

    if (current_token == TYPE) {
        eat(TYPE);
        do {
            eat(IDENTIFIER);
            eat(EQUAL);
            TIPO();
            eat(SEMICOLON);
        } while(current_token == IDENTIFIER);
    }

    if (current_token == VAR) {
        eat(VAR);
        do {
            eat(IDENTIFIER);
            while (current_token == COMMA) {
                eat(COMMA);
                eat(IDENTIFIER);
            }
            eat(COLON);
            TIPO();
            eat(SEMICOLON);
        } while(current_token == IDENTIFIER);
    }

    if (current_token == START_PROCEDURE || current_token == FUNCTION) {
        do {
            if (current_token == START_PROCEDURE) {
                eat(START_PROCEDURE);
                eat(IDENTIFIER);
                if (current_token == LPARENTHESES)
                    PARAM_FORMAIS();
            } else if (current_token == FUNCTION) {
                eat(FUNCTION);
                eat(IDENTIFIER);
                if (current_token == LPARENTHESES)
                    PARAM_FORMAIS();
                eat(COLON);
                eat(IDENTIFIER);
            }

            eat(SEMICOLON);
            BLOCO();
            eat(SEMICOLON);
        } while (current_token == START_PROCEDURE || current_token == FUNCTION);
    }

    if (current_token == BEGIN) {
        eat(BEGIN);
        COMANDO();
        while (current_token == COMMA) {
            eat(COMMA);
            COMANDO();
        }
        eat(END);
    }
}

void TIPO() {
    switch (current_token) {
        case IDENTIFIER:
            eat(IDENTIFIER);
            break;
        case ARRAY:
            eat(ARRAY);
            eat(LBRACKET);
            eat(NUMBER);
            eat(DBPERIOD);
            eat(NUMBER);
            while (current_token == COMMA) {
                eat(COMMA);
                eat(NUMBER);
                eat(DBPERIOD);
                eat(NUMBER);
            }
            eat(RBRACKET);
            eat(OF);
            TIPO();
            break;
    }
}

void PARAM_FORMAIS() {
    eat(LPARENTHESES);
    do {
        switch (current_token) {
            case VAR:
                eat(VAR);
            case IDENTIFIER:
                eat(IDENTIFIER);
                while (current_token == COMMA ) {
                    eat(COMMA);
                    eat(IDENTIFIER);
                }
                eat(COLON);
                eat(IDENTIFIER);
                break;
            case FUNCTION:
                eat(FUNCTION);
                eat(IDENTIFIER);
                while (current_token == COMMA) {
                    eat(COMMA);
                    eat(IDENTIFIER);
                }
                eat(COLON);
                eat(IDENTIFIER);
                break;
            case START_PROCEDURE:
                eat(START_PROCEDURE);
                eat(IDENTIFIER);
                while (current_token == COMMA) {
                    eat(COMMA);
                    eat(IDENTIFIER);
                }
                break;
        }
        eat(SEMICOLON);
    } while (current_token == VAR || current_token == FUNCTION || current_token == START_PROCEDURE);
    eat(RPARENTHESES);
}

void COMANDO () {
    if (current_token == NUMBER) {
        eat(NUMBER);
        eat(COLON);
    }
    COM_SEM_ROTULO();
}

void COM_SEM_ROTULO() {
    switch (current_token) {
        case IDENTIFIER:
            eat(IDENTIFIER);
            if (current_token == ATTRIB) {
                eat(ATTRIB);
                EXPRESSAO();
            } else if ( current_token == LBRACKET ) {
                eat(LBRACKET);
                EXPRESSAO();
                while (current_token == COMMA) {
                    eat(COMMA);
                    EXPRESSAO();
                }
                eat(RBRACKET);
                if (current_token == ATTRIB) {
                    eat(ATTRIB);
                    EXPRESSAO();
                }
            } else if (current_token == LPARENTHESES) {
                eat(LPARENTHESES);
                EXPRESSAO();
                while (current_token == COMMA) {
                    eat(COMMA);
                    EXPRESSAO();
                }
                eat(RPARENTHESES);
            }
            break;
        case GOTO:
            eat(GOTO);
            eat(NUMBER);
            break;
        case BEGIN:
            eat(BEGIN);
            COMANDO();
            if (current_token == SEMICOLON) {
                eat(SEMICOLON);
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
        case EQUAL:
            eat(EQUAL);
            break;
        case LESSER_GREATER:
            eat(LESSER_GREATER);
            break;
        case LESSER:
            eat(LESSER);
            break;
        case LESS_EQUAL:
            eat(LESS_EQUAL);
            break;
        case GREAT_EQUAL:
            eat(GREAT_EQUAL);
            break;
        case GREATER:
            eat(GREATER);
            break;
    }
    EXP_SIMPLES();
}

void EXP_SIMPLES() {
    if (current_token == PLUS) eat(PLUS);
    else if (current_token == MINUS) eat(MINUS);
    TERMO();
    while (current_token == PLUS || current_token == MINUS || current_token == OR) {
        switch (current_token) {
            case PLUS:
                eat(PLUS);
                break;
            case MINUS:
                eat(MINUS);
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
    while (current_token == ASTERISK || current_token == DIV || current_token == AND) {
        switch (current_token) {
            case PLUS:
                eat(ASTERISK);
                break;
            case MINUS:
                eat(DIV);
                break;
            case OR:
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
            if (current_token == LBRACKET) {
                eat(LBRACKET);
                EXPRESSAO();
                while (current_token == COMMA) {
                    eat(COMMA);
                    EXPRESSAO();
                }
                eat(RBRACKET);
            } else if (current_token == LPARENTHESES) {
                eat(LPARENTHESES);
                EXPRESSAO();
                while (current_token == COMMA) {
                    eat(COMMA);
                    EXPRESSAO();
                }
                eat(RPARENTHESES);
            }
            break;
        case NUMBER:
            eat(NUMBER);
            break;
        case LPARENTHESES:
            eat(LPARENTHESES);
            EXPRESSAO();
            eat(RPARENTHESES);
            break;
        case NOT:
            eat(NOT);
            FATOR();
            break;
        }
}

int main () {
    file.open("entrada_syntax.txt", fstream::in);
    if (!file.is_open()) {
        cout << "file not open (entrada)";
        return 0;
    }
    getToken();
    PROGRAMA();

    file.close();
    return 1;
}
