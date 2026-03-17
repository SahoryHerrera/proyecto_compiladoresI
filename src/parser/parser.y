%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/ast/ast.hpp"

int yylex();
void yyerror(const char *s);
extern int yylineno;

ASTNode* root = nullptr;
%}

%define parse.error verbose

%code requires {
    #include "../src/ast/ast.hpp"
}

%union {
    char* text;
    ASTNode* node;
}

%token FN LET IF ELSE WHILE FOR IN RETURN
%token <text> TYPE
%token <text> IDENTIFIER
%token <text> INT_LITERAL FLOAT_LITERAL BOOL_LITERAL CHAR_LITERAL STRING_LITERAL

%token PLUS MINUS MUL DIV
%token AND OR NOT
%token EQ NEQ LT GT LE GE
%token ASSIGN
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA SEMICOLON COLON
%token ARROW RANGE

%left OR
%left AND
%nonassoc EQ NEQ LT GT LE GE
%left PLUS MINUS
%left MUL DIV
%right NOT
%right UMINUS

%type <node> program function_list function
%type <node> param_list_opt param_list param
%type <text> return_type_opt
%type <node> block stmt_list_opt stmt_list stmt
%type <node> let_stmt assign_stmt return_stmt if_stmt while_stmt for_stmt expr_stmt
%type <node> expr call_expr arg_list_opt arg_list

%%

program:
    function_list
    {
        root = $1;
        $$ = $1;
    }
;

function_list:
    function
    {
        auto* p = new ProgramNode();
        p->add((FunctionNode*)$1);
        $$ = p;
    }
    | function_list function
    {
        ((ProgramNode*)$1)->add((FunctionNode*)$2);
        $$ = $1;
    }
;

function:
    FN IDENTIFIER LPAREN param_list_opt RPAREN return_type_opt block
    {
        $$ = new FunctionNode($2, (ParamListNode*)$4, $6, (BlockNode*)$7);
        free($2);
        free($6);
    }
;

param_list_opt:
    /* empty */
    {
        $$ = new ParamListNode();
    }
    | param_list
    {
        $$ = $1;
    }
;

param_list:
    param
    {
        auto* list = new ParamListNode();
        list->add((ParamNode*)$1);
        $$ = list;
    }
    | param_list COMMA param
    {
        ((ParamListNode*)$1)->add((ParamNode*)$3);
        $$ = $1;
    }
;

param:
    IDENTIFIER COLON TYPE
    {
        $$ = new ParamNode($1, $3);
        free($1);
        free($3);
    }
;

return_type_opt:
    /* empty */
    {
        $$ = strdup("");
    }
    | ARROW TYPE
    {
        $$ = $2;
    }
;

block:
    LBRACE stmt_list_opt RBRACE
    {
        $$ = new BlockNode((StatementListNode*)$2);
    }
;

stmt_list_opt:
    /* empty */
    {
        $$ = new StatementListNode();
    }
    | stmt_list
    {
        $$ = $1;
    }
;

stmt_list:
    stmt
    {
        auto* list = new StatementListNode();
        list->add((StmtNode*)$1);
        $$ = list;
    }
    | stmt_list stmt
    {
        ((StatementListNode*)$1)->add((StmtNode*)$2);
        $$ = $1;
    }
;

stmt:
    let_stmt
    | assign_stmt
    | return_stmt
    | if_stmt
    | while_stmt
    | for_stmt
    | block
    | expr_stmt
;

let_stmt:
    LET IDENTIFIER ASSIGN expr SEMICOLON
    {
        $$ = new LetNode($2, "", (ExprNode*)$4);
        free($2);
    }
    | LET IDENTIFIER COLON TYPE ASSIGN expr SEMICOLON
    {
        $$ = new LetNode($2, $4, (ExprNode*)$6);
        free($2);
        free($4);
    }
;

