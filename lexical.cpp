#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// retorna um vetor com as palavras reservadas
vector<string> reservedWords();

/* start of main */
int main(int argc, char **argv) {
    // caso o numero de parametros nao esteja correto
    if (argc != 3) {
        cerr << "Uso: \tlexical arquivo_de_entrada arquivo_de_saida" << endl;
        return 1;
    }

    // arquivos de entrada e saida
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1]);
    output_file.open(argv[2]);

    // declaracao de variaveis iniciais
    char next_char;

    // inicio do automato
    while (input_file >> noskipws >> next_char) {
        cout << next_char;
    }

    input_file.close();
    output_file.close();
    return 0;
}
/* end of main */

/* start of reservedWords */
vector<string> reservedWords() {
    // adiciona todas as palavras reservadas
    vector<string> reserved;
    reserved.push_back("program");

    return reserved;
}
/* end of reservedWords */
