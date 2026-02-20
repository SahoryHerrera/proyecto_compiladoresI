%{
#include <stdio.h>
#include <stdlib.h>
%}

%option noyywrap

DIGIT      [0-9]
ID         [a-zA-Z_][a-zA-Z0-9_]*

%%

"let"              { printf("TOKEN_LET\n"); }
"fn"               { printf("TOKEN_FN\n"); }
"if"               { printf("TOKEN_IF\n"); }
"else"             { printf("TOKEN_ELSE\n"); }
"while"            { printf("TOKEN_WHILE\n"); }

"+"                { printf("TOKEN_PLUS\n"); }
"-"                { printf("TOKEN_MINUS\n"); }
"*"                { printf("TOKEN_MULT\n"); }
"/"                { printf("TOKEN_DIV\n"); }

"="                { printf("TOKEN_ASSIGN\n"); }
";"                { printf("TOKEN_SEMICOLON\n"); }
"("                { printf("TOKEN_LPAREN\n"); }
")"                { printf("TOKEN_RPAREN\n"); }
"{"                { printf("TOKEN_LBRACE\n"); }
"}"                { printf("TOKEN_RBRACE\n"); }

{DIGIT}+           { printf("TOKEN_NUMBER: %s\n", yytext); }
{ID}               { printf("TOKEN_ID: %s\n", yytext); }

[ \t\n]+           { /* ignorar espacios */ }

.                  { printf("ERROR: caracter desconocido %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}