assign_stmt:
    IDENTIFIER ASSIGN expr SEMICOLON
    {
        $$ = new AssignNode($1, (ExprNode*)$3);
        free($1);
    }
;

return_stmt:
    RETURN SEMICOLON
    {
        $$ = new ReturnNode(nullptr);
    }
    | RETURN expr SEMICOLON
    {
        $$ = new ReturnNode((ExprNode*)$2);
    }
;

if_stmt:
    IF expr block
    {
        $$ = new IfNode((ExprNode*)$2, (BlockNode*)$3, nullptr);
    }
    | IF expr block ELSE block
    {
        $$ = new IfNode((ExprNode*)$2, (BlockNode*)$3, (BlockNode*)$5);
    }
;

while_stmt:
    WHILE expr block
    {
        $$ = new WhileNode((ExprNode*)$2, (BlockNode*)$3);
    }
;

for_stmt:
    FOR IDENTIFIER IN expr RANGE expr block
    {
        $$ = new ForNode($2, (ExprNode*)$4, (ExprNode*)$6, (BlockNode*)$7);
        free($2);
    }
;

expr_stmt:
    expr SEMICOLON
    {
        $$ = new ExprStmtNode((ExprNode*)$1);
    }
;

expr:
    INT_LITERAL
    {
        $$ = new LiteralNode("i32", $1);
        free($1);
    }
    | FLOAT_LITERAL
    {
        $$ = new LiteralNode("f64", $1);
        free($1);
    }
    | BOOL_LITERAL
    {
        $$ = new LiteralNode("bool", $1);
        free($1);
    }
    | CHAR_LITERAL
    {
        $$ = new LiteralNode("char", $1);
        free($1);
    }
    | STRING_LITERAL
    {
        $$ = new LiteralNode("str", $1);
        free($1);
    }
    | IDENTIFIER
    {
        $$ = new IdentifierNode($1);
        free($1);
    }
    | call_expr
    {
        $$ = $1;
    }
    | LPAREN expr RPAREN
    {
        $$ = $2;
    }
    | MINUS expr %prec UMINUS
    {
        $$ = new UnaryOpNode("-", (ExprNode*)$2);
    }
    | NOT expr
    {
        $$ = new UnaryOpNode("!", (ExprNode*)$2);
    }
    | expr PLUS expr
    {
        $$ = new BinaryOpNode("+", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr MINUS expr
    {
        $$ = new BinaryOpNode("-", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr MUL expr
    {
        $$ = new BinaryOpNode("*", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr DIV expr
    {
        $$ = new BinaryOpNode("/", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr EQ expr
    {
        $$ = new BinaryOpNode("==", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr NEQ expr
    {
        $$ = new BinaryOpNode("!=", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr LT expr
    {
        $$ = new BinaryOpNode("<", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr GT expr
    {
        $$ = new BinaryOpNode(">", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr LE expr
    {
        $$ = new BinaryOpNode("<=", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr GE expr
    {
        $$ = new BinaryOpNode(">=", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr AND expr
    {
        $$ = new BinaryOpNode("&&", (ExprNode*)$1, (ExprNode*)$3);
    }
    | expr OR expr
    {
        $$ = new BinaryOpNode("||", (ExprNode*)$1, (ExprNode*)$3);
    }
;

call_expr:
    IDENTIFIER LPAREN arg_list_opt RPAREN
    {
        $$ = new CallNode($1, (ArgListNode*)$3);
        free($1);
    }
;

arg_list_opt:
    /* empty */
    {
        $$ = new ArgListNode();
    }
    | arg_list
    {
        $$ = $1;
    }
;

arg_list:
    expr
    {
        auto* args = new ArgListNode();
        args->add((ExprNode*)$1);
        $$ = args;
    }
    | arg_list COMMA expr
    {
        ((ArgListNode*)$1)->add((ExprNode*)$3);
        $$ = $1;
    }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error sintactico en linea %d: %s\n", yylineno, s);
}