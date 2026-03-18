#include <iostream>
#include <cstdio>
#include "ast/ast.hpp"

using namespace std;

extern int   yyparse();
extern FILE* yyin;
extern int   yylineno;

extern ProgramNode* ast_root;

static void sep(char c = '=', int w = 58) {
    for (int i = 0; i < w; i++) cout << c;
    cout << '\n';
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <archivo.rs>\n";
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        cerr << "Error: No se pudo abrir '" << argv[1] << "'\n";
        return 1;
    }

    sep();
    cout << "  Compilador Rust (subset) - Compiladores I UNITEC\n";
    cout << "  Archivo: " << argv[1] << "\n";
    sep();

    cout << "\n###TOKENS###\n";
    cout << "  [linea col]   tipo              valor\n";
    sep('-', 58);

    int result = yyparse();

    cout << "\n###AST###\n";
    sep('-', 58);

    if (result == 0 && ast_root != nullptr) {
        ast_root->print(0);
        delete ast_root;
        ast_root = nullptr;
    }

    cout << "\n###FIN###\n";
    sep();
    if (result == 0)
        cout << "  RESULTADO: Analisis completado exitosamente\n";
    else
        cout << "  RESULTADO: Se encontraron errores (linea " << yylineno << ")\n";
    sep();
    cout << "\n";

    fclose(yyin);
    return result;
}
