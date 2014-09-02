#include <list>
#include <string>
using namespace std;

class ASTNode {
    public:
    string type;
    list<ASTNode*> children;

    public:

    ASTNode(string n_type) {
        type = n_type;
    }

    ASTNode();

    ~ASTNode() {
        for (list<ASTNode*>::iterator it = children.begin(); it != children.end(); it++) {
            delete(*it);
        }
    }

    void push_child(string c_type) {
        ASTNode *a = new ASTNode(c_type);
        children.push_back(a);
    }

    void push_child(ASTNode* n_node) {
        children.push_back(n_node);
    }

    string print() {
        string return_string = "[" + type;
        for (list<ASTNode*>::iterator it = children.begin(); it != children.end(); it++) {
            return_string += (*(*it)).print();
        }
        return_string.push_back(']');
        return return_string;
    }
};
