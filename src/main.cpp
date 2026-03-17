#include <cstdio>
#include <iostream>
#include "ast/ast.hpp"

extern int yyparse();
extern FILE* yyin;
extern ASTNode* root;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: ./build/compiler <archivo.rs>\n";
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        std::cerr << "No se pudo abrir archivo: " << argv[1] << "\n";
        return 1;
    }

    int result = yyparse();
    fclose(yyin);

    if (result == 0) {
        std::cout << "Parsing exitoso\n";
        if (root) {
            root->print();
            delete root;
            root = nullptr;
        }
        return 0;
    }

    return 1;
}