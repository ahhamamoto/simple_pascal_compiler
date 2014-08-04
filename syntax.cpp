#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

static const int program = 1, label = 2, type = 3, var = 4, procedure = 5, _function = 6, _begin = 7;
static const int _while = 8, _not = 9;
static const int op_parentheses = 10, cl_parentheses = 11, semicolon = 12, period = 13, comma = 14;
static const int _equal = 15, colon = 16, op_bracket = 17, cl_bracket = 18, db_period = 19;
static const int _else = 20, _div = 21, _and = 22, asterisk = 23, _goto = 24;
static const int identifier = 25, number = 26, array = 27, _procedure = 28, _if = 29, _then = 30;
static const int _end = 31, of = 32, attrib = 33, _do = 34, _lesser_greater = 35, _lesser = 36, _less_equal = 37;
static const int _great_equal = 38, _greater = 39, _plus = 40, _minus = 41, _or = 42;
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
        case program:
            eat(program);
            eat(identifier);
            eat(op_parentheses);
            eat(identifier);
            while ( current_token == comma ) {
                eat(comma);
                eat(identifier);
            }
            eat(cl_parentheses);
            eat(semicolon);
            BLOCO();
            eat(period);
            break;
        default:
            cout << "expected 'program...'\n";
    }
}

void BLOCO() {
    if (current_token == label) {
        eat(label);
        eat(number);
        while ( current_token == comma ) {
            eat(comma);
            eat(number);
        }
        eat(semicolon);
    }

    if (current_token == type) {
        eat(type);
        do {
            eat(identifier);
            eat(_equal);
            TIPO();
            eat(semicolon);
        } while(current_token == identifier);
    }

    if (current_token == var) {
        eat(var);
        do {
            eat(identifier);
            while (current_token == comma) {
                eat(comma);
                eat(identifier);
            }
            eat(colon);
            TIPO();
            eat(semicolon);
        } while(current_token == identifier);
    }

    if (current_token == procedure || current_token == _function) {
        do {
            if (current_token == procedure) {
                eat(procedure);
                eat(identifier);
                if (current_token == op_parentheses)
                    PARAM_FORMAIS();
            } else if (current_token == _function) {
                eat(_function);
                eat(identifier);
                if (current_token == op_parentheses)
                    PARAM_FORMAIS();
                eat(colon);
                eat(identifier);
            }

            eat(semicolon);
            BLOCO();
            eat(semicolon);
        } while (current_token == procedure || current_token == _function);
    }

    if (current_token == _begin) {
        eat(_begin);
        COMANDO();
        while (current_token == comma) {
            eat(comma);
            COMANDO();
        }
        eat(_end);
    }
}

void TIPO() {
    switch (current_token) {
        case identifier:
            eat(identifier);
            break;
        case array:
            eat(array);
            eat(op_bracket);
            eat(number);
            eat(db_period);
            eat(number);
            while (current_token == comma) {
                eat(comma);
                eat(number);
                eat(db_period);
                eat(number);
            }
            eat(cl_bracket);
            eat(of);
            TIPO();
            break;
    }
}

void PARAM_FORMAIS() {
    eat(op_parentheses);
    do {
        switch (current_token) {
            case var:
                eat(var);
            case identifier:
                eat(identifier);
                while (current_token == comma ) {
                    eat(comma);
                    eat(identifier);
                }
                eat(colon);
                eat(identifier);
                break;
            case _function:
                eat(_function);
                eat(identifier);
                while (current_token == comma) {
                    eat(comma);
                    eat(identifier);
                }
                eat(colon);
                eat(identifier);
                break;
            case procedure:
                eat(procedure);
                eat(identifier);
                while (current_token == comma) {
                    eat(comma);
                    eat(identifier);
                }
                break;
        }
        eat(semicolon);
    } while (current_token == var || current_token == _function || current_token == procedure);
    eat(cl_parentheses);
}

void COMANDO () {
    if (current_token == number) {
        eat(number);
        eat(colon);
    }
    COM_SEM_ROTULO();
}

void COM_SEM_ROTULO() {
    switch (current_token) {
        case identifier:
            eat(identifier);
            if (current_token == attrib) {
                eat(attrib);
                EXPRESSAO();
            } else if ( current_token == op_bracket ) {
                eat(op_bracket);
                EXPRESSAO();
                while (current_token == comma) {
                    eat(comma);
                    EXPRESSAO();
                }
                eat(cl_bracket);
                if (current_token == attrib) {
                    eat(attrib);
                    EXPRESSAO();
                }
            } else if (current_token == op_parentheses) {
                eat(op_parentheses);
                EXPRESSAO();
                while (current_token == comma) {
                    eat(comma);
                    EXPRESSAO();
                }
                eat(cl_parentheses);
            }
            break;
        case _goto:
            eat(_goto);
            eat(number);
            break;
        case _begin:
            eat(_begin);
            COMANDO();
            if (current_token == semicolon) {
                eat(semicolon);
                COMANDO();
            }
            eat(_end);
            break;
        case _if:
            eat (_if);
            EXPRESSAO();
            eat(_then);
            COM_SEM_ROTULO();
            if (current_token == _else) {
                eat(_else);
                COM_SEM_ROTULO();
            }
            break;
        case _while:
            eat(_while);
            EXPRESSAO();
            eat(_do);
            COM_SEM_ROTULO();
            break;
        default:
            cout << "expected...";
    }
}

void EXPRESSAO() {
    EXP_SIMPLES();
    switch (current_token) {
        case _equal:
            eat(_equal);
            break;
        case _lesser_greater:
            eat(_lesser_greater);
            break;
        case _lesser:
            eat(_lesser);
            break;
        case _less_equal:
            eat(_less_equal);
            break;
        case _great_equal:
            eat(_great_equal);
            break;
        case _greater:
            eat(_greater);
            break;
    }
    EXP_SIMPLES();
}

void EXP_SIMPLES() {
    if (current_token == _plus) eat(_plus);
    else if (current_token == _minus) eat(_minus);
    TERMO();
    while (current_token == _plus || current_token == _minus || current_token == _or) {
        switch (current_token) {
            case _plus:
                eat(_plus);
                break;
            case _minus:
                eat(_minus);
                break;
            case _or:
                eat(_or);
                break;
        }
        TERMO();
    }
}

void TERMO() {
    FATOR();
    while (current_token == asterisk || current_token == _div || current_token == _and) {
        switch (current_token) {
            case _plus:
                eat(asterisk);
                break;
            case _minus:
                eat(_div);
                break;
            case _or:
                eat(_and);
                break;
        }
        FATOR();
    }
}

void FATOR() {
    switch (current_token) {
        case identifier:
            eat(identifier);
            if (current_token == op_bracket) {
                eat(op_bracket);
                EXPRESSAO();
                while (current_token == comma) {
                    eat(comma);
                    EXPRESSAO();
                }
                eat(cl_bracket);
            } else if (current_token == op_parentheses) {
                eat(op_parentheses);
                EXPRESSAO();
                while (current_token == comma) {
                    eat(comma);
                    EXPRESSAO();
                }
                eat(cl_parentheses);
            }
            break;
        case number:
            eat(number);
            break;
        case op_parentheses:
            eat(op_parentheses);
            EXPRESSAO();
            eat(cl_parentheses);
            break;
        case _not:
            eat(_not);
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
