#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "AST.cpp"

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
#define AND 16
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
ASTNode* parent_node;
fstream input;
fstream output;

void PROGRAMA();
void BLOCO();
void PARAMETROS_FORMAIS();
void SUB_PARAMETROS_FORMAIS();
void COMANDO();
void VARIAVEL();
void COMANDO_SEM_ROTULO();
void EXPRESSAO();
void EXPRESSAO_SIMPLES();
void TERMO();
void FATOR();


int getToken() {
    if (!input.eof()) {
        input >> current_token;
        return current_token;
    } else return 0;
}

void eat(int token) {
    string PrintToken[] = { "erro","PROGRAM","LABEL","TYPE","VAR","PROCEDURE","FUNCTION","BEGIN","END",
                            "IF","THEN","ELSE","WHILE","DO","OR","DIV","AND","NOT","PONTOVIRGULA",
                            "PONTO","VIRGULA","DOISPONTOS","APARENTESES","FPARENTESES","IGUAL",
                            "MENOR","MAIOR","MAIS","MENOS","ASTERISCO","ACOLCHETES","FCOLCHETES",
                            "DOISPONTOSIGUAL","MENORMAIOR","MENORIGUAL","MAIORIGUAL","IDENTIFICADOR","NUMERO",};

    if (token == current_token) {
        (*parent_node).push_child(PrintToken[current_token]);
        cout << "Consumindo: [" << PrintToken[current_token] << "] (" << current_token << ")" << endl;
        current_token = getToken();
    } else {
        cout << "Erro: Consumindo=>[" << PrintToken[current_token] << "]  Esperado=>[" << PrintToken[token] << "] \n";
        current_token = getToken();
    }
}

void PROGRAMA() {
    ASTNode *tree = new ASTNode("PROGRAMA()");
    parent_node = tree;

    current_token = getToken();
    eat(PROGRAM);
    eat(IDENTIFICADOR);
    eat(PONTOVIRGULA);
    BLOCO();
    eat(PONTO);
    parent_node = tree;
}

void BLOCO() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("BLOCO()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == LABEL) {
        eat(LABEL);
        eat(NUMERO);
        while (current_token == VIRGULA) {
            eat(VIRGULA);
            eat(NUMERO);
        }
        eat(PONTOVIRGULA);
        BLOCO();

    } else if (current_token == TYPE) {
        eat(TYPE);
        while (current_token == IDENTIFICADOR) {
            eat(IDENTIFICADOR);
            eat(IGUAL);
            eat(IDENTIFICADOR);
            eat(PONTOVIRGULA);
        }
        BLOCO();

    } else if (current_token == VAR) {
        eat(VAR);
        while (current_token == IDENTIFICADOR) {
            eat(IDENTIFICADOR);
            while (current_token == VIRGULA) {
                eat(VIRGULA);
                eat(IDENTIFICADOR);
            }
            eat(DOISPONTOS);
            eat(IDENTIFICADOR);
            eat(PONTOVIRGULA);
        }
        BLOCO();

    } else if (current_token == PROCEDURE) {
        eat(PROCEDURE);
        eat(IDENTIFICADOR);
        PARAMETROS_FORMAIS();
        eat(PONTOVIRGULA);
        BLOCO();
        eat(PONTOVIRGULA);
        BLOCO();

    } else if (current_token == FUNCTION) {
        eat(FUNCTION);
        eat(IDENTIFICADOR);
        PARAMETROS_FORMAIS();
        eat(DOISPONTOS);
        eat(IDENTIFICADOR);
        eat(PONTOVIRGULA);
        BLOCO();
        eat(PONTOVIRGULA);
        BLOCO();
    } else if (current_token == BEGIN) {
        eat(BEGIN);
        COMANDO();
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            COMANDO();
        }
        eat(END);
    }
    parent_node = aux;
}

void PARAMETROS_FORMAIS() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("PARAMATROS-FORMAIS()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    eat(APARENTESES);
    if (current_token == FPARENTESES) {
        eat(FPARENTESES);
    } else {
        SUB_PARAMETROS_FORMAIS();
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            SUB_PARAMETROS_FORMAIS();
        }
        eat(FPARENTESES);
    }
    parent_node = aux;
}

void SUB_PARAMETROS_FORMAIS() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("SUB-PARAMETROS-FOPRMAIS()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == IDENTIFICADOR) {
        eat(IDENTIFICADOR);
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            eat(IDENTIFICADOR);
        }
        eat(DOISPONTOS);
        eat(IDENTIFICADOR);

    } else if (current_token == VAR) {
        eat(VAR);
        eat(IDENTIFICADOR);
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            eat(IDENTIFICADOR);
        }
        eat(DOISPONTOS);
        eat(IDENTIFICADOR);

    } else if (current_token == FUNCTION) {
        eat(FUNCTION);
        eat(IDENTIFICADOR);
        PARAMETROS_FORMAIS();
        eat(DOISPONTOS);
        eat(IDENTIFICADOR);

    } else if (current_token == PROCEDURE) {
        eat(PROCEDURE);
        eat(IDENTIFICADOR);
        PARAMETROS_FORMAIS();
    } else {
        eat(0);
    }
    parent_node = aux;
}

