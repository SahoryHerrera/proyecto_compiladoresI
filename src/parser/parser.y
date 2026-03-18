%{
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

int  yylex();
void yyerror(const char* s);

extern int   yylineno;
extern int   yycol;
extern FILE* yyin;

/* Incluir AST solo en el .c, no se propaga al .h */
#include "ast.hpp"

ProgramNode* ast_root = nullptr;
%}

/* El union SOLO usa tipos primitivos - ningun puntero a clase del AST
   Esto evita que parser.tab.h necesite incluir ast.hpp */
%union {
    char*  str_val;
    void*  node;
}

%token <str_val> IDENTIFIER
%token <str_val> TYPE
%token <str_val> INT_LIT
%token <str_val> FLOAT_LIT
%token <str_val> STR_LIT
%token <str_val> CHAR_LIT
%token <str_val> BOOL_LIT

%token FN LET MUT IF ELSE WHILE FOR IN RETURN PRINTLN_MACRO
%token PLUS MINUS MUL DIV MOD
%token ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token EQ NEQ LT GT LE GE
%token AND OR NOT
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET
%token COMMA SEMICOLON COLON ARROW DOT_DOT

%type <node>     program function block statements statement
%type <node>     let_stmt assign_stmt if_stmt while_stmt
%type <node>     for_stmt return_stmt expr_stmt println_stmt
%type <node>     expression call params param_list param
%type <node>     args arg_list
%type <str_val>  opt_mut opt_type ret_type

%right ASSIGN PLUS_ASSIGN MINUS_ASSIGN MUL_ASSIGN DIV_ASSIGN
%left  OR
%left  AND
%left  EQ NEQ
%left  LT GT LE GE
%left  PLUS MINUS
%left  MUL DIV MOD
%right NOT UMINUS

%start program

%%

program
    : /* vacio */
        {
            ProgramNode* p = new ProgramNode();
            ast_root = p;
            $$ = p;
        }
    | program function
        {
            ProgramNode* p = static_cast<ProgramNode*>($1);
            p->add(static_cast<FunctionNode*>($2));
            ast_root = p;
            $$ = p;
        }
    ;

function
    : FN IDENTIFIER LPAREN params RPAREN ret_type LBRACE block RBRACE
        {
            string name = $2;
            string ret  = $6 ? string($6) : string("");
            $$ = new FunctionNode(name,
                     static_cast<ParamListNode*>($4),
                     ret,
                     static_cast<BlockNode*>($8));
            free($2);
            if ($6) free($6);
        }
    ;

ret_type
    : /* vacio */      { $$ = nullptr; }
    | ARROW TYPE       { $$ = $2;      }
    | ARROW IDENTIFIER { $$ = $2;      }
    ;

params
    : /* vacio */ { $$ = new ParamListNode(); }
    | param_list  { $$ = $1;                  }
    ;

param_list
    : param
        {
            ParamListNode* pl = new ParamListNode();
            pl->add(static_cast<ParamNode*>($1));
            $$ = pl;
        }
    | param_list COMMA param
        {
            static_cast<ParamListNode*>($1)->add(static_cast<ParamNode*>($3));
            $$ = $1;
        }
    ;

param
    : IDENTIFIER COLON TYPE
        { $$ = new ParamNode(string($1), string($3)); free($1); free($3); }
    | IDENTIFIER COLON IDENTIFIER
        { $$ = new ParamNode(string($1), string($3)); free($1); free($3); }
    ;

block
    : /* vacio */
        { $$ = new BlockNode(new StatementListNode()); }
    | statements
        { $$ = new BlockNode(static_cast<StatementListNode*>($1)); }
    ;

statements
    : statement
        {
            StatementListNode* sl = new StatementListNode();
            if ($1) sl->add(static_cast<StmtNode*>($1));
            $$ = sl;
        }
    | statements statement
        {
            if ($2) static_cast<StatementListNode*>($1)->add(static_cast<StmtNode*>($2));
            $$ = $1;
        }
    ;

statement
    : let_stmt     { $$ = $1; }
    | assign_stmt  { $$ = $1; }
    | if_stmt      { $$ = $1; }
    | while_stmt   { $$ = $1; }
    | for_stmt     { $$ = $1; }
    | return_stmt  { $$ = $1; }
    | println_stmt { $$ = $1; }
    | expr_stmt    { $$ = $1; }
    ;

opt_mut
    : /* vacio */ { $$ = nullptr;       }
    | MUT         { $$ = strdup("mut"); }
    ;

opt_type
    : /* vacio */      { $$ = nullptr; }
    | COLON TYPE       { $$ = $2;      }
    | COLON IDENTIFIER { $$ = $2;      }
    ;

let_stmt
    : LET opt_mut IDENTIFIER opt_type ASSIGN expression SEMICOLON
        {
            string name = $3;
            string type = $4 ? string($4) : string("");
            if ($2) name = "mut " + name;
            $$ = new LetNode(name, type, static_cast<ExprNode*>($6));
            free($3);
            if ($2) free($2);
            if ($4) free($4);
        }
    ;

