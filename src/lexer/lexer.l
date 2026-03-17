%option noyywrap nounput noinput yylineno

%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

DIGIT       [0-9]
ID_START    [a-zA-Z_]
ID_CHAR     [a-zA-Z0-9_]

%%

"fn"            { return FN; }
"let"           { return LET; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"in"            { return IN; }
"return"        { return RETURN; }

"i32"           { yylval.text = strdup(yytext); return TYPE; }
"f64"           { yylval.text = strdup(yytext); return TYPE; }
"bool"          { yylval.text = strdup(yytext); return TYPE; }
"char"          { yylval.text = strdup(yytext); return TYPE; }
"str"           { yylval.text = strdup(yytext); return TYPE; }

"true"          { yylval.text = strdup(yytext); return BOOL_LITERAL; }
"false"         { yylval.text = strdup(yytext); return BOOL_LITERAL; }

{DIGIT}+"."{DIGIT}+      { yylval.text = strdup(yytext); return FLOAT_LITERAL; }
{DIGIT}+                 { yylval.text = strdup(yytext); return INT_LITERAL; }

\'([^\\\n]|(\\.))\'      { yylval.text = strdup(yytext); return CHAR_LITERAL; }
\"([^\\\n]|(\\.))*\"     { yylval.text = strdup(yytext); return STRING_LITERAL; }

"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
"->"            { return ARROW; }
".."            { return RANGE; }

"<"             { return LT; }
">"             { return GT; }
"!"             { return NOT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"="             { return ASSIGN; }

"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
","             { return COMMA; }
";"             { return SEMICOLON; }
":"             { return COLON; }

{ID_START}{ID_CHAR}*     { yylval.text = strdup(yytext); return IDENTIFIER; }

[ \t\r\n]+      { }
"//".*          { }

.               {
                    fprintf(stderr, "Error lexico en linea %d: simbolo no reconocido '%s'\n", yylineno, yytext);
                }

%%