void COMANDO() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("COMANDO()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == NUMERO) {
        eat(NUMERO);
        eat(DOISPONTOS);
    }
    COMANDO_SEM_ROTULO();
    parent_node = aux;
}

void COMANDO_SEM_ROTULO() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("COMANDO-SEM-ROTULO()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == IDENTIFICADOR) {
        eat(IDENTIFICADOR);
        if (current_token == DOISPONTOSIGUAL) {
            eat(DOISPONTOSIGUAL);
            EXPRESSAO();

        } else if (current_token == APARENTESES) {
            eat(APARENTESES);
            if (current_token == FPARENTESES) {
                eat(FPARENTESES);
            } else {
                EXPRESSAO();
                while (current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
            }

        } else if (current_token == ACOLCHETES) {
            while (current_token == ACOLCHETES) {
                eat(ACOLCHETES);
                EXPRESSAO();
                while (current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FCOLCHETES);
            }
        }

    } else if (current_token == BEGIN) {
        eat(BEGIN);
        COMANDO_SEM_ROTULO();
        while (current_token == PONTOVIRGULA) {
            eat(PONTOVIRGULA);
            COMANDO_SEM_ROTULO();
        }
        eat(END);

    } else if (current_token == IF) {
        eat(IF);
        EXPRESSAO();
        eat(THEN);
        COMANDO_SEM_ROTULO();
        if (current_token == ELSE) {
            eat(ELSE);
            COMANDO_SEM_ROTULO();
        }

    }else if (current_token == WHILE) {
        eat(WHILE);
        EXPRESSAO();
        eat(DO);
        COMANDO_SEM_ROTULO();
    }
    parent_node = aux;
}

void EXPRESSAO() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("EXPRESSAO()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    EXPRESSAO_SIMPLES();
    if (current_token == IGUAL) {
        eat(IGUAL);
        EXPRESSAO_SIMPLES();
    } else if (current_token == MENORMAIOR) {
        eat(MENORMAIOR);
        EXPRESSAO_SIMPLES();
    } else if (current_token == MENOR) {
        eat(MENOR);
        EXPRESSAO_SIMPLES();
    } else if (current_token == MENORIGUAL) {
        eat(MENORIGUAL);
        EXPRESSAO_SIMPLES();
    } else if (current_token == MAIORIGUAL) {
        eat(MAIORIGUAL);
        EXPRESSAO_SIMPLES();
    } else if (current_token == MAIOR) {
        eat(MAIOR);
        EXPRESSAO_SIMPLES();
    }
    parent_node = aux;
}

void EXPRESSAO_SIMPLES() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("EXPRESSAO-SIMPLES()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == MAIS) {
        eat(MAIS);
    } else if (current_token == MENOS) {
        eat(MENOS);
    }
    TERMO();
    while (current_token == MAIS || current_token == MENOS || current_token == OR) {
        if (current_token == MAIS) {
            eat(MAIS);
        } else if (current_token == MENOS) {
            eat(MENOS);
        } else if (current_token == OR){
            eat(OR);
        }
        TERMO();
    }
    parent_node = aux;
}

void TERMO() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("TERMO()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    FATOR();
    while (current_token == ASTERISCO || current_token == DIV || current_token == AND) {
        if (current_token == ASTERISCO) {
            eat(ASTERISCO);
        } else if (current_token == DIV) {
            eat(DIV);
        } else if (current_token == AND){
            eat(AND);
        }
        FATOR();
    }
    parent_node = aux;
}

void FATOR() {
    ASTNode *aux = parent_node;
    ASTNode *tree = new ASTNode("FATOR()");
    (*parent_node).push_child(tree);
    parent_node = tree;

    if (current_token == IDENTIFICADOR) {
        eat(IDENTIFICADOR);
        if (current_token == APARENTESES) {
            eat(APARENTESES);
            if (current_token == FPARENTESES) {
                eat(FPARENTESES);
            } else {
                EXPRESSAO();
                while (current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
            }

        } else if (current_token == ACOLCHETES) {
            while (current_token == ACOLCHETES) {
                eat(ACOLCHETES);
                EXPRESSAO();
                while (current_token == VIRGULA) {
                    eat(VIRGULA);
                    EXPRESSAO();
                }
                eat(FCOLCHETES);
            }
        }

    } else if (current_token == APARENTESES) {
        eat(APARENTESES);
        EXPRESSAO();
        eat(FPARENTESES);
    } else if (current_token == NOT) {
        eat(NOT);
        FATOR();
    } else if (current_token == NUMERO) {
        eat(NUMERO);
    } else {
        eat(0);
    }
    parent_node = aux;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        cerr << "Uso: Sintatico [Nome do Arquivo de Entrada] [Nome do Arquivo de Saida]" << endl;
        return(1);
    }

    input.open(argv[1], fstream::in);
    output.open(argv[2], fstream::out);

    /*
    input.open("entrada_syntax.txt", fstream::in);
    output.open("saida_syntax.txt", fstream::out);
    */

    if (!input.is_open()) {
        cout << "file not open (entrada)";
        return 0;
    }

    if (!output.is_open()) {
        cout << "file not open (saida)";
        return 0;
    }

    PROGRAMA();
    output << (*parent_node).print();
    cout << (*parent_node).print();
    return 1;
}