assign_stmt
    : IDENTIFIER ASSIGN expression SEMICOLON
        {
            $$ = new AssignNode(string($1), static_cast<ExprNode*>($3));
            free($1);
        }
    | IDENTIFIER PLUS_ASSIGN expression SEMICOLON
        {
            ExprNode* id = new IdentifierNode(string($1));
            $$ = new AssignNode(string($1), new BinaryOpNode("+", id, static_cast<ExprNode*>($3)));
            free($1);
        }
    | IDENTIFIER MINUS_ASSIGN expression SEMICOLON
        {
            ExprNode* id = new IdentifierNode(string($1));
            $$ = new AssignNode(string($1), new BinaryOpNode("-", id, static_cast<ExprNode*>($3)));
            free($1);
        }
    | IDENTIFIER MUL_ASSIGN expression SEMICOLON
        {
            ExprNode* id = new IdentifierNode(string($1));
            $$ = new AssignNode(string($1), new BinaryOpNode("*", id, static_cast<ExprNode*>($3)));
            free($1);
        }
    | IDENTIFIER DIV_ASSIGN expression SEMICOLON
        {
            ExprNode* id = new IdentifierNode(string($1));
            $$ = new AssignNode(string($1), new BinaryOpNode("/", id, static_cast<ExprNode*>($3)));
            free($1);
        }
    ;

if_stmt
    : IF expression LBRACE block RBRACE
        {
            $$ = new IfNode(static_cast<ExprNode*>($2),
                            static_cast<BlockNode*>($4), nullptr);
        }
    | IF expression LBRACE block RBRACE ELSE LBRACE block RBRACE
        {
            $$ = new IfNode(static_cast<ExprNode*>($2),
                            static_cast<BlockNode*>($4),
                            static_cast<BlockNode*>($8));
        }
    | IF expression LBRACE block RBRACE ELSE if_stmt
        {
            StatementListNode* sl = new StatementListNode();
            sl->add(static_cast<StmtNode*>($7));
            $$ = new IfNode(static_cast<ExprNode*>($2),
                            static_cast<BlockNode*>($4),
                            new BlockNode(sl));
        }
    ;

while_stmt
    : WHILE expression LBRACE block RBRACE
        {
            $$ = new WhileNode(static_cast<ExprNode*>($2),
                               static_cast<BlockNode*>($4));
        }
    ;

for_stmt
    : FOR IDENTIFIER IN expression DOT_DOT expression LBRACE block RBRACE
        {
            $$ = new ForNode(string($2),
                             static_cast<ExprNode*>($4),
                             static_cast<ExprNode*>($6),
                             static_cast<BlockNode*>($8));
            free($2);
        }
    ;

return_stmt
    : RETURN SEMICOLON
        { $$ = new ReturnNode(nullptr); }
    | RETURN expression SEMICOLON
        { $$ = new ReturnNode(static_cast<ExprNode*>($2)); }
    ;

println_stmt
    : PRINTLN_MACRO LPAREN args RPAREN SEMICOLON
        {
            $$ = new ExprStmtNode(
                     new CallNode("println!", static_cast<ArgListNode*>($3)));
        }
    ;

expr_stmt
    : expression SEMICOLON
        { $$ = new ExprStmtNode(static_cast<ExprNode*>($1)); }
    ;

expression
    : expression PLUS  expression
        { $$ = new BinaryOpNode("+", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression MINUS expression
        { $$ = new BinaryOpNode("-", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression MUL   expression
        { $$ = new BinaryOpNode("*", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression DIV   expression
        { $$ = new BinaryOpNode("/", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression MOD   expression
        { $$ = new BinaryOpNode("%", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression LT    expression
        { $$ = new BinaryOpNode("<", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression GT    expression
        { $$ = new BinaryOpNode(">", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression LE    expression
        { $$ = new BinaryOpNode("<=", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression GE    expression
        { $$ = new BinaryOpNode(">=", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression EQ    expression
        { $$ = new BinaryOpNode("==", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression NEQ   expression
        { $$ = new BinaryOpNode("!=", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression AND   expression
        { $$ = new BinaryOpNode("&&", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | expression OR    expression
        { $$ = new BinaryOpNode("||", static_cast<ExprNode*>($1), static_cast<ExprNode*>($3)); }
    | NOT   expression
        { $$ = new UnaryOpNode("!", static_cast<ExprNode*>($2)); }
    | MINUS expression %prec UMINUS
        { $$ = new UnaryOpNode("-", static_cast<ExprNode*>($2)); }
    | LPAREN expression RPAREN
        { $$ = $2; }
    | call
        { $$ = $1; }
    | INT_LIT
        { $$ = new LiteralNode("int",    string($1)); free($1); }
    | FLOAT_LIT
        { $$ = new LiteralNode("float",  string($1)); free($1); }
    | STR_LIT
        { $$ = new LiteralNode("string", string($1)); free($1); }
    | CHAR_LIT
        { $$ = new LiteralNode("char",   string($1)); free($1); }
    | BOOL_LIT
        { $$ = new LiteralNode("bool",   string($1)); free($1); }
    | IDENTIFIER
        { $$ = new IdentifierNode(string($1)); free($1); }
    ;

call
    : IDENTIFIER LPAREN args RPAREN
        {
            $$ = new CallNode(string($1), static_cast<ArgListNode*>($3));
            free($1);
        }
    ;

args
    : /* vacio */ { $$ = new ArgListNode(); }
    | arg_list    { $$ = $1;               }
    ;

arg_list
    : expression
        {
            ArgListNode* al = new ArgListNode();
            al->add(static_cast<ExprNode*>($1));
            $$ = al;
        }
    | arg_list COMMA expression
        {
            static_cast<ArgListNode*>($1)->add(static_cast<ExprNode*>($3));
            $$ = $1;
        }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "[ERROR SINTACTICO L%d C%d] %s\n", yylineno, yycol, s);
}
