%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yycol       = 1;
int yycol_start = 1;

#define YY_USER_ACTION \
    yycol_start = yycol; \
    for (int _i = 0; yytext[_i]; _i++) { \
        if (yytext[_i] == '\n') yycol = 1; \
        else yycol++; \
    }

void print_token(const char* type, const char* value) {
    fprintf(stdout, "[L%-3d C%-3d]  %-16s  %s\n",
            yylineno, yycol_start, type, value);
}
%}

%option noyywrap
%option yylineno

DIGIT      [0-9]
ALPHA      [a-zA-Z_]
ALNUM      [a-zA-Z0-9_]
INT_LIT    {DIGIT}+
FLOAT_LIT  {DIGIT}+"."{DIGIT}+
ID         {ALPHA}{ALNUM}*
STR_LIT    \"([^\"\\]|\\.)*\"
CHAR_LIT   \'([^\'\\]|\\.)\'
WS         [ \t\r]+
LINE_CMT   "//"[^\n]*

%%

{LINE_CMT}     ;
"\n"           { yycol = 1; }
{WS}           ;

"fn"           { print_token("KW_FN",     yytext); return FN;     }
"let"          { print_token("KW_LET",    yytext); return LET;    }
"mut"          { print_token("KW_MUT",    yytext); return MUT;    }
"if"           { print_token("KW_IF",     yytext); return IF;     }
"else"         { print_token("KW_ELSE",   yytext); return ELSE;   }
"while"        { print_token("KW_WHILE",  yytext); return WHILE;  }
"for"          { print_token("KW_FOR",    yytext); return FOR;    }
"in"           { print_token("KW_IN",     yytext); return IN;     }
"return"       { print_token("KW_RETURN", yytext); return RETURN; }
"true"         { print_token("LIT_BOOL",  yytext); yylval.str_val = strdup(yytext); return BOOL_LIT; }
"false"        { print_token("LIT_BOOL",  yytext); yylval.str_val = strdup(yytext); return BOOL_LIT; }
"println!"     { print_token("PRINTLN",   yytext); return PRINTLN_MACRO; }
"i32"          { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"i64"          { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"f64"          { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"f32"          { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"bool"         { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"char"         { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"str"          { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
"usize"        { print_token("TYPE", yytext); yylval.str_val = strdup(yytext); return TYPE; }
{FLOAT_LIT}    { print_token("LIT_FLOAT",  yytext); yylval.str_val = strdup(yytext); return FLOAT_LIT; }
{INT_LIT}      { print_token("LIT_INT",    yytext); yylval.str_val = strdup(yytext); return INT_LIT;   }
{STR_LIT}      { print_token("LIT_STRING", yytext); yylval.str_val = strdup(yytext); return STR_LIT;   }
{CHAR_LIT}     { print_token("LIT_CHAR",   yytext); yylval.str_val = strdup(yytext); return CHAR_LIT;  }
{ID}           { print_token("IDENTIFIER", yytext); yylval.str_val = strdup(yytext); return IDENTIFIER; }
"->"           { print_token("ARROW",       yytext); return ARROW;        }
".."           { print_token("DOT_DOT",     yytext); return DOT_DOT;      }
"=="           { print_token("OP_EQ",       yytext); return EQ;           }
"!="           { print_token("OP_NEQ",      yytext); return NEQ;          }
"<="           { print_token("OP_LE",       yytext); return LE;           }
">="           { print_token("OP_GE",       yytext); return GE;           }
"&&"           { print_token("OP_AND",      yytext); return AND;          }
"||"           { print_token("OP_OR",       yytext); return OR;           }
"+="           { print_token("OP_PLUS_EQ",  yytext); return PLUS_ASSIGN;  }
"-="           { print_token("OP_MINUS_EQ", yytext); return MINUS_ASSIGN; }
"*="           { print_token("OP_MUL_EQ",   yytext); return MUL_ASSIGN;   }
"/="           { print_token("OP_DIV_EQ",   yytext); return DIV_ASSIGN;   }
"+"            { print_token("OP_PLUS",   yytext); return PLUS;   }
"-"            { print_token("OP_MINUS",  yytext); return MINUS;  }
"*"            { print_token("OP_MUL",    yytext); return MUL;    }
"/"            { print_token("OP_DIV",    yytext); return DIV;    }
"%"            { print_token("OP_MOD",    yytext); return MOD;    }
"<"            { print_token("OP_LT",     yytext); return LT;     }
">"            { print_token("OP_GT",     yytext); return GT;     }
"="            { print_token("OP_ASSIGN", yytext); return ASSIGN; }
"!"            { print_token("OP_NOT",    yytext); return NOT;    }
"("            { print_token("LPAREN",    yytext); return LPAREN;   }
")"            { print_token("RPAREN",    yytext); return RPAREN;   }
"{"            { print_token("LBRACE",    yytext); return LBRACE;   }
"}"            { print_token("RBRACE",    yytext); return RBRACE;   }
"["            { print_token("LBRACKET",  yytext); return LBRACKET; }
"]"            { print_token("RBRACKET",  yytext); return RBRACKET; }
","            { print_token("COMMA",     yytext); return COMMA;    }
";"            { print_token("SEMICOLON", yytext); return SEMICOLON;}
":"            { print_token("COLON",     yytext); return COLON;    }
.              { fprintf(stderr, "[ERROR LEXICO L%d C%d] Caracter desconocido: '%s'\n", yylineno, yycol_start, yytext); }

%%
